#include "environment.hpp"

namespace ast {
    bool Environment::is_generated(const std::string& sym) {
        return generated.count(sym) > 0;
    }

    void Environment::gen_symbol(const std::string& sym) {
        if (!is_generated(sym)) {
            generated.insert(sym);
        }
    }

    void Environment::add_symbol(const std::string& sym, const std::string& typ, int kind) {
        if (table.count(sym) == 0) {
            table.insert({sym, {typ, kind}});
        } else {
            throw DuplicateSymbol(sym, nullptr);
        }
    }

    void Environment::update_symbol(const std::string& sym, const std::string& typ) {
        if (table.count(sym) > 0) {
            table.at(sym) = {typ, NON_STATIC};
        } else {
            table.insert({sym, {typ, NON_STATIC}});
        }
    }

    bool Environment::has_symbol(const std::string& sym) {
        return table.count(sym) != 0;
    }

    std::pair<std::string, int> Environment::get_symbol(const std::string& sym) {
        if (table.count(sym) > 0) {
            return table.find(sym)->second;
        } else {
            throw SymbolNotFound(sym, nullptr);
        }
    }

    void Environment::clear() {
        this->table.clear();
        this->generated.clear();
    }
}
