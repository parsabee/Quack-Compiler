#ifndef _CONTEXTS_H_
#define _CONTEXTS_H_

#include <utility>


#include "all.hpp"
#include "symtable.hpp"

namespace ast {
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

        void emitClassSig(const std::string& cls);

        void emitObjStruct(const std::string& cls,
                           std::unordered_map<std::string, std::string> *attrs);

        static std::string gen_stars(const std::string& str);

        std::string gen_IfLabel();

        std::string gen_BreakLabel();

        std::string gen_LoopLabel();

        std::string gen_TrueLabel();

        std::string gen_FalseLabel();

        std::string gen_EndLabel();

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