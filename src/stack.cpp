#include "stack.hpp"

#include <utility>

namespace ast {
    Stack::Stack() {
        /* adding builtin types */
        _types = {
            {"Obj", Obj_class()},
            {"String", String_class()},
            {"Int", Integer_class()},
            {"Nothing", Nothing_class()},
            {"Boolean", Boolean_class()}
        };
        _size = 0;
    }

    Stack::~Stack() {
        clear();
    }

    void Stack::push(Environment *st) {
        _stack.push_back(st);
        _size++;
    }

    Environment *Stack::pop() {
        Environment *p = nullptr;
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

    Environment *Stack::top() {
        Environment *p = nullptr;
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
        throw SymbolNotFound(sym, nullptr);
    }

    bool Stack::has_type(const std::string& sym) {
        return _types.count(sym) > 0;
    }

    void Stack::add_type(const std::string& type, Class *cls) {
        if (_types.count(type) > 0 ) {
            throw TypeRedefinition(type, nullptr);
        }
        _types.insert({type, cls});
    }

    Class *Stack::get_class(const std::string& name) {
        if (_types.count(name) > 0)
            return _types[name];
        throw TypeNotFound(name, nullptr);
    }

    std::string Stack::lca(const std::string& c1, const std::string& c2) {
        if (c1 == c2)
            return std::string(c1);
        Class *C1 = get_class(c1);
        Class *C2 = get_class(c2);
        std::vector<std::string> c1_ancestors;
        std::string super = C1->get_super();
        while (!super.empty()) {
            c1_ancestors.push_back(super);
            super = get_class(super)->get_super();
        }
        std::vector<std::string> c2_ancestors;
        super = C2->get_super();
        while (!super.empty()) {
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

    Environment *Stack::intersection(Environment *a, Environment *b) {
        auto *tmp = new Environment("intersection");
        for (const auto& i : a->table) {
            for (const auto& j : b->table) {
                if (i.first == j.first) {
                    std::string type = i.second.first;
                    if (i.second.first != j.second.first)
                        type = lca(i.second.first, j.second.first);
                    tmp->add_symbol(i.first, type, NON_STATIC);
                }
            }
        }
        return tmp;
    }

    void Stack::merge(Environment *a) {
        if (!_size) {
            std::cerr << "merge called on empty stack\n";
            assert(false);
        }
        for (const auto& i : a->table) {
            top()->add_symbol(i.first, i.second.first, i.second.second);
        }
    }

    void Stack::update_symbol(const std::string &sym, const std::string &type, int is_static) {
        if (is_reserved(sym))
            throw ReservedWord(sym, nullptr);

        std::string new_type;
        if (top()->has_symbol(sym)) {
            auto p = top()->get_symbol(sym);
            if (p.second == STATIC && !type_match(p.first, type, *this)) {
                throw TypeError("redefining symbol with static type", nullptr);
            }
            auto old_type = p.first;
            new_type = lca(old_type, type);
            top()->update_symbol(sym, new_type);
        } else {
            new_type = type;
            top()->add_symbol(sym, type, is_static);
        }
    }

    void Stack::assert_has_type(const std::string &sym) {
        if (_types.count(sym) == 0)
            throw TypeNotFound(sym, nullptr);
    }
}