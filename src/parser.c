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

#ifdef BISON_DEBUG
#define YYDEBUG 1
#endif


#line 94 "parser.c" /* yacc.c:339  */

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
    VOID = 275,
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
#define VOID 275
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
#line 75 "parser.y" /* yacc.c:355  */

	numptr num;
	expr_t *enode;
	char *str;
	program_t *prog;
	defargs_t *defargs;
	callargs_t *callargs;

#line 201 "parser.c" /* yacc.c:355  */
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
#line 58 "parser.y" /* yacc.c:355  */

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

#line 240 "parser.c" /* yacc.c:355  */

#endif /* !YY_YY_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 246 "parser.c" /* yacc.c:358  */

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
#define YYFINAL  67
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   353

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  97
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  178

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
       0,   124,   124,   125,   126,   127,   131,   143,   147,   148,
     152,   153,   157,   158,   162,   162,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   182,
     187,   195,   199,   203,   204,   208,   209,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   236,   237,   238,
     242,   243,   247,   248,   252,   264,   265,   269,   281,   288,
     298,   299,   303,   304,   305,   309,   310,   325,   326,   341,
     342,   346,   350,   354,   357,   363,   364,   368,   369,   373,
     374,   378,   382,   383,   384,   387,   393,   396
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
  "ELSE", "DEFINE", "VOID", "RETURN", "AUTOLIST", "PRINT", "NEWLINE",
  "LOGIC_OR", "LOGIC_AND", "LOGIC_NOT", "'+'", "'-'", "'*'", "'/'", "'%'",
  "'^'", "NEG", "LOWER_THAN_ELSE", "'{'", "'}'", "';'", "'['", "']'",
  "'('", "')'", "','", "$accept", "input", "program", "instruction_block",
  "instruction_inside_block", "instruction_list", "instruction",
  "instruction_non_empty", "$@1", "my_instruction_non_empty",
  "instruction_expr_assignment", "instruction_expr_no_assignment",
  "instruction_string", "expression", "expression_assignment",
  "expression_no_assignment", "print_elem", "print_list",
  "newlines_or_empty", "loop_while", "expression_or_empty", "loop_for",
  "ifseq", "defargbyval", "defarg", "defargsbyval_list", "defargs_list",
  "defargs_list_or_empty", "hackbc_enter", "hackbc_terminate",
  "function_definition", "callarg", "callargs_list",
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

#define YYPACT_NINF -114

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-114)))

#define YYTABLE_NINF -82

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     121,    -1,  -114,     4,  -114,    10,  -114,  -114,    20,  -114,
       1,     5,  -114,  -114,    14,   172,    23,    67,   172,   172,
     150,   172,    33,    53,  -114,    -4,  -114,  -114,  -114,  -114,
    -114,   271,  -114,    69,  -114,  -114,  -114,    60,  -114,  -114,
      54,   121,   172,  -114,   172,   181,    44,  -114,   172,   172,
     172,     8,   271,  -114,    47,  -114,    46,  -114,  -114,  -114,
    -114,    52,   314,  -114,     2,    -4,    85,  -114,   121,   150,
     172,   172,   172,   172,   172,   172,   172,   172,   172,    18,
     121,  -114,   286,   229,    11,   271,  -114,    77,    55,   172,
     186,   271,    90,   214,   172,   172,    83,    23,    67,   150,
    -114,  -114,  -114,  -114,   320,   307,   314,    70,    70,   113,
     113,   113,   113,   106,   145,  -114,    59,   166,   181,  -114,
     242,   128,   172,   128,   320,   258,  -114,  -114,  -114,    -4,
      26,   115,   172,  -114,  -114,  -114,  -114,   128,  -114,   122,
    -114,    66,   157,  -114,  -114,   125,   136,    26,   299,  -114,
    -114,   150,   172,   163,   172,   143,    26,   128,   141,  -114,
     146,   128,   320,   147,  -114,  -114,   128,   128,  -114,  -114,
    -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    37,    38,    32,     0,    93,    94,    96,    97,
       0,     0,    24,    25,     0,    22,     0,     0,     0,     0,
      12,     0,     0,     0,    28,     6,    10,    13,    16,    17,
      18,     0,    34,    33,    19,    20,    21,     0,    92,    44,
       0,     0,     0,    41,     0,    89,    40,    95,     0,    65,
       0,    38,    23,    33,    70,    75,    27,    57,    58,    59,
      60,    26,    55,    51,     0,     8,     0,     1,     0,    12,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     5,    29,     0,    38,    85,    87,    90,     0,     0,
       0,    66,     0,     0,     0,     0,     0,     0,     0,    12,
       7,    56,     3,    11,    52,    54,    53,    45,    46,    47,
      48,    50,    49,     0,     0,     4,    39,     0,     0,    91,
       0,    62,    65,    62,    35,     0,    71,    76,    61,     9,
      79,     0,     0,    43,    86,    88,    42,    62,    14,     0,
      14,    39,     0,    72,    77,    80,     0,    79,    30,    63,
      64,     0,    65,    68,     0,    73,     0,    62,     0,    15,
       0,    62,    36,     0,    78,    14,    62,    62,    14,    74,
      82,    14,    14,    69,    83,    82,    67,    84
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -114,   -40,  -114,  -114,  -114,    -7,   127,    58,  -114,    39,
     -14,   -10,    -8,   -13,  -114,     0,    96,  -114,  -113,  -114,
    -101,  -114,  -114,   -12,    41,  -114,  -114,    56,  -114,    25,
    -114,    84,  -114,  -114,  -114,  -114
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    22,    23,    24,    64,    25,    26,   150,   151,    27,
      28,    29,    30,    31,    32,    53,    60,    61,   138,    34,
      92,    35,    36,   143,   144,    56,   145,   146,    37,   174,
      38,    86,    87,    88,    39,    40
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      33,    81,    52,    57,    55,    62,    63,    58,    66,    59,
     140,    42,    43,    65,    46,    94,    43,    33,    94,    43,
      33,   139,   113,    41,   149,    47,    99,    54,   102,    82,
      54,    83,    85,    67,    69,    90,    91,    93,   114,   100,
     115,    33,    48,    44,   165,    45,    49,    95,   168,    45,
     117,   160,    45,   171,   172,    50,   142,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   132,   133,    33,    33,
       2,     3,     4,   154,   133,     5,   120,    68,    80,    79,
      33,   124,   125,    89,    57,   127,    96,   -31,    58,    97,
      59,    70,   129,   -31,    18,    98,    19,   119,    33,    33,
      75,    76,    77,    78,   125,    85,   -31,   -31,    21,    91,
      71,    72,   -31,    73,    74,    75,    76,    77,    78,   148,
     118,    -2,     1,   126,     2,     3,     4,   101,   122,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    91,
     -81,   162,    15,    16,    17,   -12,    78,   130,    18,   131,
      19,    33,   137,     2,     3,     4,   147,    20,     5,   -12,
     152,   155,    21,    10,    11,    12,    13,    14,   156,     2,
      51,    15,    16,    17,     5,     2,    51,    18,   157,    19,
       5,   161,   163,   166,     2,    84,    20,   169,   167,     5,
     159,    21,    70,    18,   128,    19,   103,   164,   153,    18,
     177,    19,   135,   158,     0,     0,   134,    21,    18,     0,
      19,    71,    72,    21,    73,    74,    75,    76,    77,    78,
      70,     0,    21,   170,     0,     0,   173,     0,   121,   175,
     176,     0,     0,     0,     0,    70,     0,     0,     0,    71,
      72,     0,    73,    74,    75,    76,    77,    78,    70,     0,
       0,     0,     0,     0,    71,    72,   123,    73,    74,    75,
      76,    77,    78,     0,    70,     0,     0,    71,    72,   116,
      73,    74,    75,    76,    77,    78,     0,    70,     0,     0,
       0,     0,   136,    71,    72,     0,    73,    74,    75,    76,
      77,    78,   -35,     0,     0,     0,    71,    72,   141,    73,
      74,    75,    76,    77,    78,   -36,     0,     0,     0,     0,
       0,   -35,   -35,    70,    73,    74,    75,    76,    77,    78,
      70,     0,     0,     0,   -36,   -36,     0,    73,    74,    75,
      76,    77,    78,    72,     0,    73,    74,    75,    76,    77,
      78,     0,    73,    74,    75,    76,    77,    78,    73,    74,
      75,    76,    77,    78
};

static const yytype_int16 yycheck[] =
{
       0,    41,    15,    17,    16,    18,    19,    17,    21,    17,
     123,     7,     8,    20,     4,     7,     8,    17,     7,     8,
      20,   122,     4,    24,   137,     5,    24,     4,    68,    42,
       4,    44,    45,     0,    38,    48,    49,    50,    20,    37,
      80,    41,    41,    39,   157,    41,    41,    39,   161,    41,
      39,   152,    41,   166,   167,    41,    30,    70,    71,    72,
      73,    74,    75,    76,    77,    78,     7,     8,    68,    69,
       3,     4,     5,     7,     8,     8,    89,    24,    24,    19,
      80,    94,    95,    39,    98,    97,    39,    18,    98,    43,
      98,     6,    99,    24,    27,    43,    29,    42,    98,    99,
      30,    31,    32,    33,   117,   118,    37,    38,    41,   122,
      25,    26,    43,    28,    29,    30,    31,    32,    33,   132,
      43,     0,     1,    40,     3,     4,     5,    42,    38,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,   152,
      19,   154,    21,    22,    23,    24,    33,    41,    27,     4,
      29,   151,    24,     3,     4,     5,    41,    36,     8,    38,
      38,     4,    41,    13,    14,    15,    16,    17,    43,     3,
       4,    21,    22,    23,     8,     3,     4,    27,    42,    29,
       8,    18,    39,    42,     3,     4,    36,    40,    42,     8,
     151,    41,     6,    27,    98,    29,    69,   156,   140,    27,
     175,    29,   118,   147,    -1,    -1,    40,    41,    27,    -1,
      29,    25,    26,    41,    28,    29,    30,    31,    32,    33,
       6,    -1,    41,   165,    -1,    -1,   168,    -1,    42,   171,
     172,    -1,    -1,    -1,    -1,     6,    -1,    -1,    -1,    25,
      26,    -1,    28,    29,    30,    31,    32,    33,     6,    -1,
      -1,    -1,    -1,    -1,    25,    26,    42,    28,    29,    30,
      31,    32,    33,    -1,     6,    -1,    -1,    25,    26,    40,
      28,    29,    30,    31,    32,    33,    -1,     6,    -1,    -1,
      -1,    -1,    40,    25,    26,    -1,    28,    29,    30,    31,
      32,    33,     6,    -1,    -1,    -1,    25,    26,    40,    28,
      29,    30,    31,    32,    33,     6,    -1,    -1,    -1,    -1,
      -1,    25,    26,     6,    28,    29,    30,    31,    32,    33,
       6,    -1,    -1,    -1,    25,    26,    -1,    28,    29,    30,
      31,    32,    33,    26,    -1,    28,    29,    30,    31,    32,
      33,    -1,    28,    29,    30,    31,    32,    33,    28,    29,
      30,    31,    32,    33
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     4,     5,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    21,    22,    23,    27,    29,
      36,    41,    45,    46,    47,    49,    50,    53,    54,    55,
      56,    57,    58,    59,    63,    65,    66,    72,    74,    78,
      79,    24,     7,     8,    39,    41,     4,     5,    41,    41,
      41,     4,    57,    59,     4,    67,    69,    54,    55,    56,
      60,    61,    57,    57,    48,    49,    57,     0,    24,    38,
       6,    25,    26,    28,    29,    30,    31,    32,    33,    19,
      24,    45,    57,    57,     4,    57,    75,    76,    77,    39,
      57,    57,    64,    57,     7,    39,    39,    43,    43,    24,
      37,    42,    45,    50,    57,    57,    57,    57,    57,    57,
      57,    57,    57,     4,    20,    45,    40,    39,    43,    42,
      57,    42,    38,    42,    57,    57,    40,    67,    60,    49,
      41,     4,     7,     8,    40,    75,    40,    24,    62,    64,
      62,    40,    30,    67,    68,    70,    71,    41,    57,    62,
      51,    52,    38,    51,     7,     4,    43,    42,    71,    53,
      64,    18,    57,    39,    68,    62,    42,    42,    62,    40,
      51,    62,    62,    51,    73,    51,    51,    73
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    44,    45,    45,    45,    45,    46,    47,    48,    48,
      49,    49,    50,    50,    52,    51,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    54,
      54,    55,    56,    57,    57,    58,    58,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    60,    60,    60,
      61,    61,    62,    62,    63,    64,    64,    65,    66,    66,
      67,    67,    68,    68,    68,    69,    69,    70,    70,    71,
      71,    72,    73,    74,    74,    75,    75,    76,    76,    77,
      77,    78,    79,    79,    79,    79,    79,    79
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     3,     3,     3,     1,     3,     1,     3,
       1,     3,     0,     1,     0,     2,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     2,     2,     1,     3,
       6,     1,     1,     1,     1,     3,     6,     1,     1,     4,
       2,     2,     5,     5,     1,     3,     3,     3,     3,     3,
       3,     2,     3,     3,     3,     2,     3,     1,     1,     1,
       1,     3,     0,     2,     6,     0,     1,    10,     6,     9,
       1,     3,     1,     2,     4,     1,     3,     1,     3,     0,
       1,     0,     0,     9,    10,     1,     3,     1,     3,     0,
       1,     4,     1,     1,     1,     2,     1,     1
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
#line 112 "parser.y" /* yacc.c:1257  */
      { num_destruct(&((*yyvaluep).num)); out_dbg("parser.y: freed one num\n"); }
#line 1305 "parser.c" /* yacc.c:1257  */
        break;

    case 4: /* IDENTIFIER  */
#line 114 "parser.y" /* yacc.c:1257  */
      { free(((*yyvaluep).str)); out_dbg("parser.y: freed one str\n"); }
#line 1311 "parser.c" /* yacc.c:1257  */
        break;

    case 5: /* STRING  */
#line 114 "parser.y" /* yacc.c:1257  */
      { free(((*yyvaluep).str)); out_dbg("parser.y: freed one str\n"); }
#line 1317 "parser.c" /* yacc.c:1257  */
        break;

    case 6: /* COMPARISON  */
#line 114 "parser.y" /* yacc.c:1257  */
      { free(((*yyvaluep).str)); out_dbg("parser.y: freed one str\n"); }
#line 1323 "parser.c" /* yacc.c:1257  */
        break;

    case 7: /* OP_AND_ASSIGN  */
#line 114 "parser.y" /* yacc.c:1257  */
      { free(((*yyvaluep).str)); out_dbg("parser.y: freed one str\n"); }
#line 1329 "parser.c" /* yacc.c:1257  */
        break;

    case 8: /* PLUSPLUS_MINMIN  */
#line 114 "parser.y" /* yacc.c:1257  */
      { free(((*yyvaluep).str)); out_dbg("parser.y: freed one str\n"); }
#line 1335 "parser.c" /* yacc.c:1257  */
        break;

    case 47: /* instruction_block  */
#line 115 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1341 "parser.c" /* yacc.c:1257  */
        break;

    case 48: /* instruction_inside_block  */
#line 115 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1347 "parser.c" /* yacc.c:1257  */
        break;

    case 49: /* instruction_list  */
#line 115 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1353 "parser.c" /* yacc.c:1257  */
        break;

    case 50: /* instruction  */
#line 115 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1359 "parser.c" /* yacc.c:1257  */
        break;

    case 51: /* instruction_non_empty  */
#line 115 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1365 "parser.c" /* yacc.c:1257  */
        break;

    case 53: /* my_instruction_non_empty  */
#line 115 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1371 "parser.c" /* yacc.c:1257  */
        break;

    case 54: /* instruction_expr_assignment  */
#line 115 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1377 "parser.c" /* yacc.c:1257  */
        break;

    case 55: /* instruction_expr_no_assignment  */
#line 115 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1383 "parser.c" /* yacc.c:1257  */
        break;

    case 56: /* instruction_string  */
#line 115 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1389 "parser.c" /* yacc.c:1257  */
        break;

    case 57: /* expression  */
#line 113 "parser.y" /* yacc.c:1257  */
      { expr_destruct(((*yyvaluep).enode)); out_dbg("parser.y: freed one enode\n"); }
#line 1395 "parser.c" /* yacc.c:1257  */
        break;

    case 58: /* expression_assignment  */
#line 113 "parser.y" /* yacc.c:1257  */
      { expr_destruct(((*yyvaluep).enode)); out_dbg("parser.y: freed one enode\n"); }
#line 1401 "parser.c" /* yacc.c:1257  */
        break;

    case 59: /* expression_no_assignment  */
#line 113 "parser.y" /* yacc.c:1257  */
      { expr_destruct(((*yyvaluep).enode)); out_dbg("parser.y: freed one enode\n"); }
#line 1407 "parser.c" /* yacc.c:1257  */
        break;

    case 60: /* print_elem  */
#line 115 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1413 "parser.c" /* yacc.c:1257  */
        break;

    case 61: /* print_list  */
#line 115 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1419 "parser.c" /* yacc.c:1257  */
        break;

    case 63: /* loop_while  */
#line 115 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1425 "parser.c" /* yacc.c:1257  */
        break;

    case 64: /* expression_or_empty  */
#line 113 "parser.y" /* yacc.c:1257  */
      { expr_destruct(((*yyvaluep).enode)); out_dbg("parser.y: freed one enode\n"); }
#line 1431 "parser.c" /* yacc.c:1257  */
        break;

    case 65: /* loop_for  */
#line 115 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1437 "parser.c" /* yacc.c:1257  */
        break;

    case 66: /* ifseq  */
#line 115 "parser.y" /* yacc.c:1257  */
      { program_destruct(((*yyvaluep).prog)); out_dbg("parser.y: freed one program\n"); }
#line 1443 "parser.c" /* yacc.c:1257  */
        break;

    case 67: /* defargbyval  */
#line 116 "parser.y" /* yacc.c:1257  */
      { defargs_destruct(((*yyvaluep).defargs)); out_dbg("parser.y: freed one DEF argument chain\n"); }
#line 1449 "parser.c" /* yacc.c:1257  */
        break;

    case 68: /* defarg  */
#line 116 "parser.y" /* yacc.c:1257  */
      { defargs_destruct(((*yyvaluep).defargs)); out_dbg("parser.y: freed one DEF argument chain\n"); }
#line 1455 "parser.c" /* yacc.c:1257  */
        break;

    case 69: /* defargsbyval_list  */
#line 116 "parser.y" /* yacc.c:1257  */
      { defargs_destruct(((*yyvaluep).defargs)); out_dbg("parser.y: freed one DEF argument chain\n"); }
#line 1461 "parser.c" /* yacc.c:1257  */
        break;

    case 70: /* defargs_list  */
#line 116 "parser.y" /* yacc.c:1257  */
      { defargs_destruct(((*yyvaluep).defargs)); out_dbg("parser.y: freed one DEF argument chain\n"); }
#line 1467 "parser.c" /* yacc.c:1257  */
        break;

    case 71: /* defargs_list_or_empty  */
#line 116 "parser.y" /* yacc.c:1257  */
      { defargs_destruct(((*yyvaluep).defargs)); out_dbg("parser.y: freed one DEF argument chain\n"); }
#line 1473 "parser.c" /* yacc.c:1257  */
        break;

    case 75: /* callarg  */
#line 117 "parser.y" /* yacc.c:1257  */
      { callargs_chain_destruct(((*yyvaluep).callargs)); out_dbg("parser.y: freed one CALL argument chain\n"); }
#line 1479 "parser.c" /* yacc.c:1257  */
        break;

    case 76: /* callargs_list  */
#line 117 "parser.y" /* yacc.c:1257  */
      { callargs_chain_destruct(((*yyvaluep).callargs)); out_dbg("parser.y: freed one CALL argument chain\n"); }
#line 1485 "parser.c" /* yacc.c:1257  */
        break;

    case 77: /* callargs_list_or_empty  */
#line 117 "parser.y" /* yacc.c:1257  */
      { callargs_chain_destruct(((*yyvaluep).callargs)); out_dbg("parser.y: freed one CALL argument chain\n"); }
#line 1491 "parser.c" /* yacc.c:1257  */
        break;

    case 78: /* function_call  */
#line 113 "parser.y" /* yacc.c:1257  */
      { expr_destruct(((*yyvaluep).enode)); out_dbg("parser.y: freed one enode\n"); }
#line 1497 "parser.c" /* yacc.c:1257  */
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
#line 124 "parser.y" /* yacc.c:1646  */
    { loc_reset(); }
#line 1785 "parser.c" /* yacc.c:1646  */
    break;

  case 5:
#line 127 "parser.y" /* yacc.c:1646  */
    { out_dbg("Error encountered, ran yyclearin and yyerrok\n"); yyclearin; yyerrok; }
#line 1791 "parser.c" /* yacc.c:1646  */
    break;

  case 6:
#line 131 "parser.y" /* yacc.c:1646  */
    {
		exec_ctx_t *pexec_ctx = construct_exec_ctx_t();
		int r = program_execute((yyvsp[0].prog), NULL, pexec_ctx);
		if (r != ERROR_NONE) {
			outln_exec_error(r, pexec_ctx, FALSE);
		}
		program_destruct((yyvsp[0].prog));
		destruct_exec_ctx_t(pexec_ctx, FALSE);
	}
#line 1805 "parser.c" /* yacc.c:1646  */
    break;

  case 7:
#line 143 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = (yyvsp[-1].prog); }
#line 1811 "parser.c" /* yacc.c:1646  */
    break;

  case 8:
#line 147 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = (yyvsp[0].prog); }
#line 1817 "parser.c" /* yacc.c:1646  */
    break;

  case 9:
#line 148 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = program_chain((yyvsp[-2].prog), (yyvsp[0].prog)); }
#line 1823 "parser.c" /* yacc.c:1646  */
    break;

  case 11:
#line 153 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = program_chain((yyvsp[-2].prog), (yyvsp[0].prog)); }
#line 1829 "parser.c" /* yacc.c:1646  */
    break;

  case 12:
#line 157 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = NULL; }
#line 1835 "parser.c" /* yacc.c:1646  */
    break;

  case 14:
#line 162 "parser.y" /* yacc.c:1646  */
    { hackbc_inc_nested(); }
#line 1841 "parser.c" /* yacc.c:1646  */
    break;

  case 15:
#line 162 "parser.y" /* yacc.c:1646  */
    { hackbc_dec_nested(); (yyval.prog) = (yyvsp[0].prog); }
#line 1847 "parser.c" /* yacc.c:1646  */
    break;

  case 22:
#line 172 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = program_construct_return(NULL, code_loc((yyloc))); }
#line 1853 "parser.c" /* yacc.c:1646  */
    break;

  case 23:
#line 173 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = program_construct_return((yyvsp[0].enode), code_loc((yyloc))); }
#line 1859 "parser.c" /* yacc.c:1646  */
    break;

  case 24:
#line 174 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = program_construct_break(code_loc((yyloc))); }
#line 1865 "parser.c" /* yacc.c:1646  */
    break;

  case 25:
#line 175 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = program_construct_continue(code_loc((yyloc))); }
#line 1871 "parser.c" /* yacc.c:1646  */
    break;

  case 26:
#line 176 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = (yyvsp[0].prog); }
#line 1877 "parser.c" /* yacc.c:1646  */
    break;

  case 27:
#line 177 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = program_construct_autolist((yyvsp[0].defargs), code_loc((yyloc))); }
#line 1883 "parser.c" /* yacc.c:1646  */
    break;

  case 28:
#line 178 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = (yyvsp[0].prog); }
#line 1889 "parser.c" /* yacc.c:1646  */
    break;

  case 29:
#line 182 "parser.y" /* yacc.c:1646  */
    {
		expr_t *enode = expr_construct_setvar((yyvsp[-2].str), NULL, (yyvsp[-1].str), FALSE, (yyvsp[0].enode));
		(yyval.prog) = program_construct_expr(enode, TRUE, code_loc((yyloc)));
		free((yyvsp[-1].str));
	}
#line 1899 "parser.c" /* yacc.c:1646  */
    break;

  case 30:
#line 187 "parser.y" /* yacc.c:1646  */
    {
		expr_t *enode = expr_construct_setvar((yyvsp[-5].str), (yyvsp[-3].enode), (yyvsp[-1].str), FALSE, (yyvsp[0].enode));
		(yyval.prog) = program_construct_expr(enode, TRUE, code_loc((yyloc)));
		free((yyvsp[-1].str));
	}
#line 1909 "parser.c" /* yacc.c:1646  */
    break;

  case 31:
#line 195 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = program_construct_expr((yyvsp[0].enode), FALSE, code_loc((yyloc))); }
#line 1915 "parser.c" /* yacc.c:1646  */
    break;

  case 32:
#line 199 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = program_construct_str((yyvsp[0].str), code_loc((yyloc))); }
#line 1921 "parser.c" /* yacc.c:1646  */
    break;

  case 35:
#line 208 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_setvar((yyvsp[-2].str), NULL, (yyvsp[-1].str), FALSE, (yyvsp[0].enode)); free((yyvsp[-1].str)); }
#line 1927 "parser.c" /* yacc.c:1646  */
    break;

  case 36:
#line 209 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_setvar((yyvsp[-5].str), (yyvsp[-3].enode), (yyvsp[-1].str), FALSE, (yyvsp[0].enode)); free((yyvsp[-1].str)); }
#line 1933 "parser.c" /* yacc.c:1646  */
    break;

  case 37:
#line 213 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_number((yyvsp[0].num)); }
#line 1939 "parser.c" /* yacc.c:1646  */
    break;

  case 38:
#line 214 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_getvar((yyvsp[0].str), NULL); }
#line 1945 "parser.c" /* yacc.c:1646  */
    break;

  case 39:
#line 215 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_getvar((yyvsp[-3].str), (yyvsp[-1].enode)); }
#line 1951 "parser.c" /* yacc.c:1646  */
    break;

  case 40:
#line 216 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_setvar((yyvsp[0].str), NULL, (yyvsp[-1].str), FALSE, NULL); free((yyvsp[-1].str)); }
#line 1957 "parser.c" /* yacc.c:1646  */
    break;

  case 41:
#line 217 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_setvar((yyvsp[-1].str), NULL, (yyvsp[0].str), TRUE, NULL); free((yyvsp[0].str)); }
#line 1963 "parser.c" /* yacc.c:1646  */
    break;

  case 42:
#line 218 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_setvar((yyvsp[-3].str), (yyvsp[-1].enode), (yyvsp[-4].str), FALSE, NULL); free((yyvsp[-4].str)); }
#line 1969 "parser.c" /* yacc.c:1646  */
    break;

  case 43:
#line 219 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_setvar((yyvsp[-4].str), (yyvsp[-2].enode), (yyvsp[0].str), TRUE, NULL); free((yyvsp[0].str)); }
#line 1975 "parser.c" /* yacc.c:1646  */
    break;

  case 45:
#line 221 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op2_str("+", (yyvsp[-2].enode), (yyvsp[0].enode)); }
#line 1981 "parser.c" /* yacc.c:1646  */
    break;

  case 46:
#line 222 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op2_str("-", (yyvsp[-2].enode), (yyvsp[0].enode)); }
#line 1987 "parser.c" /* yacc.c:1646  */
    break;

  case 47:
#line 223 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op2_str("*", (yyvsp[-2].enode), (yyvsp[0].enode)); }
#line 1993 "parser.c" /* yacc.c:1646  */
    break;

  case 48:
#line 224 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op2_str("/", (yyvsp[-2].enode), (yyvsp[0].enode)); }
#line 1999 "parser.c" /* yacc.c:1646  */
    break;

  case 49:
#line 225 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op2_str("^", (yyvsp[-2].enode), (yyvsp[0].enode)); }
#line 2005 "parser.c" /* yacc.c:1646  */
    break;

  case 50:
#line 226 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op2_str("%", (yyvsp[-2].enode), (yyvsp[0].enode)); }
#line 2011 "parser.c" /* yacc.c:1646  */
    break;

  case 51:
#line 227 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op1_str("-", (yyvsp[0].enode)); }
#line 2017 "parser.c" /* yacc.c:1646  */
    break;

  case 52:
#line 228 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op2_str((yyvsp[-1].str), (yyvsp[-2].enode), (yyvsp[0].enode)); free((yyvsp[-1].str)); }
#line 2023 "parser.c" /* yacc.c:1646  */
    break;

  case 53:
#line 229 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op2_str("&&", (yyvsp[-2].enode), (yyvsp[0].enode)); }
#line 2029 "parser.c" /* yacc.c:1646  */
    break;

  case 54:
#line 230 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op2_str("||", (yyvsp[-2].enode), (yyvsp[0].enode)); }
#line 2035 "parser.c" /* yacc.c:1646  */
    break;

  case 55:
#line 231 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_op1_str("!", (yyvsp[0].enode)); }
#line 2041 "parser.c" /* yacc.c:1646  */
    break;

  case 56:
#line 232 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = (yyvsp[-1].enode); }
#line 2047 "parser.c" /* yacc.c:1646  */
    break;

  case 57:
#line 236 "parser.y" /* yacc.c:1646  */
    { program_notify_is_part_of_print((yyvsp[0].prog)); (yyval.prog) = (yyvsp[0].prog); }
#line 2053 "parser.c" /* yacc.c:1646  */
    break;

  case 58:
#line 237 "parser.y" /* yacc.c:1646  */
    { program_notify_is_part_of_print((yyvsp[0].prog)); (yyval.prog) = (yyvsp[0].prog); }
#line 2059 "parser.c" /* yacc.c:1646  */
    break;

  case 59:
#line 238 "parser.y" /* yacc.c:1646  */
    { program_notify_is_part_of_print((yyvsp[0].prog)); (yyval.prog) = (yyvsp[0].prog); }
#line 2065 "parser.c" /* yacc.c:1646  */
    break;

  case 61:
#line 243 "parser.y" /* yacc.c:1646  */
    { (yyval.prog) = program_chain((yyvsp[-2].prog), (yyvsp[0].prog)); }
#line 2071 "parser.c" /* yacc.c:1646  */
    break;

  case 64:
#line 252 "parser.y" /* yacc.c:1646  */
    {
		program_loop_t loop;
		loop.exprbefore = NULL;
		loop.testbefore = (yyvsp[-3].enode);
		loop.core = (yyvsp[0].prog);
		loop.testafter = NULL;
		loop.exprafter = NULL;
		(yyval.prog) = program_construct_loop(&loop, code_loc((yyloc)));
	}
#line 2085 "parser.c" /* yacc.c:1646  */
    break;

  case 65:
#line 264 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = NULL; }
#line 2091 "parser.c" /* yacc.c:1646  */
    break;

  case 67:
#line 269 "parser.y" /* yacc.c:1646  */
    {
		program_loop_t loop;
		loop.exprbefore = (yyvsp[-7].enode);
		loop.testbefore = (yyvsp[-5].enode);
		loop.core = (yyvsp[0].prog);
		loop.testafter = NULL;
		loop.exprafter = (yyvsp[-3].enode);
		(yyval.prog) = program_construct_loop(&loop, code_loc((yyloc)));
	}
#line 2105 "parser.c" /* yacc.c:1646  */
    break;

  case 68:
#line 281 "parser.y" /* yacc.c:1646  */
    {
		program_ifseq_t ifseq;
		ifseq.expr = (yyvsp[-3].enode);
		ifseq.pif = (yyvsp[0].prog);
		ifseq.pelse = NULL;
		(yyval.prog) = program_construct_ifseq(&ifseq, code_loc((yyloc)));
	}
#line 2117 "parser.c" /* yacc.c:1646  */
    break;

  case 69:
#line 288 "parser.y" /* yacc.c:1646  */
    {
		program_ifseq_t ifseq;
		ifseq.expr = (yyvsp[-6].enode);
		ifseq.pif = (yyvsp[-3].prog);
		ifseq.pelse = (yyvsp[0].prog);
		(yyval.prog) = program_construct_ifseq(&ifseq, code_loc((yyloc)));
	}
#line 2129 "parser.c" /* yacc.c:1646  */
    break;

  case 70:
#line 298 "parser.y" /* yacc.c:1646  */
    { (yyval.defargs) = defargs_construct(DARG_VALUE, (yyvsp[0].str)); }
#line 2135 "parser.c" /* yacc.c:1646  */
    break;

  case 71:
#line 299 "parser.y" /* yacc.c:1646  */
    { (yyval.defargs) = defargs_construct(DARG_ARRAYVALUE, (yyvsp[-2].str)); }
#line 2141 "parser.c" /* yacc.c:1646  */
    break;

  case 73:
#line 304 "parser.y" /* yacc.c:1646  */
    { (yyval.defargs) = defargs_construct(DARG_REF, (yyvsp[0].str)); }
#line 2147 "parser.c" /* yacc.c:1646  */
    break;

  case 74:
#line 305 "parser.y" /* yacc.c:1646  */
    { (yyval.defargs) = defargs_construct(DARG_ARRAYREF, (yyvsp[-2].str)); }
#line 2153 "parser.c" /* yacc.c:1646  */
    break;

  case 76:
#line 310 "parser.y" /* yacc.c:1646  */
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
#line 2170 "parser.c" /* yacc.c:1646  */
    break;

  case 78:
#line 326 "parser.y" /* yacc.c:1646  */
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
#line 2187 "parser.c" /* yacc.c:1646  */
    break;

  case 79:
#line 341 "parser.y" /* yacc.c:1646  */
    { (yyval.defargs) = NULL; }
#line 2193 "parser.c" /* yacc.c:1646  */
    break;

  case 81:
#line 346 "parser.y" /* yacc.c:1646  */
    { hackbc_enter(); }
#line 2199 "parser.c" /* yacc.c:1646  */
    break;

  case 82:
#line 350 "parser.y" /* yacc.c:1646  */
    { hackbc_terminate(); }
#line 2205 "parser.c" /* yacc.c:1646  */
    break;

  case 83:
#line 354 "parser.y" /* yacc.c:1646  */
    {
		vars_user_function_construct((yyvsp[-6].str), (yyvsp[-4].defargs), (yyvsp[-1].prog), FALSE, code_loc((yyloc)));
	}
#line 2213 "parser.c" /* yacc.c:1646  */
    break;

  case 84:
#line 357 "parser.y" /* yacc.c:1646  */
    {
		vars_user_function_construct((yyvsp[-6].str), (yyvsp[-4].defargs), (yyvsp[-1].prog), TRUE, code_loc((yyloc)));
	}
#line 2221 "parser.c" /* yacc.c:1646  */
    break;

  case 85:
#line 363 "parser.y" /* yacc.c:1646  */
    { (yyval.callargs) = callargs_construct(CARG_EXPR, (yyvsp[0].enode), NULL); }
#line 2227 "parser.c" /* yacc.c:1646  */
    break;

  case 86:
#line 364 "parser.y" /* yacc.c:1646  */
    { (yyval.callargs) = callargs_construct(CARG_ARRAY, NULL, (yyvsp[-2].str)); }
#line 2233 "parser.c" /* yacc.c:1646  */
    break;

  case 88:
#line 369 "parser.y" /* yacc.c:1646  */
    { (yyval.callargs) = callargs_chain((yyvsp[-2].callargs), (yyvsp[0].callargs)); }
#line 2239 "parser.c" /* yacc.c:1646  */
    break;

  case 89:
#line 373 "parser.y" /* yacc.c:1646  */
    { (yyval.callargs) = NULL; }
#line 2245 "parser.c" /* yacc.c:1646  */
    break;

  case 91:
#line 378 "parser.y" /* yacc.c:1646  */
    { (yyval.enode) = expr_construct_function_call((yyvsp[-3].str), (yyvsp[-1].callargs)); }
#line 2251 "parser.c" /* yacc.c:1646  */
    break;

  case 93:
#line 383 "parser.y" /* yacc.c:1646  */
    { YYABORT; }
#line 2257 "parser.c" /* yacc.c:1646  */
    break;

  case 94:
#line 384 "parser.y" /* yacc.c:1646  */
    {
		vars_display_all();
	}
#line 2265 "parser.c" /* yacc.c:1646  */
    break;

  case 95:
#line 387 "parser.y" /* yacc.c:1646  */
    {
		if (num_libswitch((yyvsp[0].str)) == 0) {
			outln_error("%s", "Unknown library");
		}
		free((yyvsp[0].str));
	}
#line 2276 "parser.c" /* yacc.c:1646  */
    break;

  case 96:
#line 393 "parser.y" /* yacc.c:1646  */
    {
		outln(L_ENFORCE, "%s", num_identify_yourself());
	}
#line 2284 "parser.c" /* yacc.c:1646  */
    break;

  case 97:
#line 396 "parser.y" /* yacc.c:1646  */
    {
		lib_list();
	}
#line 2292 "parser.c" /* yacc.c:1646  */
    break;


#line 2296 "parser.c" /* yacc.c:1646  */
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
#line 401 "parser.y" /* yacc.c:1906  */


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

