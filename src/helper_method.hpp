#ifndef METHOD_CHECKER_HPP
#define METHOD_CHECKER_HPP

#include "all.hpp"
#include "stack.hpp"
#include "ast_node.hpp"
#include "errors.hpp"

namespace ast {

/* forward reference */
    class Method;

    class Actuals;

    class Stack;

/*
 * helper class for type checking methods and method calls
 */
    class MethodChecker {

        /*
         * TODO : check if MAGIC METHODS are being used properly, i.e. right number of arguments return type etc.
         * */
        Method *_method;
        Stack &_st;
        std::string _name;

    public:
        /*
         * constructor
         * takes a pointer to method to be checked
         * and reference to the environment stack
         */
        MethodChecker(Method *method, Stack &st);

        /* type checking method decleration */
        void type_check();

        /* static method, type checking a method call
         *
         * takes pointer to actuals in the call,
         * pointer to the called method,
         * and reference to the environment stack
         */
        static void call_check(Actuals *act, Method *mthd, Stack &st);
    };


}

#endif /* METHOD_CHECKER_HPP */