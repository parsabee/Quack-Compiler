#include "stack.hpp"

#include <utility>

namespace ast {
    Stack::Stack(Classes *classes) : _classes{classes}, _size{0} {
        /* adding builtin types */
        auto *builtins = new SymbolTable("___builtins___");

        _classes->append(Obj_class());
        builtins->add_symbol("Obj", "Obj", TYPE);

        _classes->append(String_class());
        builtins->add_symbol("String", "String", TYPE);

        _classes->append(Integer_class());
        builtins->add_symbol("Int", "Int", TYPE);

        _classes->append(Nothing_class());
        builtins->add_symbol("Nothing", "Nothing", TYPE);

        _classes->append(Boolean_class());
        builtins->add_symbol("Boolean", "Boolean", TYPE);

        _stack.push_back(builtins);
    }

    Stack::~Stack() {
        clear();
        delete _stack.back();
    }

    void Stack::push(SymbolTable *st) {
        if (st->get_name() != "___builtins___") {
            _stack.push_back(st);
            _size++;
        } else {
            std::cerr << "___builtins___ is a reserved word\n";
            assert(false);
        }
    }

    SymbolTable *Stack::pop() {
        SymbolTable *p = nullptr;
        if (_size) {
            p = _stack.back();
            _stack.pop_back();
            _size--;
        } else {
            std::cerr << "Stack is empty\n";
            assert(false);
        }
        return p;
    }

    SymbolTable *Stack::top() {
        SymbolTable *p = nullptr;
        if (_size) {
            p = _stack.back();
        } else {
            std::cerr << "Stack is empty\n";
            assert(false);
        }
        return p;
    }

    void Stack::clear() {
        while (_size)
            delete pop();
    }

    std::pair<std::string, int> Stack::get_symbol(const std::string& sym) {
        for (auto it = _stack.rbegin(); it != _stack.rend(); it++) {
            if ((*it)->has_symbol(sym))
                return (*it)->get_symbol(sym);
        }
        throw SymbolNotFound(sym);
    }

    bool Stack::has_type(const std::string& sym) {
        for (auto i : _stack) {
            if (i->has_type(sym))
                return true;
        }
        return false;
    }

    bool Stack::has_symbol(const std::string& sym) {
        for (auto i : _stack) {
            if (i->has_symbol(sym))
                return true;
        }
        return false;
    }

    Class *Stack::get_class(const std::string& name) {
        for (auto i : _classes->get_elements()) {
            if (i->get_name() == name)
                return i;
        }
        return nullptr;
    }

    std::string Stack::lca(std::string c1, std::string c2) {
        Class *C1 = get_class(std::move(c1));
        Class *C2 = get_class(std::move(c2));
        std::vector<std::string> c1_ancestors;
        std::string super = C1->get_super();
        while (super != "Obj") {
            c1_ancestors.push_back(super);
            super = get_class(super)->get_super();
        }
        std::vector<std::string> c2_ancestors;
        super = C2->get_super();
        while (super != "Obj") {
            c2_ancestors.push_back(super);
            super = get_class(super)->get_super();
        }
        for (auto i : c1_ancestors) {
            for (const auto& j : c2_ancestors) {
                if (i == j)
                    return i;
            }
        }
        return "Obj";
    }

    SymbolTable *Stack::intersection(SymbolTable *a, SymbolTable *b) {
        auto *tmp = new SymbolTable("intersection");
        for (const auto& i : a->table) {
            for (const auto& j : b->table) {
                if (i.first == j.first) {
                    std::string type = i.second.first;
                    if (i.second.first != j.second.first)
                        type = lca(i.second.first, j.second.first);
                    tmp->add_symbol(i.first, type, VAR);
                }
            }
        }
        return tmp;
    }

    void Stack::merge(SymbolTable *a) {
        if (!_size) {
            std::cerr << "merge called on empty stack\n";
            assert(false);
        }
        for (const auto& i : a->table) {
            top()->add_symbol(i.first, i.second.first, i.second.second);
        }
    }
}