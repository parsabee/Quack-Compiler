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

        const char *_input_file, *_output_file;
        FILE *_file;
        std::ofstream _out;
    public:
        explicit Driver(const char *input_file, const char *output_file = nullptr);
        void compile();
        void json();
        static bool assert_file_type(const char *file, const char *ext);
        ~Driver() {
            if (_file) fclose(_file);
        }
    };


}