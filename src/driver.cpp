#include "driver.hpp"
#include "environment.hpp"
#include "errors.hpp"


namespace ast {

    Driver::Driver(const char *input_file, const char *output_file)
        : _input_file(input_file), _output_file(output_file) {

        /* Processing input */
        if (!compare_file_type(input_file, ".qk")) /* making sure extension is .qk */
            throw io::BadFile("the input input_file extension is not `.qk'");

        if ((_file = fopen(_input_file, "r")) != nullptr)
            yyin = _file;
        else
            throw io::BadFile("no such input_file");

        /* Processing output */
        if (output_file != nullptr) {
            std::string tmp = output_file;
            if (!compare_file_type(output_file, ".c"))
                tmp += ".c";
            _out.open(tmp, std::ofstream::out);
        } else {
            _out.open("a.out.c", std::ofstream::out);
        }
    }

    int
    Driver::compile() {
        int status = 1;
        int result = yyparse();
        if (report::num_errors == 0 && result == 0) {

            auto *pgm = dynamic_cast<Program *>(root);
            assert(pgm != nullptr);
            Stack st;
            pgm->semantic_check(st);
            if (report::num_errors == 0) {
                st.clear();
                auto ctx = CodegenContext(_out);
                pgm->code_gen(ctx, st);
                status = 0;
            } else {
                report::summary();
            }
        } else {
            report::summary(); 
        }
        if (result == 0) { /* result is 0 if AST was generated */
            delete root;  /* done with the AST delete it */
        }
        return status;
    }

    int
    Driver::json() {
        int status = 1;
        int result = yyparse();
        if (report::num_errors == 0 && result == 0) {

            auto *pgm = dynamic_cast<Program *>(root);
            assert(pgm != nullptr);
            PrintContext ctx;
            pgm->json(std::cout, ctx);
            status = 0;
        } else {
            report::summary();
        }
        if (result == 0) { /* result is 0 if AST was generated */
            delete root;  /* done with the AST delete it */
        }
        return status;
    }

    bool Driver::compare_file_type(const char *file, const char *ext) {
        int file_len = strlen(file);
        int ext_len = strlen(ext);
        return strcmp(file + file_len - ext_len, ext) == 0;
    }
}