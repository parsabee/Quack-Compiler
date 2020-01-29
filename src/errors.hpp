#ifndef _ERROR_H_
#define _ERROR_H_

#include "all.hpp"
#include "msg.hpp"

namespace io {
    struct BadInputFile : public std::exception {
        explicit BadInputFile(const std::string& note)
            : error("BadInputFile -- " + note){}

        const char *what() const noexcept override {
            return error.c_str();
        }
        private:
            std::string error;
    };
}
namespace ast {
    /*
     * base type for type errors
     */
    struct ast_exception : public std::exception {
        ast_exception() = default;

        const char *what() const noexcept override {
            return "ast_exception";
        }
    };

    struct BadInit : public ast_exception {
        BadInit() = default;

        const char *what() const noexcept override {
            return "BadInit";
        }
    };

    struct BadInherit : public ast_exception {
        explicit BadInherit(const std::string& note = "")
                : error("BadInherit -- " + note){}
        const char *what() const noexcept override {
            return error.c_str();
        }
    private:
        std::string error;
    };

    struct SyntaxError : public ast_exception {
        SyntaxError() = default;

        const char *what() const noexcept override {
            return "SyntaxError";
        }
    };

    struct NotParsed : public ast_exception {
        NotParsed() = default;

        const char *what() const noexcept override {
            return "ASTNotParsed";
        }
    };

    struct DuplicateSymbol : public ast_exception {
        explicit DuplicateSymbol(const std::string& sym)
            : error("DuplicateSymbol -- " + sym) {}

        const char *what() const noexcept override {
            return error.c_str();
        }
    private:
        std::string error;
    };

    struct SymbolNotFound : public ast_exception {
        explicit SymbolNotFound(const std::string& sym)
            : error("SymbolNotFound -- " + sym) {}

        const char *what() const noexcept override {
            return error.c_str();
        }
    private:
        std::string error;
    };

    struct MethodNotFound : public ast_exception {

        explicit MethodNotFound(const std::string& sym)
        : error("MethodNotFound -- " + sym) {}

        const char *what() const noexcept override {
            return error.c_str();
        }
    private:
        std::string error;
    };

    struct TypeNotFound : public ast_exception {

        explicit TypeNotFound(const std::string& sym)
            : error("TypeNotFound " + sym) {}

        const char *what() const noexcept override {
            return error.c_str();
        }
    private:
        std::string error;
    };

    struct TypeError : public ast_exception {
        explicit TypeError(const std::string& note = "")
            : error("TypeError -- " + note) {}
        const char *what() const noexcept override {
            return error.c_str();
        }
    private:
        std::string error;
    };

    struct ReservedWord : public ast_exception {
        explicit ReservedWord(const std::string& wrd)
            : error("ReservedWord " + wrd) {}

        const char *what() const noexcept override {
            return error.c_str();
        }
    private:
        std::string error;
    };

    struct AttributeError : public ast_exception {
        explicit AttributeError(const std::string& wrd)
            : error("AttributeError " + wrd) {}

        const char *what() const noexcept override {
            return error.c_str();
        }
    private:
        std::string error;
    };
}
#endif /*_ERROR_H_*/