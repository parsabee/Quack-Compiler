#include "qk_builtins.hpp"

#include <utility>

namespace ast {

    static Formals *hasOther(std::string type_) {
        auto *frmls = new Formals(-1);
        frmls->append(new Formal(new Ident("other", -1), new Ident(std::move(type_), -1), -1));
        return frmls;
    }

    static Methods *primitive_methods(std::string other) {
        auto *mthds = new Methods(-1);

        mthds->append(new Method(
                new Ident("EQUALS", -1),
                hasOther(std::move(other)),
                new Ident("Boolean", -1),
                new Block(-1),
                -1
        ));

        mthds->append(new Method(
                new Ident("PRINT", -1),
                new Formals(-1),
                new Ident("Obj", -1),
                new Block(-1),
                -1
        ));

        mthds->append(new Method(
                new Ident("STR", -1),
                new Formals(-1),
                new Ident("String", -1),
                new Block(-1),
                -1
        ));

        return mthds;
    }

    Class *Obj_class() {
        Methods *mthds = primitive_methods("Obj");
        auto *c = new Class(
                new Ident("Obj", -1),
                new Ident("", -1),
                new Method(new Ident("Obj", -1), new Formals(-1),
                           new Ident("Obj", -1), new Block(-1), -1),  // Constructor
                mthds,
                -1,
                true
        );
        return c;
    }

    Class *String_class() {
        auto *mthds = new Methods(-1);
        mthds->append(new Method(new Ident("EQUALS", -1), hasOther("Obj"),
                                 new Ident("Boolean", -1), new Block(-1), -1, "String"));
        mthds->append(new Method(new Ident("STR", -1), new Formals(-1),
                                 new Ident("String", -1), new Block(-1), -1, "String"));
        mthds->append(new Method(new Ident("ATLEAST", -1), hasOther("String"),
                                 new Ident("Boolean", -1), new Block(-1), -1, "String"));
        mthds->append(new Method(new Ident("ATMOST", -1), hasOther("String"),
                                 new Ident("Boolean", -1), new Block(-1), -1, "String"));
        mthds->append(new Method(new Ident("LESS", -1), hasOther("String"),
                                 new Ident("Boolean", -1), new Block(-1), -1, "String"));
        mthds->append(new Method(new Ident("MORE", -1), hasOther("String"),
                                 new Ident("Boolean", -1), new Block(-1), -1, "String"));
        mthds->append(new Method(new Ident("PLUS", -1), hasOther("String"),
                                 new Ident("String", -1), new Block(-1), -1, "String"));
        auto *c = new Class(
                new Ident("String", -1),
                new Ident("Obj", -1),
                new Method(new Ident("String", -1), new Formals(-1),
                           new Ident("String", -1), new Block(-1), -1),  // Constructor
                mthds,
                -1,
                true
        );
        return c;
    }

    Class *Integer_class() {
        auto *mthds = new Methods(-1);
        mthds->append(new Method(new Ident("EQUALS", -1), hasOther("Obj"),
                                 new Ident("Boolean", -1), new Block(-1), -1, "Int"));
        mthds->append(new Method(new Ident("STR", -1), new Formals(-1),
                                 new Ident("String", -1), new Block(-1), -1, "Int"));
        mthds->append(new Method(new Ident("ATLEAST", -1), hasOther("Int"),
                                 new Ident("Boolean", -1), new Block(-1), -1, "Int"));
        mthds->append(new Method(new Ident("ATMOST", -1), hasOther("Int"),
                                 new Ident("Boolean", -1), new Block(-1), -1, "Int"));
        mthds->append(new Method(new Ident("DIVIDE", -1), hasOther("Int"),
                                 new Ident("Int", -1), new Block(-1), -1, "Int"));
        mthds->append(new Method(new Ident("LESS", -1), hasOther("Int"),
                                 new Ident("Boolean", -1), new Block(-1), -1, "Int"));
        mthds->append(new Method(new Ident("MINUS", -1), hasOther("Int"),
                                 new Ident("Int", -1), new Block(-1), -1, "Int"));
        mthds->append(new Method(new Ident("MORE", -1), hasOther("Int"),
                                 new Ident("Boolean", -1), new Block(-1), -1, "Int"));
        mthds->append(new Method(new Ident("PLUS", -1), hasOther("Int"),
                                 new Ident("Int", -1), new Block(-1), -1, "Int"));
        mthds->append(new Method(new Ident("TIMES", -1), hasOther("Int"),
                                 new Ident("Int", -1), new Block(-1), -1, "Int"));

        auto *c = new Class(
                new Ident("Int", -1),
                new Ident("Obj", -1),
                new Method(new Ident("Int", -1), new Formals(-1),
                           new Ident("Int", -1), new Block(-1), -1),  // Constructor
                mthds,
                -1,
                true
        );
        return c;
    }

    Class *Boolean_class() {
        auto *mthds = new Methods(-1);
        mthds->append(new Method(new Ident("STR", -1), new Formals(-1),
                                 new Ident("Boolean", -1), new Block(-1), -1, "Boolean"));
        auto *c = new Class(
                new Ident("Boolean", -1),
                new Ident("Obj", -1),
                new Method(new Ident("Boolean", -1), new Formals(-1),
                           new Ident("Boolean", -1), new Block(-1), -1),  // Constructor
                mthds,
                -1,
                true
        );
        return c;
    }

    Class *Nothing_class() {
        auto *mthds = new Methods(-1);
        mthds->append(new Method(new Ident("STR", -1), new Formals(-1),
                                 new Ident("Boolean", -1), new Block(-1), -1, "Nothing"));
        auto *c = new Class(
                new Ident("Nothing", -1),
                new Ident("Obj", -1),
                new Method(new Ident("Nothing", -1), new Formals(-1),
                           new Ident("Nothing", -1), new Block(-1), -1),  // Constructor
                mthds,
                -1,
                true
        );
        return c;
    }

}
