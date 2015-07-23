/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 27 "parser.y" /* yacc.c:339  */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "numwrap.h"
#include "vars.h"
#include "expr.h"
#include "program.h"

extern int yylex();
void yyerror(char *s, ...);
void loc_reset();

#ifdef BISON_DEBUG
#define YYDEBUG 1
#endif


#line 88 "parser.c" /* yacc.c:339  */

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
#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
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
    INTEGER = 258,
    IDENTIFIER = 259,
    STRING = 260,
    COMPARISON = 261,
    OP_AND_ASSIGN = 262,
    PLUSPLUS_MINMIN = 263,
    QUIT = 264,
    VARS = 265,
    LIBSWITCH = 266,
    LIBLIST = 267,
    WHILE = 268,
    FOR = 269,
    DEFINE = 270,
    VOID = 271,
    RETURN = 272,
    NEWLINE = 273,
    LOGIC_OR = 274,
    LOGIC_AND = 275,
    LOGIC_NOT = 276,
    NEG = 277
  };
#endif
/* Tokens.  */
#define INTEGER 258
#define IDENTIFIER 259
#define STRING 260
#define COMPARISON 261
#define OP_AND_ASSIGN 262
#define PLUSPLUS_MINMIN 263
#define QUIT 264
#define VARS 265
#define LIBSWITCH 266
#define LIBLIST 267
#define WHILE 268
#define FOR 269
#define DEFINE 270
#define VOID 271
#define RETURN 272
#define NEWLINE 273
#define LOGIC_OR 274
#define LOGIC_AND 275
#define LOGIC_NOT 276
#define NEG 277

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 57 "parser.y" /* yacc.c:355  */

	numptr num;
	expr_t *enode;
	char *str;
	program_t *prog;
	defargs_t *defargs;
	callargs_t *callargs;

#line 181 "parser.c" /* yacc.c:355  */
};
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
/* "%code provides" blocks.  */
#line 49 "parser.y" /* yacc.c:355  */

void activate_bison_debug();
void lib_list();

#line 211 "parser.c" /* yacc.c:355  */

#endif /* !YY_YY_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 217 "parser.c" /* yacc.c:358  */

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
#define YYFINAL  53
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   296

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  76
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  146

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   277

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    26,     2,     2,
      34,    35,    24,    22,    36,    23,     2,    25,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    31,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    32,     2,    33,    27,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    29,     2,    30,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    28
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   103,   103,   104,   105,   106,   110,   118,   122,   123,
     127,   128,   132,   133,   137,   138,   139,   140,   141,   142,
     143,   147,   152,   160,   161,   165,   166,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   193,   194,   198,
     210,   211,   215,   227,   231,   232,   233,   234,   238,   239,
     243,   244,   248,   253,   261,   262,   266,   267,   271,   272,
     276,   280,   281,   282,   285,   291,   294
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER", "IDENTIFIER", "STRING",
  "COMPARISON", "OP_AND_ASSIGN", "PLUSPLUS_MINMIN", "QUIT", "VARS",
  "LIBSWITCH", "LIBLIST", "WHILE", "FOR", "DEFINE", "VOID", "RETURN",
  "NEWLINE", "LOGIC_OR", "LOGIC_AND", "LOGIC_NOT", "'+'", "'-'", "'*'",
  "'/'", "'%'", "'^'", "NEG", "'{'", "'}'", "';'", "'['", "']'", "'('",
  "')'", "','", "$accept", "input", "program", "instruction_block",
  "instruction_inside_block", "instruction_list", "instruction",
  "instruction_non_empty", "instruction_assignment", "expression",
  "expression_assignment", "expression_no_assignment", "newlines_or_empty",
  "loop_while", "expression_or_empty", "loop_for", "return", "defarg",
  "defargs_list", "defargs_list_or_empty", "function_definition",
  "callarg", "callargs_list", "callargs_list_or_empty", "function_call",
  "statement", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,    43,    45,    42,    47,    37,    94,   277,   123,
     125,    59,    91,    93,    40,    41,    44
};
# endif

#define YYPACT_NINF -113

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-113)))

#define YYTABLE_NINF -27

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      94,     2,  -113,     4,  -113,    23,  -113,  -113,     3,  -113,
       6,    19,     5,   135,   135,   135,   128,   135,    64,    52,
    -113,    36,  -113,  -113,  -113,   237,  -113,    43,  -113,  -113,
    -113,  -113,  -113,    53,    94,   135,  -113,   135,   144,    47,
    -113,   135,   135,    41,    76,     7,   237,  -113,   269,  -113,
       1,    36,   157,  -113,    94,   128,   135,   135,   135,   135,
     135,   135,   135,   135,   135,    94,  -113,   247,   201,    49,
     237,  -113,    54,    50,   135,   179,   237,    61,     9,    59,
     135,   135,   128,  -113,  -113,  -113,  -113,   164,   148,   269,
     169,   169,    69,    69,    69,    69,  -113,    10,    55,   144,
    -113,   213,    82,   135,    78,   109,  -113,    80,    79,     9,
     164,   225,    36,   135,  -113,  -113,  -113,  -113,    82,   128,
      89,    88,    90,     9,    82,    91,    35,   259,  -113,  -113,
     135,  -113,    96,  -113,   128,    82,   135,    92,  -113,  -113,
     128,   164,    82,  -113,   128,  -113
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    27,    28,    16,     0,    72,    73,    75,    76,
       0,     0,     0,     0,     0,     0,    12,     0,     0,     0,
      20,     6,    10,    13,    14,     0,    24,    23,    17,    18,
      19,    71,    34,     0,     0,     0,    31,     0,    68,    30,
      74,     0,    50,     0,     0,    28,    53,    23,    45,    41,
       0,     8,     0,     1,     0,    12,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     5,    21,     0,    28,
      64,    66,    69,     0,     0,     0,    51,     0,    60,     0,
       0,     0,    12,     7,    46,     3,    11,    42,    44,    43,
      35,    36,    37,    38,    40,    39,     4,    29,     0,     0,
      70,     0,    47,    50,    54,     0,    58,    61,     0,    60,
      25,     0,     9,     0,    33,    65,    67,    32,    47,     0,
       0,     0,    56,     0,    47,     0,    29,    22,    48,    49,
      50,    55,     0,    59,     0,    47,     0,     0,    57,    62,
       0,    26,    47,    63,     0,    52
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -113,   -30,  -113,  -113,  -113,   -10,    75,  -112,  -113,   -12,
    -113,     0,   -58,  -113,   -93,  -113,  -113,    12,  -113,    28,
    -113,    51,  -113,  -113,  -113,  -113
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    18,    19,    20,    50,    21,    22,    23,    24,    25,
      26,    47,   119,    28,    77,    29,    30,   106,   107,   108,
      31,    71,    72,    73,    32,    33
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      27,    46,    48,    49,    66,    52,    51,   129,    40,    43,
     120,    35,    36,   104,    80,    36,    27,   113,   114,    82,
      34,    44,   139,    67,    85,    68,    70,    39,   143,    75,
      76,    83,   145,   105,    27,    96,    37,   137,    38,    81,
      41,    38,   136,   114,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    42,    27,    27,    80,    36,     2,    45,
     128,   -15,   101,     5,    53,    27,   134,    55,   110,   111,
      54,    65,   112,   -15,   -15,    78,    14,   140,    15,    74,
      79,    98,    27,    38,   144,   100,   111,    70,   115,    17,
      99,    76,   103,   109,    -2,     1,    64,     2,     3,     4,
     118,   127,     5,     6,     7,     8,     9,    10,    11,    12,
     121,    13,   -12,   122,   124,    14,   123,    15,    76,    27,
     130,   131,   132,    16,   141,   -12,   135,   142,    17,   138,
      86,     2,     3,     4,    27,   133,     5,   125,     2,    45,
      27,    10,    11,     5,    27,    13,     0,     2,    69,    14,
     116,    15,     5,     0,    56,     0,    14,    16,    15,     0,
       0,     0,    17,    56,     0,    14,     0,    15,    58,    17,
      59,    60,    61,    62,    63,    64,    57,    58,    17,    59,
      60,    61,    62,    63,    64,    56,    59,    60,    61,    62,
      63,    64,    84,    61,    62,    63,    64,     0,    57,    58,
       0,    59,    60,    61,    62,    63,    64,    56,     0,     0,
       0,     0,     0,     0,   102,     0,     0,     0,     0,    56,
      57,    58,     0,    59,    60,    61,    62,    63,    64,     0,
       0,    56,    57,    58,    97,    59,    60,    61,    62,    63,
      64,     0,     0,    56,    57,    58,   117,    59,    60,    61,
      62,    63,    64,   -25,     0,     0,    57,    58,   126,    59,
      60,    61,    62,    63,    64,   -26,   -25,   -25,     0,    59,
      60,    61,    62,    63,    64,    56,     0,     0,   -26,   -26,
       0,    59,    60,    61,    62,    63,    64,     0,     0,     0,
       0,    59,    60,    61,    62,    63,    64
};

static const yytype_int16 yycheck[] =
{
       0,    13,    14,    15,    34,    17,    16,   119,     5,     4,
     103,     7,     8,     4,     7,     8,    16,     7,     8,    18,
      18,    16,   134,    35,    54,    37,    38,     4,   140,    41,
      42,    30,   144,    24,    34,    65,    32,   130,    34,    32,
      34,    34,     7,     8,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    34,    54,    55,     7,     8,     3,     4,
     118,    18,    74,     8,     0,    65,   124,    31,    80,    81,
      18,    18,    82,    30,    31,    34,    21,   135,    23,    32,
       4,    32,    82,    34,   142,    35,    98,    99,    33,    34,
      36,   103,    31,    34,     0,     1,    27,     3,     4,     5,
      18,   113,     8,     9,    10,    11,    12,    13,    14,    15,
      32,    17,    18,     4,    35,    21,    36,    23,   130,   119,
      31,    33,    32,    29,   136,    31,    35,    35,    34,    33,
      55,     3,     4,     5,   134,   123,     8,   109,     3,     4,
     140,    13,    14,     8,   144,    17,    -1,     3,     4,    21,
      99,    23,     8,    -1,     6,    -1,    21,    29,    23,    -1,
      -1,    -1,    34,     6,    -1,    21,    -1,    23,    20,    34,
      22,    23,    24,    25,    26,    27,    19,    20,    34,    22,
      23,    24,    25,    26,    27,     6,    22,    23,    24,    25,
      26,    27,    35,    24,    25,    26,    27,    -1,    19,    20,
      -1,    22,    23,    24,    25,    26,    27,     6,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    -1,    -1,    -1,    -1,     6,
      19,    20,    -1,    22,    23,    24,    25,    26,    27,    -1,
      -1,     6,    19,    20,    33,    22,    23,    24,    25,    26,
      27,    -1,    -1,     6,    19,    20,    33,    22,    23,    24,
      25,    26,    27,     6,    -1,    -1,    19,    20,    33,    22,
      23,    24,    25,    26,    27,     6,    19,    20,    -1,    22,
      23,    24,    25,    26,    27,     6,    -1,    -1,    19,    20,
      -1,    22,    23,    24,    25,    26,    27,    -1,    -1,    -1,
      -1,    22,    23,    24,    25,    26,    27
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     4,     5,     8,     9,    10,    11,    12,
      13,    14,    15,    17,    21,    23,    29,    34,    38,    39,
      40,    42,    43,    44,    45,    46,    47,    48,    50,    52,
      53,    57,    61,    62,    18,     7,     8,    32,    34,     4,
       5,    34,    34,     4,    16,     4,    46,    48,    46,    46,
      41,    42,    46,     0,    18,    31,     6,    19,    20,    22,
      23,    24,    25,    26,    27,    18,    38,    46,    46,     4,
      46,    58,    59,    60,    32,    46,    46,    51,    34,     4,
       7,    32,    18,    30,    35,    38,    43,    46,    46,    46,
      46,    46,    46,    46,    46,    46,    38,    33,    32,    36,
      35,    46,    35,    31,     4,    24,    54,    55,    56,    34,
      46,    46,    42,     7,     8,    33,    58,    33,    18,    49,
      51,    32,     4,    36,    35,    56,    33,    46,    49,    44,
      31,    33,    32,    54,    49,    35,     7,    51,    33,    44,
      49,    46,    35,    44,    49,    44
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    37,    38,    38,    38,    38,    39,    40,    41,    41,
      42,    42,    43,    43,    44,    44,    44,    44,    44,    44,
      44,    45,    45,    46,    46,    47,    47,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    49,    49,    50,
      51,    51,    52,    53,    54,    54,    54,    54,    55,    55,
      56,    56,    57,    57,    58,    58,    59,    59,    60,    60,
      61,    62,    62,    62,    62,    62,    62
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     3,     3,     3,     1,     3,     1,     3,
       1,     3,     0,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     6,     1,     1,     3,     6,     1,     1,     4,
       2,     2,     5,     5,     1,     3,     3,     3,     3,     3,
       3,     2,     3,     3,     3,     2,     3,     0,     2,     6,
       0,     1,    10,     2,     1,     3,     2,     4,     1,     3,
       0,     1,     7,     8,     1,     3,     1,     3,     0,     1,
       4,     1,     1,     1,     2,     1,     1
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
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
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


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yytype)
    {
          case 3: /* INTEGER  */
#line 91 "parser.y" /* yacc.c:1257  */
      { num_destruct(&((*yyvaluep).num)); out_dbg("parser.y: freed one num\n"); }
#line 1241 "parser.c" /* yacc.c:1257  */
        break;

    case 4: /* IDENTIFIER  */
#line 93 "parser.y" /* yacc.c:1257  */
      { free(((*yyvaluep).str)); out_dbg("parser.y: freed one str\n"); }
#line 1247 "parser.c" /* yacc.c:1257  */
        break;

    case 5: /* STRING  */
#line 93 "parser.y" /* yacc.c:1257  */
      { free(((*yyvaluep).str)); out_dbg("parser.y: freed one str\n"); }
#line 1253 "parser.c" /* yacc.c:1257  */
        break;

    case 6: /* COMPARISON  */
#line 93 "parser.y" /* yacc.c:1257  */
      { free(((*yyvaluep).str)); out_dbg("parser.y: freed one str\n"); }
#line 1259 "parser.c" /* yacc.c:1257  */
        break;

    case 7: /* OP_AND_ASSIGN  */
#line 93 "parser.y" /* yacc.c:1257  */
      { free(((*yyvaluep).str)); out_dbg("parser.y: freed one str\n"); }
#line 1265 "parser.c" /* yacc.c:1257  */
        break;

    case 8: /* PLUSPLUS_MINMIN  */
#line 93 "parser.y" /* yacc.c:1257  */
      { free(((*yyvaluep).str)); out_dbg("parser.y: freed one str\n"); }
#line 1271 "parser.c" /* yacc.c:1257  */
        break;

    case 40: /* instruction_block  */
#line 94 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1277 "parser.c" /* yacc.c:1257  */
        break;

    case 41: /* instruction_inside_block  */
#line 94 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1283 "parser.c" /* yacc.c:1257  */
        break;

    case 42: /* instruction_list  */
#line 94 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1289 "parser.c" /* yacc.c:1257  */
        break;

    case 43: /* instruction  */
#line 94 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1295 "parser.c" /* yacc.c:1257  */
        break;

    case 44: /* instruction_non_empty  */
#line 94 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1301 "parser.c" /* yacc.c:1257  */
        break;

    case 45: /* instruction_assignment  */
#line 94 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1307 "parser.c" /* yacc.c:1257  */
        break;

    case 46: /* expression  */
#line 92 "parser.y" /* yacc.c:1257  */
      { expr_destruct(((*yyvaluep).enode)); out_dbg("parser.y: freed one enode\n"); }
#line 1313 "parser.c" /* yacc.c:1257  */
        break;

    case 47: /* expression_assignment  */
#line 92 "parser.y" /* yacc.c:1257  */
      { expr_destruct(((*yyvaluep).enode)); out_dbg("parser.y: freed one enode\n"); }
#line 1319 "parser.c" /* yacc.c:1257  */
        break;

    case 48: /* expression_no_assignment  */
#line 92 "parser.y" /* yacc.c:1257  */
      { expr_destruct(((*yyvaluep).enode)); out_dbg("parser.y: freed one enode\n"); }
#line 1325 "parser.c" /* yacc.c:1257  */
        break;

    case 50: /* loop_while  */
#line 94 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1331 "parser.c" /* yacc.c:1257  */
        break;

    case 51: /* expression_or_empty  */
#line 92 "parser.y" /* yacc.c:1257  */
      { expr_destruct(((*yyvaluep).enode)); out_dbg("parser.y: freed one enode\n"); }
#line 1337 "parser.c" /* yacc.c:1257  */
        break;

    case 52: /* loop_for  */
#line 94 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1343 "parser.c" /* yacc.c:1257  */
        break;

    case 53: /* return  */
#line 94 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1349 "parser.c" /* yacc.c:1257  */
        break;

    case 54: /* defarg  */
#line 95 "parser.y" /* yacc.c:1257  */
      { defargs_destruct(((*yyvaluep).defargs)); out_dbg("parser.y: freed one DEF argument chain\n"); }
#line 1355 "parser.c" /* yacc.c:1257  */
        break;

    case 55: /* defargs_list  */
#line 95 "parser.y" /* yacc.c:1257  */
      { defargs_destruct(((*yyvaluep).defargs)); out_dbg("parser.y: freed one DEF argument chain\n"); }
#line 1361 "parser.c" /* yacc.c:1257  */
        break;

    case 56: /* defargs_list_or_empty  */
#line 95 "parser.y" /* yacc.c:1257  */
      { defargs_destruct(((*yyvaluep).defargs)); out_dbg("parser.y: freed one DEF argument chain\n"); }
#line 1367 "parser.c" /* yacc.c:1257  */
        break;

    case 58: /* callarg  */
#line 96 "parser.y" /* yacc.c:1257  */
      { callargs_destruct(((*yyvaluep).callargs)); out_dbg("parser.y: freed one CALL argument chain\n"); }
#line 1373 "parser.c" /* yacc.c:1257  */
        break;

    case 59: /* callargs_list  */
#line 96 "parser.y" /* yacc.c:1257  */
      { callargs_destruct(((*yyvaluep).callargs)); out_dbg("parser.y: freed one CALL argument chain\n"); }
#line 1379 "parser.c" /* yacc.c:1257  */
        break;

    case 60: /* callargs_list_or_empty  */
#line 96 "parser.y" /* yacc.c:1257  */
      { callargs_destruct(((*yyvaluep).callargs)); out_dbg("parser.y: freed one CALL argument chain\n"); }
#line 1385 "parser.c" /* yacc.c:1257  */
        break;

    case 61: /* function_call  */
#line 92 "parser.y" /* yacc.c:1257  */
      { expr_destruct(((*yyvaluep).enode)); out_dbg("parser.y: freed one enode\n"); }
#line 1391 "parser.c" /* yacc.c:1257  */
        break;


      default:
        break;
    }
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

        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 103 "parser.y" /* yacc.c:1646  */
    { loc_reset(); }
#line 1679 "parser.c" /* yacc.c:1646  */
    break;

  case 5:
#line 106 "parser.y" /* yacc.c:1646  */
    { out_dbg("Error encountered, ran yyclearin and yyerrok\n"); yyclearin; yyerrok; }
#line 1685 "parser.c" /* yacc.c:1646  */
    break;

  case 6:
#line 110 "parser.y" /* yacc.c:1646  */
    {
		numptr num = num_undefvalue();
		program_execute((yyvsp[0].prog), &num);
		program_destruct((yyvsp[0].prog));
	}
#line 1695 "parser.c" /* yacc.c:1646  */
    break;

  case 7:
#line 118 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = (yyvsp[-1].prog); }
#line 1701 "parser.c" /* yacc.c:1646  */
    break;

  case 8:
#line 122 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = (yyvsp[0].prog); }
#line 1707 "parser.c" /* yacc.c:1646  */
    break;

  case 9:
#line 123 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = program_chain((yyvsp[-2].prog), (yyvsp[0].prog)); }
#line 1713 "parser.c" /* yacc.c:1646  */
    break;

  case 11:
#line 128 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = program_chain((yyvsp[-2].prog), (yyvsp[0].prog)); }
#line 1719 "parser.c" /* yacc.c:1646  */
    break;

  case 12:
#line 132 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = NULL; }
#line 1725 "parser.c" /* yacc.c:1646  */
    break;

  case 15:
#line 138 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = program_construct_expr((yyvsp[0].enode), FALSE); }
#line 1731 "parser.c" /* yacc.c:1646  */
    break;

  case 16:
#line 139 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = program_construct_str((yyvsp[0].str)); }
#line 1737 "parser.c" /* yacc.c:1646  */
    break;

  case 20:
#line 143 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = (yyvsp[0].prog); }
#line 1743 "parser.c" /* yacc.c:1646  */
    break;

  case 21:
#line 147 "parser.y" /* yacc.c:1646  */
    {
		expr_t *enode = expr_construct_setvar((yyvsp[-2].str), NULL, (yyvsp[-1].str), FALSE, (yyvsp[0].enode));
		(yyval.prog) = program_construct_expr(enode, TRUE);
		free((yyvsp[-1].str));
	}
#line 1753 "parser.c" /* yacc.c:1646  */
    break;

  case 22:
#line 152 "parser.y" /* yacc.c:1646  */
    {
		expr_t *enode = expr_construct_setvar((yyvsp[-5].str), (yyvsp[-3].enode), (yyvsp[-1].str), FALSE, (yyvsp[0].enode));
		(yyval.prog) = program_construct_expr(enode, TRUE);
		free((yyvsp[-1].str));
	}
#line 1763 "parser.c" /* yacc.c:1646  */
    break;

  case 25:
#line 165 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_setvar((yyvsp[-2].str), NULL, (yyvsp[-1].str), FALSE, (yyvsp[0].enode)); free((yyvsp[-1].str)); }
#line 1769 "parser.c" /* yacc.c:1646  */
    break;

  case 26:
#line 166 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_setvar((yyvsp[-5].str), (yyvsp[-3].enode), (yyvsp[-1].str), FALSE, (yyvsp[0].enode)); free((yyvsp[-1].str)); }
#line 1775 "parser.c" /* yacc.c:1646  */
    break;

  case 27:
#line 170 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_number((yyvsp[0].num)); }
#line 1781 "parser.c" /* yacc.c:1646  */
    break;

  case 28:
#line 171 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_getvar((yyvsp[0].str), NULL); }
#line 1787 "parser.c" /* yacc.c:1646  */
    break;

  case 29:
#line 172 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_getvar((yyvsp[-3].str), (yyvsp[-1].enode)); }
#line 1793 "parser.c" /* yacc.c:1646  */
    break;

  case 30:
#line 173 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_setvar((yyvsp[0].str), NULL, (yyvsp[-1].str), FALSE, NULL); free((yyvsp[-1].str)); }
#line 1799 "parser.c" /* yacc.c:1646  */
    break;

  case 31:
#line 174 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_setvar((yyvsp[-1].str), NULL, (yyvsp[0].str), TRUE, NULL); free((yyvsp[0].str)); }
#line 1805 "parser.c" /* yacc.c:1646  */
    break;

  case 32:
#line 175 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_setvar((yyvsp[-3].str), (yyvsp[-1].enode), (yyvsp[-4].str), FALSE, NULL); free((yyvsp[-4].str)); }
#line 1811 "parser.c" /* yacc.c:1646  */
    break;

  case 33:
#line 176 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_setvar((yyvsp[-4].str), (yyvsp[-2].enode), (yyvsp[0].str), TRUE, NULL); free((yyvsp[0].str)); }
#line 1817 "parser.c" /* yacc.c:1646  */
    break;

  case 35:
#line 178 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op2_str("+", (yyvsp[-2].enode), (yyvsp[0].enode)); }
#line 1823 "parser.c" /* yacc.c:1646  */
    break;

  case 36:
#line 179 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op2_str("-", (yyvsp[-2].enode), (yyvsp[0].enode)); }
#line 1829 "parser.c" /* yacc.c:1646  */
    break;

  case 37:
#line 180 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op2_str("*", (yyvsp[-2].enode), (yyvsp[0].enode)); }
#line 1835 "parser.c" /* yacc.c:1646  */
    break;

  case 38:
#line 181 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op2_str("/", (yyvsp[-2].enode), (yyvsp[0].enode)); }
#line 1841 "parser.c" /* yacc.c:1646  */
    break;

  case 39:
#line 182 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op2_str("^", (yyvsp[-2].enode), (yyvsp[0].enode)); }
#line 1847 "parser.c" /* yacc.c:1646  */
    break;

  case 40:
#line 183 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op2_str("%", (yyvsp[-2].enode), (yyvsp[0].enode)); }
#line 1853 "parser.c" /* yacc.c:1646  */
    break;

  case 41:
#line 184 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op1_str("-", (yyvsp[0].enode)); }
#line 1859 "parser.c" /* yacc.c:1646  */
    break;

  case 42:
#line 185 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op2_str((yyvsp[-1].str), (yyvsp[-2].enode), (yyvsp[0].enode)); free((yyvsp[-1].str)); }
#line 1865 "parser.c" /* yacc.c:1646  */
    break;

  case 43:
#line 186 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op2_str("&&", (yyvsp[-2].enode), (yyvsp[0].enode)); }
#line 1871 "parser.c" /* yacc.c:1646  */
    break;

  case 44:
#line 187 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op2_str("||", (yyvsp[-2].enode), (yyvsp[0].enode)); }
#line 1877 "parser.c" /* yacc.c:1646  */
    break;

  case 45:
#line 188 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op1_str("!", (yyvsp[0].enode)); }
#line 1883 "parser.c" /* yacc.c:1646  */
    break;

  case 46:
#line 189 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = (yyvsp[-1].enode); }
#line 1889 "parser.c" /* yacc.c:1646  */
    break;

  case 49:
#line 198 "parser.y" /* yacc.c:1646  */
    {
		program_loop_t loop;
		loop.exprbefore = NULL;
		loop.testbefore = (yyvsp[-3].enode);
		loop.core = (yyvsp[0].prog);
		loop.testafter = NULL;
		loop.exprafter = NULL;
		(yyval.prog) = program_construct_loop(&loop);
	}
#line 1903 "parser.c" /* yacc.c:1646  */
    break;

  case 50:
#line 210 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = NULL; }
#line 1909 "parser.c" /* yacc.c:1646  */
    break;

  case 52:
#line 215 "parser.y" /* yacc.c:1646  */
    {
		program_loop_t loop;
		loop.exprbefore = (yyvsp[-7].enode);
		loop.testbefore = (yyvsp[-5].enode);
		loop.core = (yyvsp[0].prog);
		loop.testafter = NULL;
		loop.exprafter = (yyvsp[-3].enode);
		(yyval.prog) = program_construct_loop(&loop);
	}
#line 1923 "parser.c" /* yacc.c:1646  */
    break;

  case 53:
#line 227 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = program_construct_return((yyvsp[0].enode)); }
#line 1929 "parser.c" /* yacc.c:1646  */
    break;

  case 54:
#line 231 "parser.y" /* yacc.c:1646  */
    { (yyval.defargs) = defargs_construct(DARG_VALUE, (yyvsp[0].str)); }
#line 1935 "parser.c" /* yacc.c:1646  */
    break;

  case 55:
#line 232 "parser.y" /* yacc.c:1646  */
    { (yyval.defargs) = defargs_construct(DARG_ARRAYVALUE, (yyvsp[-2].str)); }
#line 1941 "parser.c" /* yacc.c:1646  */
    break;

  case 56:
#line 233 "parser.y" /* yacc.c:1646  */
    { (yyval.defargs) = defargs_construct(DARG_REF, (yyvsp[0].str)); }
#line 1947 "parser.c" /* yacc.c:1646  */
    break;

  case 57:
#line 234 "parser.y" /* yacc.c:1646  */
    { (yyval.defargs) = defargs_construct(DARG_ARRAYREF, (yyvsp[-2].str)); }
#line 1953 "parser.c" /* yacc.c:1646  */
    break;

  case 59:
#line 239 "parser.y" /* yacc.c:1646  */
    { (yyval.defargs) = defargs_chain((yyvsp[-2].defargs), (yyvsp[0].defargs)); }
#line 1959 "parser.c" /* yacc.c:1646  */
    break;

  case 60:
#line 243 "parser.y" /* yacc.c:1646  */
    { (yyval.defargs) = NULL; }
#line 1965 "parser.c" /* yacc.c:1646  */
    break;

  case 62:
#line 248 "parser.y" /* yacc.c:1646  */
    {
		int r;
		if ((r = vars_function_construct((yyvsp[-5].str), (yyvsp[-3].defargs), (yyvsp[0].prog), FALSE)) != ERROR_NONE)
			outln_error_code(r);
	}
#line 1975 "parser.c" /* yacc.c:1646  */
    break;

  case 63:
#line 253 "parser.y" /* yacc.c:1646  */
    {
		int r;
		if ((r = vars_function_construct((yyvsp[-5].str), (yyvsp[-3].defargs), (yyvsp[0].prog), TRUE)) != ERROR_NONE)
			outln_error_code(r);
	}
#line 1985 "parser.c" /* yacc.c:1646  */
    break;

  case 64:
#line 261 "parser.y" /* yacc.c:1646  */
    { (yyval.callargs) = callargs_construct(CARG_EXPR, (yyvsp[0].enode), NULL); }
#line 1991 "parser.c" /* yacc.c:1646  */
    break;

  case 65:
#line 262 "parser.y" /* yacc.c:1646  */
    { (yyval.callargs) = callargs_construct(CARG_ARRAY, NULL, (yyvsp[-2].str)); }
#line 1997 "parser.c" /* yacc.c:1646  */
    break;

  case 67:
#line 267 "parser.y" /* yacc.c:1646  */
    { (yyval.callargs) = callargs_chain((yyvsp[-2].callargs), (yyvsp[0].callargs)); }
#line 2003 "parser.c" /* yacc.c:1646  */
    break;

  case 68:
#line 271 "parser.y" /* yacc.c:1646  */
    { (yyval.callargs) = NULL; }
#line 2009 "parser.c" /* yacc.c:1646  */
    break;

  case 70:
#line 276 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_function_call((yyvsp[-3].str), (yyvsp[-1].callargs)); }
#line 2015 "parser.c" /* yacc.c:1646  */
    break;

  case 72:
#line 281 "parser.y" /* yacc.c:1646  */
    { YYABORT; }
#line 2021 "parser.c" /* yacc.c:1646  */
    break;

  case 73:
#line 282 "parser.y" /* yacc.c:1646  */
    {
		vars_display_all();
	}
#line 2029 "parser.c" /* yacc.c:1646  */
    break;

  case 74:
#line 285 "parser.y" /* yacc.c:1646  */
    {
		if (num_libswitch((yyvsp[0].str)) == 0) {
			outln_error("Unknown library");
		}
		free((yyvsp[0].str));
	}
#line 2040 "parser.c" /* yacc.c:1646  */
    break;

  case 75:
#line 291 "parser.y" /* yacc.c:1646  */
    {
		outln(L_ENFORCE, "%s", num_identify_yourself());
	}
#line 2048 "parser.c" /* yacc.c:1646  */
    break;

  case 76:
#line 294 "parser.y" /* yacc.c:1646  */
    {
		lib_list();
	}
#line 2056 "parser.c" /* yacc.c:1646  */
    break;


#line 2060 "parser.c" /* yacc.c:1646  */
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
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
#line 299 "parser.y" /* yacc.c:1906  */


void activate_bison_debug()
{
	/*
	* Double test with caller (in main.c) as main.c also checks for BISON_DEBUG,
	* but I find it clearer. This way, main.c highlights it is only when debug
	* is activated. Below, the test is mandatory (yydebug undefined if no BISON_DEBUG)
	*/
#ifdef BISON_DEBUG
	yydebug = 1;
#endif
}

