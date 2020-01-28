#ifndef _STACK_H_
#define _STACK_H_

#include "all.hpp"
#include "symtable.hpp"
#include "ast_node.hpp"
#include "errors.hpp"
#include "qk_builtins.hpp"

namespace ast {
    class Classes; /* forward reference */
    class Class; /* forward reference */

    class Stack {
        Classes *_classes; /* list of classes */
        std::vector<SymbolTable *> _stack; /* the program stack */
        int _size;
    public:
        explicit Stack(Classes *classes);

        ~Stack();

        /* typical stack methods */
        void push(SymbolTable *st);

        SymbolTable *pop();

        SymbolTable *top();

        void clear();

        /* searching the entire stack for sym */
        bool has_type(const std::string& sym);

        bool has_symbol(const std::string& sym);

        std::pair<std::string, int> get_symbol(const std::string& sym);

        Class *get_class(const std::string& name);

        /* lowest-common-ancestor of two classes */
        std::string lca(std::string c1, std::string c2);

        SymbolTable *intersection(SymbolTable *a, SymbolTable *b);

        void merge(SymbolTable *a);
    };
}

#endif /*_STACK_H_*/