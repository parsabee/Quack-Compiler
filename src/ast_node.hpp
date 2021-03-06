#ifndef _ASTNODE_H_
#define _ASTNODE_H_

#include <utility>

#include "all.hpp"
#include "contexts.hpp"
#include "stack.hpp"
#include "errors.hpp"
#include "qk_builtins.hpp"

/*
 * unused variables
 */
#define UNUSED __attribute__((unused))

/* the environment that contains builtin types
 * sits at the bottom of environment stack */
#define BUILTIN "___builtin___"

/* global environment, every symbol in the global scope is stored here
 * sits on top of built-in environment,
 * every new (user-defined) scope will sit on top of this */
#define GLOBAL "___global___"


namespace ast {

/*
 * check whether a word is reserved
 */
    bool is_reserved(const std::string& str);
/*
 * helper function to determine if t1 matches t2:
 *
 * they match if t1 == t2
 * if t1 > t2:
 *    meaning if t2 is a subclass of t1
 */
    bool
    type_match (const std::string &t1, const std::string &t2, Stack &st);

/* forward reference */

    class Classes;
    class Stack;

/* all of the node types */
    enum nodes {
        AST_NODE,
        SEQ,
        LEXPR,
        IDENT,
        FORMAL,
        FORMALS,
        LOAD,
        DOT,
        BINOP,
        AND,
        OR,
        NOT,
        PROGRAM,
        CLASS,
        CLASSES,
        METHOD,
        METHODS,
        EXPR,
        BLOCK,
        ASSIGN,
        ASSIGN_DECLARE,
        CALL,
        STATEMENT,
        ACTUALS,
        TYPE_ALTERNATIVES,
        RETURN,
        CONSTRUCT,
        IF,
        WHILE,
        INT_CONST,
        STR_CONST,
        TYPECASE
    };

/* abstract node _input_file the AST */
    class ASTNode {
    protected:
        void json_indent(std::ostream &out, PrintContext &ctx);

        void json_head(const std::string& node_kind, std::ostream &out, PrintContext &ctx);

        void json_close(std::ostream &out, PrintContext &ctx);

        void json_child(const std::string& field, ASTNode *child, std::ostream &out, PrintContext &ctx, char serp = ',');

    public:
        virtual int type() = 0;

        virtual int get_line() = 0;

        virtual std::string type_check(Stack &st) = 0;

        virtual void json(std::ostream &out, PrintContext &ctx) = 0;

        virtual void semantic_check(Stack &st) = 0;

        virtual void code_gen(CodegenContext &ctx, Stack &st) = 0;

        virtual std::string get_signature() = 0;

        virtual ~ASTNode() = default;
    };

    template<class Kind>
    class Seq : public ASTNode {
    protected:
        std::string _kind;
        std::vector<Kind *> _elements;
        int _line_no;
    public:
        Seq(std::string kind, int line_no) : _kind{std::move(std::move(kind))},
                                             _elements{std::vector<Kind *>()}, _line_no{line_no} {}

        void
        append(Kind *el) {
            _elements.push_back(el);
        }

        int
        len() {
            return _elements.size();
        }

        std::vector<Kind *>
        get_elements() const {
            return _elements;
        }

        int
        get_line() override {
            return _line_no;
        }

        int
        type() override {
            std::cerr << "Seq: type shouldn't be called\n";
            assert(false);
        }

        std::string
        type_check(Stack &st) override {
            std::cerr << "Seq: nothing to be inferred\n";
            assert(false);
        }

        void
        json(std::ostream &out, PrintContext &ctx) override {
            json_head(_kind, out, ctx);
            out << "\"elements_\" : [";
            auto sep = "";
            for (Kind *el: _elements) {
                out << sep;
                el->json(out, ctx);
                sep = ", ";
            }
            out << "]";
            json_close(out, ctx);
        }

        void
        semantic_check(Stack &st) override {
            for (Kind *el: _elements) {
                el->semantic_check(st);
            }
        }

        void
        code_gen(CodegenContext &ctx, Stack &st) override {
            for (Kind *el: _elements) {
                el->code_gen(ctx, st);
            }
        }

        std::string
        get_signature() override {
            std::cerr << "Seq: no signature\n";
            assert(false);
        }

        ~Seq() override {
            for (Kind *el: _elements)
                delete el;
        }
    };

/* left expression abstract type */
    class LExpr : public ASTNode {
    };

    class Ident : public LExpr {
        std::string _text;
        int _line_no;
    public:
        explicit Ident(std::string txt, int line_no) :
                _text{std::move(std::move(txt))}, _line_no{line_no} {}

        std::string type_check(Stack &st) override;

        void json(std::ostream &out, PrintContext &ctx) override;

        void semantic_check(Stack &st) override;

        void code_gen(CodegenContext &ctx, Stack &st) override;

        Ident(const Ident &other) {
            _text = other._text;
            _line_no = other._line_no;
        }

        std::string
        get_text() {
            return _text;
        }

        int
        get_line() override {
            return _line_no;
        }

        int
        type() override {
            return IDENT;
        }

        std::string
        get_signature() override {
            return _text;
        }
    };

    class Block : public Seq<ASTNode> {
    public:
        explicit Block(int line_no) : Seq("Block", line_no) {}
    };

    class Formal : public ASTNode {
        Ident *_var;
        Ident *_type;
        int _line_no;
    public:
        explicit Formal(Ident *var, Ident *type, int line_no) :
                _var{var}, _type{type}, _line_no{line_no} {}

        int type() override {
            return FORMAL;
        }

        int get_line() override {
            return _line_no;
        }

        Ident *get_var() const {
            return _var;
        }

        Ident *get_type() const {
            return _type;
        }

        std::string type_check(Stack &st) override {
            return _type->get_text();
        }

        std::string get_signature() override {
            std::string sig;
            sig += _var->get_signature() + ": " + _type->get_signature();
            return sig;
        }

        void json(std::ostream &out, PrintContext &ctx) override;

        void semantic_check(Stack &st) override;

        void code_gen(CodegenContext &ctx, Stack &st) override;

        ~Formal() override {
            delete _var;
            delete _type;
        }
    };

    class Formals : public Seq<Formal> {
    public:
        explicit Formals(int line_no) : Seq("Formals", line_no) {}

        void semantic_check(Stack &st) override;

        std::string get_signature() override {
            std::string sig;
            bool first = true;
            for (auto it: get_elements()) {
                if (!first) sig += ", ";
                first = false;
                sig += it->get_signature();
            }
            return sig;
        }

        bool operator == (Formals const &other) {
            if (_elements.size() != other.get_elements().size())
                return false;
            for (int i = 0; i < _elements.size(); i++) {
                if (_elements[i]->get_type()->get_text() != other.get_elements()[i]->get_type()->get_text())
                    return false;
            }
            return true;
        }

        bool operator != (Formals const &other) {
            return !(*this == other);
        }
    };

    class Method : public ASTNode {
        friend class MethodChecker;

        Ident *_name;
        Formals *_formals;
        Ident *_returns;
        Block *_statements;
        std::string _owner;
        bool _overriden; /* is method an override?, will be set _input_file typechecking stage */
        int _line_no;
    public:
        explicit Method(Ident *name, Formals *formals,
                        Ident *returns, Block *statements, int line_no, std::string owner = "Obj") :
                _name{name}, _formals{formals}, _returns{returns}, _owner{std::move(std::move(owner))}, /* default owner */
                _statements{statements}, _overriden{false}, _line_no{line_no} {}

        void json(std::ostream &out, PrintContext &ctx) override;

        void semantic_check(Stack &st) override;

        void code_gen(CodegenContext &ctx, Stack &st) override;

        std::string get_signature() override;

        std::string
        get_owner() {
            return _owner;
        }

        std::string
        get_name() {
            return _name->get_text();
        }

        std::string
        get_return() {
            return _returns->get_text();
        }

        Block *
        get_statements() const {
            return _statements;
        }

        Formals *
        get_formals() const {
            return _formals;
        }

        int
        type() override {
            return METHOD;
        }

        int get_line() override {
            return _line_no;
        }

        std::string
        type_check(Stack &st) override {
            return _returns->type_check(st);
        }

        ~Method() override {
            delete _name;
            delete _formals;
            delete _returns;
            delete _statements;
        }
    };

    class Methods : public Seq<Method> {
    public:
        explicit Methods(int line_no) : Seq("Methods", line_no) {}
        void semantic_check(Stack &st) override ;
        void code_gen(CodegenContext &ctx, Stack &st) override ;
    };

    class Statement : public ASTNode {
    public:
        std::string type_check(Stack &st) override {
            std::cerr << "Statement: nothing to be inferred\n";
            assert(false);
        }
    };

    class Assign : public Statement {
        friend class AssignChecker;

    protected:
        LExpr *_lexpr;
        ASTNode *_rexpr;
        int _line_no;
    public:
        explicit Assign(LExpr *lexpr, ASTNode *rexpr, int line_no) :
                _lexpr{lexpr}, _rexpr{rexpr}, _line_no{line_no} {}

        LExpr *get_left() const {
            return _lexpr;
        }

        ASTNode *get_right() const {
            return _rexpr;
        }

        int type() override {
            return ASSIGN;
        }

        int get_line() override {
            return _line_no;
        }

        void json(std::ostream &out, PrintContext &ctx) override;

        void semantic_check(Stack &st) override;

        void code_gen(CodegenContext &ctx, Stack &st) override;

        std::string get_signature() override {
            std::string sig;
            sig += _lexpr->get_signature() + " = " + _rexpr->get_signature();
            return sig;
        }

        ~Assign() override {
            delete _lexpr;
            delete _rexpr;
        }
    };

    class AssignDeclare : public Assign {
        friend class AssignChecker;

        Ident *_static_type;
    public:
        explicit AssignDeclare(LExpr *lexpr, ASTNode *rexpr, Ident *static_type, int line_no) :
                Assign(lexpr, rexpr, line_no), _static_type{static_type} {}

        Ident *get_static_type() const { return _static_type; }

        int type() override { return ASSIGN_DECLARE; }

        void json(std::ostream &out, PrintContext &ctx) override;

        void semantic_check(Stack &st) override;

        std::string get_signature() override {
            std::string sig;
            sig += _lexpr->get_signature() + ": " + _static_type->get_signature() + " = " + _rexpr->get_signature();
            return sig;
        }

        ~AssignDeclare() override { delete _static_type; }
    };

    class Expr : public Statement {
    };

    class Load : public Expr {
        LExpr *_loc;
        int _line_no;
    public:
        Load(LExpr *loc, int line_no) : _loc{loc}, _line_no{line_no} {}

        LExpr *get_loc() const {
            return _loc;
        }

        int type() override {
            return LOAD;
        }

        int get_line() override {
            return _line_no;
        }

        std::string type_check(Stack &st) override;

        void json(std::ostream &out, PrintContext &ctx) override;

        void semantic_check(Stack &st) override;

        void code_gen(CodegenContext &ctx, Stack &st) override;

        std::string get_signature() override {
            return _loc->get_signature();
        }

        ~Load() override { delete _loc; }
    };

    class Return : public Statement {
        ASTNode *_expr;
        int _line_no;
    public:
        explicit Return(ASTNode *expr, int line_no) : _expr{expr}, _line_no{line_no} {}

        void json(std::ostream &out, PrintContext &ctx) override;

        void code_gen(CodegenContext &ctx, Stack &st) override;

        void semantic_check(Stack &st) override;

        int
        type() override {
            return RETURN;
        }

        int
        get_line() override {
            return _line_no;
        }

        ASTNode *
        get_expr() {
            return _expr;
        }

        std::string
        type_check(Stack &st) override {
            return _expr->type_check(st);
        }

        std::string
        get_signature() override {
            std::string sig;
            sig += "return " + _expr->get_signature();
            return sig;
        }

        ~Return() override {
            delete _expr;
        }
    };

    class If : public Statement {
        ASTNode *_cond;
        Block *_true_part;
        Block *_false_part;
        int _line_no;
    public:
        explicit If(ASTNode *cond, Block *true_part, Block *false_part, int line_no)
                : _cond{cond}, _true_part{true_part}, _false_part{false_part}, _line_no(line_no) {}

        int get_line() override {
            return _line_no;
        }

        int type() override {
            return IF;
        }

        Block *get_true() const {
            return _true_part;
        }

        Block *get_false() const {
            return _false_part;
        }

        void json(std::ostream &out, PrintContext &ctx) override;

        void semantic_check(Stack &st) override;

        void code_gen(CodegenContext &ctx, Stack &st) override;

        std::string get_signature() override {
            std::string sig;
            sig += "if (" + _cond->get_signature() + ")";
            return sig;
        }

        ~If() override {
            delete _cond;
            delete _true_part;
            delete _false_part;
        }
    };

    class While : public Statement {
        ASTNode *_cond;
        Block *_body;
        int _line_no;
    public:
        explicit While(ASTNode *cond, Block *body, int line_no) :
                _cond{cond}, _body{body}, _line_no{line_no} {}

        int type() override {
            return WHILE;
        }

        int get_line() override {
            return _line_no;
        }

        Block *get_body() const {
            return _body;
        }

        void json(std::ostream &out, PrintContext &ctx) override;

        void semantic_check(Stack &st) override;

        void code_gen(CodegenContext &ctx, Stack &st) override;

        std::string get_signature() override {
            std::string sig;
            sig += "while (" + _cond->get_signature() + ")";
            return sig;
        }

        ~While() override {
            delete _cond;
            delete _body;
        }
    };

    class Class : public ASTNode {
        friend class Assign;
        friend class AssignDeclare;

        Ident *_name;
        Ident *_super;
        Method *_constructor;
        Methods *_methods;
        std::unordered_map<std::string, std::pair<std::string, kinds>> *_attrs;
        bool _builtin;
        int _line_no;
    public:
        Class(Ident *name, Ident *super, Method *constuctor, Methods *methods, int line_no, bool builtin = false) :
                _name{name}, _super{super}, _constructor{constuctor}, _methods{methods},
                _attrs{new std::unordered_map<std::string, std::pair<std::string, kinds>>},_builtin{builtin},
                _line_no{line_no} {}

        void json(std::ostream &out, PrintContext &ctx) override;

        void semantic_check(Stack &st) override;

        void code_gen(CodegenContext &ctx, Stack &st) override;

        bool has_attr(const std::string& attr) {
            return _attrs->count(attr) != 0;
        }

        bool has_method(const std::string& name) {
            for (auto &it: _methods->get_elements()) {
                if (it->get_name() == name) {
                    return true;
                }
            }
            return false;
        }

        int
        get_line() override {
            return _line_no;
        }

        std::string
        get_name() {
            return _name->get_text();
        }

        std::string
        get_super() {
            return _super->get_text();
        }

        Method *
        get_constructor() const {
            return _constructor;
        }

        std::unordered_map<std::string, std::pair<std::string, kinds>> *
        get_attrs() const {
            return _attrs;
        }

        Method *
        get_method(const std::string& method) const {
            for (auto i: _methods->get_elements())
                if (i->get_name() == method)
                    return i;
            throw MethodNotFound(method, nullptr);
        }

        Methods *
        get_methods() const {
            return _methods;
        }

        bool
        is_builtin() {
            return _builtin;
        }

        int
        type() override {
            return CLASS;
        }

        std::string
        type_check(Stack &st) override {
            return _name->type_check(st);
        }

        std::string get_signature() override {
            std::string sig;
            sig += "class " + get_name() + "(" + _constructor->get_formals()->get_signature()
                   + ") extends " + _super->get_signature() + " { ... }";
            return sig;
        }

        ~Class() override {
            delete _name;
            delete _super;
            delete _constructor;
            delete _methods;
            delete _attrs;
        }

    private:
        void update_attribute(const std::string &attr,
                              const std::string &type,
                              kinds kind,
                              Stack &st);
    };

    class Classes : public Seq<Class> {
    public:
        explicit Classes(int line_no) : Seq<Class>("Classes", line_no) {}

        void semantic_check(Stack &st) override;

        void code_gen(CodegenContext &ctx, Stack &st) override;
    };

    class IntConst : public Expr {
        int _value;
        int _line_no;
    public:
        explicit IntConst(int v, int line_no) : _value{v}, _line_no{line_no} {}

        int type() override {
            return INT_CONST;
        }

        std::string type_check(Stack &st) override {
            return "Int";
        }

        int get_line() override {
            return _line_no;
        }

        void json(std::ostream &out, PrintContext &ctx) override;

        void semantic_check(Stack &st) override {}

        void code_gen(CodegenContext &ctx, Stack &st) override;

        std::string get_signature() override {
            return std::to_string(_value);
        }
    };

    class Type_Alternative : public ASTNode {
        Ident *_ident;
        Ident *_classname;
        Block *_block;
        int _line_no;
    public:
        explicit Type_Alternative(Ident *ident, Ident *classname, Block *block, int line_no) :
                _ident{ident}, _classname{classname}, _block{block}, _line_no{line_no} {}

        int type() override {
            return TYPE_ALTERNATIVES;
        }

        int get_line() override {
            return _line_no;
        }

        Ident *get_ident() { return _ident; }

        Ident *get_classname() { return _classname; }

        Block *get_block() { return _block; }

        std::string type_check(Stack &st) override {
            std::cerr << "Type_Alternative: Nothing to be inferred\n";
            assert(false);
        }

        void json(std::ostream &out, PrintContext &ctx) override;

        void semantic_check(Stack &st) override;

        void code_gen(CodegenContext &ctx, Stack &st) override {}

        std::string get_signature() override {
            return _ident->get_text() + ": " + _classname->get_text() + " { ... }";
        }

        ~Type_Alternative() override {
            delete _ident;
            delete _classname;
            delete _block;
        }
    };

    class Type_Alternatives : public Seq<Type_Alternative> {
    public:
        explicit Type_Alternatives(int line_no) : Seq("Type_Alternatives", line_no) {}
    };

    class Typecase : public Statement {
        Expr *_expr;
        Type_Alternatives *_cases;
        int _line_no;
    public:
        explicit Typecase(Expr *expr, Type_Alternatives *cases, int line_no) :
                _expr{expr}, _cases{cases}, _line_no{line_no} {}

        int type() override {
            return TYPECASE;
        }

        int get_line() override {
            return _line_no;
        }

        void json(std::ostream &out, PrintContext &ctx) override;

        void semantic_check(Stack &st) override;

        void code_gen(CodegenContext &ctx, Stack &st) override;

        std::string get_signature() override {
            return "";
        }

        ~Typecase() override {
            delete _expr;
            delete _cases;
        }
    };

    class StrConst : public Expr {
        std::string _value;
        int _line_no;
    public:
        explicit StrConst(std::string v, int line_no) :
                _value{std::move(std::move(v))}, _line_no{line_no} {}

        int type() override {
            return STR_CONST;
        }

        int get_line() override {
            return _line_no;
        }

        std::string type_check(Stack &st) override {
            return "String";
        }

        void json(std::ostream &out, PrintContext &ctx) override;

        void semantic_check(Stack &st) override {}

        void code_gen(CodegenContext &ctx, Stack &st) override;

        std::string get_signature() override {
            std::string sig = "\"" + _value + "\"";
            return sig;
        }
    };

    class Actuals : public Seq<Expr> {
    public:
        explicit Actuals(int line_no) : Seq("Actuals", line_no) {}

        std::string get_signature() override {
            std::string sig;
            bool first = true;
            for (auto it : _elements) {
                if (!first) sig += ", ";
                first = false;
                sig += it->get_signature();
            }
            return sig;
        }
    };

    class Construct : public Expr {
        Ident *_method;
        Actuals *_actuals;
        int _line_no;
    public:
        explicit Construct(Ident *method, Actuals *actuals, int line_no) :
                _method{method}, _actuals{actuals}, _line_no{line_no} {}

        void json(std::ostream &out, PrintContext &ctx) override;

        std::string type_check(Stack &st) override;

        void semantic_check(Stack &st) override;

        void code_gen(CodegenContext &ctx, Stack &st) override;

        int
        type() override {
            return CONSTRUCT;
        }

        int
        get_line() override {
            return _line_no;
        }

        std::string
        get_method() {
            return _method->get_text();
        }

        std::string
        get_signature() override {
            std::string sig;
            sig += _method->get_signature() + "(" + _actuals->get_signature() + ")";
            return sig;
        }

        ~Construct() override {
            delete _method;
            delete _actuals;
        }
    };

    class Call : public Expr {
        Expr *_receiver;
        Ident *_method;
        Actuals *_actuals;
        int _line_no;
    public:
        explicit Call(Expr *receiver, Ident *method, Actuals *actuals, int line_no) :
                _receiver{receiver}, _method{method}, _actuals{actuals}, _line_no{line_no} {}

        std::string type_check(Stack &st) override;

        void json(std::ostream &out, PrintContext &ctx) override;

        void semantic_check(Stack &st) override;

        void code_gen(CodegenContext &ctx, Stack &st) override;

        static Call *binop(std::string opname, Expr *receiver, Expr *arg, int line_no);

        int
        get_line() override {
            return _line_no;
        }

        int
        type() override {
            return CALL;
        }

        std::string
        get_method_name() {
            return _method->get_text();
        }

        Expr *
        get_receiver() {
            return _receiver;
        }

        std::string
        get_signature() override {
            std::string sig;
            sig += _receiver->get_signature() + "." + _method->get_signature()
                   + "(" + _actuals->get_signature() + ")";
            return sig;
        }

        ~Call() override {
            delete _receiver;
            delete _method;
            delete _actuals;
        }

    private:
        Method *get_method(Stack &st);
    };

    class BinOp : public Expr {
    protected:
        std::string opsym;
        ASTNode *_left;
        ASTNode *_right;
        int _line_no;

        BinOp(std::string sym, ASTNode *l, ASTNode *r, int line_no) :
                opsym{std::move(std::move(sym))}, _left{l}, _right{r}, _line_no{line_no} {}

    public:
        int type() override {
            return BINOP;
        }

        int get_line() override {
            return _line_no;
        }

        std::string type_check(Stack &st) override;

        void json(std::ostream &out, PrintContext &ctx) override;

        void semantic_check(Stack &st) override;

        void code_gen(CodegenContext &ctx, Stack &st) override;

        std::string get_signature() override {
            std::string sig;
            sig += _left->get_signature() + " " + opsym + " " + _right->get_signature();
            return sig;
        }

        ~BinOp() override {
            delete _left;
            delete _right;
        }
    };

    class And : public BinOp {
    public:
        explicit And(ASTNode *left, ASTNode *right, int line_no) :
                BinOp("And", left, right, line_no) {}

        int type() override {
            return AND;
        }
    };

    class Or : public BinOp {
    public:
        explicit Or(ASTNode *left, ASTNode *right, int line_no) :
                BinOp("Or", left, right, line_no) {}

        int type() override {
            return OR;
        }
    };

    class Not : public Expr {
        ASTNode *_left;
        int _line_no;
    public:
        explicit Not(ASTNode *left, int line_no) :
                _left{left}, _line_no{line_no} {}

        int type() override {
            return NOT;
        }

        std::string type_check(Stack &st) override {
            return "Boolean";
        }

        int get_line() override {
            return _line_no;
        }

        void json(std::ostream &out, PrintContext &ctx) override;

        void semantic_check(Stack &st) override {}

        void code_gen(CodegenContext &ctx, Stack &st) override {}

        std::string get_signature() override {
            std::string sig = "Not ";
            sig += _left->get_signature();
            return sig;
        }

        ~Not() override { delete _left; }
    };

    class Dot : public LExpr {
        Expr *_left;
        Ident *_right;
        int _line_no;
    public:
        explicit Dot(Expr *left, Ident *right, int line_no) :
                _left{left}, _right{right}, _line_no{line_no} {}

        void json(std::ostream &out, PrintContext &ctx) override;

        void semantic_check(Stack &st) override;

        void code_gen(CodegenContext &ctx, Stack &st) override;

        std::string type_check(Stack &st) override;

        Expr *
        get_left() const {
            return _left;
        }

        Ident *
        get_right() const {
            return _right;
        }

        int
        type() override {
            return DOT;
        }

        int
        get_line() override {
            return _line_no;
        }

        std::string
        get_signature() override {
            std::string sig;
            sig += _left->get_signature() + "." + _right->get_signature();
            return sig;
        }

        ~Dot() override {
            delete _left;
            delete _right;
        }

    };

    class Program : public ASTNode {
        friend class Driver;

        Classes *_classes;
        Block *_statements;
        int _line_no;
    public:
        explicit Program(Classes *cl, Block *st, int line_no) :
                _classes{cl}, _statements{st}, _line_no{line_no} {}

        int type() override {
            return PROGRAM;
        }

        int get_line() override {
            return _line_no;
        }

        std::string type_check(Stack &st) override {
            std::cerr << "Program: nothing to be inferred\n";
            assert(false);
        }

        void json(std::ostream &out, PrintContext &ctx) override;

        void semantic_check(Stack &st) override;

        void code_gen(CodegenContext &ctx, Stack &st) override;

        std::string get_signature() override {
            std::cerr << "Program: no signature";
            assert(false);
        }

        ~Program() override {
            delete _classes;
            delete _statements;
        }
    };

} /* namespace ast */

#endif /*_ASTNODE_H_*/

