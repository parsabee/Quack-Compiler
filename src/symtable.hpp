#ifndef _SYMTABLE_H_
#define _SYMTABLE_H_

#include <utility>


#include <utility>


#include "all.hpp"
#include "errors.hpp"

namespace ast {
    /* different kinds of symbol */
    enum kinds {
        STATIC, /*constants*/
        NON_STATIC, /*variables*/
        TYPE
    };

    class SymbolTable {
        friend class Stack;

        std::unordered_map<std::string, std::pair<std::string, int>> table; /* map between symbol to type and kind */
        std::unordered_set<std::string> generated;
        std::string _name;
    public:
        explicit SymbolTable(std::string name) : _name{std::move(std::move(name))} {}

        std::unordered_map<std::string, std::pair<std::string, int>> &
        getTable() {
            return table;
        }

        bool is_generated(const std::string& sym);

        void gen_symbol(const std::string& sym);

        void add_symbol(const std::string& sym, const std::string& typ, int kind);

        void update_symbol(const std::string& sym, const std::string& typ);

        bool has_symbol(const std::string& sym);

        bool has_type(const std::string& type);

        std::string get_name() {
            return _name;
        }

        std::pair<std::string, int> get_symbol(const std::string& sym);
    };
}

#endif /*_SYMTABLE_H_*/
