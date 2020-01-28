/*
 * attribute_parser.cpp
 *
 * defines class in attribute_parser.hpp.
 *
 * author: Parsa Bagheri
 */

#include "attribute_parser.hpp"

namespace ast {

    void
    AttributeParser::get_attr(Assign *assign, std::unordered_map<std::string, std::string> &map) {
        if (assign->get_left()->type() == DOT) {
            Dot *dot = dynamic_cast<Dot *>(assign->get_left());
            Load *load = dynamic_cast<Load *>(dot->get_left()); /* could be something else */
            if (load) {
                auto *ident = dynamic_cast<Ident *>(load->get_loc()); /* could be something else */
                if (ident) {
                    if (ident->get_text() == "this") {
                        std::string type = assign->get_right()->infer(_st);
                        std::string attr = dot->get_right()->get_text();
                        if (assign->type() == ASSIGN_DECLARE) {
                            auto *declare = dynamic_cast<AssignDeclare *>(assign);
                            std::string static_type = declare->get_static_type()->get_text();
                            map.insert({attr, static_type});
                            const_attr.insert(attr); /* attribute initialized with static type
                                                * can't be reassigned with any other type */
                        } else {
                            if (map.count(attr) == 0)
                                map.insert({attr, type});
                            else {
                                try {
                                    std::string old_type = map.at(attr);
                                    if (old_type != type && const_attr.count(attr) == 0) {
                                        std::string new_type = _st.lca(old_type, type);
                                        map.at(attr) = new_type;
                                    } else if (const_attr.count(attr) > 0) {
                                        std::cerr << "invalid Assignment to attrribute " << attr
                                                  << " with static type " << old_type << "\n";
                                        throw TypeError();
                                    }
                                }
                                catch (const ast_exception &ex) {
                                    std::stringstream msg;
                                    msg << "line " << assign->get_line() << ":    " << assign->get_signature();
                                    report::error(ex.what(), msg.str());
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    void
    AttributeParser::map_intersection(std::unordered_map<std::string, std::string> &m1,
                                      std::unordered_map<std::string, std::string> &m2,
                                      std::unordered_map<std::string, std::string> &map) {
        for (const auto& it : m1) {
            if (m2.count(it.first) != 0) {
                std::string common = _st.lca(it.second, m2.at(it.first));
                if (map.count(it.first) != 0) {
                    common = _st.lca(common, map.at(it.first));
                    map.at(it.first) = common;
                } else
                    map.insert({it.first, common});
            }
        }
        for (const auto& it : m2) {
            if (m1.count(it.first) != 0) {
                std::string common = _st.lca(it.second, m1.at(it.first));
                if (map.count(it.first) != 0) {
                    common = _st.lca(common, map.at(it.first));
                    map.at(it.first) = common;
                } else
                    map.insert({it.first, common});
            }
        }
    }

    void
    AttributeParser::parse_statement(ASTNode *node, std::unordered_map<std::string, std::string> &map) {
        if (node->type() == ASSIGN || node->type() == ASSIGN_DECLARE) {
            auto *assign = dynamic_cast<Assign *>(node);
            get_attr(assign, map);
        } else if (node->type() == IF) {
            If *if_ = dynamic_cast<If *>(node);
            std::unordered_map<std::string, std::string> m1;
            parse_helper(if_->get_true(), m1);
            std::unordered_map<std::string, std::string> m2;
            parse_helper(if_->get_false(), m2);
            map_intersection(m1, m2, map);
        }
    }

    void
    AttributeParser::parse_helper(Block *statements, std::unordered_map<std::string, std::string> &attrs) {
        std::string str = _st.top()->get_name();
        std::string environment = str.substr(0, str.find(':'));
        auto *tmp_symtable = new SymbolTable(environment); /* push a symbol table to environment stack */
        _st.push(tmp_symtable);
        for (auto it : statements->get_elements()) {
            parse_statement(it, _attrs);
            it->type_check(_st);
        }
        delete _st.pop(); /* done with this environment */
    }

}