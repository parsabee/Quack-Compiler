/*
 * helper_class.hpp
 * 
 * declares class ClassChecker,
 * a facility to check the semantics of
 * a Class.
 *
 * author: Parsa Bagheri
 */

#ifndef CLASS_CHECKER_HPP
#define CLASS_CHECKER_HPP

#include <utility>

#include "all.hpp"
#include "ast_node.hpp"
#include "contexts.hpp"

namespace ast {


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
    class ClassChecker {
        Class *_class; /* pointer to the class we are checking */
        Stack &_st; /* reference to environment stack */

    public:
        /*
         * constructor
         *
         * takes a pointer to class to be worked on (Class *)
         *       a reference to the environment stack
         */
        ClassChecker(Class *the_class, Stack &st) :
                _class(the_class), _st(st) {}

        /*
         * the only public method
         * type checks the entire class and methods
         * and updates the stack
         * will call sub routines internally
         *
         * no args
         * no return
         */
        void type_check();

    private:
        void check_inheritance();

        void check_attrs_initialized();

        void check_methods();
    };

/*
 * helper class for generating code for classes in quack
 */
    class ClassGenerator {
        /*
         * stores method information for generating dispatch tables
         */
        struct DispatchMethod {
            std::string _name;
            std::vector<std::string> _args;
            std::string _returns;
            std::string _comment;
            std::string _owner;

            DispatchMethod(std::string name, std::vector<std::string> args,
                           std::string returns, std::string comment, std::string owner)
                    : _name{std::move(name)}, _args{std::move(args)}, _owner{std::move(owner)},
                      _returns{std::move(returns)}, _comment{std::move(comment)} {}
        };

        Class *_class;
        Stack &_st;
        CodegenContext &_ctx;
    public:
        /*
         * constructor, takes pointer to the class to be generated
         * reference to the environment stack, and
         * reference to code generation contex object
         */
        ClassGenerator(Class *the_class, Stack &st, CodegenContext &ctx)
                : _class(the_class), _st(st), _ctx(ctx) {}

        void code_gen();

    private:
        void gen_helper(Class *cur, std::vector<DispatchMethod> &vec);

    };

}

#endif /* CLASS_CHECKER_HPP */
