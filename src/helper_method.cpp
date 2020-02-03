#include "helper_method.hpp"

namespace ast {

    MethodChecker::MethodChecker(Method *method, Stack &st) : _method(method), _st(st) {
        _name = _method->get_name();
    }

    void
    MethodChecker::type_check() {
        try {
            if (is_reserved(_name))
                throw ReservedWord(_name);

            std::string str = _st.top()->get_name();
            std::string environment = str + ":" + _name;
            auto *symtable = new SymbolTable(environment);
            _st.push(symtable);

            /*set owner*/
            _method->_owner = str;

            /* checking return */
            std::string formal_return = _method->get_return();
            _method->_has_return = false;
            for (auto it : _method->_statements->get_elements()) {
                if (it->type() == RETURN) {
                    _method->_has_return = true;
                    std::string actual_return = it->type_check(_st);
                    if (actual_return != formal_return) {
                        Class *ar_class = _st.get_class(actual_return);
                        if (!ar_class->has_ancestor(formal_return, _st)) {
                            std::cerr << "method " << _name << " is declared to return "
                                      << formal_return << " but it returns " << actual_return << "\n";
                            throw TypeError();
                        }
                    }
                }
            }
            if (!_method->_has_return) {
                /* if no return was found we need to make sure method returned Nothing */
                if (formal_return != "Nothing") {
                    std::cerr << "method " << _name << " is declared to return "
                              << formal_return << " but it returns Nothing\n";
                    throw TypeError();
                }
            }

            /* typechecking formals, and body */
            _method->_formals->semantic_check(_st);
            _method->_statements->semantic_check(_st);

            delete _st.pop();
        }
        catch (const ast_exception &ex) {
            ERROR(_method);
        }
    }

    void
    MethodChecker::call_check(Actuals *act, Method *mthd, Stack &st) {
        auto actuals_vector = act->get_elements();
        auto formals_vector = mthd->get_formals()->get_elements();

        if (actuals_vector.size() != formals_vector.size()) {
            std::cerr << "method '" << mthd->get_name() << "' expected "
                      << formals_vector.size() << " arguments but got "
                      << actuals_vector.size();
            throw TypeError();
        }

        for (int i = 0; i < actuals_vector.size(); i++) {
            actuals_vector[i]->semantic_check(st);
            std::string actuals_type = actuals_vector[i]->type_check(st);
            std::string formals_type = formals_vector[i]->get_type()->get_text();
            if (actuals_type != formals_type) {
                Class *actuals_class = st.get_class(actuals_type);
                if (!actuals_class->has_ancestor(formals_type, st)) {
                    NUMBER(std::cerr, i + 1);
                    std::cerr << " argument of method " << mthd->get_name() << " expected type "
                              << formals_type << " but got " << actuals_type;
                    throw TypeError();
                }
            }
        }
    }

}