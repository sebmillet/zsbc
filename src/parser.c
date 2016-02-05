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
#line 30 "parser.y" /* yacc.c:339  */


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

typedef struct YYLTYPE YYLTYPE;
const code_location_t code_loc(const YYLTYPE yl);

const char *input_get_name();

extern defargs_t *defarg_t_badarg;
extern int flag_quitting;

#ifdef BISON_DEBUG
#define YYDEBUG 1
#endif


#line 95 "parser.c" /* yacc.c:339  */

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
    SYMBOLS = 265,
    LIBSWITCH = 266,
    LIBLIST = 267,
    WHILE = 268,
    FOR = 269,
    BREAK = 270,
    CONTINUE = 271,
    IF = 272,
    ELSE = 273,
    DEFINE = 274,
    MYVOID = 275,
    RETURN = 276,
    AUTOLIST = 277,
    PRINT = 278,
    NEWLINE = 279,
    LOGIC_OR = 280,
    LOGIC_AND = 281,
    LOGIC_NOT = 282,
    NEG = 283,
    LOWER_THAN_ELSE = 284
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
#define SYMBOLS 265
#define LIBSWITCH 266
#define LIBLIST 267
#define WHILE 268
#define FOR 269
#define BREAK 270
#define CONTINUE 271
#define IF 272
#define ELSE 273
#define DEFINE 274
#define MYVOID 275
#define RETURN 276
#define AUTOLIST 277
#define PRINT 278
#define NEWLINE 279
#define LOGIC_OR 280
#define LOGIC_AND 281
#define LOGIC_NOT 282
#define NEG 283
#define LOWER_THAN_ELSE 284

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 76 "parser.y" /* yacc.c:355  */

	numptr num;
	expr_t *enode;
	char *str;
	program_t *prog;
	defargs_t *defargs;
	callargs_t *callargs;

#line 202 "parser.c" /* yacc.c:355  */
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
#line 59 "parser.y" /* yacc.c:355  */

void activate_bison_debug();
void hackbc_enter();
void hackbc_terminate();
void hackbc_inc_nested();
void hackbc_dec_nested();

#ifndef YY_TYPEDEF_YY_BUFFER_STATE
#define YY_TYPEDEF_YY_BUFFER_STATE
typedef struct yy_buffer_state *YY_BUFFER_STATE;
#endif
YY_BUFFER_STATE yy_scan_buffer(char *bytes, size_t len);

#line 241 "parser.c" /* yacc.c:355  */

#endif /* !YY_YY_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 247 "parser.c" /* yacc.c:358  */

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
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   380

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  99
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  180

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   284

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    32,     2,     2,
      41,    42,    30,    28,    43,    29,     2,    31,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    38,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    39,     2,    40,    33,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    36,     2,    37,     2,     2,     2,     2,
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
      25,    26,    27,    34,    35
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   125,   125,   126,   126,   127,   127,   128,   136,   148,
     152,   153,   157,   158,   162,   163,   167,   167,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   187,   192,   200,   204,   208,   209,   213,   214,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   241,
     242,   243,   247,   248,   252,   253,   257,   269,   270,   274,
     286,   293,   303,   304,   308,   309,   310,   314,   315,   330,
     331,   346,   347,   351,   355,   359,   362,   368,   369,   373,
     374,   378,   379,   383,   387,   388,   389,   392,   398,   401
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER", "IDENTIFIER", "STRING",
  "COMPARISON", "OP_AND_ASSIGN", "PLUSPLUS_MINMIN", "QUIT", "SYMBOLS",
  "LIBSWITCH", "LIBLIST", "WHILE", "FOR", "BREAK", "CONTINUE", "IF",
  "ELSE", "DEFINE", "MYVOID", "RETURN", "AUTOLIST", "PRINT", "NEWLINE",
  "LOGIC_OR", "LOGIC_AND", "LOGIC_NOT", "'+'", "'-'", "'*'", "'/'", "'%'",
  "'^'", "NEG", "LOWER_THAN_ELSE", "'{'", "'}'", "';'", "'['", "']'",
  "'('", "')'", "','", "$accept", "input", "$@1", "$@2", "program",
  "instruction_block", "instruction_inside_block", "instruction_list",
  "instruction", "instruction_non_empty", "$@3",
  "my_instruction_non_empty", "instruction_expr_assignment",
  "instruction_expr_no_assignment", "instruction_string", "expression",
  "expression_assignment", "expression_no_assignment", "print_elem",
  "print_list", "newlines_or_empty", "loop_while", "expression_or_empty",
  "loop_for", "ifseq", "defargbyval", "defarg", "defargsbyval_list",
  "defargs_list", "defargs_list_or_empty", "hackbc_enter",
  "hackbc_terminate", "function_definition", "callarg", "callargs_list",
  "callargs_list_or_empty", "function_call", "statement", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,    43,    45,
      42,    47,    37,    94,   283,   284,   123,   125,    59,    91,
      93,    40,    41,    44
};
# endif

#define YYPACT_NINF -116

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-116)))

#define YYTABLE_NINF -39

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     113,    -7,    19,   152,    11,   113,  -116,  -116,   169,  -116,
      28,    -6,    -1,  -116,  -116,     8,    48,    51,    42,    48,
      48,   152,    48,    46,  -116,    34,  -116,  -116,  -116,  -116,
    -116,   283,  -116,   337,  -116,  -116,  -116,  -116,  -116,  -116,
      68,  -116,    60,  -116,    54,  -116,    48,  -116,    48,   155,
      41,    48,    48,    48,   208,   283,  -116,    47,  -116,    50,
    -116,  -116,  -116,  -116,    52,   321,  -116,    -8,    34,   172,
     113,   152,    48,    48,    48,    48,    48,    48,    48,    48,
      48,  -116,    10,   113,   293,   226,   221,   283,  -116,    53,
      49,    48,   193,   283,    56,   211,    48,    48,    61,    51,
      42,   152,  -116,  -116,  -116,  -116,   334,   314,   321,    -5,
      -5,    66,    66,    66,    66,    62,    96,  -116,    35,   104,
     155,  -116,   239,    78,    48,    78,   334,   255,  -116,  -116,
    -116,    34,     9,    65,    48,  -116,  -116,  -116,  -116,    78,
    -116,    72,  -116,    59,   107,  -116,  -116,    77,    73,     9,
     304,  -116,  -116,   152,    48,   120,    48,   108,     9,    78,
     101,  -116,   106,    78,   334,   112,  -116,  -116,    78,    78,
    -116,  -116,  -116,  -116,  -116,  -116,  -116,  -116,  -116,  -116
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    14,    83,     0,     1,    39,    40,    34,
       0,     0,     0,    26,    27,     0,    24,     0,     0,     0,
       0,    14,     0,     0,    30,     8,    12,    15,    18,    19,
      20,     0,    36,    35,    21,    22,    23,    46,    95,    96,
      98,    99,     0,    94,     0,     7,     0,    43,     0,    91,
      42,     0,    67,     0,    40,    25,    35,    72,    77,    29,
      59,    60,    61,    62,    28,    57,    53,     0,    10,     0,
       0,    14,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    97,     0,     0,    31,     0,    40,    87,    89,    92,
       0,     0,     0,    68,     0,     0,     0,     0,     0,     0,
       0,    14,     9,    58,     4,    13,    54,    56,    55,    47,
      48,    49,    50,    52,    51,     0,     0,     6,    41,     0,
       0,    93,     0,    64,    67,    64,    37,     0,    73,    78,
      63,    11,    81,     0,     0,    45,    88,    90,    44,    64,
      16,     0,    16,    41,     0,    74,    79,    82,     0,    81,
      32,    65,    66,     0,    67,    70,     0,    75,     0,    64,
       0,    17,     0,    64,    38,     0,    80,    16,    64,    64,
      16,    76,    84,    16,    16,    71,    85,    84,    69,    86
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -116,     4,  -116,  -116,  -116,  -116,  -116,    -9,    75,   131,
    -116,     0,   -16,   -12,   -10,   -15,  -116,    -3,    64,  -116,
    -115,  -116,  -113,  -116,  -116,   -14,     3,  -116,  -116,    13,
    -116,     6,  -116,    67,  -116,  -116,  -116,  -116
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,    23,    24,    67,    25,    26,   152,
     153,    27,    28,    29,    30,    31,    32,    56,    63,    64,
     140,    34,    94,    35,    36,   145,   146,    59,   147,   148,
      42,   176,    43,    88,    89,    90,    37,    44
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      33,    55,    60,    58,    65,    66,    61,    69,    62,    45,
     142,   141,    68,    57,   115,    33,   101,     5,    33,     6,
      38,    39,    40,    41,   151,    77,    78,    79,    80,   102,
     116,    84,    50,    85,    87,    51,    92,    93,    95,   144,
      52,   162,   134,   135,   167,     7,     8,     9,   170,    53,
      10,     7,    54,   173,   174,    57,    10,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   156,   135,    33,    19,
      70,    20,    71,    81,   104,    19,   122,    20,    83,    82,
      91,   126,   127,    22,    60,   129,    98,   117,    61,    22,
      62,   121,   131,    99,   124,   100,   120,    33,    33,    80,
     133,   128,   139,   132,   127,    87,   149,     7,    54,    93,
     154,   157,    10,    -2,     1,   159,    -3,    -3,    -3,   150,
     158,    -3,    -5,    -5,    -5,    -5,    -3,    -3,    -3,    -3,
      -3,    19,    -5,    20,    -3,    -3,    -3,    -3,   163,    93,
      -3,   164,    -3,   168,   136,    22,   105,   165,   169,    -3,
      33,    -3,   171,   161,    -3,     7,     8,     9,     7,    86,
      10,   166,   160,    10,   130,    11,    12,    13,    14,    15,
       0,     0,     0,    16,    17,    18,    46,    47,    72,    19,
       0,    20,    19,   179,    20,     0,     0,   137,    21,     0,
       0,     0,     0,    22,     0,     0,    22,    73,    74,    72,
      75,    76,    77,    78,    79,    80,     0,     0,    48,     0,
      49,     0,     0,     0,   103,    96,    47,    72,    73,    74,
       0,    75,    76,    77,    78,    79,    80,     0,    96,    47,
       0,     0,    72,     0,     0,   123,    73,    74,     0,    75,
      76,    77,    78,    79,    80,    72,     0,    97,     0,    49,
       0,    73,    74,   125,    75,    76,    77,    78,    79,    80,
     119,    72,    49,     0,    73,    74,   118,    75,    76,    77,
      78,    79,    80,   155,     0,     0,     0,     0,     0,   138,
      73,    74,     0,    75,    76,    77,    78,    79,    80,    72,
       0,     0,     0,     0,     0,   143,     0,     0,   172,   -37,
       0,   175,     0,     0,   177,   178,     0,     0,    73,    74,
     -38,    75,    76,    77,    78,    79,    80,     0,   -37,   -37,
      72,    75,    76,    77,    78,    79,    80,    72,     0,   -38,
     -38,     0,    75,    76,    77,    78,    79,    80,     0,     0,
      74,     0,    75,    76,    77,    78,    79,    80,     0,    75,
      76,    77,    78,    79,    80,   -33,     0,     0,     0,     0,
       0,   -33,    75,    76,    77,    78,    79,    80,     0,     0,
       0,     0,     0,     0,   -33,   -33,     0,     0,     0,     0,
     -33
};

static const yytype_int16 yycheck[] =
{
       3,    16,    18,    17,    19,    20,    18,    22,    18,     5,
     125,   124,    21,     4,     4,    18,    24,    24,    21,     0,
       9,    10,    11,    12,   139,    30,    31,    32,    33,    37,
      20,    46,     4,    48,    49,    41,    51,    52,    53,    30,
      41,   154,     7,     8,   159,     3,     4,     5,   163,    41,
       8,     3,     4,   168,   169,     4,     8,    72,    73,    74,
      75,    76,    77,    78,    79,    80,     7,     8,    71,    27,
      24,    29,    38,     5,    70,    27,    91,    29,    24,    19,
      39,    96,    97,    41,   100,    99,    39,    83,   100,    41,
     100,    42,   101,    43,    38,    43,    43,   100,   101,    33,
       4,    40,    24,    41,   119,   120,    41,     3,     4,   124,
      38,     4,     8,     0,     1,    42,     3,     4,     5,   134,
      43,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    27,    19,    29,    21,    22,    23,    24,    18,   154,
      27,   156,    29,    42,    40,    41,    71,    39,    42,    36,
     153,    38,    40,   153,    41,     3,     4,     5,     3,     4,
       8,   158,   149,     8,   100,    13,    14,    15,    16,    17,
      -1,    -1,    -1,    21,    22,    23,     7,     8,     6,    27,
      -1,    29,    27,   177,    29,    -1,    -1,   120,    36,    -1,
      -1,    -1,    -1,    41,    -1,    -1,    41,    25,    26,     6,
      28,    29,    30,    31,    32,    33,    -1,    -1,    39,    -1,
      41,    -1,    -1,    -1,    42,     7,     8,     6,    25,    26,
      -1,    28,    29,    30,    31,    32,    33,    -1,     7,     8,
      -1,    -1,     6,    -1,    -1,    42,    25,    26,    -1,    28,
      29,    30,    31,    32,    33,     6,    -1,    39,    -1,    41,
      -1,    25,    26,    42,    28,    29,    30,    31,    32,    33,
      39,     6,    41,    -1,    25,    26,    40,    28,    29,    30,
      31,    32,    33,   142,    -1,    -1,    -1,    -1,    -1,    40,
      25,    26,    -1,    28,    29,    30,    31,    32,    33,     6,
      -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,   167,     6,
      -1,   170,    -1,    -1,   173,   174,    -1,    -1,    25,    26,
       6,    28,    29,    30,    31,    32,    33,    -1,    25,    26,
       6,    28,    29,    30,    31,    32,    33,     6,    -1,    25,
      26,    -1,    28,    29,    30,    31,    32,    33,    -1,    -1,
      26,    -1,    28,    29,    30,    31,    32,    33,    -1,    28,
      29,    30,    31,    32,    33,    18,    -1,    -1,    -1,    -1,
      -1,    24,    28,    29,    30,    31,    32,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    37,    38,    -1,    -1,    -1,    -1,
      43
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    45,    46,    47,    24,     0,     3,     4,     5,
       8,    13,    14,    15,    16,    17,    21,    22,    23,    27,
      29,    36,    41,    48,    49,    51,    52,    55,    56,    57,
      58,    59,    60,    61,    65,    67,    68,    80,     9,    10,
      11,    12,    74,    76,    81,    45,     7,     8,    39,    41,
       4,    41,    41,    41,     4,    59,    61,     4,    69,    71,
      56,    57,    58,    62,    63,    59,    59,    50,    51,    59,
      24,    38,     6,    25,    26,    28,    29,    30,    31,    32,
      33,     5,    19,    24,    59,    59,     4,    59,    77,    78,
      79,    39,    59,    59,    66,    59,     7,    39,    39,    43,
      43,    24,    37,    42,    45,    52,    59,    59,    59,    59,
      59,    59,    59,    59,    59,     4,    20,    45,    40,    39,
      43,    42,    59,    42,    38,    42,    59,    59,    40,    69,
      62,    51,    41,     4,     7,     8,    40,    77,    40,    24,
      64,    66,    64,    40,    30,    69,    70,    72,    73,    41,
      59,    64,    53,    54,    38,    53,     7,     4,    43,    42,
      73,    55,    66,    18,    59,    39,    70,    64,    42,    42,
      64,    40,    53,    64,    64,    53,    75,    53,    53,    75
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    44,    45,    46,    45,    47,    45,    45,    48,    49,
      50,    50,    51,    51,    52,    52,    54,    53,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    56,    56,    57,    58,    59,    59,    60,    60,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    62,
      62,    62,    63,    63,    64,    64,    65,    66,    66,    67,
      68,    68,    69,    69,    70,    70,    70,    71,    71,    72,
      72,    73,    73,    74,    75,    76,    76,    77,    77,    78,
      78,    79,    79,    80,    81,    81,    81,    81,    81,    81
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     0,     4,     0,     4,     3,     1,     3,
       1,     3,     1,     3,     0,     1,     0,     2,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     2,     2,
       1,     3,     6,     1,     1,     1,     1,     3,     6,     1,
       1,     4,     2,     2,     5,     5,     1,     3,     3,     3,
       3,     3,     3,     2,     3,     3,     3,     2,     3,     1,
       1,     1,     1,     3,     0,     2,     6,     0,     1,    10,
       6,     9,     1,     3,     1,     2,     4,     1,     3,     1,
       3,     0,     1,     0,     0,     9,    10,     1,     3,     1,
       3,     0,     1,     4,     1,     1,     1,     2,     1,     1
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
#line 113 "parser.y" /* yacc.c:1257  */
      { num_destruct(&((*yyvaluep).num)); out_dbg("parser.y: freed one num\n"); }
#line 1312 "parser.c" /* yacc.c:1257  */
        break;

    case 4: /* IDENTIFIER  */
#line 115 "parser.y" /* yacc.c:1257  */
      { free(((*yyvaluep).str)); out_dbg("parser.y: freed one str\n"); }
#line 1318 "parser.c" /* yacc.c:1257  */
        break;

    case 5: /* STRING  */
#line 115 "parser.y" /* yacc.c:1257  */
      { free(((*yyvaluep).str)); out_dbg("parser.y: freed one str\n"); }
#line 1324 "parser.c" /* yacc.c:1257  */
        break;

    case 6: /* COMPARISON  */
#line 115 "parser.y" /* yacc.c:1257  */
      { free(((*yyvaluep).str)); out_dbg("parser.y: freed one str\n"); }
#line 1330 "parser.c" /* yacc.c:1257  */
        break;

    case 7: /* OP_AND_ASSIGN  */
#line 115 "parser.y" /* yacc.c:1257  */
      { free(((*yyvaluep).str)); out_dbg("parser.y: freed one str\n"); }
#line 1336 "parser.c" /* yacc.c:1257  */
        break;

    case 8: /* PLUSPLUS_MINMIN  */
#line 115 "parser.y" /* yacc.c:1257  */
      { free(((*yyvaluep).str)); out_dbg("parser.y: freed one str\n"); }
#line 1342 "parser.c" /* yacc.c:1257  */
        break;

    case 49: /* instruction_block  */
#line 116 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1348 "parser.c" /* yacc.c:1257  */
        break;

    case 50: /* instruction_inside_block  */
#line 116 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1354 "parser.c" /* yacc.c:1257  */
        break;

    case 51: /* instruction_list  */
#line 116 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1360 "parser.c" /* yacc.c:1257  */
        break;

    case 52: /* instruction  */
#line 116 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1366 "parser.c" /* yacc.c:1257  */
        break;

    case 53: /* instruction_non_empty  */
#line 116 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1372 "parser.c" /* yacc.c:1257  */
        break;

    case 55: /* my_instruction_non_empty  */
#line 116 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1378 "parser.c" /* yacc.c:1257  */
        break;

    case 56: /* instruction_expr_assignment  */
#line 116 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1384 "parser.c" /* yacc.c:1257  */
        break;

    case 57: /* instruction_expr_no_assignment  */
#line 116 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1390 "parser.c" /* yacc.c:1257  */
        break;

    case 58: /* instruction_string  */
#line 116 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1396 "parser.c" /* yacc.c:1257  */
        break;

    case 59: /* expression  */
#line 114 "parser.y" /* yacc.c:1257  */
      { expr_destruct(((*yyvaluep).enode)); out_dbg("parser.y: freed one enode\n"); }
#line 1402 "parser.c" /* yacc.c:1257  */
        break;

    case 60: /* expression_assignment  */
#line 114 "parser.y" /* yacc.c:1257  */
      { expr_destruct(((*yyvaluep).enode)); out_dbg("parser.y: freed one enode\n"); }
#line 1408 "parser.c" /* yacc.c:1257  */
        break;

    case 61: /* expression_no_assignment  */
#line 114 "parser.y" /* yacc.c:1257  */
      { expr_destruct(((*yyvaluep).enode)); out_dbg("parser.y: freed one enode\n"); }
#line 1414 "parser.c" /* yacc.c:1257  */
        break;

    case 62: /* print_elem  */
#line 116 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1420 "parser.c" /* yacc.c:1257  */
        break;

    case 63: /* print_list  */
#line 116 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1426 "parser.c" /* yacc.c:1257  */
        break;

    case 65: /* loop_while  */
#line 116 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1432 "parser.c" /* yacc.c:1257  */
        break;

    case 66: /* expression_or_empty  */
#line 114 "parser.y" /* yacc.c:1257  */
      { expr_destruct(((*yyvaluep).enode)); out_dbg("parser.y: freed one enode\n"); }
#line 1438 "parser.c" /* yacc.c:1257  */
        break;

    case 67: /* loop_for  */
#line 116 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1444 "parser.c" /* yacc.c:1257  */
        break;

    case 68: /* ifseq  */
#line 116 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1450 "parser.c" /* yacc.c:1257  */
        break;

    case 69: /* defargbyval  */
#line 117 "parser.y" /* yacc.c:1257  */
      { defargs_destruct(((*yyvaluep).defargs)); out_dbg("parser.y: freed one DEF argument chain\n"); }
#line 1456 "parser.c" /* yacc.c:1257  */
        break;

    case 70: /* defarg  */
#line 117 "parser.y" /* yacc.c:1257  */
      { defargs_destruct(((*yyvaluep).defargs)); out_dbg("parser.y: freed one DEF argument chain\n"); }
#line 1462 "parser.c" /* yacc.c:1257  */
        break;

    case 71: /* defargsbyval_list  */
#line 117 "parser.y" /* yacc.c:1257  */
      { defargs_destruct(((*yyvaluep).defargs)); out_dbg("parser.y: freed one DEF argument chain\n"); }
#line 1468 "parser.c" /* yacc.c:1257  */
        break;

    case 72: /* defargs_list  */
#line 117 "parser.y" /* yacc.c:1257  */
      { defargs_destruct(((*yyvaluep).defargs)); out_dbg("parser.y: freed one DEF argument chain\n"); }
#line 1474 "parser.c" /* yacc.c:1257  */
        break;

    case 73: /* defargs_list_or_empty  */
#line 117 "parser.y" /* yacc.c:1257  */
      { defargs_destruct(((*yyvaluep).defargs)); out_dbg("parser.y: freed one DEF argument chain\n"); }
#line 1480 "parser.c" /* yacc.c:1257  */
        break;

    case 77: /* callarg  */
#line 118 "parser.y" /* yacc.c:1257  */
      { callargs_chain_destruct(((*yyvaluep).callargs)); out_dbg("parser.y: freed one CALL argument chain\n"); }
#line 1486 "parser.c" /* yacc.c:1257  */
        break;

    case 78: /* callargs_list  */
#line 118 "parser.y" /* yacc.c:1257  */
      { callargs_chain_destruct(((*yyvaluep).callargs)); out_dbg("parser.y: freed one CALL argument chain\n"); }
#line 1492 "parser.c" /* yacc.c:1257  */
        break;

    case 79: /* callargs_list_or_empty  */
#line 118 "parser.y" /* yacc.c:1257  */
      { callargs_chain_destruct(((*yyvaluep).callargs)); out_dbg("parser.y: freed one CALL argument chain\n"); }
#line 1498 "parser.c" /* yacc.c:1257  */
        break;

    case 80: /* function_call  */
#line 114 "parser.y" /* yacc.c:1257  */
      { expr_destruct(((*yyvaluep).enode)); out_dbg("parser.y: freed one enode\n"); }
#line 1504 "parser.c" /* yacc.c:1257  */
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
#line 125 "parser.y" /* yacc.c:1646  */
    { outstring_reset(); loc_reset(); }
#line 1792 "parser.c" /* yacc.c:1646  */
    break;

  case 3:
#line 126 "parser.y" /* yacc.c:1646  */
    { outstring_reset(); }
#line 1798 "parser.c" /* yacc.c:1646  */
    break;

  case 5:
#line 127 "parser.y" /* yacc.c:1646  */
    { outstring_reset(); }
#line 1804 "parser.c" /* yacc.c:1646  */
    break;

  case 7:
#line 128 "parser.y" /* yacc.c:1646  */
    {
		out_dbg("Error encountered, ran yyclearin and yyerrok\n");
		yyclearin; yyerrok;
		outstring_reset();
	}
#line 1814 "parser.c" /* yacc.c:1646  */
    break;

  case 8:
#line 136 "parser.y" /* yacc.c:1646  */
    {
		exec_ctx_t *pexec_ctx = construct_exec_ctx_t();
		int r = program_execute((yyvsp[0].prog), NULL, pexec_ctx);
		if (r != ERROR_NONE) {
			outln_exec_error(r, pexec_ctx, FALSE);
		}
		program_destruct((yyvsp[0].prog));
		destruct_exec_ctx_t(pexec_ctx, FALSE);
	}
#line 1828 "parser.c" /* yacc.c:1646  */
    break;

  case 9:
#line 148 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = (yyvsp[-1].prog); }
#line 1834 "parser.c" /* yacc.c:1646  */
    break;

  case 10:
#line 152 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = (yyvsp[0].prog); }
#line 1840 "parser.c" /* yacc.c:1646  */
    break;

  case 11:
#line 153 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = program_chain((yyvsp[-2].prog), (yyvsp[0].prog)); }
#line 1846 "parser.c" /* yacc.c:1646  */
    break;

  case 13:
#line 158 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = program_chain((yyvsp[-2].prog), (yyvsp[0].prog)); }
#line 1852 "parser.c" /* yacc.c:1646  */
    break;

  case 14:
#line 162 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = NULL; }
#line 1858 "parser.c" /* yacc.c:1646  */
    break;

  case 16:
#line 167 "parser.y" /* yacc.c:1646  */
    { hackbc_inc_nested(); }
#line 1864 "parser.c" /* yacc.c:1646  */
    break;

  case 17:
#line 167 "parser.y" /* yacc.c:1646  */
    { hackbc_dec_nested(); (yyval.prog) = (yyvsp[0].prog); }
#line 1870 "parser.c" /* yacc.c:1646  */
    break;

  case 24:
#line 177 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = program_construct_return(NULL, code_loc((yyloc))); }
#line 1876 "parser.c" /* yacc.c:1646  */
    break;

  case 25:
#line 178 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = program_construct_return((yyvsp[0].enode), code_loc((yyloc))); }
#line 1882 "parser.c" /* yacc.c:1646  */
    break;

  case 26:
#line 179 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = program_construct_break(code_loc((yyloc))); }
#line 1888 "parser.c" /* yacc.c:1646  */
    break;

  case 27:
#line 180 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = program_construct_continue(code_loc((yyloc))); }
#line 1894 "parser.c" /* yacc.c:1646  */
    break;

  case 28:
#line 181 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = (yyvsp[0].prog); }
#line 1900 "parser.c" /* yacc.c:1646  */
    break;

  case 29:
#line 182 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = program_construct_autolist((yyvsp[0].defargs), code_loc((yyloc))); }
#line 1906 "parser.c" /* yacc.c:1646  */
    break;

  case 30:
#line 183 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = (yyvsp[0].prog); }
#line 1912 "parser.c" /* yacc.c:1646  */
    break;

  case 31:
#line 187 "parser.y" /* yacc.c:1646  */
    {
		expr_t *enode = expr_construct_setvar((yyvsp[-2].str), NULL, (yyvsp[-1].str), FALSE, (yyvsp[0].enode));
		(yyval.prog) = program_construct_expr(enode, TRUE, code_loc((yyloc)));
		free((yyvsp[-1].str));
	}
#line 1922 "parser.c" /* yacc.c:1646  */
    break;

  case 32:
#line 192 "parser.y" /* yacc.c:1646  */
    {
		expr_t *enode = expr_construct_setvar((yyvsp[-5].str), (yyvsp[-3].enode), (yyvsp[-1].str), FALSE, (yyvsp[0].enode));
		(yyval.prog) = program_construct_expr(enode, TRUE, code_loc((yyloc)));
		free((yyvsp[-1].str));
	}
#line 1932 "parser.c" /* yacc.c:1646  */
    break;

  case 33:
#line 200 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = program_construct_expr((yyvsp[0].enode), FALSE, code_loc((yyloc))); }
#line 1938 "parser.c" /* yacc.c:1646  */
    break;

  case 34:
#line 204 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = program_construct_str((yyvsp[0].str), code_loc((yyloc))); }
#line 1944 "parser.c" /* yacc.c:1646  */
    break;

  case 37:
#line 213 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_setvar((yyvsp[-2].str), NULL, (yyvsp[-1].str), FALSE, (yyvsp[0].enode)); free((yyvsp[-1].str)); }
#line 1950 "parser.c" /* yacc.c:1646  */
    break;

  case 38:
#line 214 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_setvar((yyvsp[-5].str), (yyvsp[-3].enode), (yyvsp[-1].str), FALSE, (yyvsp[0].enode)); free((yyvsp[-1].str)); }
#line 1956 "parser.c" /* yacc.c:1646  */
    break;

  case 39:
#line 218 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_number((yyvsp[0].num)); }
#line 1962 "parser.c" /* yacc.c:1646  */
    break;

  case 40:
#line 219 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_getvar((yyvsp[0].str), NULL); }
#line 1968 "parser.c" /* yacc.c:1646  */
    break;

  case 41:
#line 220 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_getvar((yyvsp[-3].str), (yyvsp[-1].enode)); }
#line 1974 "parser.c" /* yacc.c:1646  */
    break;

  case 42:
#line 221 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_setvar((yyvsp[0].str), NULL, (yyvsp[-1].str), FALSE, NULL); free((yyvsp[-1].str)); }
#line 1980 "parser.c" /* yacc.c:1646  */
    break;

  case 43:
#line 222 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_setvar((yyvsp[-1].str), NULL, (yyvsp[0].str), TRUE, NULL); free((yyvsp[0].str)); }
#line 1986 "parser.c" /* yacc.c:1646  */
    break;

  case 44:
#line 223 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_setvar((yyvsp[-3].str), (yyvsp[-1].enode), (yyvsp[-4].str), FALSE, NULL); free((yyvsp[-4].str)); }
#line 1992 "parser.c" /* yacc.c:1646  */
    break;

  case 45:
#line 224 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_setvar((yyvsp[-4].str), (yyvsp[-2].enode), (yyvsp[0].str), TRUE, NULL); free((yyvsp[0].str)); }
#line 1998 "parser.c" /* yacc.c:1646  */
    break;

  case 47:
#line 226 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op2_str("+", (yyvsp[-2].enode), (yyvsp[0].enode)); }
#line 2004 "parser.c" /* yacc.c:1646  */
    break;

  case 48:
#line 227 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op2_str("-", (yyvsp[-2].enode), (yyvsp[0].enode)); }
#line 2010 "parser.c" /* yacc.c:1646  */
    break;

  case 49:
#line 228 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op2_str("*", (yyvsp[-2].enode), (yyvsp[0].enode)); }
#line 2016 "parser.c" /* yacc.c:1646  */
    break;

  case 50:
#line 229 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op2_str("/", (yyvsp[-2].enode), (yyvsp[0].enode)); }
#line 2022 "parser.c" /* yacc.c:1646  */
    break;

  case 51:
#line 230 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op2_str("^", (yyvsp[-2].enode), (yyvsp[0].enode)); }
#line 2028 "parser.c" /* yacc.c:1646  */
    break;

  case 52:
#line 231 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op2_str("%", (yyvsp[-2].enode), (yyvsp[0].enode)); }
#line 2034 "parser.c" /* yacc.c:1646  */
    break;

  case 53:
#line 232 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op1_str("-", (yyvsp[0].enode)); }
#line 2040 "parser.c" /* yacc.c:1646  */
    break;

  case 54:
#line 233 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op2_str((yyvsp[-1].str), (yyvsp[-2].enode), (yyvsp[0].enode)); free((yyvsp[-1].str)); }
#line 2046 "parser.c" /* yacc.c:1646  */
    break;

  case 55:
#line 234 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op2_str("&&", (yyvsp[-2].enode), (yyvsp[0].enode)); }
#line 2052 "parser.c" /* yacc.c:1646  */
    break;

  case 56:
#line 235 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op2_str("||", (yyvsp[-2].enode), (yyvsp[0].enode)); }
#line 2058 "parser.c" /* yacc.c:1646  */
    break;

  case 57:
#line 236 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op1_str("!", (yyvsp[0].enode)); }
#line 2064 "parser.c" /* yacc.c:1646  */
    break;

  case 58:
#line 237 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = (yyvsp[-1].enode); }
#line 2070 "parser.c" /* yacc.c:1646  */
    break;

  case 59:
#line 241 "parser.y" /* yacc.c:1646  */
    { program_notify_is_part_of_print((yyvsp[0].prog)); (yyval.prog) = (yyvsp[0].prog); }
#line 2076 "parser.c" /* yacc.c:1646  */
    break;

  case 60:
#line 242 "parser.y" /* yacc.c:1646  */
    { program_notify_is_part_of_print((yyvsp[0].prog)); (yyval.prog) = (yyvsp[0].prog); }
#line 2082 "parser.c" /* yacc.c:1646  */
    break;

  case 61:
#line 243 "parser.y" /* yacc.c:1646  */
    { program_notify_is_part_of_print((yyvsp[0].prog)); (yyval.prog) = (yyvsp[0].prog); }
#line 2088 "parser.c" /* yacc.c:1646  */
    break;

  case 63:
#line 248 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = program_chain((yyvsp[-2].prog), (yyvsp[0].prog)); }
#line 2094 "parser.c" /* yacc.c:1646  */
    break;

  case 66:
#line 257 "parser.y" /* yacc.c:1646  */
    {
		program_loop_t loop;
		loop.exprbefore = NULL;
		loop.testbefore = (yyvsp[-3].enode);
		loop.core = (yyvsp[0].prog);
		loop.testafter = NULL;
		loop.exprafter = NULL;
		(yyval.prog) = program_construct_loop(&loop, code_loc((yyloc)));
	}
#line 2108 "parser.c" /* yacc.c:1646  */
    break;

  case 67:
#line 269 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = NULL; }
#line 2114 "parser.c" /* yacc.c:1646  */
    break;

  case 69:
#line 274 "parser.y" /* yacc.c:1646  */
    {
		program_loop_t loop;
		loop.exprbefore = (yyvsp[-7].enode);
		loop.testbefore = (yyvsp[-5].enode);
		loop.core = (yyvsp[0].prog);
		loop.testafter = NULL;
		loop.exprafter = (yyvsp[-3].enode);
		(yyval.prog) = program_construct_loop(&loop, code_loc((yyloc)));
	}
#line 2128 "parser.c" /* yacc.c:1646  */
    break;

  case 70:
#line 286 "parser.y" /* yacc.c:1646  */
    {
		program_ifseq_t ifseq;
		ifseq.expr = (yyvsp[-3].enode);
		ifseq.pif = (yyvsp[0].prog);
		ifseq.pelse = NULL;
		(yyval.prog) = program_construct_ifseq(&ifseq, code_loc((yyloc)));
	}
#line 2140 "parser.c" /* yacc.c:1646  */
    break;

  case 71:
#line 293 "parser.y" /* yacc.c:1646  */
    {
		program_ifseq_t ifseq;
		ifseq.expr = (yyvsp[-6].enode);
		ifseq.pif = (yyvsp[-3].prog);
		ifseq.pelse = (yyvsp[0].prog);
		(yyval.prog) = program_construct_ifseq(&ifseq, code_loc((yyloc)));
	}
#line 2152 "parser.c" /* yacc.c:1646  */
    break;

  case 72:
#line 303 "parser.y" /* yacc.c:1646  */
    { (yyval.defargs) = defargs_construct(DARG_VALUE, (yyvsp[0].str)); }
#line 2158 "parser.c" /* yacc.c:1646  */
    break;

  case 73:
#line 304 "parser.y" /* yacc.c:1646  */
    { (yyval.defargs) = defargs_construct(DARG_ARRAYVALUE, (yyvsp[-2].str)); }
#line 2164 "parser.c" /* yacc.c:1646  */
    break;

  case 75:
#line 309 "parser.y" /* yacc.c:1646  */
    { (yyval.defargs) = defargs_construct(DARG_REF, (yyvsp[0].str)); }
#line 2170 "parser.c" /* yacc.c:1646  */
    break;

  case 76:
#line 310 "parser.y" /* yacc.c:1646  */
    { (yyval.defargs) = defargs_construct(DARG_ARRAYREF, (yyvsp[-2].str)); }
#line 2176 "parser.c" /* yacc.c:1646  */
    break;

  case 78:
#line 315 "parser.y" /* yacc.c:1646  */
    {
		(yyval.defargs) = defargs_chain((yyvsp[-2].defargs), (yyvsp[0].defargs));
		if ((yyval.defargs) == defarg_t_badarg && (yyvsp[-2].defargs) != defarg_t_badarg && (yyvsp[0].defargs) != defarg_t_badarg) {
			yyerror("duplicate names in autolist (autolist will be ignored)");
		}
		if ((yyval.defargs) == defarg_t_badarg) {
			if ((yyvsp[-2].defargs) != defarg_t_badarg)
				free((yyvsp[-2].defargs));
			if ((yyvsp[0].defargs) != defarg_t_badarg)
				free((yyvsp[0].defargs));
		}
	}
#line 2193 "parser.c" /* yacc.c:1646  */
    break;

  case 80:
#line 331 "parser.y" /* yacc.c:1646  */
    {
		(yyval.defargs) = defargs_chain((yyvsp[-2].defargs), (yyvsp[0].defargs));
		if ((yyval.defargs) == defarg_t_badarg && (yyvsp[-2].defargs) != defarg_t_badarg && (yyvsp[0].defargs) != defarg_t_badarg) {
			yyerror("duplicate parameter names");
		}
		if ((yyval.defargs) == defarg_t_badarg) {
			if ((yyvsp[-2].defargs) != defarg_t_badarg)
				free((yyvsp[-2].defargs));
			if ((yyvsp[0].defargs) != defarg_t_badarg)
				free((yyvsp[0].defargs));
		}
	}
#line 2210 "parser.c" /* yacc.c:1646  */
    break;

  case 81:
#line 346 "parser.y" /* yacc.c:1646  */
    { (yyval.defargs) = NULL; }
#line 2216 "parser.c" /* yacc.c:1646  */
    break;

  case 83:
#line 351 "parser.y" /* yacc.c:1646  */
    { hackbc_enter(); }
#line 2222 "parser.c" /* yacc.c:1646  */
    break;

  case 84:
#line 355 "parser.y" /* yacc.c:1646  */
    { hackbc_terminate(); }
#line 2228 "parser.c" /* yacc.c:1646  */
    break;

  case 85:
#line 359 "parser.y" /* yacc.c:1646  */
    {
		vars_user_function_construct((yyvsp[-6].str), (yyvsp[-4].defargs), (yyvsp[-1].prog), FALSE, code_loc((yyloc)));
	}
#line 2236 "parser.c" /* yacc.c:1646  */
    break;

  case 86:
#line 362 "parser.y" /* yacc.c:1646  */
    {
		vars_user_function_construct((yyvsp[-6].str), (yyvsp[-4].defargs), (yyvsp[-1].prog), TRUE, code_loc((yyloc)));
	}
#line 2244 "parser.c" /* yacc.c:1646  */
    break;

  case 87:
#line 368 "parser.y" /* yacc.c:1646  */
    { (yyval.callargs) = callargs_construct(CARG_EXPR, (yyvsp[0].enode), NULL); }
#line 2250 "parser.c" /* yacc.c:1646  */
    break;

  case 88:
#line 369 "parser.y" /* yacc.c:1646  */
    { (yyval.callargs) = callargs_construct(CARG_ARRAY, NULL, (yyvsp[-2].str)); }
#line 2256 "parser.c" /* yacc.c:1646  */
    break;

  case 90:
#line 374 "parser.y" /* yacc.c:1646  */
    { (yyval.callargs) = callargs_chain((yyvsp[-2].callargs), (yyvsp[0].callargs)); }
#line 2262 "parser.c" /* yacc.c:1646  */
    break;

  case 91:
#line 378 "parser.y" /* yacc.c:1646  */
    { (yyval.callargs) = NULL; }
#line 2268 "parser.c" /* yacc.c:1646  */
    break;

  case 93:
#line 383 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_function_call((yyvsp[-3].str), (yyvsp[-1].callargs)); }
#line 2274 "parser.c" /* yacc.c:1646  */
    break;

  case 95:
#line 388 "parser.y" /* yacc.c:1646  */
    { flag_quitting = TRUE; YYABORT; }
#line 2280 "parser.c" /* yacc.c:1646  */
    break;

  case 96:
#line 389 "parser.y" /* yacc.c:1646  */
    {
		vars_display_all();
	}
#line 2288 "parser.c" /* yacc.c:1646  */
    break;

  case 97:
#line 392 "parser.y" /* yacc.c:1646  */
    {
		if (num_libswitch((yyvsp[0].str)) == 0) {
			outln_error("%s", "Unknown library");
		}
		free((yyvsp[0].str));
	}
#line 2299 "parser.c" /* yacc.c:1646  */
    break;

  case 98:
#line 398 "parser.y" /* yacc.c:1646  */
    {
		outln(L_ENFORCE, "%s", num_identify_yourself());
	}
#line 2307 "parser.c" /* yacc.c:1646  */
    break;

  case 99:
#line 401 "parser.y" /* yacc.c:1646  */
    {
		lib_list();
	}
#line 2315 "parser.c" /* yacc.c:1646  */
    break;


#line 2319 "parser.c" /* yacc.c:1646  */
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
#line 406 "parser.y" /* yacc.c:1906  */


#define VARIBASE "ibase"
static int hackbc_has_entered = FALSE;
static int hackbc_nested_level;
static int save_ibase_is_set;
static int save_ibase;

void hackbc_enter()
{
	const numptr *pnum = vars_get_value(VARIBASE);
	if (pnum == NULL) {
		out_dbg("Entering function definition - no ibase variable set\n");
		save_ibase_is_set = FALSE;
	} else {

			/*
			 * FIXME???
			 * Check int versus long int storage capacity?
			 * It'd be a bit strange to have ibase greater than INT_MAX...
			 * So I just ignore it.
			 *
			*/
		save_ibase = (int)num_getlongint(*pnum);

		out_dbg("Entering function definition - ibase set, value: %d\n", save_ibase);
		save_ibase_is_set = TRUE;
	}
	hackbc_has_entered = TRUE;
	hackbc_nested_level = 0;
}

void hackbc_terminate()
{
	if (!hackbc_has_entered)
		return;

	if (save_ibase_is_set) {
		out_dbg("Terminating function definition - ibase set back to %d\n", save_ibase);
		const numptr *pvar;
		vars_set_value(VARIBASE, num_construct_from_int(save_ibase), &pvar);
	} else {
		out_dbg("Terminating function definition - ibase is deleted\n");
		var_delete(VARIBASE);
	}
	hackbc_has_entered = FALSE;
}

void hackbc_inc_nested()
{
	++hackbc_nested_level;
	out_dbg("hack_inc_nested(): nested = %d\n", hackbc_nested_level);
}

void hackbc_dec_nested()
{
	--hackbc_nested_level;
	out_dbg("hack_dec_nested(): nested = %d\n", hackbc_nested_level);
}

void hackbc_check(const char *name, expr_t *e)
{
	if (!hackbc_has_entered || varname_cmp(name, VARIBASE))
		return;

	if (hackbc_nested_level != 1) {
		out_dbg("hackbc_check(): eligible assignment but not at correct nested level\n");
		return;
	}

	numptr num = num_undefvalue();
	exec_ctx_t *pexec_ctx = construct_exec_ctx_t();
	int r = expr_eval(e, &num, pexec_ctx);
		/*
		 * We just ignore cases when an error occurs (ex. with an
		 * instruction like "ibase = 1 / 0", and also cases where
		 * there is no return value.
		*/
	if (r == ERROR_NONE && !num_is_not_initialized(num)) {
		out_dbg("hackbc_check(): caught variable assignment successfully: assigning new value\n");
		const numptr *pvar;
		vars_set_value(VARIBASE, num, &pvar);
	} else {
		out_dbg("hackbc_check(): CAUGHT VARIABLE ASSIGNMENT BUT COULD NOT CALCULATE CONSTANT EXPRESSION VALUE!\n");
	}
	destruct_exec_ctx_t(pexec_ctx, FALSE);
}

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

