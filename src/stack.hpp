#ifndef _STACK_H_
#define _STACK_H_

#include "all.hpp"
#include "environment.hpp"
#include "ast_node.hpp"
#include "errors.hpp"
#include "qk_builtins.hpp"

namespace ast {
    class Class; /* forward reference */

    class Stack {
        std::unordered_map<std::string, Class *> _types;
        std::vector<Environment *> _stack; /* the program stack */
        int _size;
    public:
        Stack();
        ~Stack();

        /* typical stack methods */
        void push(Environment *st);

        Environment *pop();

        Environment *top();

        void clear();

        void assert_has_type(const std::string& sym);

        /* searching the entire stack for sym */
        bool has_type(const std::string& sym);

        void add_type(const std::string& type, Class *cls);

        void update_symbol(const std::string &sym, const std::string &type, int is_static);

        std::pair<std::string, int> get_symbol(const std::string& sym);

        Class *get_class(const std::string& name);

        /* lowest-common-ancestor of two classes */
        std::string lca(const std::string& c1, const std::string& c2);

        Environment *intersection(Environment *a, Environment *b);

        void merge(Environment *a);
    };
}

#endif /*_STACK_H_*/