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
    BREAK = 270,
    CONTINUE = 271,
    IF = 272,
    ELSE = 273,
    DEFINE = 274,
    VOID = 275,
    RETURN = 276,
    NEWLINE = 277,
    LOGIC_OR = 278,
    LOGIC_AND = 279,
    LOGIC_NOT = 280,
    NEG = 281
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
#define BREAK 270
#define CONTINUE 271
#define IF 272
#define ELSE 273
#define DEFINE 274
#define VOID 275
#define RETURN 276
#define NEWLINE 277
#define LOGIC_OR 278
#define LOGIC_AND 279
#define LOGIC_NOT 280
#define NEG 281

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 56 "parser.y" /* yacc.c:355  */

	numptr num;
	expr_t *enode;
	char *str;
	program_t *prog;
	defargs_t *defargs;
	callargs_t *callargs;

#line 189 "parser.c" /* yacc.c:355  */
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

#line 218 "parser.c" /* yacc.c:355  */

#endif /* !YY_YY_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 224 "parser.c" /* yacc.c:358  */

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
#define YYFINAL  57
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   349

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  82
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  159

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   281

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    30,     2,     2,
      38,    39,    28,    26,    40,    27,     2,    29,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    35,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    36,     2,    37,    31,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    33,     2,    34,     2,     2,     2,     2,
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
      25,    32
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   102,   102,   103,   104,   105,   109,   116,   120,   121,
     125,   126,   130,   131,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   149,   154,   162,   163,   167,
     168,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   195,   196,   200,   212,   213,   217,   229,   239,   240,
     244,   245,   246,   247,   251,   252,   256,   257,   261,   266,
     274,   275,   279,   280,   284,   285,   289,   293,   294,   295,
     298,   304,   307
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER", "IDENTIFIER", "STRING",
  "COMPARISON", "OP_AND_ASSIGN", "PLUSPLUS_MINMIN", "QUIT", "VARS",
  "LIBSWITCH", "LIBLIST", "WHILE", "FOR", "BREAK", "CONTINUE", "IF",
  "ELSE", "DEFINE", "VOID", "RETURN", "NEWLINE", "LOGIC_OR", "LOGIC_AND",
  "LOGIC_NOT", "'+'", "'-'", "'*'", "'/'", "'%'", "'^'", "NEG", "'{'",
  "'}'", "';'", "'['", "']'", "'('", "')'", "','", "$accept", "input",
  "program", "instruction_block", "instruction_inside_block",
  "instruction_list", "instruction", "instruction_non_empty",
  "instruction_assignment", "expression", "expression_assignment",
  "expression_no_assignment", "newlines_or_empty", "loop_while",
  "expression_or_empty", "loop_for", "ifseq", "else_or_empty", "defarg",
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
     275,   276,   277,   278,   279,   280,    43,    45,    42,    47,
      37,    94,   281,   123,   125,    59,    91,    93,    40,    41,
      44
};
# endif

#define YYPACT_NINF -116

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-116)))

#define YYTABLE_NINF -52

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     157,    -7,  -116,     6,  -116,     5,  -116,  -116,    19,  -116,
      29,    37,  -116,  -116,    40,    18,    52,    52,    52,    93,
      52,    80,    64,  -116,    56,  -116,  -116,  -116,   278,  -116,
     -14,  -116,  -116,  -116,  -116,  -116,    70,   157,    52,  -116,
      52,   177,    59,  -116,    52,    52,    52,    61,    90,    26,
     278,  -116,   208,  -116,    -6,    56,   182,  -116,   157,    93,
      52,    52,    52,    52,    52,    52,    52,    52,    52,   157,
    -116,   292,   239,    77,   278,  -116,    60,    63,    52,   201,
     278,    68,   220,    53,    67,    52,    52,    93,  -116,  -116,
    -116,  -116,   110,   318,   208,   123,   123,    86,    86,    86,
      86,  -116,    10,   108,   177,  -116,   251,    97,    52,    97,
      85,   119,  -116,    84,    89,    53,   110,   266,    56,    52,
    -116,  -116,  -116,  -116,    97,    93,    95,    93,   106,    96,
      53,    97,   105,    58,   304,  -116,  -116,    52,    54,  -116,
     111,  -116,    93,    97,    52,   120,   116,  -116,  -116,  -116,
      93,   110,    97,    97,  -116,    93,    93,  -116,  -116
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    31,    32,    16,     0,    78,    79,    81,    82,
       0,     0,    22,    23,     0,     0,    20,     0,     0,    12,
       0,     0,     0,    24,     6,    10,    13,    14,     0,    28,
      27,    17,    18,    19,    77,    38,     0,     0,     0,    35,
       0,    74,    34,    80,     0,    54,     0,     0,     0,    32,
      21,    27,    49,    45,     0,     8,     0,     1,     0,    12,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       5,    25,     0,    32,    70,    72,    75,     0,     0,     0,
      55,     0,     0,    66,     0,     0,     0,    12,     7,    50,
       3,    11,    46,    48,    47,    39,    40,    41,    42,    44,
      43,     4,    33,     0,     0,    76,     0,    51,    54,    51,
      60,     0,    64,    67,     0,    66,    29,     0,     9,     0,
      37,    71,    73,    36,    51,     0,     0,     0,     0,    62,
       0,    51,     0,    33,    26,    52,    53,    54,    58,    61,
       0,    65,     0,    51,     0,     0,     0,    57,    63,    68,
       0,    30,    51,    51,    69,     0,     0,    56,    59
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -116,   -26,  -116,  -116,  -116,   -13,    88,  -115,  -116,   -15,
    -116,     0,   -70,  -116,  -101,  -116,  -116,  -116,    33,  -116,
      34,  -116,    71,  -116,  -116,  -116,  -116
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    21,    22,    23,    54,    24,    25,    26,    27,    28,
      29,    51,   125,    31,    81,    32,    33,   147,   112,   113,
     114,    34,    75,    76,    77,    35,    36
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      30,    50,    52,    53,   -15,    56,    55,   126,   -15,    42,
     136,    70,   138,    38,    39,    37,    87,   119,   120,    30,
     -15,   -15,    47,    71,    43,    72,    74,   149,    88,    79,
      80,    82,    90,    85,    39,   154,   145,    30,    48,   127,
     157,   158,    40,   101,    41,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   135,     2,    49,   110,    30,    30,
       5,   142,    86,   106,    41,   144,   120,    44,   146,    30,
     116,   117,   -51,   150,   118,    45,   124,    17,    46,    18,
      57,   111,   155,   156,    85,    39,    58,    30,   117,    74,
      20,    59,    69,    80,    84,    78,     2,     3,     4,    83,
     104,     5,   105,   108,   134,   115,    10,    11,    12,    13,
      14,     2,    49,   103,    16,    41,     5,    68,    17,   124,
      18,   128,    80,   129,   130,    30,    19,    30,   131,   151,
     137,    20,   140,    17,   153,    18,    63,    64,    65,    66,
      67,    68,    30,   139,   143,   121,    20,    91,   148,   132,
      30,    65,    66,    67,    68,    30,    30,    -2,     1,   152,
       2,     3,     4,   141,     0,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,   122,    15,     0,    16,   -12,
       2,    73,    17,     0,    18,     5,     0,     0,    60,     0,
      19,     0,   -12,     0,     0,    20,     0,     0,     0,     0,
       0,     0,    17,     0,    18,    61,    62,    60,    63,    64,
      65,    66,    67,    68,    60,    20,     0,     0,     0,     0,
       0,    89,     0,     0,    61,    62,    60,    63,    64,    65,
      66,    67,    68,     0,    63,    64,    65,    66,    67,    68,
     107,     0,     0,    61,    62,    60,    63,    64,    65,    66,
      67,    68,     0,     0,     0,     0,     0,    60,     0,   109,
       0,     0,    61,    62,     0,    63,    64,    65,    66,    67,
      68,     0,    60,     0,    61,    62,   102,    63,    64,    65,
      66,    67,    68,     0,    60,     0,     0,     0,   123,    61,
      62,     0,    63,    64,    65,    66,    67,    68,   -29,     0,
       0,    61,    62,   133,    63,    64,    65,    66,    67,    68,
     -30,     0,     0,     0,     0,   -29,   -29,     0,    63,    64,
      65,    66,    67,    68,    60,     0,     0,   -30,   -30,     0,
      63,    64,    65,    66,    67,    68,     0,     0,     0,     0,
       0,     0,    62,     0,    63,    64,    65,    66,    67,    68
};

static const yytype_int16 yycheck[] =
{
       0,    16,    17,    18,    18,    20,    19,   108,    22,     4,
     125,    37,   127,     7,     8,    22,    22,     7,     8,    19,
      34,    35,     4,    38,     5,    40,    41,   142,    34,    44,
      45,    46,    58,     7,     8,   150,   137,    37,    20,   109,
     155,   156,    36,    69,    38,    60,    61,    62,    63,    64,
      65,    66,    67,    68,   124,     3,     4,     4,    58,    59,
       8,   131,    36,    78,    38,     7,     8,    38,   138,    69,
      85,    86,    18,   143,    87,    38,    22,    25,    38,    27,
       0,    28,   152,   153,     7,     8,    22,    87,   103,   104,
      38,    35,    22,   108,     4,    36,     3,     4,     5,    38,
      40,     8,    39,    35,   119,    38,    13,    14,    15,    16,
      17,     3,     4,    36,    21,    38,     8,    31,    25,    22,
      27,    36,   137,     4,    40,   125,    33,   127,    39,   144,
      35,    38,    36,    25,    18,    27,    26,    27,    28,    29,
      30,    31,   142,    37,    39,    37,    38,    59,    37,   115,
     150,    28,    29,    30,    31,   155,   156,     0,     1,    39,
       3,     4,     5,   130,    -1,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,   104,    19,    -1,    21,    22,
       3,     4,    25,    -1,    27,     8,    -1,    -1,     6,    -1,
      33,    -1,    35,    -1,    -1,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    25,    -1,    27,    23,    24,     6,    26,    27,
      28,    29,    30,    31,     6,    38,    -1,    -1,    -1,    -1,
      -1,    39,    -1,    -1,    23,    24,     6,    26,    27,    28,
      29,    30,    31,    -1,    26,    27,    28,    29,    30,    31,
      39,    -1,    -1,    23,    24,     6,    26,    27,    28,    29,
      30,    31,    -1,    -1,    -1,    -1,    -1,     6,    -1,    39,
      -1,    -1,    23,    24,    -1,    26,    27,    28,    29,    30,
      31,    -1,     6,    -1,    23,    24,    37,    26,    27,    28,
      29,    30,    31,    -1,     6,    -1,    -1,    -1,    37,    23,
      24,    -1,    26,    27,    28,    29,    30,    31,     6,    -1,
      -1,    23,    24,    37,    26,    27,    28,    29,    30,    31,
       6,    -1,    -1,    -1,    -1,    23,    24,    -1,    26,    27,
      28,    29,    30,    31,     6,    -1,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    -1,    -1,    -1,    -1,
      -1,    -1,    24,    -1,    26,    27,    28,    29,    30,    31
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     4,     5,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    19,    21,    25,    27,    33,
      38,    42,    43,    44,    46,    47,    48,    49,    50,    51,
      52,    54,    56,    57,    62,    66,    67,    22,     7,     8,
      36,    38,     4,     5,    38,    38,    38,     4,    20,     4,
      50,    52,    50,    50,    45,    46,    50,     0,    22,    35,
       6,    23,    24,    26,    27,    28,    29,    30,    31,    22,
      42,    50,    50,     4,    50,    63,    64,    65,    36,    50,
      50,    55,    50,    38,     4,     7,    36,    22,    34,    39,
      42,    47,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    42,    37,    36,    40,    39,    50,    39,    35,    39,
       4,    28,    59,    60,    61,    38,    50,    50,    46,     7,
       8,    37,    63,    37,    22,    53,    55,    53,    36,     4,
      40,    39,    61,    37,    50,    53,    48,    35,    48,    37,
      36,    59,    53,    39,     7,    55,    53,    58,    37,    48,
      53,    50,    39,    18,    48,    53,    53,    48,    48
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    41,    42,    42,    42,    42,    43,    44,    45,    45,
      46,    46,    47,    47,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    49,    49,    50,    50,    51,
      51,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    53,    53,    54,    55,    55,    56,    57,    58,    58,
      59,    59,    59,    59,    60,    60,    61,    61,    62,    62,
      63,    63,    64,    64,    65,    65,    66,    67,    67,    67,
      67,    67,    67
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     3,     3,     3,     1,     3,     1,     3,
       1,     3,     0,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     1,     1,     3,     6,     1,     1,     3,
       6,     1,     1,     4,     2,     2,     5,     5,     1,     3,
       3,     3,     3,     3,     3,     2,     3,     3,     3,     2,
       3,     0,     2,     6,     0,     1,    10,     7,     0,     4,
       1,     3,     2,     4,     1,     3,     0,     1,     7,     8,
       1,     3,     1,     3,     0,     1,     4,     1,     1,     1,
       2,     1,     1
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
#line 90 "parser.y" /* yacc.c:1257  */
      { num_destruct(&((*yyvaluep).num)); out_dbg("parser.y: freed one num\n"); }
#line 1267 "parser.c" /* yacc.c:1257  */
        break;

    case 4: /* IDENTIFIER  */
#line 92 "parser.y" /* yacc.c:1257  */
      { free(((*yyvaluep).str)); out_dbg("parser.y: freed one str\n"); }
#line 1273 "parser.c" /* yacc.c:1257  */
        break;

    case 5: /* STRING  */
#line 92 "parser.y" /* yacc.c:1257  */
      { free(((*yyvaluep).str)); out_dbg("parser.y: freed one str\n"); }
#line 1279 "parser.c" /* yacc.c:1257  */
        break;

    case 6: /* COMPARISON  */
#line 92 "parser.y" /* yacc.c:1257  */
      { free(((*yyvaluep).str)); out_dbg("parser.y: freed one str\n"); }
#line 1285 "parser.c" /* yacc.c:1257  */
        break;

    case 7: /* OP_AND_ASSIGN  */
#line 92 "parser.y" /* yacc.c:1257  */
      { free(((*yyvaluep).str)); out_dbg("parser.y: freed one str\n"); }
#line 1291 "parser.c" /* yacc.c:1257  */
        break;

    case 8: /* PLUSPLUS_MINMIN  */
#line 92 "parser.y" /* yacc.c:1257  */
      { free(((*yyvaluep).str)); out_dbg("parser.y: freed one str\n"); }
#line 1297 "parser.c" /* yacc.c:1257  */
        break;

    case 44: /* instruction_block  */
#line 93 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1303 "parser.c" /* yacc.c:1257  */
        break;

    case 45: /* instruction_inside_block  */
#line 93 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1309 "parser.c" /* yacc.c:1257  */
        break;

    case 46: /* instruction_list  */
#line 93 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1315 "parser.c" /* yacc.c:1257  */
        break;

    case 47: /* instruction  */
#line 93 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1321 "parser.c" /* yacc.c:1257  */
        break;

    case 48: /* instruction_non_empty  */
#line 93 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1327 "parser.c" /* yacc.c:1257  */
        break;

    case 49: /* instruction_assignment  */
#line 93 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1333 "parser.c" /* yacc.c:1257  */
        break;

    case 50: /* expression  */
#line 91 "parser.y" /* yacc.c:1257  */
      { expr_destruct(((*yyvaluep).enode)); out_dbg("parser.y: freed one enode\n"); }
#line 1339 "parser.c" /* yacc.c:1257  */
        break;

    case 51: /* expression_assignment  */
#line 91 "parser.y" /* yacc.c:1257  */
      { expr_destruct(((*yyvaluep).enode)); out_dbg("parser.y: freed one enode\n"); }
#line 1345 "parser.c" /* yacc.c:1257  */
        break;

    case 52: /* expression_no_assignment  */
#line 91 "parser.y" /* yacc.c:1257  */
      { expr_destruct(((*yyvaluep).enode)); out_dbg("parser.y: freed one enode\n"); }
#line 1351 "parser.c" /* yacc.c:1257  */
        break;

    case 54: /* loop_while  */
#line 93 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1357 "parser.c" /* yacc.c:1257  */
        break;

    case 55: /* expression_or_empty  */
#line 91 "parser.y" /* yacc.c:1257  */
      { expr_destruct(((*yyvaluep).enode)); out_dbg("parser.y: freed one enode\n"); }
#line 1363 "parser.c" /* yacc.c:1257  */
        break;

    case 56: /* loop_for  */
#line 93 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1369 "parser.c" /* yacc.c:1257  */
        break;

    case 57: /* ifseq  */
#line 93 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1375 "parser.c" /* yacc.c:1257  */
        break;

    case 58: /* else_or_empty  */
#line 93 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1381 "parser.c" /* yacc.c:1257  */
        break;

    case 59: /* defarg  */
#line 94 "parser.y" /* yacc.c:1257  */
      { defargs_destruct(((*yyvaluep).defargs)); out_dbg("parser.y: freed one DEF argument chain\n"); }
#line 1387 "parser.c" /* yacc.c:1257  */
        break;

    case 60: /* defargs_list  */
#line 94 "parser.y" /* yacc.c:1257  */
      { defargs_destruct(((*yyvaluep).defargs)); out_dbg("parser.y: freed one DEF argument chain\n"); }
#line 1393 "parser.c" /* yacc.c:1257  */
        break;

    case 61: /* defargs_list_or_empty  */
#line 94 "parser.y" /* yacc.c:1257  */
      { defargs_destruct(((*yyvaluep).defargs)); out_dbg("parser.y: freed one DEF argument chain\n"); }
#line 1399 "parser.c" /* yacc.c:1257  */
        break;

    case 63: /* callarg  */
#line 95 "parser.y" /* yacc.c:1257  */
      { callargs_chain_destruct(((*yyvaluep).callargs)); out_dbg("parser.y: freed one CALL argument chain\n"); }
#line 1405 "parser.c" /* yacc.c:1257  */
        break;

    case 64: /* callargs_list  */
#line 95 "parser.y" /* yacc.c:1257  */
      { callargs_chain_destruct(((*yyvaluep).callargs)); out_dbg("parser.y: freed one CALL argument chain\n"); }
#line 1411 "parser.c" /* yacc.c:1257  */
        break;

    case 65: /* callargs_list_or_empty  */
#line 95 "parser.y" /* yacc.c:1257  */
      { callargs_chain_destruct(((*yyvaluep).callargs)); out_dbg("parser.y: freed one CALL argument chain\n"); }
#line 1417 "parser.c" /* yacc.c:1257  */
        break;

    case 66: /* function_call  */
#line 91 "parser.y" /* yacc.c:1257  */
      { expr_destruct(((*yyvaluep).enode)); out_dbg("parser.y: freed one enode\n"); }
#line 1423 "parser.c" /* yacc.c:1257  */
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
#line 102 "parser.y" /* yacc.c:1646  */
    { loc_reset(); }
#line 1711 "parser.c" /* yacc.c:1646  */
    break;

  case 5:
#line 105 "parser.y" /* yacc.c:1646  */
    { out_dbg("Error encountered, ran yyclearin and yyerrok\n"); yyclearin; yyerrok; }
#line 1717 "parser.c" /* yacc.c:1646  */
    break;

  case 6:
#line 109 "parser.y" /* yacc.c:1646  */
    {
		program_execute((yyvsp[0].prog), NULL);
		program_destruct((yyvsp[0].prog));
	}
#line 1726 "parser.c" /* yacc.c:1646  */
    break;

  case 7:
#line 116 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = (yyvsp[-1].prog); }
#line 1732 "parser.c" /* yacc.c:1646  */
    break;

  case 8:
#line 120 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = (yyvsp[0].prog); }
#line 1738 "parser.c" /* yacc.c:1646  */
    break;

  case 9:
#line 121 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = program_chain((yyvsp[-2].prog), (yyvsp[0].prog)); }
#line 1744 "parser.c" /* yacc.c:1646  */
    break;

  case 11:
#line 126 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = program_chain((yyvsp[-2].prog), (yyvsp[0].prog)); }
#line 1750 "parser.c" /* yacc.c:1646  */
    break;

  case 12:
#line 130 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = NULL; }
#line 1756 "parser.c" /* yacc.c:1646  */
    break;

  case 15:
#line 136 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = program_construct_expr((yyvsp[0].enode), FALSE); }
#line 1762 "parser.c" /* yacc.c:1646  */
    break;

  case 16:
#line 137 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = program_construct_str((yyvsp[0].str)); }
#line 1768 "parser.c" /* yacc.c:1646  */
    break;

  case 20:
#line 141 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = program_construct_return(NULL); }
#line 1774 "parser.c" /* yacc.c:1646  */
    break;

  case 21:
#line 142 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = program_construct_return((yyvsp[0].enode)); }
#line 1780 "parser.c" /* yacc.c:1646  */
    break;

  case 22:
#line 143 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = program_construct_break(); }
#line 1786 "parser.c" /* yacc.c:1646  */
    break;

  case 23:
#line 144 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = program_construct_continue(); }
#line 1792 "parser.c" /* yacc.c:1646  */
    break;

  case 24:
#line 145 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = (yyvsp[0].prog); }
#line 1798 "parser.c" /* yacc.c:1646  */
    break;

  case 25:
#line 149 "parser.y" /* yacc.c:1646  */
    {
		expr_t *enode = expr_construct_setvar((yyvsp[-2].str), NULL, (yyvsp[-1].str), FALSE, (yyvsp[0].enode));
		(yyval.prog) = program_construct_expr(enode, TRUE);
		free((yyvsp[-1].str));
	}
#line 1808 "parser.c" /* yacc.c:1646  */
    break;

  case 26:
#line 154 "parser.y" /* yacc.c:1646  */
    {
		expr_t *enode = expr_construct_setvar((yyvsp[-5].str), (yyvsp[-3].enode), (yyvsp[-1].str), FALSE, (yyvsp[0].enode));
		(yyval.prog) = program_construct_expr(enode, TRUE);
		free((yyvsp[-1].str));
	}
#line 1818 "parser.c" /* yacc.c:1646  */
    break;

  case 29:
#line 167 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_setvar((yyvsp[-2].str), NULL, (yyvsp[-1].str), FALSE, (yyvsp[0].enode)); free((yyvsp[-1].str)); }
#line 1824 "parser.c" /* yacc.c:1646  */
    break;

  case 30:
#line 168 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_setvar((yyvsp[-5].str), (yyvsp[-3].enode), (yyvsp[-1].str), FALSE, (yyvsp[0].enode)); free((yyvsp[-1].str)); }
#line 1830 "parser.c" /* yacc.c:1646  */
    break;

  case 31:
#line 172 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_number((yyvsp[0].num)); }
#line 1836 "parser.c" /* yacc.c:1646  */
    break;

  case 32:
#line 173 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_getvar((yyvsp[0].str), NULL); }
#line 1842 "parser.c" /* yacc.c:1646  */
    break;

  case 33:
#line 174 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_getvar((yyvsp[-3].str), (yyvsp[-1].enode)); }
#line 1848 "parser.c" /* yacc.c:1646  */
    break;

  case 34:
#line 175 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_setvar((yyvsp[0].str), NULL, (yyvsp[-1].str), FALSE, NULL); free((yyvsp[-1].str)); }
#line 1854 "parser.c" /* yacc.c:1646  */
    break;

  case 35:
#line 176 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_setvar((yyvsp[-1].str), NULL, (yyvsp[0].str), TRUE, NULL); free((yyvsp[0].str)); }
#line 1860 "parser.c" /* yacc.c:1646  */
    break;

  case 36:
#line 177 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_setvar((yyvsp[-3].str), (yyvsp[-1].enode), (yyvsp[-4].str), FALSE, NULL); free((yyvsp[-4].str)); }
#line 1866 "parser.c" /* yacc.c:1646  */
    break;

  case 37:
#line 178 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_setvar((yyvsp[-4].str), (yyvsp[-2].enode), (yyvsp[0].str), TRUE, NULL); free((yyvsp[0].str)); }
#line 1872 "parser.c" /* yacc.c:1646  */
    break;

  case 39:
#line 180 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op2_str("+", (yyvsp[-2].enode), (yyvsp[0].enode)); }
#line 1878 "parser.c" /* yacc.c:1646  */
    break;

  case 40:
#line 181 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op2_str("-", (yyvsp[-2].enode), (yyvsp[0].enode)); }
#line 1884 "parser.c" /* yacc.c:1646  */
    break;

  case 41:
#line 182 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op2_str("*", (yyvsp[-2].enode), (yyvsp[0].enode)); }
#line 1890 "parser.c" /* yacc.c:1646  */
    break;

  case 42:
#line 183 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op2_str("/", (yyvsp[-2].enode), (yyvsp[0].enode)); }
#line 1896 "parser.c" /* yacc.c:1646  */
    break;

  case 43:
#line 184 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op2_str("^", (yyvsp[-2].enode), (yyvsp[0].enode)); }
#line 1902 "parser.c" /* yacc.c:1646  */
    break;

  case 44:
#line 185 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op2_str("%", (yyvsp[-2].enode), (yyvsp[0].enode)); }
#line 1908 "parser.c" /* yacc.c:1646  */
    break;

  case 45:
#line 186 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op1_str("-", (yyvsp[0].enode)); }
#line 1914 "parser.c" /* yacc.c:1646  */
    break;

  case 46:
#line 187 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op2_str((yyvsp[-1].str), (yyvsp[-2].enode), (yyvsp[0].enode)); free((yyvsp[-1].str)); }
#line 1920 "parser.c" /* yacc.c:1646  */
    break;

  case 47:
#line 188 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op2_str("&&", (yyvsp[-2].enode), (yyvsp[0].enode)); }
#line 1926 "parser.c" /* yacc.c:1646  */
    break;

  case 48:
#line 189 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op2_str("||", (yyvsp[-2].enode), (yyvsp[0].enode)); }
#line 1932 "parser.c" /* yacc.c:1646  */
    break;

  case 49:
#line 190 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op1_str("!", (yyvsp[0].enode)); }
#line 1938 "parser.c" /* yacc.c:1646  */
    break;

  case 50:
#line 191 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = (yyvsp[-1].enode); }
#line 1944 "parser.c" /* yacc.c:1646  */
    break;

  case 53:
#line 200 "parser.y" /* yacc.c:1646  */
    {
		program_loop_t loop;
		loop.exprbefore = NULL;
		loop.testbefore = (yyvsp[-3].enode);
		loop.core = (yyvsp[0].prog);
		loop.testafter = NULL;
		loop.exprafter = NULL;
		(yyval.prog) = program_construct_loop(&loop);
	}
#line 1958 "parser.c" /* yacc.c:1646  */
    break;

  case 54:
#line 212 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = NULL; }
#line 1964 "parser.c" /* yacc.c:1646  */
    break;

  case 56:
#line 217 "parser.y" /* yacc.c:1646  */
    {
		program_loop_t loop;
		loop.exprbefore = (yyvsp[-7].enode);
		loop.testbefore = (yyvsp[-5].enode);
		loop.core = (yyvsp[0].prog);
		loop.testafter = NULL;
		loop.exprafter = (yyvsp[-3].enode);
		(yyval.prog) = program_construct_loop(&loop);
	}
#line 1978 "parser.c" /* yacc.c:1646  */
    break;

  case 57:
#line 229 "parser.y" /* yacc.c:1646  */
    {
		program_ifseq_t ifseq;
		ifseq.expr = (yyvsp[-4].enode);
		ifseq.pif = (yyvsp[-1].prog);
		ifseq.pelse = (yyvsp[0].prog);
		(yyval.prog) = program_construct_ifseq(&ifseq);
	}
#line 1990 "parser.c" /* yacc.c:1646  */
    break;

  case 58:
#line 239 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = NULL; }
#line 1996 "parser.c" /* yacc.c:1646  */
    break;

  case 59:
#line 240 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = (yyvsp[0].prog); }
#line 2002 "parser.c" /* yacc.c:1646  */
    break;

  case 60:
#line 244 "parser.y" /* yacc.c:1646  */
    { (yyval.defargs) = defargs_construct(DARG_VALUE, (yyvsp[0].str)); }
#line 2008 "parser.c" /* yacc.c:1646  */
    break;

  case 61:
#line 245 "parser.y" /* yacc.c:1646  */
    { (yyval.defargs) = defargs_construct(DARG_ARRAYVALUE, (yyvsp[-2].str)); }
#line 2014 "parser.c" /* yacc.c:1646  */
    break;

  case 62:
#line 246 "parser.y" /* yacc.c:1646  */
    { (yyval.defargs) = defargs_construct(DARG_REF, (yyvsp[0].str)); }
#line 2020 "parser.c" /* yacc.c:1646  */
    break;

  case 63:
#line 247 "parser.y" /* yacc.c:1646  */
    { (yyval.defargs) = defargs_construct(DARG_ARRAYREF, (yyvsp[-2].str)); }
#line 2026 "parser.c" /* yacc.c:1646  */
    break;

  case 65:
#line 252 "parser.y" /* yacc.c:1646  */
    { (yyval.defargs) = defargs_chain((yyvsp[-2].defargs), (yyvsp[0].defargs)); }
#line 2032 "parser.c" /* yacc.c:1646  */
    break;

  case 66:
#line 256 "parser.y" /* yacc.c:1646  */
    { (yyval.defargs) = NULL; }
#line 2038 "parser.c" /* yacc.c:1646  */
    break;

  case 68:
#line 261 "parser.y" /* yacc.c:1646  */
    {
		int r;
		if ((r = vars_function_construct((yyvsp[-5].str), (yyvsp[-3].defargs), (yyvsp[0].prog), FALSE)) != ERROR_NONE)
			outln_error_code(r);
	}
#line 2048 "parser.c" /* yacc.c:1646  */
    break;

  case 69:
#line 266 "parser.y" /* yacc.c:1646  */
    {
		int r;
		if ((r = vars_function_construct((yyvsp[-5].str), (yyvsp[-3].defargs), (yyvsp[0].prog), TRUE)) != ERROR_NONE)
			outln_error_code(r);
	}
#line 2058 "parser.c" /* yacc.c:1646  */
    break;

  case 70:
#line 274 "parser.y" /* yacc.c:1646  */
    { (yyval.callargs) = callargs_construct(CARG_EXPR, (yyvsp[0].enode), NULL); }
#line 2064 "parser.c" /* yacc.c:1646  */
    break;

  case 71:
#line 275 "parser.y" /* yacc.c:1646  */
    { (yyval.callargs) = callargs_construct(CARG_ARRAY, NULL, (yyvsp[-2].str)); }
#line 2070 "parser.c" /* yacc.c:1646  */
    break;

  case 73:
#line 280 "parser.y" /* yacc.c:1646  */
    { (yyval.callargs) = callargs_chain((yyvsp[-2].callargs), (yyvsp[0].callargs)); }
#line 2076 "parser.c" /* yacc.c:1646  */
    break;

  case 74:
#line 284 "parser.y" /* yacc.c:1646  */
    { (yyval.callargs) = NULL; }
#line 2082 "parser.c" /* yacc.c:1646  */
    break;

  case 76:
#line 289 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_function_call((yyvsp[-3].str), (yyvsp[-1].callargs)); }
#line 2088 "parser.c" /* yacc.c:1646  */
    break;

  case 78:
#line 294 "parser.y" /* yacc.c:1646  */
    { YYABORT; }
#line 2094 "parser.c" /* yacc.c:1646  */
    break;

  case 79:
#line 295 "parser.y" /* yacc.c:1646  */
    {
		vars_display_all();
	}
#line 2102 "parser.c" /* yacc.c:1646  */
    break;

  case 80:
#line 298 "parser.y" /* yacc.c:1646  */
    {
		if (num_libswitch((yyvsp[0].str)) == 0) {
			outln_error("Unknown library");
		}
		free((yyvsp[0].str));
	}
#line 2113 "parser.c" /* yacc.c:1646  */
    break;

  case 81:
#line 304 "parser.y" /* yacc.c:1646  */
    {
		outln(L_ENFORCE, "%s", num_identify_yourself());
	}
#line 2121 "parser.c" /* yacc.c:1646  */
    break;

  case 82:
#line 307 "parser.y" /* yacc.c:1646  */
    {
		lib_list();
	}
#line 2129 "parser.c" /* yacc.c:1646  */
    break;


#line 2133 "parser.c" /* yacc.c:1646  */
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
#line 312 "parser.y" /* yacc.c:1906  */


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

