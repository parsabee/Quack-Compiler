#include "helper_assign.hpp"
#include "errors.hpp"

namespace ast {


    void
    AssignChecker::type_check() {
        if (_assign->type() == ASSIGN) {
            assign_check();
        } else if (_assign->type() == ASSIGN_DECLARE) {
            assign_decl_check();
        } else {
            throw ast_exception();
        }
    }

    void
    AssignChecker::assign_check() {
        /* semantics checking */
        try {
            std::string rhs_inferred = _assign->get_right()->type_check(_st);
            check_scope();
            Class *rhs_type = _st.get_class(rhs_inferred);
            auto *ident = dynamic_cast<Ident *>(_assign->_lexpr);
            if (ident != nullptr) {
                /* see if left has a type , then it's a reassignment
                 * else it's a new assignment */
                try {

                    /* reassignment */
                    std::string left_type = _assign->_lexpr->type_check(_st);
                    if (rhs_inferred != left_type && !rhs_type->has_ancestor(left_type, _st)) {
                        std::string sym = ident->get_text();
                        if (_st.get_symbol(sym).second == VAR) {

                            /* reassignment of a variable with different type
                             * we take least common ancestor */
                            std::string lca = _st.lca(left_type, rhs_inferred);
                            _st.top()->update_symbol(sym, lca);
                        } else {
                            throw TypeError("variable " + sym + " with static type "
                                                        + left_type + " can't be reassigned to type " + rhs_inferred);
                        }
                        /* if it's a Dot (attribute assignment)
                         * the AttributeParser will take care of it */
                    }
                    /* otherwise it's a legal assignment */
                } catch (SymbolNotFound &ex) {

                    /* new assignment */
                    if (is_reserved(ident->get_text()))
                        throw ReservedWord(ident->get_text());

                    _st.top()->add_symbol(ident->get_text(), rhs_inferred, VAR);
                }
            } else if (_assign->_lexpr->type() != DOT) {
                assert(false);
            }
        }
            /* reporting possible errors */
        catch (const ast_exception &ex) {
            ERROR(_assign);
        }
    }

    void
    AssignChecker::assign_decl_check() {

        /* semantic check of AssignDeclare */
        auto *decl = dynamic_cast<AssignDeclare *>(_assign);
        assert(decl != nullptr);
        try {
            check_scope();

            std::string inferred_type = decl->get_right()->type_check(_st); /* Inferring type of right expr */
            Class *inferred_class = _st.get_class(inferred_type);

            auto *_lexpr_ident = dynamic_cast<Ident *>(decl->_lexpr);
            if (_lexpr_ident != nullptr) {

                std::string var_name = _lexpr_ident->get_text();

                if (_st.has_symbol(var_name)) /* can't be a reassignment */ {
                    throw DuplicateSymbol("static assignment of an already defined symbol " + var_name);
                } else {

                    if (inferred_type != decl->_static_type->get_text() &&
                        !inferred_class->has_ancestor(decl->_static_type->get_text(), _st)) {
                        throw TypeError("right expression of type " + inferred_type
                                                                    + " cannot be assigned to static type "
                                                                    + decl->_static_type->get_text());
                    } else
                        _st.top()->add_symbol(var_name, decl->_static_type->get_text(), LET);
                }
            } else if (decl->_lexpr->type() != DOT) {
                assert(false);
            }
        }
        catch (ast_exception &ex) {
            ERROR(decl);
        }
    }

    void AssignChecker::check_scope() {

        /* an assignment _input_file the global scope can't have Dot left expression */
        if (_assign->_lexpr->type() == DOT) {
            std::string str = _st.top()->get_name();
            std::string environment = str.substr(0, str.find(':'));
            if (environment == "___global___") {
                throw TypeError("accessing private data from global scope");
            }
        }
    }


    void AssignGenerator::code_gen() {

        std::string var_type = _assign->get_left()->type_check(_st);
        _assign->get_right()->code_gen(_ctx, _st);
        std::string right_tmp = _ctx.get_last_temp();

        auto ident = dynamic_cast<Ident *>(_assign->get_left());
        if (ident) {
            gen_ident();
            std::string str = ast::CodegenContext::gen_variable(ident->get_text());
            str += " = (obj_" + var_type + ")" + right_tmp + ";\n";
            _ctx.emit(str);
        } else {
            auto dot = dynamic_cast<Dot *>(_assign->get_left());
            assert(dot);
            dot->get_left()->code_gen(_ctx, _st);
            std::string str = _ctx.get_last_temp() + "->" + dot->get_right()->get_text()
            + " = (obj_" + var_type + ")" + right_tmp + ";\n";
            _ctx.emit(str);
        }
    }

    void AssignGenerator::gen_ident() {
        auto left = dynamic_cast<Ident *>(_assign->get_left());
        assert (left != nullptr);
        try {
            _ctx.declare_variable(left->type_check(_st), left->get_text(), _st);
        } catch (SymbolNotFound &ex) {
            assert(false); /* after type checking, we can't have symbol not found*/
        }
    }
}