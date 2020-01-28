#include "ast_node.hpp"

#include <utility>
#include "helper_assign.hpp"
#include "helper_method.hpp"
#include "helper_class.hpp"


namespace ast {

    bool
    is_reserved(const std::string& str) {
        std::string reserved[] = {"this", "___global___", "___builtin___"};
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
 * declares variables before assignment (in target code)
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

        std::string global_str = "___global___";
        auto *global = new SymbolTable(global_str);
        st.push(global);
        try {
            /* adding every type to the global environment */
            for (auto i : _classes->get_elements())
                global->add_symbol(i->get_name(), i->get_name(), TYPE);

            _classes->type_check(st);
            _statements->type_check(st);
        }
        catch (const DuplicateSymbol &ex) {
            report::error(ex.what());
        }

        /* Code Generation */
        st.clear();
        if (report::num_errors == 0) {
            global = new SymbolTable(global_str);
            ctx.emit("#include <stdlib.h>\n");
            ctx.emit("#include \"builtins.h\"\n\n"); /* preamble */
            if (_classes->len() > 5) /* 5 builtin classes */
                ctx.emit("/* ======================= Class Declerations ======================= */\n\n");

            auto the_classes = _classes->get_elements();
            for (Class *cls: the_classes) {
                if (!cls->is_builtin()) {
                    std::string class_name = cls->get_name();
                    ctx.emitClassSig(class_name); /* outputting forward references to our classes */
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
            _statements->type_check(st); /* do this to fill the symbol table */
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
    Formals::type_check(Stack &st) {
        SymbolTable *symtable = st.top();
        for (auto formal: get_elements()) {
            /* Adding each formal to symbol table */
            std::string formal_type = formal->get_type()->get_text();
            if (!st.has_type(formal_type))
                report::error("*** SymbolNotFound " + formal_type);
            else
                symtable->add_symbol(formal->get_var()->get_text(), formal_type, VAR);
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
    Method::type_check(Stack &st) {
        auto mc = MethodChecker(this, st);
        mc.type_check();
    }

    void
    Method::code_gen(CodegenContext &ctx, Stack &st) {
        std::string str = st.top()->get_name();
        auto *symtable = new SymbolTable(str + ":" + _name->get_text());
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
    Assign::type_check(Stack &st) {
        auto ac = AssignChecker(this, st);
        ac.type_check();
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
    AssignDeclare::type_check(Stack &st) {
        auto ac = AssignChecker(this, st);
        ac.type_check();
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

    void
    Return::type_check(Stack &st) {
        try {
            _expr->type_check(st);
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
    If::type_check(Stack &st) {
        /* =====================================================
         * if (<cond>) {
         *   <statements>
         * } else {
         *   <statements>
         * }
         * typechecking rules:
         *  1) cond must be boolean
         *  2) call type_check() on true_part and false_part
         * ===================================================== */

        _cond->type_check(st);
        if (_cond->infer(st) != "Boolean")
            report::error("*** TypeError, if statements condition isn't Boolean");
        std::string str = st.top()->get_name();
        std::string environment = str.substr(0, str.find(':'));
        auto *true_table = new SymbolTable(environment);
        st.push(true_table);
        _true_part->type_check(st);
        (void) st.pop();
        auto *false_table = new SymbolTable(environment);
        st.push(false_table);
        _false_part->type_check(st);
        (void) st.pop();

        /* collecting symbols defined in both true and false branches */
        SymbolTable *ture_false_intersection = st.intersection(true_table, false_table);
        /* merging intersection with the top-most symbol table */
        st.merge(ture_false_intersection);

        delete ture_false_intersection;
        delete true_table;
        delete false_table;
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
        true_label = ctx.gen_TrueLabel();
        false_label = ctx.gen_FalseLabel();
        end_label = ctx.gen_EndLabel();
        _true_part->type_check(st);
        _false_part->type_check(st);
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
    While::type_check(Stack &st) {
        /* =====================================================
         * while (<cond>) {
         *  <statements>
         * }
         * typechecking rule:
         *  1) cond must be boolean
         *  2) call type_check() on statements
         * ===================================================== */

        _cond->type_check(st);
        if (_cond->infer(st) != "Boolean")
            report::error("*** TypeError", "while loops condition isn't Boolean");
        _body->type_check(st);
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
        if_label = ctx.gen_IfLabel();
        loop_label = ctx.gen_LoopLabel();
        break_label = ctx.gen_BreakLabel();
        forward_ref(ctx, st, _body, "loop");
        ctx.emit("goto " + if_label + ";\n");
        ctx.emit("\n" + loop_label + ": /* while loop */ ;\n");
        ctx.indent();
        _body->type_check(st);
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
    Load::infer(Stack &st) {
/* ======================
 * return whatever _loc is
 * ====================== */
        return _loc->infer(st);
    }

    void
    Load::type_check(Stack &st) {
        _loc->type_check(st);
    }

    void
    Load::code_gen(CodegenContext &ctx, Stack &st) {
        _loc->code_gen(ctx, st);
    }

    std::string
    Ident::infer(Stack &st) {
        if (_text == "true" || _text == "false")
            return "Boolean";
        else if (_text == "none")
            return "Nothing";
        else {
            if (_text == "this")
                throw ReservedWord(_text);
            auto t = st.get_symbol(_text); /* SymbolNotFound may be thrown */
            if (t.second != LET &&
                t.second != VAR) { /* error, can't be anything but VAR or LET, e.g TYPE or METHOD are invalid */
                throw TypeError();
            }
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
    Ident::type_check(Stack &st) {
        /* =====================================================
         * typechecking rules:
         *  1) check if symbol is a keyword e.g. "true"
         *  2) check if symbol exists
         * ===================================================== */

        if (_text == "true" || _text == "false" || _text == "none")
            return;
        if (!st.has_symbol(_text))
            throw SymbolNotFound(_text);
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
                std::string var = ast::CodegenContext::gen_variable(_text);
                if (!st.top()->is_generated(_text)) {
                    ctx.emit("obj_" + type + " " + var + ";\n");
                    st.top()->gen_symbol(_text);
                }
                ctx.emit("obj_" + type + " " + tmp + " = " + var + ";\n");
            }
            catch (const SymbolNotFound &ex) { /* it's ok, already typechecked */ }
        }
    }

    void
    Classes::type_check(Stack &st) {
        for (auto el: _elements) {
            if (!el->is_builtin())
                el->type_check(st);
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
        return _attributes->count(attr) ? true : false;
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
    Class::type_check(Stack &st) {
        auto cc = ClassChecker(this, st);
        cc.type_check();
    }

    void
    Class::code_gen(CodegenContext &ctx, Stack &st) {
        auto cg = ClassGenerator(this, st, ctx);
        cg.code_gen();
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
        std::string receiver_type = _receiver->infer(st);
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
        return calling_method;
    }

    std::string
    Call::infer(Stack &st) {
        std::string receiver_type = this->get_receiver()->infer(st);
        Class *receiver_class = st.get_class(receiver_type);
        Method *method = receiver_class->get_method(this->get_method_name());
        if (method)
            return method->get_return();

        throw MethodNotFound(this->get_method_name());
    }

    void
    Call::type_check(Stack &st) {
        /* =====================================================
         * <object>.<method>(<args>)
         * typechecking rules:
         *  1) object is valid
         *  2) object has method
         *  3) args are valid
         * ===================================================== */

        try {
            _receiver->type_check(st);
            std::string receiver_type = _receiver->infer(st);
            Method *calling_method = get_method(st);
            if (calling_method != nullptr)
                MethodChecker::call_check(_actuals, calling_method, st);
            else {
                std::cerr << "type " << receiver_type << " has no method named "
                          << _method->get_text();
                throw TypeError();
            }
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
        std::string receiver_type = _receiver->infer(st);
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
    Construct::infer(Stack &st) {
        std::string method = _method->get_text();
        if (st.has_type(method))
            return method;
        throw TypeNotFound(method);
    }

    void
    Construct::type_check(Stack &st) {
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
    Dot::infer(Stack &st) {
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
        try {
            left_type = get_left()->infer(st);
        }
        catch (const ReservedWord &ex) {
            std::string str = st.top()->get_name();
            std::string environment = str.substr(0, str.find(':'));
            if (environment == "___global___") {
                std::cerr << "accessing private data in global scope\n";
                throw TypeError();
            } else
                left_type = environment;
        }
        Class *left_class = st.get_class(left_type);
        if (left_class) {
            std::string attr = get_right()->get_text();
            if (left_class->has_attr(attr))
                return left_class->get_attrs()->at(attr);
            else {
                std::cerr << "type '" << left_type << "' has no attribute '"
                          << attr << "'\n";
                throw AttributeError(attr);
            }
        }
        assert(false);
    }

    void
    Dot::json(std::ostream &out, PrintContext &ctx) {
        json_head("Dot", out, ctx);
        json_child("left_", _left, out, ctx);
        json_child("right_", _right, out, ctx, ' ');
        json_close(out, ctx);
    }

    void
    Dot::type_check(Stack &st) {
        try {
            /* if we can infer it's type then it's legal */
            (void) this->infer(st);
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
            type = _left->infer(st);
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

