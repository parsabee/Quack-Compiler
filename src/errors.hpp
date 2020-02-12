#ifndef _ERROR_H_
#define _ERROR_H_

#include "all.hpp"
#include "msg.hpp"

namespace io {
    struct BadFile : public std::exception {
        explicit BadFile(const std::string& note)
            : error("BadFile -- " + note){}

        const char *what() const noexcept override {
            return error.c_str();
        }
        private:
            std::string error;
    };
}
namespace ast {

    class ASTNode; /* forward reference */

    /*
     * base type for type errors
     */
    struct ast_exception : public std::exception {
        ast_exception() = default;

        const char *what() const noexcept override {
            return "ASTException";
        }
        virtual ASTNode *get_node() const noexcept {
            return nullptr;
        }
    };

    struct BadInherit : public ast_exception {
        BadInherit(const std::string& note, ASTNode *obj)
                : error("BadInherit -- " + note), obj(obj) {}
        const char *what() const noexcept override {
            return error.c_str();
        }
        ASTNode *get_node() const noexcept override {
            return obj;
        }
    private:
        std::string error;
        ASTNode *obj;
    };

    struct DuplicateSymbol : public ast_exception {
        DuplicateSymbol(const std::string& sym, ASTNode *obj)
            : error("DuplicateSymbol -- " + sym), obj(obj) {}

        const char *what() const noexcept override {
            return error.c_str();
        }
        ASTNode *get_node() const noexcept override {
            return obj;
        }
    private:
        std::string error;
        ASTNode *obj;
    };

    struct SymbolNotFound : public ast_exception {
        SymbolNotFound(const std::string& sym, ASTNode *obj)
            : error("SymbolNotFound -- " + sym), obj(obj) {}

        const char *what() const noexcept override {
            return error.c_str();
        }
        ASTNode *get_node() const noexcept override {
            return obj;
        }
    private:
        std::string error;
        ASTNode *obj;
    };

    struct MethodOverload : public ast_exception {
        MethodOverload(const std::string& sym, ASTNode *obj)
                : error("MethodOverload -- " + sym), obj(obj) {}

        const char *what() const noexcept override {
            return error.c_str();
        }
        ASTNode *get_node() const noexcept override {
            return obj;
        }
    private:
        std::string error;
        ASTNode *obj;
    };

    struct MethodNotFound : public ast_exception {

        MethodNotFound(const std::string& sym, ASTNode *obj)
        : error("MethodNotFound -- " + sym), obj(obj) {}

        const char *what() const noexcept override {
            return error.c_str();
        }
        ASTNode *get_node() const noexcept override {
            return obj;
        }
    private:
        std::string error;
        ASTNode *obj;
    };

    struct TypeNotFound : public ast_exception {

        TypeNotFound(const std::string& sym, ASTNode *obj)
            : error("TypeNotFound -- " + sym), obj(obj) {}

        const char *what() const noexcept override {
            return error.c_str();
        }
        ASTNode *get_node() const noexcept override {
            return obj;
        }
    private:
        std::string error;
        ASTNode *obj;
    };

    struct TypeRedefinition : public ast_exception {
        TypeRedefinition(const std::string& note, ASTNode *obj)
                : error("TypeRedefinition -- " + note), obj(obj) {}
        const char *what() const noexcept override {
            return error.c_str();
        }
        ASTNode *get_node() const noexcept override {
            return obj;
        }
    private:
        std::string error;
        ASTNode *obj;
    };

    struct TypeError : public ast_exception {
        TypeError(const std::string& note, ASTNode *obj)
            : error("TypeError -- " + note), obj(obj) {}
        const char *what() const noexcept override {
            return error.c_str();
        }
        ASTNode *get_node() const noexcept override {
            return obj;
        }
    private:
        std::string error;
        ASTNode *obj;
    };

    struct ReservedWord : public ast_exception {
        ReservedWord(const std::string& wrd, ASTNode *obj)
            : error("ReservedWord -- " + wrd), obj(obj) {}

        const char *what() const noexcept override {
            return error.c_str();
        }
        ASTNode *get_node() const noexcept override {
            return obj;
        }
    private:
        std::string error;
        ASTNode *obj;
    };

    struct AttributeError : public ast_exception {
        AttributeError(const std::string& wrd, ASTNode *obj)
            : error("AttributeError -- " + wrd), obj(obj) {}

        const char *what() const noexcept override {
            return error.c_str();
        }
        ASTNode *get_node() const noexcept override {
            return obj;
        }
    private:
        std::string error;
        ASTNode *obj;
    };
}
#endif /*_ERROR_H_*/