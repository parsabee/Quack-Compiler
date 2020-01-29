/* A Bison parser, made by GNU Bison 3.4.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_USERS_PARSABAGHERI_DEV_QUACK_COMPILER_CMAKE_BUILD_DEBUG_PARSER_HPP_INCLUDED
# define YY_YY_USERS_PARSABAGHERI_DEV_QUACK_COMPILER_CMAKE_BUILD_DEBUG_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"

    #include "all.hpp"
    #include "ast_node.hpp"
    int yylex();
    void yyerror(const char *msg);

#line 55 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.hpp"

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    CLASS = 258,
    DEF = 259,
    EXTENDS = 260,
    IF = 261,
    ELIF = 262,
    ELSE = 263,
    WHILE = 264,
    RETURN = 265,
    TYPECASE = 266,
    ATLEAST = 267,
    ATMOST = 268,
    EQUALS = 269,
    AND = 270,
    OR = 271,
    NOT = 272,
    IDENT = 273,
    INT_LIT = 274,
    STRING_LIT = 275,
    NEG = 276
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 23 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"

    /* Tokens */
    int   num;
    char*  str;
    /* Abstract syntax tree values */
    ast::ASTNode* node;
    ast::Class* clazz;
    ast::Ident* ident;
    ast::LExpr* l_expr;
    ast::Load*  load;
    ast::Formal* formal;
    ast::Method* method;
    ast::Statement* statement;
    ast::Expr* expr;
    ast::Methods* methods;
    ast::Formals* formals;
    ast::Actuals* actuals;
    ast::Block* block;
    ast::Classes* classes;
    ast::Type_Alternatives* type_alternatives;

#line 110 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_USERS_PARSABAGHERI_DEV_QUACK_COMPILER_CMAKE_BUILD_DEBUG_PARSER_HPP_INCLUDED  */
