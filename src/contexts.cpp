#include "contexts.hpp"
#include "stack.hpp"

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

    void CodegenContext::emit_class_sig(const std::string& cls) {
        std::string str = cls + " forward reference";
        std::string stars = gen_stars(str);
        this->emit("/*" + stars + "\n * " + str + "\n " + stars + "*/\n");
        this->emit("struct class_" + cls + "_struct;\n");
        this->emit("typedef struct obj_" + cls + "_struct *obj_" + cls + ";\n");
        this->emit("typedef struct class_" + cls + "_struct *class_" + cls + ";\n\n");
    }

    void CodegenContext::emit_obj_struct(const std::string& cls,
                                         std::unordered_map<std::string, std::pair<std::string, kinds>> *attrs) {
        std::string str = cls + " definition";
        std::string stars = gen_stars(str);
        this->emit("/*" + stars + "\n * " + str + "\n " + stars + "*/\n");
        this->emit("struct obj_" + cls + "_struct {\n");
        this->emit("  struct class_" + cls + "_struct *clazz;\n");
        for (auto & attr : *attrs) {
            this->emit("  obj_" + attr.second.first + " " + attr.first + ";\n");
        }
        this->emit("};\n\n");
    }

    std::string CodegenContext::gen_if() {
        std::stringstream ss;
        if ( _if > 999 ){
            ss << "cond___" << _if++;
        } else {
            ss << "cond___" << std::setw(3) << std::setfill('0') << _if++;
        }
        return ss.str();
    }

    std::string CodegenContext::gen_break() {
        std::stringstream ss;
        if (_break > 999){
            ss << "break___" << _break++;
        } else {
            ss << "break___" << std::setw(3) << std::setfill('0') << _break++;
        }
        return ss.str();
    }

    std::string CodegenContext::gen_loop() {
        std::stringstream ss;
        if (_loop > 999){
            ss << "loop___" << _loop++;
        } else {
            ss << "loop___" << std::setw(3) << std::setfill('0') << _loop++;
        }
        return ss.str();
    }

    std::string CodegenContext::gen_true() {
        std::stringstream ss;
        if (_true > 999) {
            ss << "true___" << _true++;
        } else {
            ss << "true___" << std::setw(3) << std::setfill('0') << _true++;
        }
        return ss.str();
    }

    std::string CodegenContext::gen_false() {
        std::stringstream ss;
        if (_false > 999) {
            ss << "false___" << _false++;
        } else {
            ss << "false___" << std::setw(3) << std::setfill('0') << _false++;
        }
        return ss.str();
    }

    std::string CodegenContext::gen_end() {
        std::stringstream ss;
        if (_end > 999) {
            ss << "endif___" << _end;
        } else {
            ss << "endif___" << std::setw(3) << std::setfill('0') << _end++;
        }
        return ss.str();
    }

    std::string CodegenContext::gen_temp() {
        std::stringstream ss;
        if (_reg > 999) {
            ss << "tmp__" << _reg++;
        } else {
            ss << "tmp__" << std::setw(3) << std::setfill('0') << _reg++;
        }
        return ss.str();
    }

    std::string CodegenContext::gen_variable(const std::string& var) {
        std::stringstream ss;
        ss << "var__" << var;
        return ss.str();
    }

    std::string CodegenContext::get_last_temp(int n) {
        std::stringstream ss;
        int tmp = _reg - n - 1;
        if (tmp > 999) {
            ss << "tmp__" << tmp;
        } else {
            ss << "tmp__" << std::setw(3) << std::setfill('0') << tmp;
        }
        return ss.str();
    }

    void CodegenContext::declare_variable(const std::string &type, const std::string &var, Stack& st) {
        std::string variable = this->gen_variable(var);
        if ( !st.top()->is_generated(var) ) {
            this->emit("obj_" + type + " " + variable + ";\n");
            st.top()->gen_symbol(var);
        }
    }
}