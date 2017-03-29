/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "jac.y" /* yacc.c:339  */

	#include <stdio.h>
	#include <stdlib.h>

	#include "ast.h"

	int yylex(void);
	void yyerror(const char *s);

	extern node_t* ast_root;
	extern char* yytext;
	extern int line, col, yyleng;

#line 80 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    BOOL = 258,
    BOOLLIT = 259,
    CLASS = 260,
    DO = 261,
    DOTLENGTH = 262,
    DOUBLE = 263,
    ELSE = 264,
    IF = 265,
    INT = 266,
    PARSEINT = 267,
    PRINT = 268,
    PUBLIC = 269,
    RETURN = 270,
    STATIC = 271,
    STRING = 272,
    VOID = 273,
    WHILE = 274,
    OCURV = 275,
    CCURV = 276,
    OBRACE = 277,
    CBRACE = 278,
    OSQUARE = 279,
    CSQUARE = 280,
    AND = 281,
    OR = 282,
    LT = 283,
    GT = 284,
    EQ = 285,
    NEQ = 286,
    LEQ = 287,
    GEQ = 288,
    PLUS = 289,
    MINUS = 290,
    STAR = 291,
    DIV = 292,
    MOD = 293,
    NOT = 294,
    ASSIGN = 295,
    SEMI = 296,
    COMMA = 297,
    RESERVED = 298,
    STRLIT = 299,
    ID = 300,
    DECLIT = 301,
    REALLIT = 302,
    NO_ELSE = 303
  };
#endif
/* Tokens.  */
#define BOOL 258
#define BOOLLIT 259
#define CLASS 260
#define DO 261
#define DOTLENGTH 262
#define DOUBLE 263
#define ELSE 264
#define IF 265
#define INT 266
#define PARSEINT 267
#define PRINT 268
#define PUBLIC 269
#define RETURN 270
#define STATIC 271
#define STRING 272
#define VOID 273
#define WHILE 274
#define OCURV 275
#define CCURV 276
#define OBRACE 277
#define CBRACE 278
#define OSQUARE 279
#define CSQUARE 280
#define AND 281
#define OR 282
#define LT 283
#define GT 284
#define EQ 285
#define NEQ 286
#define LEQ 287
#define GEQ 288
#define PLUS 289
#define MINUS 290
#define STAR 291
#define DIV 292
#define MOD 293
#define NOT 294
#define ASSIGN 295
#define SEMI 296
#define COMMA 297
#define RESERVED 298
#define STRLIT 299
#define ID 300
#define DECLIT 301
#define REALLIT 302
#define NO_ELSE 303

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 19 "jac.y" /* yacc.c:355  */

	char *str;
	struct node *node;

#line 221 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 238 "y.tab.c" /* yacc.c:358  */

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
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
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
#  define YYSIZE_T unsigned int
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

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
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
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   356

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  91
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  180

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   303

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    41,    41,    43,    44,    46,    47,    48,    50,    52,
      53,    55,    56,    58,    60,    61,    63,    64,    66,    67,
      69,    71,    72,    74,    76,    77,    78,    80,    82,    83,
      85,    86,    87,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   104,   105,   107,
     109,   110,   112,   113,   115,   116,   118,   119,   121,   122,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   151,   153,   155,   157,   159,
     161,   163
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "BOOL", "BOOLLIT", "CLASS", "DO",
  "DOTLENGTH", "DOUBLE", "ELSE", "IF", "INT", "PARSEINT", "PRINT",
  "PUBLIC", "RETURN", "STATIC", "STRING", "VOID", "WHILE", "OCURV",
  "CCURV", "OBRACE", "CBRACE", "OSQUARE", "CSQUARE", "AND", "OR", "LT",
  "GT", "EQ", "NEQ", "LEQ", "GEQ", "PLUS", "MINUS", "STAR", "DIV", "MOD",
  "NOT", "ASSIGN", "SEMI", "COMMA", "RESERVED", "STRLIT", "ID", "DECLIT",
  "REALLIT", "NO_ELSE", "$accept", "Program", "ProgramAux", "ProgramL",
  "ClassDecl", "FieldDecl", "CommaId", "MethodDecl", "MethodHeader",
  "MethodParams", "ParamDecl", "StringArray", "CommaTypeId", "MethodBody",
  "MethodBodyL", "VarDecl", "VarDeclAux", "Type", "Statement",
  "StatementEmpty", "Assignment", "MethodInvocation", "MethodInvAux",
  "CommaExpr", "ParseArgs", "Expr", "ExprL", "IDAux", "IDAuxVar",
  "BoolAux", "DecAux", "RealAux", "StrAux", "VoidAux", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303
};
# endif

#define YYPACT_NINF -28

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-28)))

#define YYTABLE_NINF -54

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      19,   -20,    18,     7,   -28,   -28,   -28,   -28,    13,    28,
      65,   -28,   -28,   -28,   -28,   -28,   -28,    27,   -28,   -28,
     -28,   -28,    63,   -20,   -20,   -28,   -28,    64,    66,   198,
      23,   -22,    23,    46,   240,    70,    71,    72,   245,    73,
     213,   -28,   -28,   -28,   -20,   -28,    67,    68,    74,    -8,
      83,    90,   -28,   -20,   -20,   -28,   -20,    95,   -28,    98,
     283,     2,   262,   -28,   151,   283,   283,   283,   -28,   -28,
     -28,   -28,   -28,   -28,    78,   305,     1,   -28,   -28,   -28,
     283,   213,    99,    41,   -28,   -28,   -28,   -28,   -28,   119,
     283,   100,   -28,   -28,   -28,   -28,   -28,   104,   105,   106,
     113,   -28,   108,   120,   121,   123,   -28,    44,   -28,   -28,
     -28,   283,   283,   283,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   -28,   124,   -28,   -28,   -28,   -20,
     130,   136,   117,   -28,   -28,   125,   283,   240,   -28,   283,
     127,   128,   -28,   -28,   145,   318,    40,    40,    40,    40,
      40,    40,    30,    30,   -28,   -28,   -28,   240,   -28,   -28,
     -28,   283,   -28,    62,   140,   153,   159,   -28,   -28,   -28,
     117,   -20,   146,   240,   167,   -28,   -28,   -28,   -28,   -28
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,    85,     8,     1,     4,     0,     0,
       0,     2,     7,     3,     5,     6,    10,     0,    30,    32,
      31,    91,     0,     0,     0,    26,    13,    12,     0,     0,
      17,     0,    17,     0,     0,     0,     0,     0,     0,     0,
       0,    23,    43,    24,     0,    25,     0,     0,     0,     0,
       0,     0,    16,     0,     0,     9,     0,     0,    46,     0,
       0,     0,     0,    87,     0,     0,     0,     0,    45,    88,
      89,    58,    60,    61,     0,    59,    78,    81,    82,    83,
       0,     0,     0,     0,    86,    29,    40,    41,    42,     0,
       0,     0,    14,    19,    22,    11,    15,     0,     0,     0,
       0,    90,     0,     0,     0,     0,    75,    78,    76,    77,
      44,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    79,     0,    47,    33,    27,     0,
       0,     0,    55,    49,    20,    18,     0,     0,    57,     0,
       0,     0,    84,    80,    62,    63,    68,    66,    64,    69,
      67,    65,    70,    71,    72,    73,    74,     0,    28,    51,
      50,     0,    52,     0,     0,    34,     0,    38,    39,    36,
      55,     0,     0,     0,     0,    54,    21,    37,    35,    56
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   157,
     -28,   -28,   -28,   -28,   -28,   -28,   -28,   -16,   -27,   110,
     -25,   -24,   -28,    22,   -23,   -18,   -17,    -1,    76,   -28,
     -28,   -28,   -28,   -28
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     8,    13,     3,    14,    31,    15,    22,    51,
      52,    53,   135,    26,    29,    43,    83,    54,    81,    82,
      71,    72,   131,   162,    73,    74,    75,   107,    85,    77,
      78,    79,   103,    24
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
       5,    23,    45,    99,    46,    47,    48,    59,   124,    46,
      47,    48,    89,    44,     9,    46,    47,    48,     6,    55,
      56,    89,    27,    28,     1,     4,    18,    10,    49,     7,
      18,    19,    90,    49,    20,    19,    11,    76,    20,    49,
      50,    90,    98,    84,   102,    21,   105,     4,   106,   108,
     109,   124,    93,    94,    12,    95,    46,    47,    48,    76,
     100,    76,   125,    76,    89,    18,   121,   122,   123,    16,
      19,   132,   133,    20,   119,   120,   121,   122,   123,    76,
      49,    17,   128,   129,    30,    25,    32,    58,    76,    76,
      60,    61,    62,    80,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,    91,    86,    87,
     165,    92,    46,    47,    48,    88,    96,    97,   164,   110,
     130,   166,   127,    63,   136,   134,   137,   138,    84,   140,
     169,    36,    46,    47,    48,    76,    49,   139,    76,    64,
     -53,   141,   142,   170,   143,   157,   178,   171,    46,    47,
      48,   159,   104,    65,    66,    63,    49,   160,    67,   161,
      76,   172,   173,    36,     4,    69,    70,   163,   167,   168,
     176,    64,    49,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   174,    65,    66,   177,   179,    57,
      67,   126,   175,     0,     0,     0,     4,    69,    70,    33,
       0,    18,     0,     0,    34,   158,    19,     0,    35,    20,
      36,    37,     0,    38,    33,     0,     0,    39,     0,    34,
      40,    41,     0,    35,     0,    36,    37,     0,    38,     0,
       0,     0,    39,     0,     0,    40,   -48,     0,     0,    42,
       0,    33,     0,     4,     0,     0,    34,     0,     0,    63,
      35,     0,    36,    37,    42,    38,     0,    36,     4,    39,
       0,     0,    40,     0,     0,    64,    63,     0,     0,     0,
       0,     0,     0,     0,    36,     0,     0,     0,     0,    65,
      66,    42,    64,     0,    67,     4,    68,    63,     0,     0,
       4,    69,    70,     0,     0,    36,    65,    66,     0,     0,
       0,    67,     0,    64,     0,     0,   101,     4,    69,    70,
       0,     0,     0,     0,     0,     0,     0,    65,    66,     0,
       0,     0,    67,     0,     0,     0,     0,     0,     4,    69,
      70,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   111,     0,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123
};

static const yytype_int16 yycheck[] =
{
       1,    17,    29,     1,    29,    29,    29,    34,     7,    34,
      34,    34,    20,    29,     1,    40,    40,    40,     0,    41,
      42,    20,    23,    24,     5,    45,     3,    14,    29,    22,
       3,     8,    40,    34,    11,     8,    23,    38,    11,    40,
      17,    40,    60,    44,    62,    18,    64,    45,    65,    66,
      67,     7,    53,    54,    41,    56,    81,    81,    81,    60,
      61,    62,    80,    64,    20,     3,    36,    37,    38,    41,
       8,    89,    90,    11,    34,    35,    36,    37,    38,    80,
      81,    16,    41,    42,    20,    22,    20,    41,    89,    90,
      20,    20,    20,    20,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,    24,    41,    41,
     137,    21,   137,   137,   137,    41,    21,    19,   136,    41,
       1,   139,    23,     4,    20,    25,    21,    21,   129,    21,
     157,    12,   157,   157,   157,   136,   137,    24,   139,    20,
      21,    21,    21,   161,    21,    21,   173,   163,   173,   173,
     173,    21,     1,    34,    35,     4,   157,    21,    39,    42,
     161,    21,     9,    12,    45,    46,    47,    42,    41,    41,
     171,    20,   173,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    25,    34,    35,    41,    21,    32,
      39,    81,   170,    -1,    -1,    -1,    45,    46,    47,     1,
      -1,     3,    -1,    -1,     6,   129,     8,    -1,    10,    11,
      12,    13,    -1,    15,     1,    -1,    -1,    19,    -1,     6,
      22,    23,    -1,    10,    -1,    12,    13,    -1,    15,    -1,
      -1,    -1,    19,    -1,    -1,    22,    23,    -1,    -1,    41,
      -1,     1,    -1,    45,    -1,    -1,     6,    -1,    -1,     4,
      10,    -1,    12,    13,    41,    15,    -1,    12,    45,    19,
      -1,    -1,    22,    -1,    -1,    20,     4,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    12,    -1,    -1,    -1,    -1,    34,
      35,    41,    20,    -1,    39,    45,    41,     4,    -1,    -1,
      45,    46,    47,    -1,    -1,    12,    34,    35,    -1,    -1,
      -1,    39,    -1,    20,    -1,    -1,    44,    45,    46,    47,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    -1,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    45,    46,
      47,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    26,    -1,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,    50,    53,    45,    76,     0,    22,    51,     1,
      14,    23,    41,    52,    54,    56,    41,    16,     3,     8,
      11,    18,    57,    66,    82,    22,    62,    76,    76,    63,
      20,    55,    20,     1,     6,    10,    12,    13,    15,    19,
      22,    23,    41,    64,    66,    67,    69,    70,    73,    76,
      17,    58,    59,    60,    66,    41,    42,    58,    41,    67,
      20,    20,    20,     4,    20,    34,    35,    39,    41,    46,
      47,    69,    70,    73,    74,    75,    76,    78,    79,    80,
      20,    67,    68,    65,    76,    77,    41,    41,    41,    20,
      40,    24,    21,    76,    76,    76,    21,    19,    74,     1,
      76,    44,    74,    81,     1,    74,    75,    76,    75,    75,
      41,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,     7,    74,    68,    23,    41,    42,
       1,    71,    74,    74,    25,    61,    20,    21,    21,    24,
      21,    21,    21,    21,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    21,    77,    21,
      21,    42,    72,    42,    74,    67,    74,    41,    41,    67,
      74,    66,    21,     9,    25,    72,    76,    41,    67,    21
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    49,    50,    51,    51,    52,    52,    52,    53,    54,
      54,    55,    55,    56,    57,    57,    58,    58,    59,    59,
      60,    61,    61,    62,    63,    63,    63,    64,    65,    65,
      66,    66,    66,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    68,    68,    69,
      70,    70,    71,    71,    72,    72,    73,    73,    74,    74,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    76,    77,    78,    79,    80,
      81,    82
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     2,     0,     1,     1,     1,     2,     6,
       2,     3,     0,     4,     5,     5,     1,     0,     3,     2,
       3,     4,     0,     3,     2,     2,     0,     3,     3,     1,
       1,     1,     1,     3,     5,     7,     5,     7,     5,     5,
       2,     2,     2,     1,     3,     2,     2,     2,     0,     3,
       4,     4,     2,     0,     3,     0,     7,     4,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     2,     1,     2,
       3,     1,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
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
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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
            /* Fall through.  */
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

  return yystpcpy (yyres, yystr) - yyres;
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
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
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

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
| yyreduce -- Do a reduction.  |
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 41 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_root = ast_insert_node("Program", 1, 2, (yyvsp[-3].node), (yyvsp[-1].node));}
#line 1477 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 43 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("ProgramAux", 0, 2, (yyvsp[-1].node), (yyvsp[0].node));}
#line 1483 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 44 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_terminal("Empty", 0, NULL);}
#line 1489 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 46 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("FieldDeclAux", 0, 1, (yyvsp[0].node));}
#line 1495 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 47 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("MethodDecl", 1, 1, (yyvsp[0].node));}
#line 1501 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 48 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_terminal("Empty", 0, NULL);}
#line 1507 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 50 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("ClassDecl", 0, 1, (yyvsp[0].node));}
#line 1513 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 52 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("FieldDecl", 1, 2, (yyvsp[-3].node), (yyvsp[-2].node));}
#line 1519 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 53 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = NULL;}
#line 1525 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 55 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("FieldDecl", 1, 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 1531 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 56 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_terminal("Empty", 0, NULL);}
#line 1537 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 58 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("MethodDecl", 0, 2, (yyvsp[-1].node), (yyvsp[0].node));}
#line 1543 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 60 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("MethodHeader", 1, 3, (yyvsp[-4].node), (yyvsp[-3].node), (yyvsp[-1].node));}
#line 1549 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 61 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("MethodHeader", 1, 3, (yyvsp[-4].node), (yyvsp[-3].node), (yyvsp[-1].node));}
#line 1555 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 63 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("MethodParams", 1, 1, (yyvsp[0].node));}
#line 1561 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 64 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_terminal("Empty", 0, NULL);}
#line 1567 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 66 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("ParamDecl", 1, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1573 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 67 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("ParamDecl", 1, 2, (yyvsp[-1].node), (yyvsp[0].node));}
#line 1579 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 69 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("StringArray", 1, 0);}
#line 1585 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 71 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("CommaTypeId", 0, 3, (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1591 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 72 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_terminal("Empty", 0, NULL);}
#line 1597 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 74 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("MethodBody", 1, 1, (yyvsp[-1].node));}
#line 1603 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 76 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("MethodBodyL", 0, 2, (yyvsp[-1].node), (yyvsp[0].node));}
#line 1609 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 77 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("MethodBodyL", 0, 2, (yyvsp[-1].node), (yyvsp[0].node));}
#line 1615 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 78 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = NULL;}
#line 1621 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 80 "jac.y" /* yacc.c:1646  */
    {ast_insert_vardecl((yyvsp[-2].node), (yyvsp[-1].node)); (yyval.node) = (yyvsp[-1].node);}
#line 1627 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 82 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("VarDecl", 0, 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 1633 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 83 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1639 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 85 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_terminal("Bool", 1, NULL);}
#line 1645 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 86 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_terminal("Int", 1, NULL);}
#line 1651 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 87 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_terminal("Double", 1, NULL);}
#line 1657 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 89 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("StmEmptyAux", 0, 1, (yyvsp[-1].node));}
#line 1663 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 90 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("If", 1, 3, (yyvsp[-2].node), (yyvsp[0].node), NULL);}
#line 1669 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 91 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("If", 1, 3, (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));}
#line 1675 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 92 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("While", 1, 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 1681 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 93 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("DoWhile", 1, 2, (yyvsp[-5].node), (yyvsp[-2].node));}
#line 1687 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 94 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("Print", 1, 1, (yyvsp[-2].node));}
#line 1693 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 95 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("Print", 1, 1, (yyvsp[-2].node));}
#line 1699 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 96 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("Assignment", 0, 1, (yyvsp[-1].node));}
#line 1705 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 97 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("MethodInvocationList", 0, 1, (yyvsp[-1].node));}
#line 1711 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 98 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("ParseArgsAux", 0, 1, (yyvsp[-1].node));}
#line 1717 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 99 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_terminal("Empty", 0, NULL);}
#line 1723 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 100 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("Return", 1, 1, (yyvsp[-1].node));}
#line 1729 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 101 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("Return", 1, 0);}
#line 1735 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 102 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = NULL;}
#line 1741 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 104 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("StatementEmpty", 0, 2, (yyvsp[-1].node), (yyvsp[0].node));}
#line 1747 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 105 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_terminal("Empty", 0, NULL);}
#line 1753 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 107 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("Assign", 1, 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 1759 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 109 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("Call", 1, 2, (yyvsp[-3].node), (yyvsp[-1].node));}
#line 1765 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 110 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = NULL;}
#line 1771 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 112 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("MethodInvAux", 0, 2, (yyvsp[-1].node), (yyvsp[0].node));}
#line 1777 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 113 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_terminal("Empty", 0, NULL);}
#line 1783 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 115 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("CommaExpr", 0, 2, (yyvsp[-1].node), (yyvsp[0].node));}
#line 1789 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 116 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_terminal("Empty", 0, NULL);}
#line 1795 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 118 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("ParseArgs", 1, 2, (yyvsp[-4].node), (yyvsp[-2].node));}
#line 1801 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 119 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = NULL;}
#line 1807 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 121 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("Assignment", 0, 1, (yyvsp[0].node));}
#line 1813 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 122 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("ExprL", 0, 1, (yyvsp[0].node));}
#line 1819 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 125 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("MethodInvocationList", 0, 1, (yyvsp[0].node));}
#line 1825 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 126 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("ParseArgsAux", 0, 1, (yyvsp[0].node));}
#line 1831 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 127 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("And", 1, 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 1837 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 128 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("Or", 1, 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 1843 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 129 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("Eq", 1, 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 1849 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 130 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("Geq", 1, 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 1855 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 131 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("Gt", 1, 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 1861 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 132 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("Leq", 1, 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 1867 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 133 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("Lt", 1, 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 1873 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 134 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("Neq", 1, 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 1879 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 135 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("Add", 1, 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 1885 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 136 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("Sub", 1, 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 1891 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 137 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("Mul", 1, 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 1897 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 138 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("Div", 1, 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 1903 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 139 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("Mod", 1, 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 1909 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 140 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("Plus", 1, 1, (yyvsp[0].node));}
#line 1915 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 141 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("Minus", 1, 1, (yyvsp[0].node));}
#line 1921 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 142 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("Not", 1, 1, (yyvsp[0].node));}
#line 1927 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 143 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("IdAux", 0, 1, (yyvsp[0].node));}
#line 1933 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 144 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("Length", 1, 1, (yyvsp[-1].node));}
#line 1939 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 145 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("ExprCurvs", 0, 1, (yyvsp[-1].node));}
#line 1945 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 146 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("BoolAux", 0, 1, (yyvsp[0].node));}
#line 1951 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 147 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("DecAux", 0, 1, (yyvsp[0].node));}
#line 1957 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 148 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("RealAux", 0, 1, (yyvsp[0].node));}
#line 1963 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 149 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = NULL;}
#line 1969 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 151 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_terminal("Id", 1, (yyvsp[0].str));}
#line 1975 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 153 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_node("VarDecl", 1, 1, (yyvsp[0].node));}
#line 1981 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 155 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_terminal("BoolLit", 1, (yyvsp[0].str));}
#line 1987 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 157 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_terminal("DecLit", 1, (yyvsp[0].str));}
#line 1993 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 159 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_terminal("RealLit", 1, (yyvsp[0].str));}
#line 1999 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 161 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_terminal("StrLit", 1, (yyvsp[0].str));}
#line 2005 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 163 "jac.y" /* yacc.c:1646  */
    {(yyval.node) = ast_insert_terminal("Void", 1, NULL);}
#line 2011 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2015 "y.tab.c" /* yacc.c:1646  */
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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

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
                      yytoken, &yylval);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
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
#line 165 "jac.y" /* yacc.c:1906  */


void yyerror(const char* s) {
	error_flag = 1;
	printf("Line %d, col %d: %s: %s\n", line, col - (int) yyleng, s, yytext);
}
