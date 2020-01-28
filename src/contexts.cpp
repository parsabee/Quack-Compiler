#include "contexts.hpp"

namespace ast {
    std::string
    CodegenContext::gen_stars(const std::string& str) {
        std::stringstream ss;
        for (int i = 0; i < str.length() + 2; i++)
            ss << '*';
        return ss.str();
    }

    void CodegenContext::emit(const std::string& str) {
        for (int i = 0; i < _indent; i++)
            _out << "  ";
        _out << str;
    }

    void CodegenContext::emitClassSig(const std::string& cls) {
        std::string str = cls + " forward reference";
        std::string stars = gen_stars(str);
        this->emit("/*" + stars + "\n * " + str + "\n " + stars + "*/\n");
        this->emit("struct class_" + cls + "_struct;\n");
        this->emit("typedef struct obj_" + cls + "_struct *obj_" + cls + ";\n");
        this->emit("typedef struct class_" + cls + "_struct *class_" + cls + ";\n\n");
    }

    void CodegenContext::emitObjStruct(const std::string& cls,
                                       std::unordered_map<std::string, std::string> *attrs) {
        std::string str = cls + " definition";
        std::string stars = gen_stars(str);
        this->emit("/*" + stars + "\n * " + str + "\n " + stars + "*/\n");
        this->emit("struct obj_" + cls + "_struct {\n");
        this->emit("  struct class_" + cls + "_struct *clazz;\n");
        for (auto & attr : *attrs) {
            this->emit("  obj_" + attr.second + " " + attr.first + ";\n");
        }
        this->emit("};\n\n");
    }

    std::string CodegenContext::gen_IfLabel() {
        std::stringstream ss;
        ss << "cond___" << std::setw(3) << std::setfill('0') << _if++;
        return ss.str();
    }

    std::string CodegenContext::gen_BreakLabel() {
        std::stringstream ss;
        ss << "break___" << std::setw(3) << std::setfill('0') << _break++;
        return ss.str();
    }

    std::string CodegenContext::gen_LoopLabel() {
        std::stringstream ss;
        ss << "loop___" << std::setw(3) << std::setfill('0') << _loop++;
        return ss.str();
    }

    std::string CodegenContext::gen_TrueLabel() {
        std::stringstream ss;
        ss << "true___" << std::setw(3) << std::setfill('0') << _true++;
        return ss.str();
    }

    std::string CodegenContext::gen_FalseLabel() {
        std::stringstream ss;
        ss << "false___" << std::setw(3) << std::setfill('0') << _false++;
        return ss.str();
    }

    std::string CodegenContext::gen_EndLabel() {
        std::stringstream ss;
        ss << "endif___" << std::setw(3) << std::setfill('0') << _end++;
        return ss.str();
    }

    std::string CodegenContext::gen_temp() {
        std::stringstream ss;
        ss << "tmp__" << std::setw(4) << std::setfill('0') << _reg++;
        return ss.str();
    }

    std::string CodegenContext::gen_variable(const std::string& var) {
        std::stringstream ss;
        ss << "var__" << var;
        return ss.str();
    }

    std::string CodegenContext::get_last_temp(int n) {
        std::stringstream ss;
        ss << "tmp__" << std::setw(4) << std::setfill('0') << _reg - n - 1;
        return ss.str();
    }
}