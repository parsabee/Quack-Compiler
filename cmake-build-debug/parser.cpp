/* A Bison parser, made by GNU Bison 3.4.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.4.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1





# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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

#line 109 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"

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

#line 164 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"

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


/* Unqualified %code blocks.  */
#line 8 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"

    #include "msg.hpp"
    int report::num_errors = 0;
    ast::ASTNode *root = nullptr; /* root of AST */
    void yyerror(const char *msg) {
      report::num_errors++;
      fprintf(stderr, "%d: %s\n\n", yylloc.first_line, msg);
    }
    int yylex_destroy();

#line 206 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   430

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  79
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  142

#define YYUNDEFTOK  2
#define YYMAXUTOK   276

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      29,    30,    25,    23,    33,    24,    28,    26,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    34,    35,
      22,    36,    21,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    31,     2,    32,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    27
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   117,   117,   122,   123,   129,   130,   142,   148,   149,
     154,   161,   162,   166,   167,   170,   172,   177,   179,   190,
     191,   194,   197,   198,   199,   202,   203,   205,   208,   210,
     227,   231,   234,   236,   243,   252,   253,   262,   263,   270,
     273,   274,   277,   280,   281,   283,   291,   292,   295,   297,
     299,   310,   320,   321,   336,   337,   341,   342,   352,   353,
     354,   355,   356,   359,   360,   361,   362,   363,   365,   366,
     367,   368,   383,   386,   389,   390,   393,   395,   397,   401
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CLASS", "DEF", "EXTENDS", "IF", "ELIF",
  "ELSE", "WHILE", "RETURN", "TYPECASE", "ATLEAST", "ATMOST", "EQUALS",
  "AND", "OR", "NOT", "IDENT", "INT_LIT", "STRING_LIT", "'>'", "'<'",
  "'+'", "'-'", "'*'", "'/'", "NEG", "'.'", "'('", "')'", "'{'", "'}'",
  "','", "':'", "';'", "'='", "$accept", "pgm", "classes", "statements",
  "class", "optExtends", "formals", "formals_nonempty", "formal",
  "methods", "method", "optReturnType", "statement_block", "statement",
  "opt_elif_parts", "type_alternatives", "l_expr", "expr", "actual_args",
  "actual_args_nonempty", "ident", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,    62,    60,    43,    45,    42,    47,   276,    46,    40,
      41,   123,   125,    44,    58,    59,    61
};
# endif

#define YYPACT_NINF -53

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-53)))

#define YYTABLE_NINF -76

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-76)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -53,    33,    62,   -53,   -11,   286,   -53,   -53,    13,   -53,
     299,   299,    73,   299,   299,   -53,   -53,   299,   299,   -53,
      37,   123,   -18,   -53,   -11,   -53,   231,   231,   -53,   317,
     257,   370,   -10,   334,    14,   299,   -53,   299,   299,   299,
     299,   299,   299,   299,   299,   299,   299,   299,    16,   -53,
     102,     5,    54,   -53,     2,   -53,   -53,    78,   -53,   -53,
     -53,     9,   -53,   -53,    53,   140,   402,   387,    44,   370,
     370,   387,   402,    50,    50,   -10,   -10,   -53,    66,   353,
      64,     7,   -53,    95,   -11,   -53,   -11,   210,   299,     8,
     -53,   -53,    -6,   299,   -53,   -53,   102,   -53,   -53,   299,
     -11,    12,   -53,   -53,   -53,   231,   -53,   -53,     4,   158,
      71,   353,   -53,   -53,   -53,    78,   -53,    59,   -53,   -53,
     -53,   186,   -53,   -53,     8,    27,   -53,    63,   -53,   -53,
     -53,    18,   -53,   -11,    15,   -53,    72,    65,     8,   -53,
     -53,   -53
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     6,     1,     0,     0,     3,    79,     0,    55,
       0,     0,     0,     0,     0,    57,    56,     0,     0,     5,
      54,     0,    51,     8,    14,    54,     0,     0,    36,     0,
       0,    70,    62,     0,     0,     0,    38,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    37,
       0,     0,    13,    16,     0,    29,     6,    33,    34,    35,
      40,     0,    71,    50,     0,     0,    64,    66,    63,    68,
      69,    65,    67,    60,    61,    58,    59,    53,    52,    77,
       0,     0,     9,    12,     0,    18,     0,     0,     0,     0,
      30,    41,     0,     0,    48,    46,     0,    73,    78,     0,
       0,     0,    15,    17,    28,     0,    32,    39,     0,     0,
       0,    76,    11,    10,     6,    33,    44,     0,    49,    47,
      72,     0,    31,    45,     0,     0,    42,     0,     7,    19,
      22,     0,    23,    14,     0,    24,    26,     0,     0,    27,
      25,    21
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -53,   -53,   -53,   -52,   -53,   -53,   -28,   -53,    25,   -53,
     -53,   -53,   -26,   -53,    -1,   -53,    -3,    11,    19,   -53,
      -4
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     5,     6,   101,    51,    52,    53,   125,
     129,   138,    57,    19,    90,    92,    25,    21,    80,    81,
      22
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
       8,    58,    20,    85,    87,   116,    82,     7,    98,    55,
      91,    50,     7,   113,    23,    63,   135,    77,    48,   132,
      54,    26,    27,    29,    30,    31,   107,   -43,    32,    33,
      64,   127,     7,     3,     7,    83,    86,   -74,   117,    56,
      99,   -43,    24,   114,    78,   136,    65,   133,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,   128,
     123,    79,   121,   106,   130,     4,   139,    44,    45,    46,
      47,    34,    48,    35,     9,    46,    47,     7,    48,   115,
      54,     7,   103,     7,    20,    88,    89,    84,   108,    93,
      14,     7,    15,    16,    97,    96,   112,    17,   126,   105,
     100,   120,    18,     9,   109,   134,   137,    79,    28,   102,
     111,     0,   141,   124,   122,   110,     0,     0,    20,    14,
       7,    15,    16,   131,    36,     0,    17,     0,     0,    54,
       0,    18,   -75,   140,     0,    37,    38,    39,    40,    41,
       0,    94,     0,     0,    42,    43,    44,    45,    46,    47,
       0,    48,    37,    38,    39,    40,    41,     0,    49,   118,
       0,    42,    43,    44,    45,    46,    47,     0,    48,     0,
      37,    38,    39,    40,    41,    95,     0,     0,     0,    42,
      43,    44,    45,    46,    47,     0,    48,     9,     0,     0,
     -20,     0,    10,   119,     0,    11,    12,    13,     0,     0,
       0,     0,     0,    14,     7,    15,    16,     0,     0,     0,
      17,     9,     0,     0,     0,    18,    10,     0,   -20,    11,
      12,    13,     0,     0,     0,     0,     0,    14,     7,    15,
      16,     0,    55,     0,    17,     0,     0,     0,     0,    18,
       0,     0,   104,    37,    38,    39,    40,    41,     0,     0,
       0,     0,    42,    43,    44,    45,    46,    47,    60,    48,
       0,     0,    56,     0,     0,     0,     0,     0,     0,    37,
      38,    39,    40,    41,     0,     0,     0,     0,    42,    43,
      44,    45,    46,    47,     0,    48,    -2,     9,    61,     0,
       0,     0,    10,     0,     0,    11,    12,    13,     0,     0,
       9,     0,     0,    14,     7,    15,    16,     0,     0,     0,
      17,     0,     0,     0,     0,    18,    14,     7,    15,    16,
       0,     0,     0,    17,     0,     0,     0,     0,    18,    37,
      38,    39,    40,    41,     0,     0,     0,     0,    42,    43,
      44,    45,    46,    47,     0,    48,    37,    38,    39,    40,
      41,     0,    59,     0,     0,    42,    43,    44,    45,    46,
      47,     0,    48,     0,    62,    37,    38,    39,    40,    41,
       0,     0,     0,     0,    42,    43,    44,    45,    46,    47,
       0,    48,    37,    38,    39,     0,     0,     0,     0,     0,
       0,    42,    43,    44,    45,    46,    47,     0,    48,    37,
     -76,    39,     0,     0,     0,     0,     0,     0,   -76,    43,
      44,    45,    46,    47,   -76,    48,    39,     0,     0,     0,
       0,     0,     0,     0,   -76,    44,    45,    46,    47,     0,
      48
};

static const yytype_int16 yycheck[] =
{
       4,    27,     5,     1,    56,     1,     1,    18,     1,     1,
       1,    29,    18,     1,     1,     1,     1,     1,    28,     1,
      24,    10,    11,    12,    13,    14,    32,    18,    17,    18,
      34,     4,    18,     0,    18,    30,    34,    30,    34,    31,
      33,    32,    29,    31,    48,    30,    35,    29,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    32,
       1,    50,   114,    89,     1,     3,     1,    23,    24,    25,
      26,    34,    28,    36,     1,    25,    26,    18,    28,   105,
      84,    18,    86,    18,    87,     7,     8,    33,    92,    36,
      17,    18,    19,    20,    30,    29,   100,    24,   124,    88,
       5,    30,    29,     1,    93,   133,    34,    96,    35,    84,
      99,    -1,   138,   117,   115,    96,    -1,    -1,   121,    17,
      18,    19,    20,   127,     1,    -1,    24,    -1,    -1,   133,
      -1,    29,    30,   137,    -1,    12,    13,    14,    15,    16,
      -1,     1,    -1,    -1,    21,    22,    23,    24,    25,    26,
      -1,    28,    12,    13,    14,    15,    16,    -1,    35,     1,
      -1,    21,    22,    23,    24,    25,    26,    -1,    28,    -1,
      12,    13,    14,    15,    16,    35,    -1,    -1,    -1,    21,
      22,    23,    24,    25,    26,    -1,    28,     1,    -1,    -1,
       4,    -1,     6,    35,    -1,     9,    10,    11,    -1,    -1,
      -1,    -1,    -1,    17,    18,    19,    20,    -1,    -1,    -1,
      24,     1,    -1,    -1,    -1,    29,     6,    -1,    32,     9,
      10,    11,    -1,    -1,    -1,    -1,    -1,    17,    18,    19,
      20,    -1,     1,    -1,    24,    -1,    -1,    -1,    -1,    29,
      -1,    -1,    32,    12,    13,    14,    15,    16,    -1,    -1,
      -1,    -1,    21,    22,    23,    24,    25,    26,     1,    28,
      -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    12,
      13,    14,    15,    16,    -1,    -1,    -1,    -1,    21,    22,
      23,    24,    25,    26,    -1,    28,     0,     1,    31,    -1,
      -1,    -1,     6,    -1,    -1,     9,    10,    11,    -1,    -1,
       1,    -1,    -1,    17,    18,    19,    20,    -1,    -1,    -1,
      24,    -1,    -1,    -1,    -1,    29,    17,    18,    19,    20,
      -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    29,    12,
      13,    14,    15,    16,    -1,    -1,    -1,    -1,    21,    22,
      23,    24,    25,    26,    -1,    28,    12,    13,    14,    15,
      16,    -1,    35,    -1,    -1,    21,    22,    23,    24,    25,
      26,    -1,    28,    -1,    30,    12,    13,    14,    15,    16,
      -1,    -1,    -1,    -1,    21,    22,    23,    24,    25,    26,
      -1,    28,    12,    13,    14,    -1,    -1,    -1,    -1,    -1,
      -1,    21,    22,    23,    24,    25,    26,    -1,    28,    12,
      13,    14,    -1,    -1,    -1,    -1,    -1,    -1,    21,    22,
      23,    24,    25,    26,    12,    28,    14,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    22,    23,    24,    25,    26,    -1,
      28
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    38,    39,     0,     3,    40,    41,    18,    57,     1,
       6,     9,    10,    11,    17,    19,    20,    24,    29,    50,
      53,    54,    57,     1,    29,    53,    54,    54,    35,    54,
      54,    54,    54,    54,    34,    36,     1,    12,    13,    14,
      15,    16,    21,    22,    23,    24,    25,    26,    28,    35,
      29,    43,    44,    45,    57,     1,    31,    49,    49,    35,
       1,    31,    30,     1,    57,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,     1,    57,    54,
      55,    56,     1,    30,    33,     1,    34,    40,     7,     8,
      51,     1,    52,    36,     1,    35,    29,    30,     1,    33,
       5,    42,    45,    57,    32,    54,    49,    32,    57,    54,
      55,    54,    57,     1,    31,    49,     1,    34,     1,    35,
      30,    40,    51,     1,    57,    46,    49,     4,    32,    47,
       1,    57,     1,    29,    43,     1,    30,    34,    48,     1,
      57,    49
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    37,    38,    39,    39,    40,    40,    41,    41,    41,
      41,    42,    42,    43,    43,    44,    44,    45,    45,    46,
      46,    47,    47,    47,    47,    48,    48,    48,    49,    49,
      50,    51,    51,    51,    50,    50,    50,    50,    50,    50,
      50,    50,    52,    52,    52,    52,    50,    50,    50,    50,
      50,    53,    53,    53,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    55,    55,    56,    56,    56,    57
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     0,     2,     0,    10,     3,     5,
       7,     2,     0,     1,     0,     3,     1,     3,     2,     2,
       0,     7,     2,     3,     5,     2,     0,     2,     3,     1,
       4,     4,     2,     0,     3,     3,     2,     2,     2,     5,
       3,     4,     5,     0,     3,     4,     4,     6,     4,     6,
       3,     1,     3,     3,     1,     1,     1,     1,     3,     3,
       3,     3,     2,     3,     3,     3,     3,     3,     3,     3,
       2,     3,     6,     4,     1,     0,     3,     1,     2,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yynewstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 117 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.node) = new ast::Program((yyvsp[-1].classes), (yyvsp[0].block), (yyloc).first_line); root = (yyval.node);
                                      yylex_destroy(); }
#line 1537 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 3:
#line 122 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.classes) = (yyvsp[-1].classes); (yyval.classes)->append((yyvsp[0].clazz)); }
#line 1543 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 4:
#line 123 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.classes) = new ast::Classes((yyloc).first_line); }
#line 1549 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 5:
#line 129 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.block) = (yyvsp[-1].block); (yyval.block)->append((yyvsp[0].statement)); }
#line 1555 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 6:
#line 130 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.block) = new ast::Block((yyloc).first_line); }
#line 1561 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 7:
#line 142 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    {
                                      ast::Ident *constructor_name = new ast::Ident((yyvsp[-8].ident)->get_text(), (yyloc).first_line);
                                      ast::Ident *return_type = new ast::Ident((yyvsp[-8].ident)->get_text(), (yyloc).first_line);
                                      ast::Method *constructor = new ast::Method(constructor_name, (yyvsp[-6].formals), return_type, (yyvsp[-2].block), (yyloc).first_line);
                                      (yyval.clazz) = new ast::Class((yyvsp[-8].ident), (yyvsp[-4].ident), constructor, (yyvsp[-1].methods), (yyloc).first_line); }
#line 1571 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 8:
#line 148 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.clazz) = new ast::Class((yyvsp[-1].ident), nullptr, nullptr, nullptr, (yyloc).first_line); }
#line 1577 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 9:
#line 149 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { 
                                      ast::Ident *constructor_name = new ast::Ident(*(yyvsp[-3].ident));
                                      ast::Ident *return_type = new ast::Ident(*(yyvsp[-3].ident));
                                      ast::Method *constructor = new ast::Method(constructor_name, (yyvsp[-1].formals), return_type, nullptr, (yyloc).first_line);
                                      (yyval.clazz) = new ast::Class((yyvsp[-3].ident), nullptr, constructor, nullptr, (yyloc).first_line); }
#line 1587 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 10:
#line 154 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    {
                                      ast::Ident *constructor_name = new ast::Ident(*(yyvsp[-5].ident));
                                      ast::Ident *return_type = new ast::Ident(*(yyvsp[-5].ident));
                                      ast::Method *constructor = new ast::Method(constructor_name, (yyvsp[-3].formals), return_type, nullptr, (yyloc).first_line);
                                      (yyval.clazz) = new ast::Class((yyvsp[-5].ident), (yyvsp[-1].ident), constructor, nullptr, (yyloc).first_line); }
#line 1597 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 11:
#line 161 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.ident) = (yyvsp[0].ident); }
#line 1603 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 12:
#line 162 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.ident) = new ast::Ident("Obj", (yyloc).first_line); }
#line 1609 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 13:
#line 166 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.formals) = (yyvsp[0].formals); }
#line 1615 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 14:
#line 167 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.formals) = new ast::Formals((yyloc).first_line); }
#line 1621 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 15:
#line 170 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { 
                                      (yyval.formals) = (yyvsp[-2].formals); (yyval.formals)->append((yyvsp[0].formal)); }
#line 1628 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 16:
#line 172 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.formals) = new ast::Formals((yyloc).first_line); 
                                      (yyval.formals)->append((yyvsp[0].formal)); }
#line 1635 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 17:
#line 177 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.formal) = new ast::Formal((yyvsp[-2].ident), (yyvsp[0].ident), (yyloc).first_line); }
#line 1641 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 18:
#line 179 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.formal) = new ast::Formal((yyvsp[-1].ident), nullptr, (yyloc).first_line); }
#line 1647 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 19:
#line 190 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.methods) = (yyvsp[-1].methods); (yyval.methods)->append((yyvsp[0].method)); }
#line 1653 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 20:
#line 191 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.methods) = new ast::Methods( (yyloc).first_line); }
#line 1659 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 21:
#line 194 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { 
                                      (yyval.method) = new ast::Method((yyvsp[-5].ident), (yyvsp[-3].formals), (yyvsp[-1].ident), (yyvsp[0].block), (yyloc).first_line); }
#line 1666 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 22:
#line 197 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.method) = nullptr; }
#line 1672 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 23:
#line 198 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.method) = new ast::Method((yyvsp[-1].ident), nullptr, nullptr, nullptr, (yyloc).first_line); }
#line 1678 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 24:
#line 199 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.method) = new ast::Method((yyvsp[-3].ident), (yyvsp[-1].formals), nullptr, nullptr, (yyloc).first_line); }
#line 1684 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 25:
#line 202 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.ident) = (yyvsp[0].ident); }
#line 1690 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 26:
#line 203 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.ident) = new ast::Ident("Nothing",(yyloc).first_line); }
#line 1696 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 27:
#line 205 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.ident) = nullptr; }
#line 1702 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 28:
#line 208 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.block) = (yyvsp[-1].block);}
#line 1708 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 29:
#line 210 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.block) = nullptr; }
#line 1714 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 30:
#line 227 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { 
                                      (yyval.statement) = new ast::If((yyvsp[-2].expr), (yyvsp[-1].block), (yyvsp[0].block), (yyloc).first_line); }
#line 1721 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 31:
#line 231 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { 
                                      (yyval.block) = new ast::Block((yyloc).first_line);
                                      (yyval.block)->append(new ast::If((yyvsp[-2].expr), (yyvsp[-1].block), (yyvsp[0].block), (yyloc).first_line)); }
#line 1729 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 32:
#line 234 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { 
                                      (yyval.block) = (yyvsp[0].block); }
#line 1736 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 33:
#line 236 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.block) = new ast::Block((yyloc).first_line); }
#line 1742 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 34:
#line 243 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { 
                                      (yyval.statement) = new ast::While((yyvsp[-1].expr), (yyvsp[0].block), (yyloc).first_line); }
#line 1749 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 35:
#line 252 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.statement) = new ast::Return((yyvsp[-1].expr), (yyloc).first_line); }
#line 1755 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 36:
#line 253 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.statement) = new ast::Return(new ast::Ident("Nothing", (yyloc).first_line), (yyloc).first_line); }
#line 1761 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 37:
#line 262 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.statement) = (yyvsp[-1].expr); }
#line 1767 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 38:
#line 263 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.statement) = nullptr; delete (yyvsp[-1].expr); }
#line 1773 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 39:
#line 270 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { 
                                      (yyval.statement) = new ast::Typecase((yyvsp[-3].expr), (yyvsp[-1].type_alternatives), (yyloc).first_line); }
#line 1780 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 40:
#line 273 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.statement) = new ast::Typecase((yyvsp[-1].expr), nullptr, (yyloc).first_line); }
#line 1786 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 41:
#line 274 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.statement) = new ast::Typecase((yyvsp[-2].expr), nullptr, (yyloc).first_line); }
#line 1792 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 42:
#line 277 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { 
                                      (yyval.type_alternatives) = (yyvsp[-4].type_alternatives);
                                      (yyval.type_alternatives)->append(new ast::Type_Alternative((yyvsp[-3].ident), (yyvsp[-1].ident), (yyvsp[0].block), (yyloc).first_line)); }
#line 1800 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 43:
#line 280 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.type_alternatives) = new ast::Type_Alternatives((yyloc).first_line); }
#line 1806 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 44:
#line 281 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { 
                                      delete (yyvsp[-1].ident); (yyval.type_alternatives) = nullptr; }
#line 1813 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 45:
#line 283 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { 
                                      delete (yyvsp[-2].ident); (yyval.type_alternatives) = nullptr; }
#line 1820 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 46:
#line 291 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.statement) = new ast::Assign((yyvsp[-3].l_expr), (yyvsp[-1].expr), (yyloc).first_line); }
#line 1826 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 47:
#line 293 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.statement) = new ast::AssignDeclare((yyvsp[-5].l_expr), (yyvsp[-1].expr), (yyvsp[-3].ident), (yyloc).first_line); }
#line 1832 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 48:
#line 296 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.statement) = new ast::Assign((yyvsp[-3].l_expr), (yyvsp[-1].expr), (yyloc).first_line); }
#line 1838 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 49:
#line 298 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.statement) = new ast::AssignDeclare((yyvsp[-5].l_expr), (yyvsp[-1].expr), (yyvsp[-3].ident), (yyloc).first_line); }
#line 1844 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 50:
#line 299 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.statement) = new ast::AssignDeclare((yyvsp[-2].l_expr), nullptr, nullptr, (yyloc).first_line); }
#line 1850 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 51:
#line 310 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.l_expr) = (yyvsp[0].ident); }
#line 1856 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 52:
#line 320 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.l_expr) = new ast::Dot((yyvsp[-2].expr), (yyvsp[0].ident), (yyloc).first_line); }
#line 1862 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 53:
#line 321 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.l_expr) = new ast::Dot((yyvsp[-2].expr), nullptr, (yyloc).first_line); }
#line 1868 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 54:
#line 336 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.expr) = new ast::Load((yyvsp[0].l_expr), (yyloc).first_line); }
#line 1874 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 55:
#line 337 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.expr) = nullptr; }
#line 1880 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 56:
#line 341 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.expr) = new ast::StrConst((yyvsp[0].str), (yyloc).first_line); free((yyvsp[0].str)); }
#line 1886 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 57:
#line 342 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.expr) = new ast::IntConst((yyvsp[0].num), (yyloc).first_line); }
#line 1892 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 58:
#line 352 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.expr) = ast::Call::binop("TIMES", (yyvsp[-2].expr), (yyvsp[0].expr), (yyloc).first_line); }
#line 1898 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 59:
#line 353 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.expr) = ast::Call::binop("DIV", (yyvsp[-2].expr), (yyvsp[0].expr), (yyloc).first_line); }
#line 1904 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 60:
#line 354 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.expr) = ast::Call::binop("PLUS", (yyvsp[-2].expr), (yyvsp[0].expr), (yyloc).first_line); }
#line 1910 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 61:
#line 355 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.expr) = ast::Call::binop("MINUS", (yyvsp[-2].expr), (yyvsp[0].expr), (yyloc).first_line); }
#line 1916 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 62:
#line 356 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { auto zero = new ast::IntConst(0, (yyloc).first_line);
                                      (yyval.expr) = ast::Call::binop("MINUS", zero, (yyvsp[0].expr), (yyloc).first_line); }
#line 1923 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 63:
#line 359 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.expr) = ast::Call::binop("EQUALS", (yyvsp[-2].expr), (yyvsp[0].expr), (yyloc).first_line); }
#line 1929 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 64:
#line 360 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.expr) = ast::Call::binop("ATLEAST", (yyvsp[-2].expr), (yyvsp[0].expr), (yyloc).first_line); }
#line 1935 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 65:
#line 361 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.expr) = ast::Call::binop("MORE", (yyvsp[-2].expr), (yyvsp[0].expr), (yyloc).first_line); }
#line 1941 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 66:
#line 362 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.expr) = ast::Call::binop("ATMOST", (yyvsp[-2].expr), (yyvsp[0].expr), (yyloc).first_line); }
#line 1947 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 67:
#line 363 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.expr) = ast::Call::binop("MORE", (yyvsp[-2].expr), (yyvsp[0].expr), (yyloc).first_line); }
#line 1953 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 68:
#line 365 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.expr) = new ast::And((yyvsp[-2].expr), (yyvsp[0].expr), (yyloc).first_line); }
#line 1959 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 69:
#line 366 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.expr) = new ast::Or((yyvsp[-2].expr), (yyvsp[0].expr), (yyloc).first_line); }
#line 1965 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 70:
#line 367 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.expr) = new ast::Not((yyvsp[0].expr), (yyloc).first_line); }
#line 1971 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 71:
#line 368 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 1977 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 72:
#line 383 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { 
                                      (yyval.expr) = new ast::Call((yyvsp[-5].expr), (yyvsp[-3].ident), (yyvsp[-1].actuals), (yyloc).first_line); }
#line 1984 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 73:
#line 386 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.expr) = new ast::Construct((yyvsp[-3].ident), (yyvsp[-1].actuals), (yyloc).first_line); }
#line 1990 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 74:
#line 389 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.actuals) = (yyvsp[0].actuals); }
#line 1996 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 75:
#line 390 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.actuals) = new ast::Actuals((yyloc).first_line); }
#line 2002 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 76:
#line 393 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { 
                                      (yyval.actuals) = (yyvsp[-2].actuals); (yyval.actuals)->append((yyvsp[0].expr)); }
#line 2009 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 77:
#line 395 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.actuals) = new ast::Actuals((yyloc).first_line); (yyval.actuals)->append((yyvsp[0].expr)); }
#line 2015 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 78:
#line 397 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { 
                                      (yyval.actuals) = (yyvsp[-1].actuals); }
#line 2022 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;

  case 79:
#line 401 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"
    { (yyval.ident) = new ast::Ident((yyvsp[0].str), (yyloc).first_line); free((yyvsp[0].str)); }
#line 2028 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"
    break;


#line 2032 "/Users/parsabagheri/dev/Quack-Compiler/cmake-build-debug/parser.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 404 "/Users/parsabagheri/dev/Quack-Compiler/src/qk.ypp"

