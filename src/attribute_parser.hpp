
/*
 * attribute_parser.hpp
 *
 * declares a helper class to extract attributes
 * from a block of statements, designed to use inside a
 * Class node type_checker.
 *
 * author: Parsa Bagheri
 */

#ifndef _ATTR_PARSER_H_
#define _ATTR_PARSER_H_

#include "all.hpp"
#include "stack.hpp"
#include "ast_node.hpp"

namespace ast {

    class AttributeParser {
        Stack &_st; /* reference to environment stack */
        std::unordered_map<std::string, std::string> &_attrs; /* reference to environment stack */
        std::unordered_set<std::string> const_attr; /* local map, to keep track of static declarations */
        Block *_statements; /* pointer to block of statements whithin a Class constructor */

    public:
        /*
         * constructor
         *
         * takes environment stack (Stack&)
         *       pointer to block of statements _input_file a class constructor (Block*)
         *       attribute name-type map (unordered_map<string, string>&)
         */
        explicit AttributeParser(Stack &st, Block *statements,
                                 std::unordered_map<std::string, std::string> &attrs)
                : _statements(statements), _st(st), _attrs(attrs) {}

        /*
         * the only public method of AttributeParser
         * parses the statements block and fills the attributes map
         * mapping between attributes
         *
         * no args
         * no return
         */
        void
        parse() {
            parse_helper(_statements, _attrs);
        }

    private:
        /*
         * private method,
         * extracts the attribute name and type
         * inserts them into attributes map
         */
        void
        get_attr(Assign *assign, std::unordered_map<std::string, std::string> &map);

        /*
         * private method,
         * takes the intersection of maps m1 and m2,
         * inserts them _input_file map `map'
         */
        void
        map_intersection(std::unordered_map<std::string, std::string> &m1,
                         std::unordered_map<std::string, std::string> &m2,
                         std::unordered_map<std::string, std::string> &map);

        /*
         * helper private method for parse()
         */
        void parse_statement(ASTNode *node, std::unordered_map<std::string, std::string> &map);

        void parse_helper(Block *statements, std::unordered_map<std::string, std::string> &attrs);
    };

} /* namespace ast */

#endif /*_ATTR_PARSER_H_*/