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

            _pgm->_classes->type_check(_st);
            _pgm->_statements->type_check(_st);
        }
        catch (const DuplicateSymbol &ex) {
            report::error(ex.what());
        }
    }

    void
    Driver::CodeGenerator::code_gen() {
        CodegenContext _ctx(_out);
        std::string global_str = "___global___";
        auto *global = new SymbolTable(global_str);

        _ctx.emit("#include <stdlib.h>\n");
        _ctx.emit("#include \"builtins.h\"\n\n"); /* preamble */
        if (_pgm->_classes->len() > 5) /* 5 builtin classes */
            _ctx.emit("/* ======================= Class Declerations ======================= */\n\n");

        auto the_classes = _pgm->_classes->get_elements();
        for (Class *cls: the_classes) {
            if (!cls->is_builtin()) {
                std::string class_name = cls->get_name();
                _ctx.emitClassSig(class_name); /* outputting forward references to our classes */
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
        _pgm->_statements->type_check(_st); /* do this to fill the symbol table */
        _pgm->_statements->code_gen(_ctx, _st);
        _ctx.emit("exit(0);\n");
        _ctx.dedent();
        _ctx.emit("}\n");
        delete _st.pop();
    }

    Driver::Driver(std::ostream &out, char *file) : _filename(file), _out(out) {
        if ((_file = fopen(_filename, "r")) != nullptr)
            yyin = _file;
        else
            throw io::BadInputFile();
    }

    void
    Driver::compile() {
        if (yyparse() == 0) {
            auto *pgm = dynamic_cast<Program *>(root);
            assert(pgm);
            Stack st(pgm->_classes);
            TypeChecker tc(pgm, st);
            tc.type_check();
            if (report::num_errors == 0) {
                CodeGenerator cg(pgm, _out, st);
                cg.code_gen();
            } else
                report::summary();
        } else
            throw NotParsed();
    }

}