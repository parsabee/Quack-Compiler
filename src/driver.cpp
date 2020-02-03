#include "driver.hpp"
#include "symtable.hpp"
#include "errors.hpp"


namespace ast {

    void
    Driver::TypeChecker::type_check() {
        std::string global_str = "___global___";
        auto *global = new SymbolTable(global_str);
        _st.push(global);
        try {
            /* adding every type to the global environment */
            for (auto i : _pgm->_classes->get_elements())
                global->add_symbol(i->get_name(), i->get_name(), TYPE);

            _pgm->_classes->semantic_check(_st);
            _pgm->_statements->semantic_check(_st);
        }
        catch (const DuplicateSymbol &ex) {
            report::error(ex.what());
        }
    }

    void
    Driver::CodeGenerator::code_gen() {
        CodegenContext _ctx(_out);
        _ctx.emit("/*\n"
                  " * MIT License\n"
                  " *\n"
                  " * Copyright (c) 2020 Parsa Bagheri\n"
                  " *\n"
                  " * Permission is hereby granted, free of charge, to any person obtaining a copy\n"
                  " * of this software and associated documentation files (the \"Software\"), to deal\n"
                  " * _input_file the Software without restriction, including without limitation the rights\n"
                  " * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n"
                  " * copies of the Software, and to permit persons to whom the Software is\n"
                  " * furnished to do so, subject to the following conditions:\n"
                  " *\n"
                  " * The above copyright notice and this permission notice shall be included _input_file all\n"
                  " * copies or substantial portions of the Software.\n"
                  " *\n"
                  " * THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n"
                  " * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n"
                  " * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n"
                  " * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n"
                  " * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n"
                  " * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n"
                  " * SOFTWARE.\n"
                  " */\n\n");
        _ctx.emit("#include <stdlib.h>\n");
        _ctx.emit("#include \"builtins.h\"\n\n"); /* preamble */

        std::string global_str = "___global___";
        auto *global = new SymbolTable(global_str);

        if (_pgm->_classes->len() > 5) /* 5 builtin classes */
            _ctx.emit("/* ======================= Class Declerations ======================= */\n\n");

        auto the_classes = _pgm->_classes->get_elements();
        for (Class *cls: the_classes) {
            if (!cls->is_builtin()) {
                std::string class_name = cls->get_name();
                _ctx.emit_class_sig(class_name); /* outputting forward references to our classes */
                global->add_symbol(class_name, class_name, TYPE);
            }
        }
        _st.push(global);
        if (_pgm->_classes->len() > 5) /* 5 builtin classes */
            _ctx.emit("/* ======================= Class Definitions ======================== */\n\n");

        _pgm->_classes->code_gen(_ctx, _st);
        _ctx.emit("/* ============================== Main ============================== */\n\n");
        _ctx.emit("int main (int argc, char *argv[]) {\n");
        _ctx.indent();
        _pgm->_statements->semantic_check(_st); /* do this to fill the symbol table */
        _pgm->_statements->code_gen(_ctx, _st);
        _ctx.emit("exit(0);\n");
        _ctx.dedent();
        _ctx.emit("}\n");
        delete _st.pop();
    }

    Driver::Driver(const char *input_file, const char *output_file)
        : _input_file(input_file), _output_file(output_file) {

        /* Processing input */
        if (!assert_file_type(input_file, ".qk")) /* making sure extension is .qk */
            throw io::BadFile("the input input_file extension is not `.qk'");

        if ((_file = fopen(_input_file, "r")) != nullptr)
            yyin = _file;
        else
            throw io::BadFile("no such input_file");

        /* Processing output */
        if (output_file != nullptr) {
            std::string tmp = output_file;
            if (!assert_file_type(output_file, ".c"))
                tmp += ".c";
            _out.open(tmp, std::ofstream::out);
        } else {
            _out.open("a.out.c", std::ofstream::out);
        }
    }

    void
    Driver::compile() {
        int result = yyparse();
        if (report::num_errors == 0 && result == 0) {

            auto *pgm = dynamic_cast<Program *>(root);
            assert(pgm != nullptr);
            Stack st(pgm->_classes);

            TypeChecker tc(pgm, st);
            tc.type_check();

            if (report::num_errors == 0) {
                CodeGenerator cg(pgm, _out, st);
                cg.code_gen();
            } else {
                report::summary();
            }
        } else {
            report::summary(); 
        }
        if (result == 0) { /* result is 0 if AST was generated */
            delete root;  /* done with the AST delete it */
        }
    }

    void Driver::json() {
        int result = yyparse();
        if (report::num_errors == 0 && result == 0) {

            auto *pgm = dynamic_cast<Program *>(root);
            assert(pgm != nullptr);
            PrintContext ctx;
            pgm->json(std::cout, ctx);

        } else {
            report::summary();
        }
        if (result == 0) { /* result is 0 if AST was generated */
            delete root;  /* done with the AST delete it */
        }
    }

    bool Driver::assert_file_type(const char *file, const char *ext) {
        int file_len = strlen(file);
        int ext_len = strlen(ext);
        return strcmp(file + file_len - ext_len, ext) == 0;
    }

}