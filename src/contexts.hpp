#ifndef _CONTEXTS_H_
#define _CONTEXTS_H_

#include <utility>


#include "all.hpp"
#include "symtable.hpp"

namespace ast {
    class Stack; /* forward reference */

    class PrintContext {
    public:
        int _indent;

        PrintContext() : _indent{0} {}

        void indent() { _indent++; }

        void dedent() { _indent--; }
    };

    class CodegenContext : public PrintContext {
        int _reg;
        int _if, _loop, _break;
        int _true, _false, _end;
        std::ostream &_out;
    public:
        explicit CodegenContext(std::ostream &out) : PrintContext(),
                                            _reg{1}, _if{1}, _loop{1}, _break{1}, _end{1},
                                            _true{1}, _false{1}, _out{out} {}

        void resetReg() { _reg = 1; }

        void emit(const std::string& str);

        void emit_class_sig(const std::string& cls);

        void emit_obj_struct(const std::string& cls,
                             std::unordered_map<std::string, std::string> *attrs);

        /* if variable is not already declared, generate the declaration */
        void declare_variable(const std::string& type, const std::string& var, Stack& st);

        static std::string gen_stars(const std::string& str);

        std::string gen_if();

        std::string gen_break();

        std::string gen_loop();

        std::string gen_true();

        std::string gen_false();

        std::string gen_end();

        std::string gen_temp();

        static std::string gen_variable(const std::string& var);

        std::string get_last_temp(int n = 0);
    };

    class InferContext {
        std::string _type;
    public:
        InferContext() : _type{""} {}

        void setType(std::string type) { _type = std::move(type); }

        std::string getType() { return _type; }
    };
}

#endif /*_CONTEXTS_H_*/