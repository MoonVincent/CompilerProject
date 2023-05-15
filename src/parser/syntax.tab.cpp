/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "./src/parser/syntax.ypp"

    #include "syntaxNode.hpp"
    #include "lex.yy.c"
    #define NO_VALUE ""
    #define NO_LINE -1
    tree syntaxTree = nullptr;
    void yyerror(char*);

#line 80 "syntax.tab.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
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

#include "syntax.tab.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_FLOAT = 4,                      /* FLOAT  */
  YYSYMBOL_ID = 5,                         /* ID  */
  YYSYMBOL_SEMI = 6,                       /* SEMI  */
  YYSYMBOL_COMMA = 7,                      /* COMMA  */
  YYSYMBOL_ASSIGNOP = 8,                   /* ASSIGNOP  */
  YYSYMBOL_RELOP = 9,                      /* RELOP  */
  YYSYMBOL_PLUS = 10,                      /* PLUS  */
  YYSYMBOL_MINUS = 11,                     /* MINUS  */
  YYSYMBOL_STAR = 12,                      /* STAR  */
  YYSYMBOL_STRING = 13,                    /* STRING  */
  YYSYMBOL_DIV = 14,                       /* DIV  */
  YYSYMBOL_AND = 15,                       /* AND  */
  YYSYMBOL_OR = 16,                        /* OR  */
  YYSYMBOL_DOT = 17,                       /* DOT  */
  YYSYMBOL_NOT = 18,                       /* NOT  */
  YYSYMBOL_TYPE = 19,                      /* TYPE  */
  YYSYMBOL_LP = 20,                        /* LP  */
  YYSYMBOL_RP = 21,                        /* RP  */
  YYSYMBOL_LB = 22,                        /* LB  */
  YYSYMBOL_RB = 23,                        /* RB  */
  YYSYMBOL_LC = 24,                        /* LC  */
  YYSYMBOL_RC = 25,                        /* RC  */
  YYSYMBOL_STRUCT = 26,                    /* STRUCT  */
  YYSYMBOL_RETURN = 27,                    /* RETURN  */
  YYSYMBOL_IF = 28,                        /* IF  */
  YYSYMBOL_ELSE = 29,                      /* ELSE  */
  YYSYMBOL_WHILE = 30,                     /* WHILE  */
  YYSYMBOL_YYACCEPT = 31,                  /* $accept  */
  YYSYMBOL_Program = 32,                   /* Program  */
  YYSYMBOL_ExtDefList = 33,                /* ExtDefList  */
  YYSYMBOL_ExtDef = 34,                    /* ExtDef  */
  YYSYMBOL_ExtDecList = 35,                /* ExtDecList  */
  YYSYMBOL_Specifier = 36,                 /* Specifier  */
  YYSYMBOL_StructSpecifier = 37,           /* StructSpecifier  */
  YYSYMBOL_OptTag = 38,                    /* OptTag  */
  YYSYMBOL_Tag = 39,                       /* Tag  */
  YYSYMBOL_VarDec = 40,                    /* VarDec  */
  YYSYMBOL_FunDec = 41,                    /* FunDec  */
  YYSYMBOL_VarList = 42,                   /* VarList  */
  YYSYMBOL_ParamDec = 43,                  /* ParamDec  */
  YYSYMBOL_CompSt = 44,                    /* CompSt  */
  YYSYMBOL_StmtList = 45,                  /* StmtList  */
  YYSYMBOL_Stmt = 46,                      /* Stmt  */
  YYSYMBOL_DefList = 47,                   /* DefList  */
  YYSYMBOL_Def = 48,                       /* Def  */
  YYSYMBOL_DecList = 49,                   /* DecList  */
  YYSYMBOL_Dec = 50,                       /* Dec  */
  YYSYMBOL_Exp = 51,                       /* Exp  */
  YYSYMBOL_Args = 52                       /* Args  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   237

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  60
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  112

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   285


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    33,    33,    36,    37,    40,    41,    42,    45,    46,
      49,    50,    53,    54,    57,    58,    61,    64,    65,    68,
      69,    72,    73,    76,    79,    82,    83,    86,    87,    88,
      89,    90,    91,    94,    95,    98,   101,   102,   105,   106,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   130,
     131
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INT", "FLOAT", "ID",
  "SEMI", "COMMA", "ASSIGNOP", "RELOP", "PLUS", "MINUS", "STAR", "STRING",
  "DIV", "AND", "OR", "DOT", "NOT", "TYPE", "LP", "RP", "LB", "RB", "LC",
  "RC", "STRUCT", "RETURN", "IF", "ELSE", "WHILE", "$accept", "Program",
  "ExtDefList", "ExtDef", "ExtDecList", "Specifier", "StructSpecifier",
  "OptTag", "Tag", "VarDec", "FunDec", "VarList", "ParamDec", "CompSt",
  "StmtList", "Stmt", "DefList", "Def", "DecList", "Dec", "Exp", "Args", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-49)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-15)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -13,   -49,     2,    17,   -49,   -13,    52,   -49,     9,    14,
     -49,   -49,   -49,    22,   -49,    34,    -6,    23,   -13,    20,
     -49,    44,    48,   -13,   -49,    44,    28,   -13,   -49,    44,
      40,    59,   -49,   -49,    47,    32,     1,    49,    65,   -49,
     -49,    54,   -49,   -13,   -49,   -49,   -49,    70,    64,   -49,
      64,    64,    64,    75,    76,   -49,    72,    32,    77,    64,
     -49,    44,   -49,    60,   215,    -3,   139,    92,    64,    64,
     -49,   -49,   -49,    64,    64,    64,    64,    64,    64,    64,
      64,    69,    64,   184,   -49,   -49,   108,    58,   -49,   -49,
     154,   169,   184,   211,   215,   215,    -3,    -3,   193,   202,
     -49,   123,    64,   -49,    32,    32,   -49,   -49,    81,   -49,
      32,   -49
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,    10,    15,     0,     2,     4,     0,    11,    16,     0,
      13,     1,     3,    17,     6,     0,     8,     0,    34,     0,
       5,     0,     0,    34,     7,     0,     0,    34,    20,     0,
       0,    22,    17,     9,     0,    26,    38,     0,    36,    12,
      33,    23,    19,     0,    18,    56,    58,    55,     0,    57,
       0,     0,     0,     0,     0,    28,     0,    26,     0,     0,
      35,     0,    21,     0,    49,    50,     0,     0,     0,     0,
      24,    25,    27,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    39,    37,    52,    60,     0,    48,    29,
       0,     0,    40,    43,    44,    45,    46,    47,    41,    42,
      54,     0,     0,    51,     0,     0,    53,    59,    30,    32,
       0,    31
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -49,   -49,   100,   -49,    90,     5,   -49,   -49,   -49,   -17,
     -49,    78,   -49,    95,    56,   126,    -5,   -49,    66,   -49,
     -48,    24
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     3,     4,     5,    15,    25,     7,     9,    10,    16,
      17,    30,    31,    55,    56,    57,    26,    27,    37,    38,
      58,    87
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      64,    21,    65,    66,    67,     6,     1,     8,    36,    59,
       6,    83,    41,     2,    81,    86,    22,    11,    35,    82,
      90,    91,    40,    22,    29,    92,    93,    94,    95,    96,
      97,    98,    99,   -14,   101,    45,    46,    47,    18,     1,
      20,    28,    19,    48,    36,    49,     2,    23,    29,    32,
      50,    34,    51,    39,    86,    60,    23,    13,    14,    52,
      53,    42,    54,    45,    46,    47,    43,    45,    46,    47,
      44,    48,    61,    49,   100,    48,    22,    49,    50,   103,
      51,    85,    50,    72,    51,    73,    74,    75,    76,    77,
      63,    78,    79,    80,    81,    68,    69,    70,    89,    82,
      73,    74,    75,    76,    77,    12,    78,    79,    80,    81,
     110,    33,    24,    71,    82,   102,    73,    74,    75,    76,
      77,    62,    78,    79,    80,    81,   107,    84,     0,     0,
      82,    73,    74,    75,    76,    77,     0,    78,    79,    80,
      81,     0,     0,     0,     0,    82,   106,    73,    74,    75,
      76,    77,     0,    78,    79,    80,    81,     0,     0,     0,
      88,    82,    73,    74,    75,    76,    77,     0,    78,    79,
      80,    81,     0,     0,     0,   104,    82,    73,    74,    75,
      76,    77,     0,    78,    79,    80,    81,     0,     0,     0,
     105,    82,    73,    74,    75,    76,    77,     0,    78,    79,
      80,    81,    74,    75,    76,    77,    82,    78,     0,    80,
      81,    74,    75,    76,    77,    82,    78,     0,     0,    81,
       0,    75,    76,    77,    82,    78,     0,    77,    81,    78,
     108,   109,    81,    82,     0,     0,   111,    82
};

static const yytype_int8 yycheck[] =
{
      48,     7,    50,    51,    52,     0,    19,     5,    25,     8,
       5,    59,    29,    26,    17,    63,    22,     0,    23,    22,
      68,    69,    27,    22,    19,    73,    74,    75,    76,    77,
      78,    79,    80,    24,    82,     3,     4,     5,    24,    19,
       6,    21,    20,    11,    61,    13,    26,    24,    43,     5,
      18,     3,    20,    25,   102,     6,    24,     5,     6,    27,
      28,    21,    30,     3,     4,     5,     7,     3,     4,     5,
      23,    11,     7,    13,     5,    11,    22,    13,    18,    21,
      20,    21,    18,     6,    20,     8,     9,    10,    11,    12,
      20,    14,    15,    16,    17,    20,    20,    25,     6,    22,
       8,     9,    10,    11,    12,     5,    14,    15,    16,    17,
      29,    21,    17,    57,    22,     7,     8,     9,    10,    11,
      12,    43,    14,    15,    16,    17,   102,    61,    -1,    -1,
      22,     8,     9,    10,    11,    12,    -1,    14,    15,    16,
      17,    -1,    -1,    -1,    -1,    22,    23,     8,     9,    10,
      11,    12,    -1,    14,    15,    16,    17,    -1,    -1,    -1,
      21,    22,     8,     9,    10,    11,    12,    -1,    14,    15,
      16,    17,    -1,    -1,    -1,    21,    22,     8,     9,    10,
      11,    12,    -1,    14,    15,    16,    17,    -1,    -1,    -1,
      21,    22,     8,     9,    10,    11,    12,    -1,    14,    15,
      16,    17,     9,    10,    11,    12,    22,    14,    -1,    16,
      17,     9,    10,    11,    12,    22,    14,    -1,    -1,    17,
      -1,    10,    11,    12,    22,    14,    -1,    12,    17,    14,
     104,   105,    17,    22,    -1,    -1,   110,    22
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    19,    26,    32,    33,    34,    36,    37,     5,    38,
      39,     0,    33,     5,     6,    35,    40,    41,    24,    20,
       6,     7,    22,    24,    44,    36,    47,    48,    21,    36,
      42,    43,     5,    35,     3,    47,    40,    49,    50,    25,
      47,    40,    21,     7,    23,     3,     4,     5,    11,    13,
      18,    20,    27,    28,    30,    44,    45,    46,    51,     8,
       6,     7,    42,    20,    51,    51,    51,    51,    20,    20,
      25,    45,     6,     8,     9,    10,    11,    12,    14,    15,
      16,    17,    22,    51,    49,    21,    51,    52,    21,     6,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
       5,    51,     7,    21,    21,    21,    23,    52,    46,    46,
      29,    46
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    31,    32,    33,    33,    34,    34,    34,    35,    35,
      36,    36,    37,    37,    38,    38,    39,    40,    40,    41,
      41,    42,    42,    43,    44,    45,    45,    46,    46,    46,
      46,    46,    46,    47,    47,    48,    49,    49,    50,    50,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    52,
      52
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     2,     3,     1,     3,
       1,     1,     5,     2,     1,     0,     1,     1,     4,     4,
       3,     3,     1,     2,     4,     2,     0,     2,     1,     3,
       5,     7,     5,     2,     0,     3,     1,     3,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     4,     3,     4,     3,     1,     1,     1,     1,     3,
       1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Program: ExtDefList  */
#line 33 "./src/parser/syntax.ypp"
                          {syntaxTree = buildTree(1, NO_LINE, false, "Program", NO_VALUE, (yyvsp[0].node));}
#line 1214 "syntax.tab.cpp"
    break;

  case 3: /* ExtDefList: ExtDef ExtDefList  */
#line 36 "./src/parser/syntax.ypp"
                                    {(yyval.node) = buildTree(2, NO_LINE, false, "ExtDefList", NO_VALUE, (yyvsp[-1].node), (yyvsp[0].node));}
#line 1220 "syntax.tab.cpp"
    break;

  case 4: /* ExtDefList: %empty  */
#line 37 "./src/parser/syntax.ypp"
                {(yyval.node) = nullptr;}
#line 1226 "syntax.tab.cpp"
    break;

  case 5: /* ExtDef: Specifier ExtDecList SEMI  */
#line 40 "./src/parser/syntax.ypp"
                                        {(yyval.node) = buildTree(3, NO_LINE, false, "ExtDef", NO_VALUE, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1232 "syntax.tab.cpp"
    break;

  case 6: /* ExtDef: Specifier SEMI  */
#line 41 "./src/parser/syntax.ypp"
                           {(yyval.node) = buildTree(2, NO_LINE, false, "ExtDef", NO_VALUE, (yyvsp[-1].node), (yyvsp[0].node));}
#line 1238 "syntax.tab.cpp"
    break;

  case 7: /* ExtDef: Specifier FunDec CompSt  */
#line 42 "./src/parser/syntax.ypp"
                                    {(yyval.node) = buildTree(3, NO_LINE, false, "ExtDef", NO_VALUE, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1244 "syntax.tab.cpp"
    break;

  case 8: /* ExtDecList: VarDec  */
#line 45 "./src/parser/syntax.ypp"
                         {(yyval.node) = buildTree(1, NO_LINE, false, "ExtDecList", NO_VALUE, (yyvsp[0].node));}
#line 1250 "syntax.tab.cpp"
    break;

  case 9: /* ExtDecList: VarDec COMMA ExtDecList  */
#line 46 "./src/parser/syntax.ypp"
                                        {(yyval.node) = buildTree(3, NO_LINE, false, "ExtDecList", NO_VALUE, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1256 "syntax.tab.cpp"
    break;

  case 10: /* Specifier: TYPE  */
#line 49 "./src/parser/syntax.ypp"
                      {(yyval.node) = buildTree(1, NO_LINE, false, "Specifier", NO_VALUE, (yyvsp[0].node));}
#line 1262 "syntax.tab.cpp"
    break;

  case 11: /* Specifier: StructSpecifier  */
#line 50 "./src/parser/syntax.ypp"
                               {(yyval.node) = buildTree(1, NO_LINE, false, "Specifier", NO_VALUE, (yyvsp[0].node));}
#line 1268 "syntax.tab.cpp"
    break;

  case 12: /* StructSpecifier: STRUCT OptTag LC DefList RC  */
#line 53 "./src/parser/syntax.ypp"
                                                   {(yyval.node) = buildTree(5, NO_LINE, false, "StructSpecifier", NO_VALUE, (yyvsp[-4].node), (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1274 "syntax.tab.cpp"
    break;

  case 13: /* StructSpecifier: STRUCT Tag  */
#line 54 "./src/parser/syntax.ypp"
                                {(yyval.node) = buildTree(2, NO_LINE, false, "StructSpecifier", NO_VALUE, (yyvsp[-1].node), (yyvsp[0].node));}
#line 1280 "syntax.tab.cpp"
    break;

  case 14: /* OptTag: ID  */
#line 57 "./src/parser/syntax.ypp"
                 {(yyval.node) = buildTree(1, NO_LINE, false, "OptTag", NO_VALUE, (yyvsp[0].node));}
#line 1286 "syntax.tab.cpp"
    break;

  case 15: /* OptTag: %empty  */
#line 58 "./src/parser/syntax.ypp"
              {(yyval.node) = nullptr;}
#line 1292 "syntax.tab.cpp"
    break;

  case 16: /* Tag: ID  */
#line 61 "./src/parser/syntax.ypp"
              {(yyval.node) = buildTree(1, NO_LINE, false, "Tag", NO_VALUE, (yyvsp[0].node));}
#line 1298 "syntax.tab.cpp"
    break;

  case 17: /* VarDec: ID  */
#line 64 "./src/parser/syntax.ypp"
                 {(yyval.node) = buildTree(1, NO_LINE, false, "VarDec", NO_VALUE, (yyvsp[0].node));}
#line 1304 "syntax.tab.cpp"
    break;

  case 18: /* VarDec: VarDec LB INT RB  */
#line 65 "./src/parser/syntax.ypp"
                             {(yyval.node) = buildTree(4, NO_LINE, false, "VarDec", NO_VALUE, (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1310 "syntax.tab.cpp"
    break;

  case 19: /* FunDec: ID LP VarList RP  */
#line 68 "./src/parser/syntax.ypp"
                               {(yyval.node) = buildTree(4, NO_LINE, false, "FunDec", NO_VALUE, (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1316 "syntax.tab.cpp"
    break;

  case 20: /* FunDec: ID LP RP  */
#line 69 "./src/parser/syntax.ypp"
                     {(yyval.node) = buildTree(3, NO_LINE, false, "FunDec", NO_VALUE, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1322 "syntax.tab.cpp"
    break;

  case 21: /* VarList: ParamDec COMMA VarList  */
#line 72 "./src/parser/syntax.ypp"
                                      {(yyval.node) = buildTree(3, NO_LINE, false, "VarList", NO_VALUE, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1328 "syntax.tab.cpp"
    break;

  case 22: /* VarList: ParamDec  */
#line 73 "./src/parser/syntax.ypp"
                      {(yyval.node) = buildTree(1, NO_LINE, false, "VarList", NO_VALUE, (yyvsp[0].node));}
#line 1334 "syntax.tab.cpp"
    break;

  case 23: /* ParamDec: Specifier VarDec  */
#line 76 "./src/parser/syntax.ypp"
                                 {(yyval.node) = buildTree(2, NO_LINE, false, "ParamDec", NO_VALUE, (yyvsp[-1].node), (yyvsp[0].node));}
#line 1340 "syntax.tab.cpp"
    break;

  case 24: /* CompSt: LC DefList StmtList RC  */
#line 79 "./src/parser/syntax.ypp"
                                     {(yyval.node) = buildTree(4, NO_LINE, false, "CompSt", NO_VALUE, (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1346 "syntax.tab.cpp"
    break;

  case 25: /* StmtList: Stmt StmtList  */
#line 82 "./src/parser/syntax.ypp"
                              {(yyval.node) = buildTree(2, NO_LINE, false, "StmtList", NO_VALUE, (yyvsp[-1].node), (yyvsp[0].node));}
#line 1352 "syntax.tab.cpp"
    break;

  case 26: /* StmtList: %empty  */
#line 83 "./src/parser/syntax.ypp"
                {(yyval.node) = nullptr;}
#line 1358 "syntax.tab.cpp"
    break;

  case 27: /* Stmt: Exp SEMI  */
#line 86 "./src/parser/syntax.ypp"
                     {(yyval.node) = buildTree(2, NO_LINE, false, "Stmt", NO_VALUE, (yyvsp[-1].node), (yyvsp[0].node));}
#line 1364 "syntax.tab.cpp"
    break;

  case 28: /* Stmt: CompSt  */
#line 87 "./src/parser/syntax.ypp"
                           {(yyval.node) = buildTree(1, NO_LINE, false, "Stmt", NO_VALUE, (yyvsp[0].node));}
#line 1370 "syntax.tab.cpp"
    break;

  case 29: /* Stmt: RETURN Exp SEMI  */
#line 88 "./src/parser/syntax.ypp"
                                    {(yyval.node) = buildTree(3, NO_LINE, false, "Stmt", NO_VALUE, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1376 "syntax.tab.cpp"
    break;

  case 30: /* Stmt: IF LP Exp RP Stmt  */
#line 89 "./src/parser/syntax.ypp"
                                      {(yyval.node) = buildTree(5, NO_LINE, false, "Stmt", NO_VALUE, (yyvsp[-4].node), (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1382 "syntax.tab.cpp"
    break;

  case 31: /* Stmt: IF LP Exp RP Stmt ELSE Stmt  */
#line 90 "./src/parser/syntax.ypp"
                                                {(yyval.node) = buildTree(7, NO_LINE, false, "Stmt", NO_VALUE, (yyvsp[-6].node), (yyvsp[-5].node), (yyvsp[-4].node), (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1388 "syntax.tab.cpp"
    break;

  case 32: /* Stmt: WHILE LP Exp RP Stmt  */
#line 91 "./src/parser/syntax.ypp"
                                         {(yyval.node) = buildTree(5, NO_LINE, false, "Stmt", NO_VALUE, (yyvsp[-4].node), (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1394 "syntax.tab.cpp"
    break;

  case 33: /* DefList: Def DefList  */
#line 94 "./src/parser/syntax.ypp"
                           {(yyval.node) = buildTree(2, NO_LINE, false, "DefList", NO_VALUE, (yyvsp[-1].node), (yyvsp[0].node));}
#line 1400 "syntax.tab.cpp"
    break;

  case 34: /* DefList: %empty  */
#line 95 "./src/parser/syntax.ypp"
            {(yyval.node)=nullptr;}
#line 1406 "syntax.tab.cpp"
    break;

  case 35: /* Def: Specifier DecList SEMI  */
#line 98 "./src/parser/syntax.ypp"
                                  {(yyval.node) = buildTree(3, NO_LINE, false, "Def", NO_VALUE, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1412 "syntax.tab.cpp"
    break;

  case 36: /* DecList: Dec  */
#line 101 "./src/parser/syntax.ypp"
                   {(yyval.node) = buildTree(1, NO_LINE, false, "DecList", NO_VALUE, (yyvsp[0].node));}
#line 1418 "syntax.tab.cpp"
    break;

  case 37: /* DecList: Dec COMMA DecList  */
#line 102 "./src/parser/syntax.ypp"
                              {(yyval.node) = buildTree(3, NO_LINE, false, "DecList", NO_VALUE, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1424 "syntax.tab.cpp"
    break;

  case 38: /* Dec: VarDec  */
#line 105 "./src/parser/syntax.ypp"
                  {(yyval.node) = buildTree(1, NO_LINE, false, "Dec", NO_VALUE, (yyvsp[0].node));}
#line 1430 "syntax.tab.cpp"
    break;

  case 39: /* Dec: VarDec ASSIGNOP Exp  */
#line 106 "./src/parser/syntax.ypp"
                                {(yyval.node) = buildTree(3, NO_LINE, false, "Dec", NO_VALUE, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1436 "syntax.tab.cpp"
    break;

  case 40: /* Exp: Exp ASSIGNOP Exp  */
#line 109 "./src/parser/syntax.ypp"
                            {(yyval.node) = buildTree(3, NO_LINE, false, "Exp", NO_VALUE, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1442 "syntax.tab.cpp"
    break;

  case 41: /* Exp: Exp AND Exp  */
#line 110 "./src/parser/syntax.ypp"
                         {(yyval.node) = buildTree(3, NO_LINE, false, "Exp", NO_VALUE, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1448 "syntax.tab.cpp"
    break;

  case 42: /* Exp: Exp OR Exp  */
#line 111 "./src/parser/syntax.ypp"
                         {(yyval.node) = buildTree(3, NO_LINE, false, "Exp", NO_VALUE, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1454 "syntax.tab.cpp"
    break;

  case 43: /* Exp: Exp RELOP Exp  */
#line 112 "./src/parser/syntax.ypp"
                            {(yyval.node) = buildTree(3, NO_LINE, false, "Exp", NO_VALUE, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1460 "syntax.tab.cpp"
    break;

  case 44: /* Exp: Exp PLUS Exp  */
#line 113 "./src/parser/syntax.ypp"
                           {(yyval.node) = buildTree(3, NO_LINE, false, "Exp", NO_VALUE, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1466 "syntax.tab.cpp"
    break;

  case 45: /* Exp: Exp MINUS Exp  */
#line 114 "./src/parser/syntax.ypp"
                            {(yyval.node) = buildTree(3, NO_LINE, false, "Exp", NO_VALUE, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1472 "syntax.tab.cpp"
    break;

  case 46: /* Exp: Exp STAR Exp  */
#line 115 "./src/parser/syntax.ypp"
                           {(yyval.node) = buildTree(3, NO_LINE, false, "Exp", NO_VALUE, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1478 "syntax.tab.cpp"
    break;

  case 47: /* Exp: Exp DIV Exp  */
#line 116 "./src/parser/syntax.ypp"
                          {(yyval.node) = buildTree(3, NO_LINE, false, "Exp", NO_VALUE, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1484 "syntax.tab.cpp"
    break;

  case 48: /* Exp: LP Exp RP  */
#line 117 "./src/parser/syntax.ypp"
                        {(yyval.node) = buildTree(3, NO_LINE, false, "Exp", NO_VALUE, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1490 "syntax.tab.cpp"
    break;

  case 49: /* Exp: MINUS Exp  */
#line 118 "./src/parser/syntax.ypp"
                        {(yyval.node) = buildTree(2, NO_LINE, false, "Exp", NO_VALUE, (yyvsp[-1].node), (yyvsp[0].node));}
#line 1496 "syntax.tab.cpp"
    break;

  case 50: /* Exp: NOT Exp  */
#line 119 "./src/parser/syntax.ypp"
                      {(yyval.node) = buildTree(2, NO_LINE, false, "Exp", NO_VALUE, (yyvsp[-1].node), (yyvsp[0].node));}
#line 1502 "syntax.tab.cpp"
    break;

  case 51: /* Exp: ID LP Args RP  */
#line 120 "./src/parser/syntax.ypp"
                            {(yyval.node) = buildTree(4, NO_LINE, false, "Exp", NO_VALUE, (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1508 "syntax.tab.cpp"
    break;

  case 52: /* Exp: ID LP RP  */
#line 121 "./src/parser/syntax.ypp"
                       {(yyval.node) = buildTree(3, NO_LINE, false, "Exp", NO_VALUE, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1514 "syntax.tab.cpp"
    break;

  case 53: /* Exp: Exp LB Exp RB  */
#line 122 "./src/parser/syntax.ypp"
                            {(yyval.node) = buildTree(4, NO_LINE, false, "Exp", NO_VALUE, (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1520 "syntax.tab.cpp"
    break;

  case 54: /* Exp: Exp DOT ID  */
#line 123 "./src/parser/syntax.ypp"
                         {(yyval.node) = buildTree(3, NO_LINE, false, "Exp", NO_VALUE, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1526 "syntax.tab.cpp"
    break;

  case 55: /* Exp: ID  */
#line 124 "./src/parser/syntax.ypp"
                 {(yyval.node) = buildTree(1, NO_LINE, false, "Exp", NO_VALUE, (yyvsp[0].node));}
#line 1532 "syntax.tab.cpp"
    break;

  case 56: /* Exp: INT  */
#line 125 "./src/parser/syntax.ypp"
                  {(yyval.node) = buildTree(1, NO_LINE, false, "Exp", NO_VALUE, (yyvsp[0].node));}
#line 1538 "syntax.tab.cpp"
    break;

  case 57: /* Exp: STRING  */
#line 126 "./src/parser/syntax.ypp"
                     {(yyval.node) = buildTree(1, NO_LINE, false, "Exp", NO_VALUE, (yyvsp[0].node));}
#line 1544 "syntax.tab.cpp"
    break;

  case 58: /* Exp: FLOAT  */
#line 127 "./src/parser/syntax.ypp"
                    {(yyval.node) = buildTree(1, NO_LINE, false, "Exp", NO_VALUE, (yyvsp[0].node));}
#line 1550 "syntax.tab.cpp"
    break;

  case 59: /* Args: Exp COMMA Args  */
#line 130 "./src/parser/syntax.ypp"
                           {(yyval.node) = buildTree(3, NO_LINE, false, "Args", NO_VALUE, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1556 "syntax.tab.cpp"
    break;

  case 60: /* Args: Exp  */
#line 131 "./src/parser/syntax.ypp"
                  {(yyval.node) = buildTree(1, NO_LINE, false, "Args", NO_VALUE, (yyvsp[0].node));}
#line 1562 "syntax.tab.cpp"
    break;


#line 1566 "syntax.tab.cpp"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 134 "./src/parser/syntax.ypp"


void yyerror(char* msg){
    
}


