/*
 * helper_class.cpp
 * definition of ClassChecker
 *
 * author: Parsa Bagheri
 */

#include "helper_class.hpp"
#include "attribute_parser.hpp"
#include "symtable.hpp"

namespace ast {

/*
 * procedure to check if a class has valid inheritance
 * throw exceptions if errors occured
 */
    void
    ClassChecker::check_inheritance() {
        std::string super_type = _class->get_super();
        if (!_st.has_type(super_type)) {
            std::cerr << "type " << super_type << " doesn't exist\n";
            throw BadInherit();
        } else { /* Detecting circular inheritance */
            std::string cur_super = super_type;
            std::string this_class = _class->get_name();
            while (cur_super != "Obj") {
                if (this_class == cur_super) {
                    std::cerr << "circular inheritance detected for type "
                              << this_class << "\n";
                    throw BadInherit();
                }
                Class *cur = _st.get_class(cur_super);
                if (cur != nullptr)
                    cur_super = cur->get_super();
                else
                    break;
            }
        }
    }

/* 
 * private method
 * making sure every parent attribute is also initialized
 * throw exceptions if error occurs
 */
    void
    ClassChecker::check_attrs_initialized() {
        Class *parent = _st.get_class(_class->get_super());
        for (auto & it : *parent->get_attrs()) {
            if (!_class->has_attr(it.first)) {
                std::cerr << "inherited attribute '" << it.first
                          << "' is not initialized _input_file class "
                          << _class->get_name() << "\n";
                throw AttributeError(it.first);
            } else if (_class->get_attrs()->at(it.first) != it.second) {
                Class *tmp = _st.get_class(_class->get_attrs()->at(it.first));
                if (!tmp->has_ancestor(it.second, _st)) {
                    std::cerr << "inherited attribute '" << it.first << "'s type "
                              << tmp->get_name() << " doesn't match it's parent type "
                              << it.second << " _input_file class " << _class->get_name() << "\n";
                    throw AttributeError(it.first);
                }
            }
        }
    }

/* 
 * overloading is not allowed
 * checking for overloading
 * throw exception _input_file case of error
 */
    void
    ClassChecker::check_methods() {
        Class *parent = _st.get_class(_class->get_super());
        while (parent != nullptr) {
            for (auto i : _class->get_methods()->get_elements()) {
                Method *m = parent->get_method(i->get_name());
                if (m != nullptr) {
                    i->setOverride(true);
                    /* checking return type of method */
                    if (i->get_return() != m->get_return()) {
                        if (!_st.get_class(i->get_return())->has_ancestor(m->get_return(), _st)) {
                            std::cerr << "method '" << _class->get_name() << "::" << i->get_name()
                                      << " is overriden but its return type doesn't match its ancestor's\n";
                            std::cerr << "overriden: => " + i->get_signature() << "\n";
                            std::cerr << " original: => " + m->get_signature() << "\n";
                            throw TypeError();
                        }
                    }
                    i->get_formals()->type_check(_st);
                    /* checking number of arguments */
                    if (i->get_formals()->len() != m->get_formals()->len()) {
                        std::cerr << "method '" << _class->get_name() << "::" << i->get_name()
                                  << " is overriden but its number of arguments doesn't match its ancestor's\n";
                        std::cerr << "overriden: => " + i->get_signature() << "\n";
                        std::cerr << " original: => " + m->get_signature() << "\n";
                        throw TypeError();
                    }
                        /* checking type of each argument */
                    else {
                        auto overriden_formals = i->get_formals()->get_elements(); /* vector */
                        auto original_formals = m->get_formals()->get_elements(); /* vector */
                        for (int j = 0; j != overriden_formals.size(); j++) {
                            if (overriden_formals[j]->get_type()->get_text() !=
                                original_formals[j]->get_type()->get_text()) {
                                Class *c = _st.get_class(overriden_formals[j]->get_type()->get_text());
                                if (c != nullptr &&
                                    !c->has_ancestor(original_formals[j]->get_type()->get_text(), _st)) {
                                    std::cerr << "method " << _class->get_name() << "::" << i->get_name()
                                              << " is overriden but its ";
                                    NUMBER(std::cerr, j);
                                    std::cerr << " argument doesn't match its ancestor's\n";
                                    std::cerr << "overriden: => " + i->get_signature() << "\n";
                                    std::cerr << " original: => " + m->get_signature() << "\n";
                                    throw TypeError();
                                }
                            }
                        }
                    }
                }
            }
            parent = _st.get_class(parent->get_super());
        }
    }


/*
 * class <name> {
 *  <statements>
 *  <methods>
 * }
 * typechecking rules:
 *  1) check if inheritance is valid
 *  2) <statements> are part of the constructor, 
 *     typecheck that first
 *  3) typecheck <methods>
 */
    void
    ClassChecker::type_check() {
        /* don't typecheck builtins */
        if (_class->is_builtin())
            return;
        try {
            /* new environment added to stack */
            auto *symtable = new SymbolTable(_class->get_name());
            symtable->add_symbol(_class->get_name(), _class->get_name(), TYPE);
            _st.push(symtable);

            check_inheritance();
            _class->get_constructor()->get_formals()->type_check(_st);

            /* parsing every statment
             * typechecking and finding attributes */
            Block *stmnts = _class->get_constructor()->get_statements();
            AttributeParser ap(_st, stmnts, *(_class->get_attributes()));
            ap.parse();

            check_attrs_initialized();
            check_methods();
            _class->get_methods()->type_check(_st);

            delete _st.pop(); /* done with the current environment */
        }
        catch (const ast_exception &ex) {
            ERROR(_class);
        }
    }

    void
    ClassGenerator::code_gen() {
        /* don't codegen builtins */
        if (_class->_builtin)
            return;

        auto symtable = new SymbolTable(_class->get_name());
        _st.push(symtable);
        Formals *tmp_formals = _class->_constructor->get_formals();
        bool first = true;

        /* generating class/object struct === */

        _ctx.emit_obj_struct(_class->_name->get_text(), _class->_attributes);
        _ctx.emit("struct class_" + _class->get_name() + "_struct {\n");
        _ctx.indent();
        _ctx.emit("class_" + _class->get_super() + " _super;\n\n");
        _ctx.emit("/* method table */\n");
        std::string str;
        str += "obj_" + _class->get_name() + " (*constructor)(";
        for (auto formal: tmp_formals->get_elements()) {
            if (!first) str += ", ";
            first = false;
            symtable->add_symbol(formal->get_var()->get_text(), formal->get_type()->get_text(), LET);
            str += "obj_" + formal->get_type()->get_text() + " " + formal->get_var()->get_text();
            _st.top()->gen_symbol(formal->get_var()->get_text());
        }
        if (first) str += "void";
        str += ");\n";
        _ctx.emit(str);
        std::vector<DispatchMethod> vec; /* methods, _input_file order of appearance */
        gen_helper(_class, vec);

        /* ================================================================
         * TODO: this got a little hairy, I should rethink this
         *
         * Because quack is object oriented, we use dynamic dispatch.
         * methods need to be topologically sorted
         * with 'Obj's (every class inherits it) methods appearing first _input_file the table
         * following datastructures is for ensuring our dynamic dispatch calls
         * the correct function
         * ================================================================ */

        std::unordered_map<std::string, DispatchMethod &> helper;
        std::unordered_set<std::string> gen; /* generated methods */
        for (auto it = vec.rbegin(); it != vec.rend(); it++) {
            if (helper.count(it->_name) == 0)
                helper.insert({it->_name, *it});
            else
                helper.at(it->_name) = *it;
        }
        for (auto it = vec.rbegin(); it != vec.rend(); it++) {
            if (gen.count(it->_name) == 0) {
                DispatchMethod &dm = helper.at(it->_name);
                std::stringstream ss;
                ss << "obj_" << dm._returns << " (*" << dm._name << ")(obj_" << dm._owner;
                for (const auto& i : dm._args)
                    ss << ", obj_" << i;
                ss << ") " << dm._comment << ";\n";
                _ctx.emit(ss.str());
                gen.insert(it->_name);
            }
        }
        gen.clear();
        _ctx.dedent();
        _ctx.emit("};\n\n");

        /* generating constructor */

        _ctx.emit("extern class_" + _class->get_name() + " the_class_" + _class->get_name() + ";\n\n");
        std::string comment = _class->get_name() + " constructor";
        std::string stars = ast::CodegenContext::gen_stars(comment);
        _ctx.emit("/*" + stars + "\n * " + comment + "\n " + stars + "*/\n");

        /* formals */
        _ctx.emit("obj_" + _class->get_name() + " new_" + _class->get_name() + "( ");
        first = true;
        for (auto formal: tmp_formals->get_elements()) {
            /* adding each formal to symbol table */
            if (!first) _ctx.emit(", ");
            first = false;
            _ctx.emit("obj_" + formal->get_type()->get_text() + " " + ast::CodegenContext::gen_variable(formal->get_var()->get_text()));
        }
        _ctx.emit(" ) {\n");

        /* body */
        _ctx.indent();
        _ctx.emit("obj_" + _class->get_name() + " this = (obj_" + _class->get_name()
                  + ")malloc(sizeof(struct obj_" + _class->get_name() + "_struct));\n");
        _ctx.emit("this->clazz = the_class_" + _class->get_name() + ";\n");
        Block *stmnts = _class->_constructor->get_statements();
        for (auto stmnt: stmnts->get_elements())
            stmnt->code_gen(_ctx, _st);

        _ctx.emit("return this;\n");
        _ctx.dedent();
        _ctx.emit("}\n\n");
        _ctx.resetReg(); /* reset the register number to start from 0 */

        /* methods */
        _class->_methods->code_gen(_ctx, _st);

        /* class singleton */
        _ctx.emit("/* The " + _class->get_name() + " Class (a singleton) */\n");
        _ctx.emit("struct class_" + _class->get_name() + "_struct the_class_" + _class->get_name() + "_struct = {\n");
        _ctx.indent();
        _ctx.emit("&the_class_" + _class->get_super() + "_struct,\n");
        str = "new_" + _class->get_name();
        for (auto it = vec.rbegin(); it != vec.rend(); it++) {
            if (gen.count(it->_name) == 0) {
                DispatchMethod &dm = helper.at(it->_name);
                str += ",\n";
                _ctx.emit(str);
                str = dm._owner + "_method_" + dm._name;
                gen.insert(it->_name);
            }
        }
        _ctx.emit(str + "\n");
        _ctx.dedent();
        _ctx.emit("};\n\n");
        _ctx.emit("class_" + _class->get_name() + " the_class_" + _class->get_name()
                  + " = &the_class_" + _class->get_name() + "_struct;\n\n");
        delete _st.pop();
    }


/*  
 * helper method to recursively topologically sort methods of a class
 * storing them _input_file argument 'vec'
 */
    void
    ClassGenerator::gen_helper(Class *cur, std::vector<DispatchMethod> &vec) {
        assert (cur != nullptr);
        if (!cur->get_super().empty())
            gen_helper(_st.get_class(cur->get_super()), vec);

        for (auto i : cur->get_methods()->get_elements()) {
            std::stringstream ss;
            Method *tmp = (_class->get_method(i->get_name()) != nullptr)
                          ? _class->get_method(i->get_name()) : i;

            std::string returns = tmp->get_return();

            std::string name = tmp->get_name();
            std::vector<std::string> args;
            std::string comment;

            for (auto j : tmp->get_formals()->get_elements())
                args.push_back(j->get_type()->get_text());

            if (_class->get_method(i->get_name()) != nullptr) {
                if (_class->get_method(i->get_name())->isOverriden())
                    comment = "/* override */";
            } else
                comment = "/* inherit */";

            DispatchMethod dm(name, args, returns, comment, cur->get_name());
            vec.insert(vec.begin(), dm);
        }
    }


}