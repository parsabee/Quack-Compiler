#ifndef _ASTNODE_H_
#define _ASTNODE_H_

#include <utility>


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

/*
 * error reporting facility
 */
#define ERROR(OBJ) {                                                        \
  std::stringstream msg;                                                    \
  msg << "line " << (OBJ)->get_line() << ":    " << (OBJ)->get_signature(); \
  report::error(ex.what(), msg.str());                                      \
}

/*
 * number _input_file a sequence
 */
#define NUMBER(OUT, NUM) {      \
  switch(NUM)                   \
    {                           \
    case 0:                     \
      (OUT) << "1st";           \
      break;                    \
    case 1:                     \
      (OUT) << "2nd";           \
      break;                    \
    case 2:                     \
      (OUT) << "3rd";           \
      break;                    \
    default:                    \
      (OUT) << (NUM)+1 << "th"; \
    }                           \
}


namespace ast {

/*
 * check whether a word is reserved
 */
    bool is_reserved(const std::string& str);

/* forward reference */
    class ClassChecker;

    class AssignChecker;

    class Classes;

    class Stack;

    extern Classes *classes;

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

        virtual std::string infer(Stack &st) = 0;

        virtual void json(std::ostream &out, PrintContext &ctx) = 0;

        virtual void type_check(Stack &st) = 0;

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
        infer(Stack &st) override {
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
        type_check(Stack &st) override {
            for (Kind *el: _elements) {
                el->type_check(st);
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

        std::string infer(Stack &st) override;

        void json(std::ostream &out, PrintContext &ctx) override;

        void type_check(Stack &st) override;

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

        std::string infer(Stack &st) override {
            std::cerr << "Formal: nothing to be inferred\n";
            assert(false);
        }

        std::string get_signature() override {
            std::string sig;
            sig += _var->get_signature() + ": " + _type->get_signature();
            return sig;
        }

        void json(std::ostream &out, PrintContext &ctx) override;

        void type_check(Stack &st) override {}

        void code_gen(CodegenContext &ctx, Stack &st) override {}

        ~Formal() override {
            delete _var;
            delete _type;
        }
    };

    class Formals : public Seq<Formal> {
    public:
        explicit Formals(int line_no) : Seq("Formals", line_no) {}

        void type_check(Stack &st) override;

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
    };

    class Method : public ASTNode {
        friend class MethodChecker;

        Ident *_name;
        Formals *_formals;
        Ident *_returns;
        Block *_statements;
        std::string _owner;
        bool _overriden; /* is method an override?, will be set _input_file typechecking stage */
        bool _has_return; /* let the code generator know if there is't a return, take appropriate action */
        int _line_no;
    public:
        explicit Method(Ident *name, Formals *formals,
                        Ident *returns, Block *statements, int line_no, std::string owner = "Obj") :
                _name{name}, _formals{formals}, _returns{returns}, _owner{std::move(std::move(owner))}, /* default owner */
                _statements{statements}, _overriden{false}, _line_no{line_no} {}

        void json(std::ostream &out, PrintContext &ctx) override;

        void type_check(Stack &st) override;

        void code_gen(CodegenContext &ctx, Stack &st) override;

        std::string get_signature() override;

        bool
        isOverriden() {
            return _overriden;
        }

        void
        setOverride(bool x) {
            _overriden = x;
        }

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
        infer(Stack &st) override {
            return _returns->infer(st);
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
    };

    class Statement : public ASTNode {
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

        std::string infer(Stack &st) override {
            std::cerr << "Assign: nothing to be inferred\n";
            assert(false);
        }

        void json(std::ostream &out, PrintContext &ctx) override;

        void type_check(Stack &st) override;

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

        std::string infer(Stack &st) override {
            std::cerr << "void ast::AssignDeclare::infer(InferContext& _ctx, Stack& st)" <<
                      "\n*** Nothing to be inferred ***\n";
            assert(false);
        }

        void json(std::ostream &out, PrintContext &ctx) override;

        void type_check(Stack &st) override;

        void code_gen(CodegenContext &ctx, Stack &st) override;

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

        std::string infer(Stack &st) override;

        void json(std::ostream &out, PrintContext &ctx) override;

        void type_check(Stack &st) override;

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

        void type_check(Stack &st) override;

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
        infer(Stack &st) override {
            return _expr->infer(st);
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

        std::string infer(Stack &st) override {
            std::cerr << "If: nothing to be inferred\n";
            assert(false);
        }

        Block *get_true() const {
            return _true_part;
        }

        Block *get_false() const {
            return _false_part;
        }

        void json(std::ostream &out, PrintContext &ctx) override;

        void type_check(Stack &st) override;

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

        std::string infer(Stack &st) override {
            std::cerr << "While: nothing to be inferred\n";
            assert(false);
        }

        int get_line() override {
            return _line_no;
        }

        Block *getBody() const {
            return _body;
        }

        void json(std::ostream &out, PrintContext &ctx) override;

        void type_check(Stack &st) override;

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
        friend class ClassChecker;

        friend class ClassGenerator;

        Ident *_name;
        Ident *_super;
        Method *_constructor;
        Methods *_methods;
        /* attributes of class,
         * a name => type mapping */
        std::unordered_map<std::string, std::string> *_attributes;
        bool _builtin;
        int _line_no;
    public:
        Class(Ident *name, Ident *super, Method *constuctor, Methods *methods, int line_no, bool builtin = false) :
                _name{name}, _super{super}, _constructor{constuctor}, _methods{methods},
                _attributes{new std::unordered_map<std::string, std::string>}, _builtin{builtin}, _line_no{line_no} {}

        void json(std::ostream &out, PrintContext &ctx) override;

        void type_check(Stack &st) override;

        void code_gen(CodegenContext &ctx, Stack &st) override;

        void add_attr(const std::string& name, const std::string& type);

        bool has_attr(const std::string& attr);

        bool has_ancestor(const std::string& ancestor, Stack &st);

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

        std::unordered_map<std::string, std::string> *
        get_attributes() const {
            return _attributes;
        }

        Method *
        get_method(const std::string& method) const {
            for (auto i: _methods->get_elements())
                if (i->get_name() == method)
                    return i;
            return nullptr;
        }

        Methods *
        get_methods() const {
            return _methods;
        }

        bool
        is_builtin() {
            return _builtin;
        }

        auto
        get_attrs() const {
            return _attributes;
        }

        int
        type() override {
            return CLASS;
        }

        std::string
        infer(Stack &st) override {
            return _name->infer(st);
        }

        std::string get_signature() override {
            std::string sig;
            sig += "class " + get_name() + "(" + _constructor->get_formals()->get_signature()
                   + ") extends " + _super->get_signature();
            return sig;
        }

        ~Class() override {
            delete _name;
            delete _super;
            delete _constructor;
            delete _methods;
            delete _attributes;
        }
    };

    class Classes : public Seq<Class> {
    public:
        explicit Classes(int line_no) : Seq<Class>("Classes", line_no) {}

        void type_check(Stack &st) override;

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

        std::string infer(Stack &st) override {
            return "Int";
        }

        int get_line() override {
            return _line_no;
        }

        void json(std::ostream &out, PrintContext &ctx) override;

        void type_check(Stack &st) override {}

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

        std::string infer(Stack &st) override {
            std::cerr << "Type_Alternative: Nothing to be inferred\n";
            assert(false);
        }

        void json(std::ostream &out, PrintContext &ctx) override;

        void type_check(Stack &st) override {}

        void code_gen(CodegenContext &ctx, Stack &st) override {}

        std::string get_signature() override {
            return "";
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

        std::string infer(Stack &st) override {
            std::cerr << "Typecase: nothing to be inferred\n";
            assert(false);
        }

        void json(std::ostream &out, PrintContext &ctx) override;

        void type_check(Stack &st) override {}

        void code_gen(CodegenContext &ctx, Stack &st) override {}

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

        std::string infer(Stack &st) override {
            return "String";
        }

        void json(std::ostream &out, PrintContext &ctx) override;

        void type_check(Stack &st) override {}

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

        std::string infer(Stack &st) override;

        void type_check(Stack &st) override;

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

        std::string infer(Stack &st) override;

        void json(std::ostream &out, PrintContext &ctx) override;

        void type_check(Stack &st) override;

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

        std::string infer(Stack &st) override {
            return "Boolean";
        }

        void json(std::ostream &out, PrintContext &ctx) override;

        void type_check(Stack &st) override {}

        void code_gen(CodegenContext &ctx, Stack &st) override {}

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
    };

    class Or : public BinOp {
    public:
        explicit Or(ASTNode *left, ASTNode *right, int line_no) :
                BinOp("Or", left, right, line_no) {}
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

        std::string infer(Stack &st) override {
            return "Boolean";
        }

        int get_line() override {
            return _line_no;
        }

        void json(std::ostream &out, PrintContext &ctx) override;

        void type_check(Stack &st) override {}

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

        void type_check(Stack &st) override;

        void code_gen(CodegenContext &ctx, Stack &st) override;

        std::string infer(Stack &st) override;

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

        std::string infer(Stack &st) override {
            std::cerr << "Program: nothing to be inferred\n";
            assert(false);
        }

        void json(std::ostream &out, PrintContext &ctx) override;

        void type_check(Stack &st) override {
            std::cerr << "Program: nothing to be typechecked\n";
            assert(false);
        }

        /* this is the one actually used, stack is generated here */
        void code_gen(CodegenContext &ctx);

        void code_gen(CodegenContext &ctx, Stack &st) override {
            std::cerr << "Program: wrong codegen invoked\n";
            assert(false);
        }

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

