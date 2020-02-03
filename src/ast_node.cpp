#include "ast_node.hpp"

#include <utility>
#include "helper_assign.hpp"
#include "helper_method.hpp"
#include "helper_class.hpp"

#define GLOBAL "___global___"
#define BUILTIN "___builtin___"

namespace ast {

    bool
    is_reserved(const std::string& str) {
        static std::string reserved[] = {GLOBAL, BUILTIN};
        /*
         * there are only so many reserved words
         * so for looping through it is fine
         */
        for (const auto& i : reserved) {
            if (str == i)
                return true;
        }
        return false;
    }

/*
 * static function, code-gen helper
 * declares variables before assignment (_input_file target code)
 */
    static void
    forward_ref(CodegenContext &ctx, Stack &st, Block *statements, const std::string& opt = "") {
        for (auto i : statements->get_elements()) {
            if (i->type() == ASSIGN || i->type() == ASSIGN_DECLARE) {
                auto *assign = dynamic_cast<Assign *>(i);
                assign->get_left()->code_gen(ctx, st);
            } else if (i->type() == IF) {
                If *tmp = dynamic_cast<If *>(i);
                forward_ref(ctx, st, tmp->get_true(), "true");
                forward_ref(ctx, st, tmp->get_false(), "false");
            } else if (i->type() == WHILE) {
                auto *tmp = dynamic_cast<While *>(i);
                forward_ref(ctx, st, tmp->getBody(), "while");
            }
        }
    }

/* Indent to a given level */
    void
    ASTNode::json_indent(std::ostream &out, PrintContext &ctx) {
        if (ctx._indent > 0)
            out << std::endl;
        for (int i = 0; i < ctx._indent; i++)
            out << "    ";
    }

/* The head element looks like { "kind" : "block", */
    void
    ASTNode::json_head(const std::string& node_kind, std::ostream &out, PrintContext &ctx) {
        json_indent(out, ctx);
        out << R"({ "kind" : ")" << node_kind << "\",";
        ctx.indent();     }

    void
    ASTNode::json_close(std::ostream &out, PrintContext &ctx) {
        json_indent(out, ctx);
        out << "}";
        ctx.dedent();
    }

    void
    ASTNode::json_child(const std::string& field, ASTNode *child, std::ostream &out, PrintContext &ctx, char sep) {
        json_indent(out, ctx);
        out << "\"" << field << "\" : ";
        child->json(out, ctx);
        out << sep;
    }

    void
    Program::json(std::ostream &out, PrintContext &ctx) {
        json_head("Program", out, ctx);
        json_child("classes_", _classes, out, ctx);
        json_child("statements_", _statements, out, ctx, ' ');
        json_close(out, ctx);
    }

    void
    Program::code_gen(CodegenContext &ctx) {
        Stack st(_classes);

        /* Type Checking */

        auto *global = new SymbolTable(GLOBAL);
        st.push(global);
        try {
            /* adding every type to the global environment */
            for (auto i : _classes->get_elements())
                global->add_symbol(i->get_name(), i->get_name(), TYPE);

            _classes->semantic_check(st);
            _statements->semantic_check(st);
        }
        catch (const DuplicateSymbol &ex) {
            report::error(ex.what());
        }

        /* Code Generation */
        st.clear();
        if (report::num_errors == 0) {
            global = new SymbolTable(GLOBAL);
            ctx.emit("#include <stdlib.h>\n");
            ctx.emit("#include \"builtins.h\"\n\n"); /* preamble */
            if (_classes->len() > 5) /* 5 builtin classes */
                ctx.emit("/* ======================= Class Declerations ======================= */\n\n");

            auto the_classes = _classes->get_elements();
            for (Class *cls: the_classes) {
                if (!cls->is_builtin()) {
                    std::string class_name = cls->get_name();
                    ctx.emit_class_sig(class_name); /* outputting forward references to our classes */
                    global->add_symbol(class_name, class_name, TYPE);
                }
            }
            st.push(global);
            if (_classes->len() > 5) /* 5 builtin classes */
                ctx.emit("/* ======================= Class Definitions ======================== */\n\n");

            _classes->code_gen(ctx, st);
            ctx.emit(    "/* ============================== Main ============================== */\n\n");
            ctx.emit("int main (int argc, char *argv[]) {\n");
            ctx.indent();
            _statements->semantic_check(st); /* do this to fill the symbol table */
            _statements->code_gen(ctx, st);
            ctx.emit("exit(0);\n");
            ctx.dedent();
            ctx.emit("}\n");
            delete st.pop();
        } else
            delete this;
    }

    void
    Formal::json(std::ostream &out, PrintContext &ctx) {
        json_head("Formal", out, ctx);
        json_child("var_", _var, out, ctx);
        json_child("type_", _type, out, ctx, ' ');
        json_close(out, ctx);
    }

    void
    Formals::semantic_check(Stack &st) {
        /* ===============================================
         * semantics of Formals of a method:
         * checking the type of every formal,
         * if type was found, add the variable to the
         * symbol table,
         * otherwise, type not found.
         * =============================================== */
        SymbolTable *symtable = st.top();
        for (auto formal: get_elements()) {
            /* Adding each formal to symbol table */
            std::string formal_type = formal->get_type()->get_text();
            if (!st.has_type(formal_type))
                throw TypeNotFound(formal_type);
            symtable->add_symbol(formal->get_var()->get_text(), formal_type, NON_STATIC);
        }
    }

    std::string
    Method::get_signature() {
        /* =================================
         * error reporting facility
         * generates the signature of method
         * ================================= */

        std::stringstream ss;
        ss << get_name() << " (";
        bool first = true;
        for (auto i: _formals->get_elements()) {
            /* i is Formal * */
            if (!first)
                ss << ", ";
            ss << i->get_var()->get_text() << ": " << i->get_type()->get_text();
            first = false;
        }
        ss << "): " << get_return();

        return ss.str();
    }

    void
    Method::json(std::ostream &out, PrintContext &ctx) {
        json_head("Method", out, ctx);
        json_child("name_", _name, out, ctx);
        json_child("formals_", _formals, out, ctx);
        json_child("returns_", _returns, out, ctx);
        json_child("statements_", _statements, out, ctx, ' ');
        json_close(out, ctx);
    }

    void
    Method::semantic_check(Stack &st) {
        try {
            auto mc = MethodChecker(this, st);
            mc.type_check();
        } catch (const ast_exception &ex) {
            ERROR(this);
        }
    }

    void
    Method::code_gen(CodegenContext &ctx, Stack &st) {

        std::string str = st.top()->get_name();
        auto symtable = new SymbolTable(str + ":" + _name->get_text());
        st.push(symtable);
        std::string method_name = _owner + "_method_" + _name->get_text();
        std::string return_type = _returns->get_text();
        std::stringstream ss;
        ss << "( obj_" << _owner << " this";
        for (auto it: _formals->get_elements()) {
            ss << ", ";
            ss << "obj_" << it->get_type()->get_text() << " ";
            std::string var = ast::CodegenContext::gen_variable(it->get_var()->get_text());
            ss << var;
            st.top()->gen_symbol(it->get_var()->get_text());
            st.top()->add_symbol(it->get_var()->get_text(), it->get_type()->get_text(), STATIC);
        }
        ss << " )";
        ctx.emit("obj_" + return_type + " " + method_name + ss.str() + " {\n");
        ctx.indent();
        _statements->code_gen(ctx, st);
        if (!_has_return) {
            ctx.emit("return none;\n");
        }
        ctx.dedent();
        ctx.emit("}\n\n");
        delete st.pop();
        ctx.resetReg();
    }

    void
    Assign::json(std::ostream &out, PrintContext &ctx) {
        json_head("Assign", out, ctx);
        json_child("lexpr_", _lexpr, out, ctx);
        json_child("rexpr_", _rexpr, out, ctx, ' ');
        json_close(out, ctx);
    }

    void
    Assign::semantic_check(Stack &st) {
        /* ===============================================
         * <symbol> = <value>;
         * <receiver.attribute> = <value>;
         *
         * semantics of an Assignment:
         * if it is a dot, find it's receiver type and
         * update the corresponding attribute
         * if it is an ident, update symbol table
         *
         * if the types don't match, take least common ancestor
         * of the two types.
         * =============================================== */
        try {
            std::string rhs_type = _rexpr->type_check(st);
            auto dot = dynamic_cast<Dot *>(_lexpr);
            if (dot) {
                auto receiver = dot->get_left()->type_check(st);
                auto clss = st.get_class(receiver);
                clss->update_attribute(dot->get_right()->get_text(), rhs_type, NON_STATIC, st);
            } else {
                auto ident = dynamic_cast<Ident *>(_lexpr);
                assert(ident != nullptr);
                st.update_symbol(ident->get_text(), rhs_type, NON_STATIC);
            }
        } catch (const ast_exception &ex) {
            ERROR(this);
        }
    }

    void
    Assign::code_gen(CodegenContext &ctx, Stack &st) {
        /* generating code for left side */

        auto ag = AssignGenerator(this, ctx, st);
        ag.code_gen();
    }

    void
    AssignDeclare::json(std::ostream &out, PrintContext &ctx) {
        json_head("Assign", out, ctx);
        json_child("lexpr_", _lexpr, out, ctx);
        json_child("rexpr_", _rexpr, out, ctx);
        json_child("static_type_", _static_type, out, ctx, ' ');
        json_close(out, ctx);
    }

    void
    AssignDeclare::semantic_check(Stack &st) {
        /* ===============================================
         * <symbol>: <type> = <value>;
         * <receiver.attribute>: <type> = <value>;
         *
         * semantics of assignment with type declaration:
         * these have to be new assignments,
         * reassignments leads to symbol redefinition error
         * =============================================== */
        try {
            std::string rhs_type = _rexpr->type_check(st);
            auto dot = dynamic_cast<Dot *>(_lexpr);
            if (dot) {
                auto receiver = dot->get_left()->type_check(st);
                auto clss = st.get_class(receiver);
                clss->update_attribute(dot->get_right()->get_text(), rhs_type, STATIC, st);
            } else {
                auto ident = dynamic_cast<Ident *>(_lexpr);
                assert(ident != nullptr);
                st.update_symbol(ident->get_text(), rhs_type, STATIC);
            }
        } catch (const ast_exception &ex) {
            ERROR(this);
        }
    }

    void
    AssignDeclare::code_gen(CodegenContext &ctx, Stack &st) {
        /* generating code for left side */

        auto ag = AssignGenerator(this, ctx, st);
        ag.code_gen();
    }

    void
    Return::json(std::ostream &out, PrintContext &ctx) {
        json_head("Return", out, ctx);
        json_child("expr_", _expr, out, ctx, ' ');
        json_close(out, ctx);
    }

    void
    Return::code_gen(CodegenContext &ctx, Stack &st) {
        _expr->code_gen(ctx, st);
        std::string str = st.top()->get_name();
        std::string the_class = str.substr(0, str.find(':'));
        std::string the_method = str.substr(str.find(':') + 1, str.length());
        Class *c = st.get_class(the_class);
        Method *m = c->get_method(the_method);
        std::string type = m->get_return();
        ctx.emit("return (obj_" + type + ")" + ctx.get_last_temp() + ";\n");
    }

    static bool
    type_match (const std::string &t1, const std::string &t2, Stack &st) {
        /* ===============================================
         * helper function to determine if t1 matches t2:
         *
         * they match if t1 == t2
         * if t1 > t2:
         *    meaning if t2 is a subclass of t1
         * =============================================== */
        if (t1 == t2)
            return true;
        auto clss = st.get_class(t2); /* might throw error */
        auto super = clss->get_super();
        while (!super.empty()) {
            clss = st.get_class(super);
            super = clss->get_super();
            if (super == t1)
                return true;
        }
        return false;
    }

    void
    Return::semantic_check(Stack &st) {
        /* ===============================================
         * return <expression>;
         *
         * semantics of return:
         * this statement has to be within a method
         * the type of expression has to match the
         * return type of method
         * =============================================== */
        try {
            auto environ = st.top()->get_name();
            auto type = environ.substr(0, environ.find(':'));
            auto method = environ.substr(environ.find(':') + 1, environ.length());

            if (type == GLOBAL) {
                throw TypeError("return found in the global scope");
            } if (method.empty()) {
                throw TypeError("return not being used inside a method");
            }

            auto clss = st.get_class(type);
            for (auto m : clss->get_methods()->get_elements()) {
                if (m->get_name() == method) {
                    if (!type_match(m->get_return(),_expr->type_check(st), st)) {
                        throw TypeError("mismatch between method return type and its return statement");
                    }
                    break;
                }
            }
        }
        catch (const ast_exception &ex) {
            ERROR(this);
        }
    }

    void
    If::json(std::ostream &out, PrintContext &ctx) {
        json_head("If", out, ctx);
        json_child("cond_", _cond, out, ctx);
        json_child("truepart_", _true_part, out, ctx);
        json_child("falsepart_", _false_part, out, ctx, ' ');
        json_close(out, ctx);
    }


    void
    If::semantic_check(Stack &st) {
        /* =====================================================
         * if (<cond>) {
         *   <statements>
         * } else {
         *   <statements>
         * }
         * semantics of if:
         * the condition has to be boolean
         * if a symbol or class attribute is defined on both
         * true and false paths, then it's added to the current
         * symbol table.
         * ===================================================== */

        try {
            if (_cond->type_check(st) != "Boolean")
                throw TypeError("if statements condition isn't Boolean");
            auto true_table = new SymbolTable(st.top()->get_name());
            st.push(true_table);
            _true_part->semantic_check(st);
            (void) st.pop();
            auto false_table = new SymbolTable(st.top()->get_name());
            st.push(false_table);
            _false_part->semantic_check(st);
            (void) st.pop();

            /* collecting symbols defined _input_file both true and false branches */
            SymbolTable *ture_false_intersection = st.intersection(true_table, false_table);
            /* merging intersection with the top-most symbol table */
            st.merge(ture_false_intersection);

            delete ture_false_intersection;
            delete true_table;
            delete false_table;
        } catch (const ast_exception &ex) {
            ERROR(this);
        }
    }

    void
    If::code_gen(CodegenContext &ctx, Stack &st) {
        /* =====================================================
         * if (<cond>) goto true___xxx;
         * else goto false___xxx;
         * true___xxx:  ;
         *  <statements>
         *  goto end___xxx;
         * false___xxx:
         *  <statements>
         *  goto end___xxx;
         * end___xxx:  ;
         * ===================================================== */

        std::string true_label, false_label, end_label;
        true_label = ctx.gen_true();
        false_label = ctx.gen_false();
        end_label = ctx.gen_end();
        _true_part->semantic_check(st);
        _false_part->semantic_check(st);
        forward_ref(ctx, st, _true_part, "true");
        forward_ref(ctx, st, _false_part, "false");
        _cond->code_gen(ctx, st);
        ctx.emit("if ( " + ctx.get_last_temp() + "->value ) goto " + true_label + ";\n");
        ctx.emit("else goto " + false_label + ";\n");
        ctx.emit("\n" + true_label + ": /* if */ ;\n");
        ctx.indent();
        _true_part->code_gen(ctx, st);
        ctx.emit("goto " + end_label + ";\n");
        ctx.dedent();
        ctx.emit("\n" + false_label + ": /* else */ ;\n");
        ctx.indent();
        _false_part->code_gen(ctx, st);
        ctx.emit("goto " + end_label + ";\n");
        ctx.dedent();
        ctx.emit("\n" + end_label + ": /* fi */ ;\n");
    }

    void
    While::json(std::ostream &out, PrintContext &ctx) {
        json_head("While", out, ctx);
        json_child("cond_", _cond, out, ctx);
        json_child("body_", _body, out, ctx, ' ');
        json_close(out, ctx);
    }

    void
    While::semantic_check(Stack &st) {
        /* =====================================================
         * while (<cond>) {
         *  <statements>
         * }
         * semantics of While loop:
         *  1) cond must be boolean
         *  2) check semantics of statements
         * ===================================================== */

        try {
            if (_cond->type_check(st) != "Boolean")
                throw TypeError("while loops condition isn't Boolean");

            st.push(new SymbolTable(st.top()->get_name()));
            _body->semantic_check(st);
            delete st.pop();
        } catch (const ast_exception &ex) {
            ERROR(this);
        }
    }

    void
    While::code_gen(CodegenContext &ctx, Stack &st) {
        /* =====================================================
         * goto if___x;
         * loop___x:  ;
         *  <body>
         * if___x:  ;
         *  if (<cond>) goto loop___x;
         *  else goto break___x;
         * break___x:  ;
         * ===================================================== */

        std::string if_label, loop_label, break_label;
        if_label = ctx.gen_if();
        loop_label = ctx.gen_loop();
        break_label = ctx.gen_break();
        forward_ref(ctx, st, _body, "loop");
        ctx.emit("goto " + if_label + ";\n");
        ctx.emit("\n" + loop_label + ": /* while loop */ ;\n");
        ctx.indent();
        _body->semantic_check(st);
        _body->code_gen(ctx, st);
        ctx.dedent();
        ctx.emit("\n" + if_label + ": /* condition test */ ;\n");
        ctx.indent();
        _cond->code_gen(ctx, st);
        ctx.emit("if ( " + ctx.get_last_temp() + "->value ) goto " + loop_label + ";\n");
        ctx.emit("else goto " + break_label + ";\n");
        ctx.dedent();
        ctx.emit("\n" + break_label + ": /* end of loop */ ;\n");
    }

    void
    Typecase::json(std::ostream &out, PrintContext &ctx) {
        json_head("Typecase", out, ctx);
        json_child("expr_", _expr, out, ctx);
        json_child("cases_", _cases, out, ctx, ' ');
        json_close(out, ctx);
    }

    void
    Type_Alternative::json(std::ostream &out, PrintContext &ctx) {
        json_head("Type_Alternative", out, ctx);
        json_child("ident_", _ident, out, ctx);
        json_child("classname_", _classname, out, ctx);
        json_child("block_", _block, out, ctx, ' ');
        json_close(out, ctx);
    }

    void
    Load::json(std::ostream &out, PrintContext &ctx) {
        json_head("Load", out, ctx);
        json_child("loc_", _loc, out, ctx, ' ');
        json_close(out, ctx);
    }

    std::string
    Load::type_check(Stack &st) {
        /* ======================
         * return whatever _loc is
         * ====================== */
        return _loc->type_check(st);
    }

    void
    Load::semantic_check(Stack &st) {
        _loc->semantic_check(st);
    }

    void
    Load::code_gen(CodegenContext &ctx, Stack &st) {
        _loc->code_gen(ctx, st);
    }

    std::string
    Ident::type_check(Stack &st) {
        if (_text == "true" || _text == "false") {
            return "Boolean";
        } else if (_text == "none") {
            return "Nothing";
        } else if (_text == "this") {
            auto environ = st.top()->get_name();
            if (environ == GLOBAL)
                throw TypeError("usage of `this' outside of a class");
            auto type = environ.substr(0, environ.find(':'));
            return type;
        } else {
            auto t = st.get_symbol(_text); /* SymbolNotFound may be thrown */
            return t.first;
        }
    }

    void
    Ident::json(std::ostream &out, PrintContext &ctx) {
        json_head("Ident", out, ctx);
        out << R"("text_" : ")" << _text << "\"";
        json_close(out, ctx);
    }

    void
    Ident::semantic_check(Stack &st) {
        /* =====================================================
         * typechecking rules:
         *  1) check if symbol is a keyword e.g. "true"
         *  2) check if symbol exists
         * ===================================================== */
        try {
            (void) type_check(st);
        } catch (const ast_exception &ex) {
            ERROR(this);
        }
    }

    void
    Ident::code_gen(CodegenContext &ctx, Stack &st) {
        /* =====================================================
         * if it's not previously generated, or a builtin
         *  obj_<type> _var___<var_name>;
         * ===================================================== */
        std::string tmp = ctx.gen_temp();
        if (_text == "this") {
            std::string str = st.top()->get_name();
            std::string environment = str.substr(0, str.find(':'));
            ctx.emit("obj_" + environment + " " + tmp + " = (obj_"
                     + environment + ")this;\n");
        } else if (_text == "true" || _text == "false") {
            std::string lit = _text == "true" ? "lit_true" : "lit_false";
            ctx.emit("obj_Boolean " + tmp + " = " + lit + ";\n");
        } else if (_text == "none")
            ctx.emit("obj_Nothing " + tmp + " = none;\n");
        else {
            try {
                std::string type = st.get_symbol(_text).first;
                ctx.declare_variable(type, _text, st);
                std::string var = ast::CodegenContext::gen_variable(_text);
                ctx.emit("obj_" + type + " " + tmp + " = " + var + ";\n");
            }
            catch (const SymbolNotFound &ex) { /* it's ok, already typechecked */ }
        }
    }

    void
    Classes::semantic_check(Stack &st) {
        for (auto el: _elements) {
            if (!el->is_builtin())
                el->semantic_check(st);
        }
    }

    void
    Classes::code_gen(CodegenContext &ctx, Stack &st) {
        for (auto el: _elements) {
            if (!el->is_builtin())
                el->code_gen(ctx, st);
        }
    }

    void
    Class::add_attr(const std::string& name, const std::string& type) {
        if (_attributes->count(name) == 0)
            _attributes->insert({name, type});
        else
            throw DuplicateSymbol(name);
    }

    bool
    Class::has_attr(const std::string& attr) {
        return _attributes->count(attr) != 0;
    }

    bool
    Class::has_ancestor(const std::string& ancestor, Stack &st) {
        std::string obj_str = "Obj";
        /* every class has Obj as ancestor */
        if (ancestor == obj_str)
            return true;
        /* going up the class hierarchy */
        std::string super_str = get_super();
        while (super_str != obj_str) {
            if (ancestor == super_str)
                return true;

            Class *super = st.get_class(super_str);
            super_str = super->get_super();
        }
        return false;
    }

    void
    Class::json(std::ostream &out, PrintContext &ctx) {
        json_head("Class", out, ctx);
        json_child("name_", _name, out, ctx);
        json_child("super_", _super, out, ctx);
        json_child("constructor_", _constructor, out, ctx);
        json_child("methods_", _methods, out, ctx, ' ');
        json_close(out, ctx);
    }

    void
    Class::semantic_check(Stack &st) {
        try {
            auto cc = ClassChecker(this, st);
            cc.type_check();
        } catch (const ast_exception &ex) {
            ERROR(this);
        }
    }

    void
    Class::code_gen(CodegenContext &ctx, Stack &st) {
        auto cg = ClassGenerator(this, st, ctx);
        cg.code_gen();
    }

    void Class::update_attribute(const std::string &attr,
                                 const std::string &type,
                                 kinds kind,
                                 Stack &st) {
        /*
         * private method accessible to Assign classes
         * for updating the attributes of a class
         */
        if (_attrs->count(attr) == 0) {
            _attrs->insert({attr, {type, kind}});
        } else {
            if (_attrs->at(attr).second == STATIC) {
                throw TypeError("redefining symbol with static type");
            }
            if (kind == STATIC) {
                throw TypeError("statically declaring an already defined symbol");
            }
            std::string &old_type = _attrs->at(attr).first;
            std::string new_type = st.lca(old_type, type);
            _attrs->at(attr) = {new_type, NON_STATIC};
        }
    }

    void
    Call::json(std::ostream &out, PrintContext &ctx) {
        json_head("Call", out, ctx);
        json_child("obj_", _receiver, out, ctx);
        json_child("method_", _method, out, ctx);
        json_child("actuals_", _actuals, out, ctx, ' ');
        json_close(out, ctx);
    }

    Method *
    Call::get_method(Stack &st) {
        std::string receiver_type = _receiver->type_check(st);
        Class *receiver_class = st.get_class(receiver_type);
        Method *calling_method = nullptr;
        Class *cur = receiver_class;
        while (cur != nullptr) {
            for (auto i: cur->get_methods()->get_elements()) {
                /* i is Method * */
                if (i->get_name() == _method->get_text()) {
                    calling_method = i;
                    break;
                }
            }
            if (calling_method != nullptr)
                break;

            cur = st.get_class(cur->get_super());
        }
        if (calling_method)
            return calling_method;
        throw MethodNotFound(_method->get_text());
    }

    std::string
    Call::type_check(Stack &st) {
        auto receiver_type = get_receiver()->type_check(st);
        auto receiver_class = st.get_class(receiver_type);
        auto method = receiver_class->get_method(get_method_name());
        if (method)
            return method->get_return();

        throw MethodNotFound(get_method_name());
    }

    void
    Call::semantic_check(Stack &st) {
        /* =====================================================
         * <object>.<method>(<args>)
         * typechecking rules:
         *  1) object is valid
         *  2) object has method
         *  3) args are valid
         * ===================================================== */

        try {
            _receiver->semantic_check(st);
            std::string receiver_type = _receiver->type_check(st);
            Method *calling_method = get_method(st);
            MethodChecker::call_check(_actuals, calling_method, st);
        }
        catch (const ast_exception &ex) {
            ERROR(this);
        }
    }

    void
    Call::code_gen(CodegenContext &ctx, Stack &st) {
        /* =====================================================
         * obj_<arg1_type> _tmp___x = <arg1>
         * obj_<arg2_type> _tmp___x = <arg2>
         *  ...
         * obj_<method_return_type> _tmp___x =
         *    _var___<var_name>->clazz-><method>->(arg1, arg2 ...);
         * ===================================================== */
        std::string receiver_type = _receiver->type_check(st);
        Class *receiver_class = st.get_class(receiver_type);
        Method *calling_method = nullptr;
        Class *cur = receiver_class;
        while (cur != nullptr) {
            for (auto i: cur->get_methods()->get_elements()) { /* i is Method * */
                if (i->get_name() == _method->get_text()) {
                    calling_method = i;
                    break;
                }
            }
            if (calling_method != nullptr)
                break;

            cur = st.get_class(cur->get_super());
        }
        if (calling_method != nullptr) {
            std::string tmp = ctx.gen_temp();
            std::stringstream ss;
            ss << "obj_" << calling_method->get_return()
               << " " << tmp
               << " = (obj_" << calling_method->get_return()
               << ")";
            std::string caller_tmp = ctx.gen_temp();
            _receiver->code_gen(ctx, st);
            ctx.emit("obj_" + receiver_type + " " + caller_tmp + " = " + ctx.get_last_temp() + ";\n");
            ss << caller_tmp << "->clazz->" << _method->get_text() << "((obj_" << calling_method->get_owner()
               << ")" << caller_tmp;

            auto actuals_vector = _actuals->get_elements();
            auto formals_vector = calling_method->get_formals()->get_elements();
            for (int i = 0; i < actuals_vector.size(); i++) {
                ss << ", ";
                ss << "(obj_" << formals_vector[i]->get_type()->get_text() << ")";
                actuals_vector[i]->code_gen(ctx, st);
                ss << ctx.get_last_temp();
            }
            ss << ");\n";
            ctx.emit(ss.str());
            ctx.emit("obj_" + calling_method->get_return()
                     + " " + ctx.gen_temp() + " = " + tmp + ";\n");
        }
    }

/* Convenience factory for operations like +, -, *, / */
    Call *
    Call::binop(std::string opname, Expr *receiver, Expr *arg, int line_no) {
        auto *method = new Ident(std::move(opname), line_no);
        auto *actuals = new Actuals(line_no);
        actuals->append(arg);
        return new Call(receiver, method, actuals, line_no);
    }

    void
    Construct::json(std::ostream &out, PrintContext &ctx) {
        json_head("Construct", out, ctx);
        json_child("method_", _method, out, ctx);
        json_child("actuals_", _actuals, out, ctx, ' ');
        json_close(out, ctx);
    }

    std::string
    Construct::type_check(Stack &st) {
        std::string method = _method->get_text();
        if (st.has_type(method))
            return method;
        throw TypeNotFound(method);
    }

    void
    Construct::semantic_check(Stack &st) {
        try {
            std::string type = _method->get_text();
            Method *constructor = st.get_class(type)->get_constructor();
            MethodChecker::call_check(_actuals, constructor, st);
        }
        catch (ast_exception &ex) {
            ERROR(this);
        }
    }

    void
    Construct::code_gen(CodegenContext &ctx, Stack &st) {
        std::string constructor = "new_" + _method->get_text();
        Class *c = st.get_class(_method->get_text());
        Method *construct = c->get_constructor();
        std::vector<std::string> arg_types;
        for (auto it: construct->get_formals()->get_elements()) {
            arg_types.push_back(it->get_type()->get_text());
        }
        std::stringstream args;
        args << "(";
        bool first = true;
        int i = 0;
        for (auto it: _actuals->get_elements()) {
            if (!first) args << ", ";
            first = false;
            it->code_gen(ctx, st);
            std::string last_temp = ctx.get_last_temp();
            args << "(obj_" << arg_types[i] << ")" << last_temp;
            i++;
        }
        args << ")";
        std::string temp = ctx.gen_temp();
        ctx.emit("obj_" + c->get_name() + " " + temp + " = " + constructor + args.str() + ";\n");
    }

    void
    IntConst::json(std::ostream &out, PrintContext &ctx) {
        json_head("IntConst", out, ctx);
        out << "\"value_\" : " << _value;
        json_close(out, ctx);
    }

    void
    IntConst::code_gen(CodegenContext &ctx, Stack &st) {
        std::stringstream ss;
        ss << "int_literal( " << _value << " );\n";
        std::string tmp = ctx.gen_temp();
        ctx.emit("obj_Int " + tmp + " = " + ss.str());
    }

    void
    StrConst::json(std::ostream &out, PrintContext &ctx) {
        json_head("StrConst", out, ctx);
        out << R"("value_" : ")" << _value << "\"";
        json_close(out, ctx);
    }

    void
    StrConst::code_gen(CodegenContext &ctx, Stack &st) {
        std::string tmp = ctx.gen_temp();
        std::string out;
        for (auto c : _value) {
            switch (c) {
                case '\n':
                    out += "\\n";
                    break;
                case '\t':
                    out += "\\t";
                    break;
                default:
                    out += c;
            }
        }
        ctx.emit("obj_String " + tmp + " = str_literal( \"" + out + "\" );\n");
    }

    void
    BinOp::json(std::ostream &out, PrintContext &ctx) {
        json_head(opsym, out, ctx);
        json_child("left_", _left, out, ctx);
        json_child("right_", _right, out, ctx, ' ');
        json_close(out, ctx);
    }

    void
    Not::json(std::ostream &out, PrintContext &ctx) {
        json_head("Not", out, ctx);
        json_child("left_", _left, out, ctx, ' ');
        json_close(out, ctx);
    }

    std::string
    Dot::type_check(Stack &st) {
        /* ===============================================
         * if left side is "this":
         *  then the type has to be the current scope;
         *  and if this type has the right side as
         *  an attribute, then we return the type of the attribute
         * otherwise:
         *  we infer the type of left side and check to see if
         *  it has the right side as an attribute and return
         *  its type, otherwise attribute error.
         *
         *  if infered type is not the same as the scope, its
         *  an attribute error
         * =============================================== */

        std::string left_type;
        left_type = _left->type_check(st);
        auto left_class = st.get_class(left_type);
        auto attr = _right->get_text();
        if (left_class->has_attr(attr))
            return left_class->get_attrs()->at(attr);
        else
            throw AttributeError(attr);
    }

    void
    Dot::json(std::ostream &out, PrintContext &ctx) {
        json_head("Dot", out, ctx);
        json_child("left_", _left, out, ctx);
        json_child("right_", _right, out, ctx, ' ');
        json_close(out, ctx);
    }

    void
    Dot::semantic_check(Stack &st) {
        /* ===============================================
         * semantics of a Dot:
         * left side is an object of type T,
         * right side is an attribute of type T
         * =============================================== */
        try {
            /* if we can infer it's type then it's legal */
            (void) this->type_check(st);
        }
        catch (const ast_exception &ex) {
            ERROR(this);
        }
    }

    void
    Dot::code_gen(CodegenContext &ctx, Stack &st) {
        _left->code_gen(ctx, st);
        std::string left_tmp = ctx.get_last_temp();
        std::string type;
        try {
            type = _left->type_check(st);
        }
        catch (const ReservedWord &ex) {
            std::string str = st.top()->get_name();
            type = str.substr(0, str.find(':'));
        }
        Class *left_class = st.get_class(type);
        if (left_class) {
            std::string attr_type = left_class->get_attrs()->at(_right->get_text());
            std::string dot_tmp = ctx.gen_temp();
            ctx.emit("obj_" + attr_type + " " + dot_tmp + " = (obj_" + attr_type + ")("
                     + left_tmp + "->" + _right->get_text() + ");\n");
        }
    }

} /* namespace ast */


