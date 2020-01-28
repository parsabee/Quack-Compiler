/*
 * helper_assign.hpp
 * A helper module for typechecking and codegenerating assignments
 *
 * Author: Parsa Bagheri
 */

#ifndef HELPER_ASSIGN_HPP
#define HELPER_ASSIGN_HPP

#include "all.hpp"
#include "ast_node.hpp"

namespace ast {

/*
 * an assignment can be to an attribute or to a variable
 * if it is to a variable:
 *   we look in the environment to see if variable is present.
 *   if it is, then it's a reassignment:
 *     Quack is statically typed; if the reassignment is of
 *     a different type that is not compatible, then we update
 *     the symbols type to be the least common ancestor of
 *     left hand side and right hand side.
 *     for example:
 *        x = 10;
 *        x = "ten"
 *     above is valid, the least common ancestor of x is Obj
 *     so x will get the type Obj.
 *   otherwise if its a new assignment:
 *     we assign the "variable" type of right hand side's type to symbol
 * otherwise it's to an attribute:
 *   left side of the dot becomes the receiver object and right is attr
 *   we look to make sure the receiver object has the attribute.
 *   also in Quack, every attribute is private,
 *   so we need to check the scope and make sure that the scope
 *   is the same as the receiver objects type.
 */

    class Assignment {
    protected:
        Assign *_assign;
        Stack &_st;
        Assignment(Assign *assign, Stack &st)
            : _assign(assign), _st(st) {}
    };

    class AssignChecker : public Assignment{
    public:
        /*
         * constructor, takes a pointer to assingment,
         * and reference to environment stack
         */
        AssignChecker(Assign *assign, Stack &st) : Assignment(assign, st) {}

        void type_check();

    private:
        void assign_decl_check();

        void assign_check();

        void check_scope();
    };

    class AssignGenerator : public Assignment {
        CodegenContext &_ctx;
    public:
        AssignGenerator(Assign *assign, CodegenContext& ctx, Stack& st)
            : Assignment(assign, st), _ctx(ctx) {}
        void code_gen();
    private:
        void gen_ident();
    };


}

#endif /* HELPER_ASSIGN_HPP */