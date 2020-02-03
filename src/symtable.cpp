#include "symtable.hpp"

#include <utility>

namespace ast {
    bool SymbolTable::is_generated(const std::string& sym) {
        return generated.count(sym) > 0;
    }

    void SymbolTable::gen_symbol(const std::string& sym) {
        if (!is_generated(sym)) {
            generated.insert(sym);
        }
    }

    void SymbolTable::add_symbol(const std::string& sym, const std::string& typ, int kind) {
        if (table.count(sym) == 0) {
            table.insert(std::make_pair(sym, std::make_pair(typ, kind)));
        } else {
            throw DuplicateSymbol(sym);
        }
    }

    void SymbolTable::update_symbol(const std::string& sym, const std::string& typ) {
        if (table.count(sym) > 0) {
            table.at(sym) = {typ, VAR};
        } else {
            throw SymbolNotFound(sym);
        }
    }

    bool SymbolTable::has_symbol(const std::string& sym) {
        return table.count(sym) != 0;
    }

    bool SymbolTable::has_type(const std::string& sym) {
        bool status = false;
        try {
            auto pair = get_symbol(sym);
            if (pair.second == TYPE)
                status = true;
        }
        catch (SymbolNotFound &ex) {}
        return status;
    }

    std::pair<std::string, int> SymbolTable::get_symbol(const std::string& sym) {
        if (table.count(sym) > 0) {
            return table.find(sym)->second;
        } else {
            throw SymbolNotFound(sym);
        }
    }
}
