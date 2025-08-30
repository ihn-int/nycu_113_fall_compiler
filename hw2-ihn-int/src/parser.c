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
#line 1 "parser.y"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

extern int32_t line_num;    /* declared in scanner.l */
extern char current_line[]; /* declared in scanner.l */
extern FILE *yyin;          /* declared by lex */
extern char *yytext;        /* declared by lex */

extern int yylex(void);
static void yyerror(const char *msg);
extern int yylex_destroy(void);

#line 86 "parser.c"

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

#include "parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_COMMA = 3,                      /* COMMA  */
  YYSYMBOL_SEMICOLON = 4,                  /* SEMICOLON  */
  YYSYMBOL_COLON = 5,                      /* COLON  */
  YYSYMBOL_LEFT_PAREN = 6,                 /* LEFT_PAREN  */
  YYSYMBOL_RIGHT_PAREN = 7,                /* RIGHT_PAREN  */
  YYSYMBOL_LEFT_BRACKET = 8,               /* LEFT_BRACKET  */
  YYSYMBOL_RIGHT_BRACKET = 9,              /* RIGHT_BRACKET  */
  YYSYMBOL_IDENTIFIER = 10,                /* IDENTIFIER  */
  YYSYMBOL_DECIMAL = 11,                   /* DECIMAL  */
  YYSYMBOL_OCTAL = 12,                     /* OCTAL  */
  YYSYMBOL_FLOAT = 13,                     /* FLOAT  */
  YYSYMBOL_SCIENTIFIC = 14,                /* SCIENTIFIC  */
  YYSYMBOL_KW_VAR = 15,                    /* KW_VAR  */
  YYSYMBOL_KW_DEF = 16,                    /* KW_DEF  */
  YYSYMBOL_KW_ARRAY = 17,                  /* KW_ARRAY  */
  YYSYMBOL_KW_OF = 18,                     /* KW_OF  */
  YYSYMBOL_KW_BOOL = 19,                   /* KW_BOOL  */
  YYSYMBOL_KW_INT = 20,                    /* KW_INT  */
  YYSYMBOL_KW_REAL = 21,                   /* KW_REAL  */
  YYSYMBOL_KW_STR = 22,                    /* KW_STR  */
  YYSYMBOL_KW_TRUE = 23,                   /* KW_TRUE  */
  YYSYMBOL_KW_FALSE = 24,                  /* KW_FALSE  */
  YYSYMBOL_KW_WHILE = 25,                  /* KW_WHILE  */
  YYSYMBOL_KW_DO = 26,                     /* KW_DO  */
  YYSYMBOL_KW_IF = 27,                     /* KW_IF  */
  YYSYMBOL_KW_THEN = 28,                   /* KW_THEN  */
  YYSYMBOL_KW_ELSE = 29,                   /* KW_ELSE  */
  YYSYMBOL_KW_FOR = 30,                    /* KW_FOR  */
  YYSYMBOL_KW_TO = 31,                     /* KW_TO  */
  YYSYMBOL_KW_BEGIN = 32,                  /* KW_BEGIN  */
  YYSYMBOL_KW_END = 33,                    /* KW_END  */
  YYSYMBOL_KW_PRINT = 34,                  /* KW_PRINT  */
  YYSYMBOL_KW_READ = 35,                   /* KW_READ  */
  YYSYMBOL_KW_RETURN = 36,                 /* KW_RETURN  */
  YYSYMBOL_CHAR = 37,                      /* CHAR  */
  YYSYMBOL_STRING = 38,                    /* STRING  */
  YYSYMBOL_SPACE = 39,                     /* SPACE  */
  YYSYMBOL_ASSIGNMENT = 40,                /* ASSIGNMENT  */
  YYSYMBOL_OR = 41,                        /* OR  */
  YYSYMBOL_AND = 42,                       /* AND  */
  YYSYMBOL_NOT = 43,                       /* NOT  */
  YYSYMBOL_LT = 44,                        /* LT  */
  YYSYMBOL_GT = 45,                        /* GT  */
  YYSYMBOL_EQ = 46,                        /* EQ  */
  YYSYMBOL_LE = 47,                        /* LE  */
  YYSYMBOL_GE = 48,                        /* GE  */
  YYSYMBOL_NE = 49,                        /* NE  */
  YYSYMBOL_ADD = 50,                       /* ADD  */
  YYSYMBOL_SUB = 51,                       /* SUB  */
  YYSYMBOL_MUL = 52,                       /* MUL  */
  YYSYMBOL_DIV = 53,                       /* DIV  */
  YYSYMBOL_MOD = 54,                       /* MOD  */
  YYSYMBOL_NEG = 55,                       /* NEG  */
  YYSYMBOL_YYACCEPT = 56,                  /* $accept  */
  YYSYMBOL_NT_PROGRAM = 57,                /* NT_PROGRAM  */
  YYSYMBOL_NT_DECLARATION_LIST_OPT = 58,   /* NT_DECLARATION_LIST_OPT  */
  YYSYMBOL_NT_DECLARATION_LIST = 59,       /* NT_DECLARATION_LIST  */
  YYSYMBOL_NT_FUNCTION_LIST_OPT = 60,      /* NT_FUNCTION_LIST_OPT  */
  YYSYMBOL_NT_FUNCTION_LIST = 61,          /* NT_FUNCTION_LIST  */
  YYSYMBOL_NT_FUNCTION = 62,               /* NT_FUNCTION  */
  YYSYMBOL_NT_FUNCTION_HEADER = 63,        /* NT_FUNCTION_HEADER  */
  YYSYMBOL_NT_FORMAL_ARG_LIST_OPT = 64,    /* NT_FORMAL_ARG_LIST_OPT  */
  YYSYMBOL_NT_FORMAL_ARG_LIST = 65,        /* NT_FORMAL_ARG_LIST  */
  YYSYMBOL_NT_RETURN_TYPE = 66,            /* NT_RETURN_TYPE  */
  YYSYMBOL_NT_FUNCTION_DECLARATION = 67,   /* NT_FUNCTION_DECLARATION  */
  YYSYMBOL_NT_FUNCTION_DEFINITION = 68,    /* NT_FUNCTION_DEFINITION  */
  YYSYMBOL_NT_FORMAL_ARG = 69,             /* NT_FORMAL_ARG  */
  YYSYMBOL_NT_DECLARATION = 70,            /* NT_DECLARATION  */
  YYSYMBOL_NT_VARIABLE_DECLARATION = 71,   /* NT_VARIABLE_DECLARATION  */
  YYSYMBOL_NT_CONSTANT_DECLARATION = 72,   /* NT_CONSTANT_DECLARATION  */
  YYSYMBOL_NT_IDENTIFIER_LIST = 73,        /* NT_IDENTIFIER_LIST  */
  YYSYMBOL_NT_TYPE = 74,                   /* NT_TYPE  */
  YYSYMBOL_NT_SCALAR_TYPE = 75,            /* NT_SCALAR_TYPE  */
  YYSYMBOL_NT_ARRAY_TYPE = 76,             /* NT_ARRAY_TYPE  */
  YYSYMBOL_NT_STATEMENT = 77,              /* NT_STATEMENT  */
  YYSYMBOL_NT_SIMPLE_STATEMENT = 78,       /* NT_SIMPLE_STATEMENT  */
  YYSYMBOL_NT_ASSIGNMENT = 79,             /* NT_ASSIGNMENT  */
  YYSYMBOL_NT_PRINT_STATEMENT = 80,        /* NT_PRINT_STATEMENT  */
  YYSYMBOL_NT_READ_STATEMENT = 81,         /* NT_READ_STATEMENT  */
  YYSYMBOL_NT_CONDITIONAL_STATEMENT = 82,  /* NT_CONDITIONAL_STATEMENT  */
  YYSYMBOL_NT_FUNCTION_CALL_STATEMENT = 83, /* NT_FUNCTION_CALL_STATEMENT  */
  YYSYMBOL_NT_LOOP_STATEMENT = 84,         /* NT_LOOP_STATEMENT  */
  YYSYMBOL_NT_RETURN_STATEMENT = 85,       /* NT_RETURN_STATEMENT  */
  YYSYMBOL_NT_COMPOUND_STATEMENT = 86,     /* NT_COMPOUND_STATEMENT  */
  YYSYMBOL_NT_STATEMENT_LIST_OPT = 87,     /* NT_STATEMENT_LIST_OPT  */
  YYSYMBOL_NT_STATEMENT_LIST = 88,         /* NT_STATEMENT_LIST  */
  YYSYMBOL_NT_EXPRESSION = 89,             /* NT_EXPRESSION  */
  YYSYMBOL_NT_LITERAL_CONSTANT = 90,       /* NT_LITERAL_CONSTANT  */
  YYSYMBOL_NT_INTEGER_LITERAL = 91,        /* NT_INTEGER_LITERAL  */
  YYSYMBOL_NT_REAL_LITERAL = 92,           /* NT_REAL_LITERAL  */
  YYSYMBOL_NT_STRING_LITERAL = 93,         /* NT_STRING_LITERAL  */
  YYSYMBOL_NT_BOOLEAN_LITERAL = 94,        /* NT_BOOLEAN_LITERAL  */
  YYSYMBOL_NT_VARIABLE_REFERENCE = 95,     /* NT_VARIABLE_REFERENCE  */
  YYSYMBOL_NT_BRACKET_EXPRESSION_LIST_OPT = 96, /* NT_BRACKET_EXPRESSION_LIST_OPT  */
  YYSYMBOL_NT_BRACKET_EXPRESSION_LIST = 97, /* NT_BRACKET_EXPRESSION_LIST  */
  YYSYMBOL_NT_BRACKET_EXPRESSION = 98,     /* NT_BRACKET_EXPRESSION  */
  YYSYMBOL_NT_FUNCTION_CALL = 99,          /* NT_FUNCTION_CALL  */
  YYSYMBOL_NT_EXPRESSION_LIST_OPT = 100,   /* NT_EXPRESSION_LIST_OPT  */
  YYSYMBOL_NT_EXPRESSION_LIST = 101,       /* NT_EXPRESSION_LIST  */
  YYSYMBOL_NT_BINARY_OPERATION = 102,      /* NT_BINARY_OPERATION  */
  YYSYMBOL_NT_RELATIONAL_OPERATOR = 103,   /* NT_RELATIONAL_OPERATOR  */
  YYSYMBOL_NT_UNARY_OPERATION = 104        /* NT_UNARY_OPERATION  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   326

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  107
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  185

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   310


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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   116,   116,   123,   124,   126,   127,   130,   131,   134,
     135,   138,   139,   142,   145,   146,   149,   150,   153,   154,
     157,   160,   165,   170,   171,   174,   177,   178,   179,   180,
     181,   182,   186,   187,   191,   192,   195,   196,   197,   198,
     201,   205,   206,   207,   208,   209,   210,   213,   214,   215,
     218,   221,   224,   227,   232,   237,   240,   243,   248,   251,
     257,   258,   261,   262,   266,   267,   268,   269,   270,   271,
     274,   275,   276,   277,   279,   280,   283,   284,   287,   290,
     291,   294,   297,   298,   301,   302,   305,   308,   311,   312,
     315,   316,   319,   320,   321,   322,   323,   324,   325,   326,
     329,   330,   331,   332,   333,   334,   337,   338
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
  "\"end of file\"", "error", "\"invalid token\"", "COMMA", "SEMICOLON",
  "COLON", "LEFT_PAREN", "RIGHT_PAREN", "LEFT_BRACKET", "RIGHT_BRACKET",
  "IDENTIFIER", "DECIMAL", "OCTAL", "FLOAT", "SCIENTIFIC", "KW_VAR",
  "KW_DEF", "KW_ARRAY", "KW_OF", "KW_BOOL", "KW_INT", "KW_REAL", "KW_STR",
  "KW_TRUE", "KW_FALSE", "KW_WHILE", "KW_DO", "KW_IF", "KW_THEN",
  "KW_ELSE", "KW_FOR", "KW_TO", "KW_BEGIN", "KW_END", "KW_PRINT",
  "KW_READ", "KW_RETURN", "CHAR", "STRING", "SPACE", "ASSIGNMENT", "OR",
  "AND", "NOT", "LT", "GT", "EQ", "LE", "GE", "NE", "ADD", "SUB", "MUL",
  "DIV", "MOD", "NEG", "$accept", "NT_PROGRAM", "NT_DECLARATION_LIST_OPT",
  "NT_DECLARATION_LIST", "NT_FUNCTION_LIST_OPT", "NT_FUNCTION_LIST",
  "NT_FUNCTION", "NT_FUNCTION_HEADER", "NT_FORMAL_ARG_LIST_OPT",
  "NT_FORMAL_ARG_LIST", "NT_RETURN_TYPE", "NT_FUNCTION_DECLARATION",
  "NT_FUNCTION_DEFINITION", "NT_FORMAL_ARG", "NT_DECLARATION",
  "NT_VARIABLE_DECLARATION", "NT_CONSTANT_DECLARATION",
  "NT_IDENTIFIER_LIST", "NT_TYPE", "NT_SCALAR_TYPE", "NT_ARRAY_TYPE",
  "NT_STATEMENT", "NT_SIMPLE_STATEMENT", "NT_ASSIGNMENT",
  "NT_PRINT_STATEMENT", "NT_READ_STATEMENT", "NT_CONDITIONAL_STATEMENT",
  "NT_FUNCTION_CALL_STATEMENT", "NT_LOOP_STATEMENT", "NT_RETURN_STATEMENT",
  "NT_COMPOUND_STATEMENT", "NT_STATEMENT_LIST_OPT", "NT_STATEMENT_LIST",
  "NT_EXPRESSION", "NT_LITERAL_CONSTANT", "NT_INTEGER_LITERAL",
  "NT_REAL_LITERAL", "NT_STRING_LITERAL", "NT_BOOLEAN_LITERAL",
  "NT_VARIABLE_REFERENCE", "NT_BRACKET_EXPRESSION_LIST_OPT",
  "NT_BRACKET_EXPRESSION_LIST", "NT_BRACKET_EXPRESSION",
  "NT_FUNCTION_CALL", "NT_EXPRESSION_LIST_OPT", "NT_EXPRESSION_LIST",
  "NT_BINARY_OPERATION", "NT_RELATIONAL_OPERATOR", "NT_UNARY_OPERATION", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-66)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       5,    25,    30,    27,   -66,    63,    66,   -66,    27,   -66,
     -66,    71,    83,    84,    59,   -66,    66,     2,   -66,   -66,
     -66,    63,   210,    63,    27,    60,   -66,   -66,    70,   -66,
     -66,   -66,   -66,   -66,    15,   -66,   -66,   -66,   -66,   -66,
     -66,   -66,    72,   100,   -66,   -66,   103,   119,   120,   121,
     122,   -66,   126,   142,    62,   -66,   -66,   108,   127,   144,
     -66,   -66,   -66,   -66,   -66,   145,    63,     3,    10,   202,
     202,   141,   202,   202,   202,    62,   -66,   -66,   -66,   -66,
     -66,   -66,   -66,   -66,   -66,   116,   -66,   112,   150,     3,
     -66,   -66,    80,   -66,   -66,   -66,   202,   202,   -66,   -66,
     147,   202,   202,   202,   218,   -66,   -66,   -66,   -66,   -66,
     -66,   -66,   -66,   -66,   245,   117,    13,    64,    91,   -66,
     -66,   202,   -66,   -66,   -66,    -1,   149,   -66,   153,   -66,
     139,   230,   -66,    59,   202,   202,   -66,   -66,   -66,   -66,
     -66,   -66,   202,   202,   202,   202,   202,   202,    59,    15,
     -66,   -66,   -66,   123,   202,   -66,   -66,   -66,   128,   272,
     230,    68,    68,   -66,   -66,   -66,   259,    42,   129,   -66,
     -66,   133,    59,   136,    15,   -66,   146,   -66,   152,   155,
      59,   -66,   163,   183,   -66
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     3,     1,     0,     7,     4,     6,    23,
      24,    33,     0,     0,     0,     8,    10,     0,    11,    12,
       5,     0,     0,    14,     3,     0,     9,    20,     0,    32,
      74,    75,    76,    77,     0,    39,    36,    37,    38,    79,
      80,    78,     0,     0,    34,    35,     0,     0,     0,     0,
       0,    15,    17,     0,    60,     2,    21,     0,     0,     0,
      25,    27,    29,    30,    31,    18,     0,     0,    82,     0,
       0,     0,     0,     0,     0,    63,    41,    47,    48,    49,
      42,    43,    44,    45,    46,     0,    61,     0,     0,     0,
      26,    28,     0,    13,    16,    22,    88,     0,    81,    83,
      85,     0,     0,     0,     0,    64,    70,    71,    72,    73,
      65,    66,    67,    68,     0,     0,     0,     0,     0,    62,
      59,     0,    55,    40,    19,    91,     0,    89,     0,    84,
       0,   106,   107,     0,     0,     0,   100,   104,   105,   101,
     103,   102,     0,     0,     0,     0,     0,     0,     0,     0,
      51,    52,    58,     0,     0,    87,    86,    69,     0,    92,
      93,    96,    95,    99,    97,    98,    94,     0,     0,    50,
      90,     0,     0,     0,     0,    56,     0,    54,     0,     0,
       0,    53,     0,     0,    57
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -66,   -66,   186,   203,   -66,   201,   -66,   -66,   -66,   154,
     -66,   -66,   -66,   -66,   -66,   -66,   -66,     7,   -56,   143,
     -66,   -66,   -66,   -66,   -66,   -66,   -66,   -66,   -66,   -66,
     -14,   -66,   161,   -65,   -66,   -21,    -3,   196,   197,   -44,
     -66,   137,   -66,   -40,   -66,    74,   -66,   -66,   -66
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     6,     7,    14,    15,    16,    17,    50,    51,
      93,    18,    19,    52,     8,     9,    10,    53,    43,    44,
      45,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,   125,   105,   106,   107,   108,   109,   110,
      98,    99,   100,   111,   126,   127,   112,   147,   113
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      25,    46,   154,    28,   104,   114,    27,   116,   117,   118,
      87,    95,    12,    57,    88,     1,    96,   150,    97,    47,
      34,    58,    35,    36,    37,    38,    30,    31,    29,     3,
       4,    87,   128,   123,    24,    88,   130,   131,   132,    59,
     134,   135,     5,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   134,   135,   153,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   151,   159,
     160,   172,    68,    11,    21,   173,    13,   161,   162,   163,
     164,   165,   166,    30,    31,    32,    33,    69,    22,    70,
      23,    24,    71,    55,    24,   152,    72,    73,    74,    35,
      36,    37,    38,    56,    60,   134,   135,    61,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   158,
     144,   145,   146,    62,    63,    64,    89,   169,   168,    65,
      66,    90,   134,   135,   167,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   157,    67,    91,   120,
      92,   115,   121,   178,   122,    97,   155,   149,   176,   175,
     174,   171,   156,   177,   134,   135,   182,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   180,   179,
     134,   135,   181,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   134,   135,   183,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   101,   184,
      54,    20,    68,    30,    31,    32,    33,    26,    48,    49,
      94,    30,    31,    32,    33,    39,    40,    34,   170,    35,
      36,    37,    38,    39,    40,   124,   119,   129,     0,     0,
      41,     0,     0,     0,   133,   102,     0,     0,    41,     0,
       0,     0,     0,   103,     0,     0,     0,     0,     0,   134,
     135,    42,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   148,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,     0,   134,   135,     0,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     134,   135,     0,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   135,     0,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146
};

static const yytype_int16 yycheck[] =
{
      14,    22,     3,    17,    69,    70,     4,    72,    73,    74,
      54,    67,     5,    34,    54,    10,     6,     4,     8,    22,
      17,    42,    19,    20,    21,    22,    11,    12,    21,     4,
       0,    75,    97,    89,    32,    75,   101,   102,   103,    42,
      41,    42,    15,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    41,    42,   121,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,     4,   134,
     135,    29,    10,    10,     3,    33,    10,   142,   143,   144,
     145,   146,   147,    11,    12,    13,    14,    25,     5,    27,
       6,    32,    30,    33,    32,     4,    34,    35,    36,    19,
      20,    21,    22,    33,     4,    41,    42,     4,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,   133,
      52,    53,    54,     4,     4,     4,    18,     4,   149,     7,
       4,     4,    41,    42,   148,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,     7,     5,     4,    33,
       5,    10,    40,   174,     4,     8,     7,    40,   172,    26,
      31,    33,     9,    27,    41,    42,   180,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    26,    33,
      41,    42,    27,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    41,    42,    33,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,     6,    26,
      24,     8,    10,    11,    12,    13,    14,    16,    22,    22,
      66,    11,    12,    13,    14,    23,    24,    17,   154,    19,
      20,    21,    22,    23,    24,    92,    75,   100,    -1,    -1,
      38,    -1,    -1,    -1,    26,    43,    -1,    -1,    38,    -1,
      -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,    41,
      42,    51,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    28,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    -1,    41,    42,    -1,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      41,    42,    -1,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    42,    -1,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    10,    57,     4,     0,    15,    58,    59,    70,    71,
      72,    10,    73,    10,    60,    61,    62,    63,    67,    68,
      59,     3,     5,     6,    32,    86,    61,     4,    86,    73,
      11,    12,    13,    14,    17,    19,    20,    21,    22,    23,
      24,    38,    51,    74,    75,    76,    91,    92,    93,    94,
      64,    65,    69,    73,    58,    33,    33,    91,    91,    92,
       4,     4,     4,     4,     4,     7,     4,     5,    10,    25,
      27,    30,    34,    35,    36,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    95,    99,    18,
       4,     4,     5,    66,    65,    74,     6,     8,    96,    97,
      98,     6,    43,    51,    89,    90,    91,    92,    93,    94,
      95,    99,   102,   104,    89,    10,    89,    89,    89,    88,
      33,    40,     4,    74,    75,    89,   100,   101,    89,    97,
      89,    89,    89,    26,    41,    42,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,   103,    28,    40,
       4,     4,     4,    89,     3,     7,     9,     7,    86,    89,
      89,    89,    89,    89,    89,    89,    89,    86,    91,     4,
     101,    33,    29,    33,    31,    26,    86,    27,    91,    33,
      26,    27,    86,    33,    26
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    56,    57,    58,    58,    59,    59,    60,    60,    61,
      61,    62,    62,    63,    64,    64,    65,    65,    66,    66,
      67,    68,    69,    70,    70,    71,    72,    72,    72,    72,
      72,    72,    73,    73,    74,    74,    75,    75,    75,    75,
      76,    77,    77,    77,    77,    77,    77,    78,    78,    78,
      79,    80,    81,    82,    82,    83,    84,    84,    85,    86,
      87,    87,    88,    88,    89,    89,    89,    89,    89,    89,
      90,    90,    90,    90,    91,    91,    92,    92,    93,    94,
      94,    95,    96,    96,    97,    97,    98,    99,   100,   100,
     101,   101,   102,   102,   102,   102,   102,   102,   102,   102,
     103,   103,   103,   103,   103,   103,   104,   104
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     6,     0,     1,     2,     1,     0,     1,     2,
       1,     1,     1,     5,     0,     1,     3,     1,     0,     2,
       2,     3,     3,     1,     1,     5,     6,     5,     6,     5,
       5,     5,     3,     1,     1,     1,     1,     1,     1,     1,
       4,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       4,     3,     3,     8,     6,     2,     6,    10,     3,     4,
       0,     1,     2,     1,     1,     1,     1,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     0,     1,     2,     1,     3,     4,     0,     1,
       3,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     1,     1,     1,     1,     1,     2,     2
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

#line 1346 "parser.c"

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

#line 342 "parser.y"


void yyerror(const char *msg) {
    fprintf(stderr,
            "\n"
            "|-----------------------------------------------------------------"
            "---------\n"
            "| Error found in Line #%d: %s\n"
            "|\n"
            "| Unmatched token: %s\n"
            "|-----------------------------------------------------------------"
            "---------\n",
            line_num, current_line, yytext);
    exit(-1);
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(-1);
    }

    yyin = fopen(argv[1], "r");
    if (yyin == NULL) {
        perror("fopen() failed");
        exit(-1);
    }

    yyparse();

    fclose(yyin);
    yylex_destroy();

    printf("\n"
           "|--------------------------------|\n"
           "|  There is no syntactic error!  |\n"
           "|--------------------------------|\n");
    return 0;
}
