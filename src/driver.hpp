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

/* from bison */
extern ast::ASTNode *root;
extern FILE *yyin;

extern int yyparse();

namespace ast {

    class Driver {
        class TypeChecker {
            Stack& _st;
            Program *_pgm;

        public:
            TypeChecker(Program *pgm, Stack& st)
                    : _pgm(pgm), _st(st) {}

            void type_check();
        };

        class CodeGenerator {
            Stack& _st;
            Program *_pgm;
            std::ostream &_out;

        public:
            CodeGenerator(Program *pgm, std::ostream &out, Stack& st)
                    : _pgm(pgm), _out(out), _st(st) {}

            void code_gen();
        };

        char *_filename;
        FILE *_file;
        std::ostream &_out;
    public:
        Driver(std::ostream &out, char *file);
        void compile();
        ~Driver() {
            if (_file) fclose(_file);
        }
    };


}