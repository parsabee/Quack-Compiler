/*
 * driver.hpp
 * a driver to the abstract syntax tree 
 * for type checking and code generation
 *
 * Author: Parsa Bagheri
 */

#include "all.hpp"
#include "ast_node.hpp"
#include "stack.hpp"
#include "msg.hpp"
#include <fstream>

/* from bison */
extern ast::ASTNode *root;
extern FILE *yyin;

extern int yyparse();

namespace ast {

    class Driver {
        const char *_input_file, *_output_file;
        FILE *_file;
        std::ofstream _out;
    public:
        explicit Driver(const char *input_file, const char *output_file = nullptr);
        int compile(); /* returns exit status (1: error, 0: success) */
        int json();
        bool compare_file_type(const char *file, const char *ext);
        ~Driver() {
            if (_file) fclose(_file);
        }
    };
}