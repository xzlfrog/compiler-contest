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
#line 10 "src/frontend/sysy.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/frontend/frontendTool.hpp"
#include<string>
#include<vector>
#include"../../include/llvm.hpp"
#include"../../include/sym.hpp"
#include"../../include/exp.hpp"
#include<stack>
#include<fstream>
extern FILE* yyin;
#include<iostream>


void yyerror(const char *s);
extern int yylex(void);
extern int yylineno;
extern ModuleList* module_list;
extern int scope;
extern std::vector<std::unordered_map<std::string,int>> variable_rename_table;
extern std::vector<std::unordered_map<std::string,Symbol*>> variable_table;
extern std::stack<int>array_initial;
extern int array_init_idx;

#line 98 "src/frontend/sysy.y.cpp"

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

#include "sysy.y.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_FLOAT = 4,                      /* FLOAT  */
  YYSYMBOL_CONST = 5,                      /* CONST  */
  YYSYMBOL_VOID = 6,                       /* VOID  */
  YYSYMBOL_IF = 7,                         /* IF  */
  YYSYMBOL_ELSE = 8,                       /* ELSE  */
  YYSYMBOL_WHILE = 9,                      /* WHILE  */
  YYSYMBOL_BREAK = 10,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 11,                  /* CONTINUE  */
  YYSYMBOL_RETURN = 12,                    /* RETURN  */
  YYSYMBOL_EQ = 13,                        /* EQ  */
  YYSYMBOL_NE = 14,                        /* NE  */
  YYSYMBOL_LT = 15,                        /* LT  */
  YYSYMBOL_GT = 16,                        /* GT  */
  YYSYMBOL_LE = 17,                        /* LE  */
  YYSYMBOL_GE = 18,                        /* GE  */
  YYSYMBOL_AND = 19,                       /* AND  */
  YYSYMBOL_OR = 20,                        /* OR  */
  YYSYMBOL_NOT = 21,                       /* NOT  */
  YYSYMBOL_IDENTIFIER = 22,                /* IDENTIFIER  */
  YYSYMBOL_INT_CONST = 23,                 /* INT_CONST  */
  YYSYMBOL_FLOAT_CONST = 24,               /* FLOAT_CONST  */
  YYSYMBOL_IFX = 25,                       /* IFX  */
  YYSYMBOL_26_ = 26,                       /* ';'  */
  YYSYMBOL_27_ = 27,                       /* ','  */
  YYSYMBOL_28_ = 28,                       /* '['  */
  YYSYMBOL_29_ = 29,                       /* ']'  */
  YYSYMBOL_30_ = 30,                       /* '='  */
  YYSYMBOL_31_ = 31,                       /* '('  */
  YYSYMBOL_32_ = 32,                       /* ')'  */
  YYSYMBOL_33_ = 33,                       /* '{'  */
  YYSYMBOL_34_ = 34,                       /* '}'  */
  YYSYMBOL_35_ = 35,                       /* '+'  */
  YYSYMBOL_36_ = 36,                       /* '-'  */
  YYSYMBOL_37_ = 37,                       /* '*'  */
  YYSYMBOL_38_ = 38,                       /* '/'  */
  YYSYMBOL_39_ = 39,                       /* '%'  */
  YYSYMBOL_YYACCEPT = 40,                  /* $accept  */
  YYSYMBOL_comp_unit = 41,                 /* comp_unit  */
  YYSYMBOL_decl_or_func_list = 42,         /* decl_or_func_list  */
  YYSYMBOL_decl_or_func = 43,              /* decl_or_func  */
  YYSYMBOL_decl = 44,                      /* decl  */
  YYSYMBOL_const_decl = 45,                /* const_decl  */
  YYSYMBOL_var_decl = 46,                  /* var_decl  */
  YYSYMBOL_btype = 47,                     /* btype  */
  YYSYMBOL_const_def_list = 48,            /* const_def_list  */
  YYSYMBOL_var_def_list = 49,              /* var_def_list  */
  YYSYMBOL_const_def = 50,                 /* const_def  */
  YYSYMBOL_var_def = 51,                   /* var_def  */
  YYSYMBOL_dim_list = 52,                  /* dim_list  */
  YYSYMBOL_func_def = 53,                  /* func_def  */
  YYSYMBOL_func_params = 54,               /* func_params  */
  YYSYMBOL_func_param_list = 55,           /* func_param_list  */
  YYSYMBOL_func_param = 56,                /* func_param  */
  YYSYMBOL_block = 57,                     /* block  */
  YYSYMBOL_58_1 = 58,                      /* $@1  */
  YYSYMBOL_block_items = 59,               /* block_items  */
  YYSYMBOL_block_item = 60,                /* block_item  */
  YYSYMBOL_stmt = 61,                      /* stmt  */
  YYSYMBOL_62_2 = 62,                      /* @2  */
  YYSYMBOL_LVal = 63,                      /* LVal  */
  YYSYMBOL_index_list = 64,                /* index_list  */
  YYSYMBOL_expr = 65,                      /* expr  */
  YYSYMBOL_cond = 66,                      /* cond  */
  YYSYMBOL_or_expr = 67,                   /* or_expr  */
  YYSYMBOL_and_expr = 68,                  /* and_expr  */
  YYSYMBOL_eq_expr = 69,                   /* eq_expr  */
  YYSYMBOL_rel_expr = 70,                  /* rel_expr  */
  YYSYMBOL_add_expr = 71,                  /* add_expr  */
  YYSYMBOL_mul_expr = 72,                  /* mul_expr  */
  YYSYMBOL_unary_expr = 73,                /* unary_expr  */
  YYSYMBOL_primary_expr = 74,              /* primary_expr  */
  YYSYMBOL_func_call = 75,                 /* func_call  */
  YYSYMBOL_expr_list = 76,                 /* expr_list  */
  YYSYMBOL_const_exp = 77,                 /* const_exp  */
  YYSYMBOL_const_init_val = 78,            /* const_init_val  */
  YYSYMBOL_const_init_list = 79,           /* const_init_list  */
  YYSYMBOL_var_init_val = 80,              /* var_init_val  */
  YYSYMBOL_81_3 = 81,                      /* $@3  */
  YYSYMBOL_var_init_list = 82              /* var_init_list  */
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
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   204

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  95
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  170

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   280


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
       2,     2,     2,     2,     2,     2,     2,    39,     2,     2,
      31,    32,    37,    35,    27,    36,     2,    38,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    26,
       2,    30,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    28,     2,    29,     2,     2,     2,     2,     2,     2,
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
      25
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    70,    70,    75,    77,    81,    83,    87,    89,    93,
     101,   109,   111,   113,   117,   122,   128,   133,   139,   141,
     146,   149,   155,   156,   163,   171,   172,   177,   181,   187,
     193,   202,   201,   214,   215,   221,   223,   227,   229,   231,
     233,   235,   237,   240,   239,   243,   245,   247,   249,   253,
     259,   260,   267,   271,   275,   277,   281,   282,   286,   287,
     289,   293,   294,   296,   298,   300,   304,   305,   307,   311,
     312,   314,   316,   320,   322,   324,   326,   330,   332,   334,
     336,   338,   342,   344,   348,   350,   356,   360,   364,   369,
     373,   379,   384,   383,   393,   397
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
  "\"end of file\"", "error", "\"invalid token\"", "INT", "FLOAT",
  "CONST", "VOID", "IF", "ELSE", "WHILE", "BREAK", "CONTINUE", "RETURN",
  "EQ", "NE", "LT", "GT", "LE", "GE", "AND", "OR", "NOT", "IDENTIFIER",
  "INT_CONST", "FLOAT_CONST", "IFX", "';'", "','", "'['", "']'", "'='",
  "'('", "')'", "'{'", "'}'", "'+'", "'-'", "'*'", "'/'", "'%'", "$accept",
  "comp_unit", "decl_or_func_list", "decl_or_func", "decl", "const_decl",
  "var_decl", "btype", "const_def_list", "var_def_list", "const_def",
  "var_def", "dim_list", "func_def", "func_params", "func_param_list",
  "func_param", "block", "$@1", "block_items", "block_item", "stmt", "@2",
  "LVal", "index_list", "expr", "cond", "or_expr", "and_expr", "eq_expr",
  "rel_expr", "add_expr", "mul_expr", "unary_expr", "primary_expr",
  "func_call", "expr_list", "const_exp", "const_init_val",
  "const_init_list", "var_init_val", "$@3", "var_init_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-137)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      63,  -137,  -137,    79,  -137,    19,    63,  -137,  -137,  -137,
    -137,     7,  -137,    20,  -137,  -137,   -25,   -11,  -137,    31,
       6,  -137,    79,    30,  -137,    48,    53,    50,  -137,    20,
      65,    58,    78,  -137,   148,   120,  -137,  -137,   148,    83,
    -137,  -137,   148,    53,   148,   148,  -137,    77,    60,  -137,
    -137,  -137,  -137,  -137,   148,  -137,    92,   101,    79,   116,
    -137,  -137,    77,  -137,  -137,    71,   118,   122,  -137,   -16,
    -137,  -137,   148,   148,   148,   148,   148,   129,   131,  -137,
    -137,  -137,  -137,   120,  -137,  -137,    32,   148,  -137,    53,
    -137,    60,    60,  -137,  -137,  -137,   137,  -137,   126,  -137,
      28,   148,  -137,   145,  -137,    53,   147,   149,   150,   156,
     159,   142,  -137,  -137,    48,  -137,   152,   126,  -137,   146,
     161,   120,  -137,  -137,  -137,  -137,   148,   148,  -137,  -137,
    -137,   162,  -137,  -137,   148,  -137,  -137,   157,   170,   172,
     103,    93,    77,   160,  -137,   167,    15,   148,   148,   148,
     148,   148,   148,   148,   148,  -137,  -137,   186,   172,   103,
      93,    93,    77,    77,    77,    77,    15,    15,  -137,  -137
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    11,    12,     0,    13,     0,     2,     3,     5,     7,
       8,     0,     6,     0,     1,     4,    22,     0,    16,    22,
       0,    14,    25,    20,    10,     0,     0,     0,     9,     0,
       0,     0,    26,    27,     0,     0,    22,    17,     0,    50,
      78,    79,     0,     0,     0,     0,    77,    86,    66,    69,
      73,    81,    87,    19,     0,    15,    29,     0,     0,     0,
      92,    91,    52,    21,    76,     0,    49,     0,    89,     0,
      74,    75,     0,     0,     0,     0,     0,     0,     0,    31,
      24,    28,    23,     0,    82,    84,     0,     0,    80,     0,
      88,    67,    68,    70,    71,    72,    23,    22,    33,    94,
       0,     0,    83,     0,    90,     0,    30,     0,     0,     0,
       0,     0,    39,    35,     0,    40,     0,    33,    36,    77,
       0,     0,    93,    85,    51,    18,     0,     0,    45,    46,
      48,     0,    32,    34,     0,    38,    95,     0,    53,    54,
      56,    58,    61,     0,    47,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    43,    37,    41,    55,    57,
      59,    60,    62,    63,    64,    65,     0,     0,    44,    42
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -137,  -137,  -137,   189,   -77,  -137,  -137,    -2,  -137,  -137,
     168,   171,   -17,  -137,  -137,  -137,   140,   143,  -137,    82,
    -137,  -136,  -137,   -94,  -137,   -30,    74,  -137,    55,    56,
     -10,   -26,    46,   -31,  -137,  -137,  -137,     0,   -40,  -137,
     -74,  -137,  -137
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     5,     6,     7,     8,     9,    10,    11,    20,    17,
      21,    18,    23,    12,    31,    32,    33,   115,    98,   116,
     117,   118,   166,    46,    66,   120,   137,   138,   139,   140,
     141,    62,    48,    49,    50,    51,    86,    52,    53,    69,
      63,    83,   100
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      47,    13,    27,    68,   119,    61,    22,    64,    47,    99,
     157,    89,    67,    70,    71,    24,    25,    47,    90,    14,
      30,   113,   107,   119,   108,   109,   110,   111,    47,    16,
     168,   169,    28,    29,    59,    85,    38,    39,    40,    41,
     113,   112,    19,    93,    94,    95,    42,   136,    79,   104,
      44,    45,   119,    61,    77,   121,    30,   103,    34,   101,
      35,    26,   122,    47,   102,   125,     1,     2,     3,     4,
      36,   123,   119,   119,    38,    39,    40,    41,    54,    47,
     106,   131,     1,     2,    42,     4,    43,    56,    44,    45,
      57,    61,    38,    39,    40,    41,   114,    74,    75,    76,
     142,   142,    42,    84,   145,    58,    44,    45,   151,   152,
     153,   154,    72,    73,    65,   114,   149,   150,    91,    92,
      78,   142,   142,   142,   142,   162,   163,   164,   165,     1,
       2,     3,     4,   107,    79,   108,   109,   110,   111,   160,
     161,    38,    39,    40,    41,    82,    87,    38,    39,    40,
      41,    42,   112,    60,    88,    44,    45,    42,    96,    79,
      97,    44,    45,    38,    39,    40,    41,   105,   130,    38,
      39,    40,    41,    42,   124,    34,   134,    44,    45,    42,
     126,   127,   128,    44,    45,   129,   132,   135,   144,   146,
     147,   148,   155,   156,   167,    15,    37,    55,    81,   133,
      80,   143,   158,     0,   159
};

static const yytype_int16 yycheck[] =
{
      26,     3,    19,    43,    98,    35,    31,    38,    34,    83,
     146,    27,    42,    44,    45,    26,    27,    43,    34,     0,
      22,    98,     7,   117,     9,    10,    11,    12,    54,    22,
     166,   167,    26,    27,    34,    65,    21,    22,    23,    24,
     117,    26,    22,    74,    75,    76,    31,   121,    33,    89,
      35,    36,   146,    83,    54,    27,    58,    87,    28,    27,
      30,    30,    34,    89,    32,   105,     3,     4,     5,     6,
      22,   101,   166,   167,    21,    22,    23,    24,    28,   105,
      97,   111,     3,     4,    31,     6,    33,    22,    35,    36,
      32,   121,    21,    22,    23,    24,    98,    37,    38,    39,
     126,   127,    31,    32,   134,    27,    35,    36,    15,    16,
      17,    18,    35,    36,    31,   117,    13,    14,    72,    73,
      28,   147,   148,   149,   150,   151,   152,   153,   154,     3,
       4,     5,     6,     7,    33,     9,    10,    11,    12,   149,
     150,    21,    22,    23,    24,    29,    28,    21,    22,    23,
      24,    31,    26,    33,    32,    35,    36,    31,    29,    33,
      29,    35,    36,    21,    22,    23,    24,    30,    26,    21,
      22,    23,    24,    31,    29,    28,    30,    35,    36,    31,
      31,    31,    26,    35,    36,    26,    34,    26,    26,    32,
      20,    19,    32,    26,     8,     6,    25,    29,    58,   117,
      57,   127,   147,    -1,   148
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,    41,    42,    43,    44,    45,
      46,    47,    53,    47,     0,    43,    22,    49,    51,    22,
      48,    50,    31,    52,    26,    27,    30,    52,    26,    27,
      47,    54,    55,    56,    28,    30,    22,    51,    21,    22,
      23,    24,    31,    33,    35,    36,    63,    71,    72,    73,
      74,    75,    77,    78,    28,    50,    22,    32,    27,    77,
      33,    65,    71,    80,    73,    31,    64,    65,    78,    79,
      73,    73,    35,    36,    37,    38,    39,    77,    28,    33,
      57,    56,    29,    81,    32,    65,    76,    28,    32,    27,
      34,    72,    72,    73,    73,    73,    29,    29,    58,    80,
      82,    27,    32,    65,    78,    30,    52,     7,     9,    10,
      11,    12,    26,    44,    47,    57,    59,    60,    61,    63,
      65,    27,    34,    65,    29,    78,    31,    31,    26,    26,
      26,    65,    34,    59,    30,    26,    80,    66,    67,    68,
      69,    70,    71,    66,    26,    65,    32,    20,    19,    13,
      14,    15,    16,    17,    18,    32,    26,    61,    68,    69,
      70,    70,    71,    71,    71,    71,    62,     8,    61,    61
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    40,    41,    42,    42,    43,    43,    44,    44,    45,
      46,    47,    47,    47,    48,    48,    49,    49,    50,    50,
      51,    51,    52,    52,    53,    54,    54,    55,    55,    56,
      56,    58,    57,    59,    59,    60,    60,    61,    61,    61,
      61,    61,    61,    62,    61,    61,    61,    61,    61,    63,
      64,    64,    65,    66,    67,    67,    68,    68,    69,    69,
      69,    70,    70,    70,    70,    70,    71,    71,    71,    72,
      72,    72,    72,    73,    73,    73,    73,    74,    74,    74,
      74,    74,    75,    75,    76,    76,    77,    78,    78,    79,
      79,    80,    81,    80,    82,    82
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     4,
       3,     1,     1,     1,     1,     3,     1,     3,     7,     3,
       2,     4,     0,     4,     6,     0,     1,     1,     3,     2,
       5,     0,     4,     0,     2,     1,     1,     4,     2,     1,
       1,     5,     7,     0,     6,     2,     2,     3,     2,     2,
       0,     4,     1,     1,     1,     3,     1,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     1,     3,     3,     1,
       3,     3,     3,     1,     2,     2,     2,     1,     1,     1,
       3,     1,     3,     4,     1,     3,     1,     1,     3,     1,
       3,     1,     0,     4,     1,     3
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
  case 2: /* comp_unit: decl_or_func_list  */
#line 70 "src/frontend/sysy.y"
                             { 
    end_parser();
}
#line 1292 "src/frontend/sysy.y.cpp"
    break;

  case 3: /* decl_or_func_list: decl_or_func  */
#line 76 "src/frontend/sysy.y"
    {   module_list->InsertHead((yyvsp[0].llvm)); }
#line 1298 "src/frontend/sysy.y.cpp"
    break;

  case 4: /* decl_or_func_list: decl_or_func_list decl_or_func  */
#line 78 "src/frontend/sysy.y"
    {   module_list->InsertTail((yyvsp[0].llvm)); }
#line 1304 "src/frontend/sysy.y.cpp"
    break;

  case 5: /* decl_or_func: decl  */
#line 82 "src/frontend/sysy.y"
    { (yyval.llvm) = (yyvsp[0].llvm); }
#line 1310 "src/frontend/sysy.y.cpp"
    break;

  case 6: /* decl_or_func: func_def  */
#line 84 "src/frontend/sysy.y"
    { (yyval.llvm) = (yyvsp[0].llvm); }
#line 1316 "src/frontend/sysy.y.cpp"
    break;

  case 7: /* decl: const_decl  */
#line 88 "src/frontend/sysy.y"
    { (yyval.llvm) = (yyvsp[0].llvm); }
#line 1322 "src/frontend/sysy.y.cpp"
    break;

  case 8: /* decl: var_decl  */
#line 90 "src/frontend/sysy.y"
    { (yyval.llvm) = (yyvsp[0].llvm); }
#line 1328 "src/frontend/sysy.y.cpp"
    break;

  case 9: /* const_decl: CONST btype const_def_list ';'  */
#line 94 "src/frontend/sysy.y"
    { 
        if((yyvsp[-2].dtype)==VOID_TYPE)
            throw std::runtime_error("the variable is not allowed to be a void type");
        (yyval.llvm) = create_const_decl((yyvsp[-2].dtype), (yyvsp[-1].sym_vector)); 
    }
#line 1338 "src/frontend/sysy.y.cpp"
    break;

  case 10: /* var_decl: btype var_def_list ';'  */
#line 102 "src/frontend/sysy.y"
    { 
        if((yyvsp[-2].dtype)==VOID_TYPE)
            throw std::runtime_error("the variable is not allowed to be a void type");
        (yyval.llvm) = create_var_decl((yyvsp[-2].dtype), (yyvsp[-1].sym_vector)); 
    }
#line 1348 "src/frontend/sysy.y.cpp"
    break;

  case 11: /* btype: INT  */
#line 110 "src/frontend/sysy.y"
    { (yyval.dtype) = INT_TYPE; }
#line 1354 "src/frontend/sysy.y.cpp"
    break;

  case 12: /* btype: FLOAT  */
#line 112 "src/frontend/sysy.y"
    { (yyval.dtype) = FLOAT_TYPE; }
#line 1360 "src/frontend/sysy.y.cpp"
    break;

  case 13: /* btype: VOID  */
#line 114 "src/frontend/sysy.y"
    { (yyval.dtype) = VOID_TYPE;}
#line 1366 "src/frontend/sysy.y.cpp"
    break;

  case 14: /* const_def_list: const_def  */
#line 117 "src/frontend/sysy.y"
                          {
        std::vector<Symbol*>* syms=new std::vector<Symbol*>(0);
        syms->push_back((yyvsp[0].sym));
        (yyval.sym_vector)=syms;
    }
#line 1376 "src/frontend/sysy.y.cpp"
    break;

  case 15: /* const_def_list: const_def_list ',' const_def  */
#line 122 "src/frontend/sysy.y"
                                  { 
        (yyvsp[-2].sym_vector)->push_back((yyvsp[0].sym));
        (yyval.sym_vector) = (yyvsp[-2].sym_vector);
    }
#line 1385 "src/frontend/sysy.y.cpp"
    break;

  case 16: /* var_def_list: var_def  */
#line 128 "src/frontend/sysy.y"
                      {
        std::vector<Symbol*>* syms=new std::vector<Symbol*>(0);
        syms->push_back((yyvsp[0].sym));
        (yyval.sym_vector)=syms;
    }
#line 1395 "src/frontend/sysy.y.cpp"
    break;

  case 17: /* var_def_list: var_def_list ',' var_def  */
#line 133 "src/frontend/sysy.y"
                              { 
        (yyvsp[-2].sym_vector)->push_back((yyvsp[0].sym));
        (yyval.sym_vector) = (yyvsp[-2].sym_vector);
    }
#line 1404 "src/frontend/sysy.y.cpp"
    break;

  case 18: /* const_def: IDENTIFIER dim_list '[' const_exp ']' '=' const_init_val  */
#line 140 "src/frontend/sysy.y"
    {   (yyval.sym) = create_array_const_def(*((yyvsp[-6].str)), (yyvsp[-5].int_vector), (yyvsp[-3].exp), dynamic_cast<ArrayInitial*>((yyvsp[0].exp)->sym->data)); }
#line 1410 "src/frontend/sysy.y.cpp"
    break;

  case 19: /* const_def: IDENTIFIER '=' const_init_val  */
#line 141 "src/frontend/sysy.y"
                                   {
      (yyval.sym) = create_const_def(*((yyvsp[-2].str)), (yyvsp[0].exp)); 
    }
#line 1418 "src/frontend/sysy.y.cpp"
    break;

  case 20: /* var_def: IDENTIFIER dim_list  */
#line 146 "src/frontend/sysy.y"
                             { 
        (yyval.sym) = create_var_def(*((yyvsp[-1].str)), (yyvsp[0].int_vector)); 
    }
#line 1426 "src/frontend/sysy.y.cpp"
    break;

  case 21: /* var_def: IDENTIFIER dim_list '=' var_init_val  */
#line 149 "src/frontend/sysy.y"
                                          { 
        (yyval.sym) = create_var_def(*((yyvsp[-3].str)), (yyvsp[-2].int_vector), (yyvsp[0].exp)); 
    }
#line 1434 "src/frontend/sysy.y.cpp"
    break;

  case 22: /* dim_list: %empty  */
#line 155 "src/frontend/sysy.y"
    { (yyval.int_vector) = new std::vector<int>(0); }
#line 1440 "src/frontend/sysy.y.cpp"
    break;

  case 23: /* dim_list: dim_list '[' const_exp ']'  */
#line 156 "src/frontend/sysy.y"
                                {  
        (yyval.int_vector) = (yyvsp[-3].int_vector);
        ConstSymbol* constSym=dynamic_cast<ConstSymbol*>((yyvsp[-1].exp)->sym);
        (yyval.int_vector)->push_back(std::get<int>(constSym->data->getValue()));
    }
#line 1450 "src/frontend/sysy.y.cpp"
    break;

  case 24: /* func_def: btype IDENTIFIER '(' func_params ')' block  */
#line 164 "src/frontend/sysy.y"
    {
        scope=GLOBAL_SCOPE;
        (yyval.llvm) = create_func_def((yyvsp[-5].dtype), *((yyvsp[-4].str)), (yyvsp[-2].sym_vector), (yyvsp[0].llvm));
    }
#line 1459 "src/frontend/sysy.y.cpp"
    break;

  case 25: /* func_params: %empty  */
#line 171 "src/frontend/sysy.y"
    {   (yyval.sym_vector)=new std::vector<Symbol*>(0); }
#line 1465 "src/frontend/sysy.y.cpp"
    break;

  case 26: /* func_params: func_param_list  */
#line 172 "src/frontend/sysy.y"
                     {   
        (yyval.sym_vector)=(yyvsp[0].sym_vector);  
    }
#line 1473 "src/frontend/sysy.y.cpp"
    break;

  case 27: /* func_param_list: func_param  */
#line 177 "src/frontend/sysy.y"
                            { 
        (yyval.sym_vector)=new std::vector<Symbol*>(0);
        (yyval.sym_vector)->push_back((yyvsp[0].sym));
    }
#line 1482 "src/frontend/sysy.y.cpp"
    break;

  case 28: /* func_param_list: func_param_list ',' func_param  */
#line 181 "src/frontend/sysy.y"
                                    {
        (yyval.sym_vector) = (yyvsp[-2].sym_vector);
        (yyval.sym_vector)->push_back((yyvsp[0].sym));
    }
#line 1491 "src/frontend/sysy.y.cpp"
    break;

  case 29: /* func_param: btype IDENTIFIER  */
#line 188 "src/frontend/sysy.y"
    { 
        if((yyvsp[0].str)==VOID_TYPE)
            throw std::runtime_error("the variable is not allowed to be a void type");
        (yyval.sym) = create_param_nonarray((yyvsp[-1].dtype),*((yyvsp[0].str))); 
    }
#line 1501 "src/frontend/sysy.y.cpp"
    break;

  case 30: /* func_param: btype IDENTIFIER '[' ']' dim_list  */
#line 194 "src/frontend/sysy.y"
    { 
        if((yyvsp[-3].str)==VOID_TYPE)
            throw std::runtime_error("the variable is not allowed to be a void type");
        (yyval.sym) = create_param_array((yyvsp[-4].dtype),*((yyvsp[-3].str)),(yyvsp[0].int_vector));
    }
#line 1511 "src/frontend/sysy.y.cpp"
    break;

  case 31: /* $@1: %empty  */
#line 202 "src/frontend/sysy.y"
    {
        scope+=1;
        variable_table.push_back(std::unordered_map<std::string,Symbol*>());
    }
#line 1520 "src/frontend/sysy.y.cpp"
    break;

  case 32: /* block: '{' $@1 block_items '}'  */
#line 206 "src/frontend/sysy.y"
                   { 
        (yyval.llvm)=(yyvsp[-1].llvm);
        scope-=1;
        variable_table.pop_back();
    }
#line 1530 "src/frontend/sysy.y.cpp"
    break;

  case 33: /* block_items: %empty  */
#line 214 "src/frontend/sysy.y"
    {   (yyval.llvm)=new LLVMList();}
#line 1536 "src/frontend/sysy.y.cpp"
    break;

  case 34: /* block_items: block_item block_items  */
#line 215 "src/frontend/sysy.y"
                            {  
        (yyval.llvm)=(yyvsp[0].llvm);
        (yyval.llvm)->InsertHead((yyvsp[-1].llvm));
    }
#line 1545 "src/frontend/sysy.y.cpp"
    break;

  case 35: /* block_item: decl  */
#line 222 "src/frontend/sysy.y"
    {   (yyval.llvm) = (yyvsp[0].llvm); }
#line 1551 "src/frontend/sysy.y.cpp"
    break;

  case 36: /* block_item: stmt  */
#line 224 "src/frontend/sysy.y"
    {   (yyval.llvm) = (yyvsp[0].llvm); }
#line 1557 "src/frontend/sysy.y.cpp"
    break;

  case 37: /* stmt: LVal '=' expr ';'  */
#line 228 "src/frontend/sysy.y"
    {   (yyval.llvm)=assign_array_item((yyvsp[-3].exp),(yyvsp[-1].exp));}
#line 1563 "src/frontend/sysy.y.cpp"
    break;

  case 38: /* stmt: expr ';'  */
#line 230 "src/frontend/sysy.y"
    {   (yyval.llvm)=(yyvsp[-1].exp)->llvmlist;}
#line 1569 "src/frontend/sysy.y.cpp"
    break;

  case 39: /* stmt: ';'  */
#line 232 "src/frontend/sysy.y"
    {   (yyval.llvm)=new LLVMList();}
#line 1575 "src/frontend/sysy.y.cpp"
    break;

  case 40: /* stmt: block  */
#line 234 "src/frontend/sysy.y"
    {   (yyval.llvm)=(yyvsp[0].llvm); }
#line 1581 "src/frontend/sysy.y.cpp"
    break;

  case 41: /* stmt: IF '(' cond ')' stmt  */
#line 236 "src/frontend/sysy.y"
    { (yyval.llvm) = create_if_stmt((yyvsp[-2].exp), (yyvsp[0].llvm)); }
#line 1587 "src/frontend/sysy.y.cpp"
    break;

  case 42: /* stmt: IF '(' cond ')' stmt ELSE stmt  */
#line 238 "src/frontend/sysy.y"
    { (yyval.llvm) = create_if_else_stmt((yyvsp[-4].exp), (yyvsp[-2].llvm), (yyvsp[0].llvm)); }
#line 1593 "src/frontend/sysy.y.cpp"
    break;

  case 43: /* @2: %empty  */
#line 240 "src/frontend/sysy.y"
    { (yyval.llvm) = create_while((yyvsp[-1].exp)); }
#line 1599 "src/frontend/sysy.y.cpp"
    break;

  case 44: /* stmt: WHILE '(' cond ')' @2 stmt  */
#line 242 "src/frontend/sysy.y"
    { (yyval.llvm) = create_while_stmt((yyvsp[-1].llvm),(yyvsp[0].llvm));}
#line 1605 "src/frontend/sysy.y.cpp"
    break;

  case 45: /* stmt: BREAK ';'  */
#line 244 "src/frontend/sysy.y"
    { (yyval.llvm) = create_break_stmt();}
#line 1611 "src/frontend/sysy.y.cpp"
    break;

  case 46: /* stmt: CONTINUE ';'  */
#line 246 "src/frontend/sysy.y"
    { (yyval.llvm) = create_continue_stmt();}
#line 1617 "src/frontend/sysy.y.cpp"
    break;

  case 47: /* stmt: RETURN expr ';'  */
#line 248 "src/frontend/sysy.y"
    { (yyval.llvm) = create_return_stmt((yyvsp[-1].exp)); }
#line 1623 "src/frontend/sysy.y.cpp"
    break;

  case 48: /* stmt: RETURN ';'  */
#line 250 "src/frontend/sysy.y"
    { (yyval.llvm) = create_return_stmt(nullptr); }
#line 1629 "src/frontend/sysy.y.cpp"
    break;

  case 49: /* LVal: IDENTIFIER index_list  */
#line 253 "src/frontend/sysy.y"
                            {
    (yyval.exp)=get_element(*((yyvsp[-1].str)),(yyvsp[0].exp_vector));
}
#line 1637 "src/frontend/sysy.y.cpp"
    break;

  case 50: /* index_list: %empty  */
#line 259 "src/frontend/sysy.y"
    {   (yyval.exp_vector)=new std::vector<Expression*>(0); }
#line 1643 "src/frontend/sysy.y.cpp"
    break;

  case 51: /* index_list: index_list '[' expr ']'  */
#line 260 "src/frontend/sysy.y"
                            {   
        (yyval.exp_vector)=(yyvsp[-3].exp_vector);
        (yyval.exp_vector)->push_back((yyvsp[-1].exp));
    }
#line 1652 "src/frontend/sysy.y.cpp"
    break;

  case 52: /* expr: add_expr  */
#line 268 "src/frontend/sysy.y"
    { (yyval.exp) = (yyvsp[0].exp); }
#line 1658 "src/frontend/sysy.y.cpp"
    break;

  case 53: /* cond: or_expr  */
#line 272 "src/frontend/sysy.y"
    { (yyval.exp) = (yyvsp[0].exp);}
#line 1664 "src/frontend/sysy.y.cpp"
    break;

  case 54: /* or_expr: and_expr  */
#line 276 "src/frontend/sysy.y"
    {   (yyval.exp) = (yyvsp[0].exp);  }
#line 1670 "src/frontend/sysy.y.cpp"
    break;

  case 55: /* or_expr: or_expr OR and_expr  */
#line 278 "src/frontend/sysy.y"
    { (yyval.exp) = create_binary_expr(BINARY_OR, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1676 "src/frontend/sysy.y.cpp"
    break;

  case 57: /* and_expr: and_expr AND eq_expr  */
#line 283 "src/frontend/sysy.y"
    { (yyval.exp) = create_binary_expr(BINARY_AND, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1682 "src/frontend/sysy.y.cpp"
    break;

  case 59: /* eq_expr: eq_expr EQ rel_expr  */
#line 288 "src/frontend/sysy.y"
    { (yyval.exp) = create_binary_expr(BINARY_EQ, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1688 "src/frontend/sysy.y.cpp"
    break;

  case 60: /* eq_expr: eq_expr NE rel_expr  */
#line 290 "src/frontend/sysy.y"
    { (yyval.exp) = create_binary_expr(BINARY_NE, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1694 "src/frontend/sysy.y.cpp"
    break;

  case 62: /* rel_expr: rel_expr LT add_expr  */
#line 295 "src/frontend/sysy.y"
    { (yyval.exp) = create_binary_expr(BINARY_LT, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1700 "src/frontend/sysy.y.cpp"
    break;

  case 63: /* rel_expr: rel_expr GT add_expr  */
#line 297 "src/frontend/sysy.y"
    { (yyval.exp) = create_binary_expr(BINARY_GT, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1706 "src/frontend/sysy.y.cpp"
    break;

  case 64: /* rel_expr: rel_expr LE add_expr  */
#line 299 "src/frontend/sysy.y"
    { (yyval.exp) = create_binary_expr(BINARY_LE, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1712 "src/frontend/sysy.y.cpp"
    break;

  case 65: /* rel_expr: rel_expr GE add_expr  */
#line 301 "src/frontend/sysy.y"
    { (yyval.exp) = create_binary_expr(BINARY_GE, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1718 "src/frontend/sysy.y.cpp"
    break;

  case 67: /* add_expr: add_expr '+' mul_expr  */
#line 306 "src/frontend/sysy.y"
    { (yyval.exp) = create_binary_expr(BINARY_ADD, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1724 "src/frontend/sysy.y.cpp"
    break;

  case 68: /* add_expr: add_expr '-' mul_expr  */
#line 308 "src/frontend/sysy.y"
    { (yyval.exp) = create_binary_expr(BINARY_SUB, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1730 "src/frontend/sysy.y.cpp"
    break;

  case 70: /* mul_expr: mul_expr '*' unary_expr  */
#line 313 "src/frontend/sysy.y"
    { (yyval.exp) = create_binary_expr(BINARY_MUL, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1736 "src/frontend/sysy.y.cpp"
    break;

  case 71: /* mul_expr: mul_expr '/' unary_expr  */
#line 315 "src/frontend/sysy.y"
    { (yyval.exp) = create_binary_expr(BINARY_DIV, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1742 "src/frontend/sysy.y.cpp"
    break;

  case 72: /* mul_expr: mul_expr '%' unary_expr  */
#line 317 "src/frontend/sysy.y"
    { (yyval.exp) = create_binary_expr(BINARY_REM, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1748 "src/frontend/sysy.y.cpp"
    break;

  case 73: /* unary_expr: primary_expr  */
#line 321 "src/frontend/sysy.y"
    { (yyval.exp) = (yyvsp[0].exp); }
#line 1754 "src/frontend/sysy.y.cpp"
    break;

  case 74: /* unary_expr: '+' unary_expr  */
#line 323 "src/frontend/sysy.y"
    { (yyval.exp) = create_unary_expr(SINGLE_POSITIVE, (yyvsp[0].exp)); }
#line 1760 "src/frontend/sysy.y.cpp"
    break;

  case 75: /* unary_expr: '-' unary_expr  */
#line 325 "src/frontend/sysy.y"
    { (yyval.exp) = create_unary_expr(SINGLE_NEGTIVE, (yyvsp[0].exp)); }
#line 1766 "src/frontend/sysy.y.cpp"
    break;

  case 76: /* unary_expr: NOT unary_expr  */
#line 327 "src/frontend/sysy.y"
    { (yyval.exp) = create_unary_expr(SINGLE_NOT, (yyvsp[0].exp)); }
#line 1772 "src/frontend/sysy.y.cpp"
    break;

  case 77: /* primary_expr: LVal  */
#line 331 "src/frontend/sysy.y"
    { (yyval.exp) = (yyvsp[0].exp);}
#line 1778 "src/frontend/sysy.y.cpp"
    break;

  case 78: /* primary_expr: INT_CONST  */
#line 333 "src/frontend/sysy.y"
    { (yyval.exp) = create_primary_INTCONST(stoi(*((yyvsp[0].str))));  }
#line 1784 "src/frontend/sysy.y.cpp"
    break;

  case 79: /* primary_expr: FLOAT_CONST  */
#line 335 "src/frontend/sysy.y"
    { (yyval.exp) = create_primary_FLOATCONST(stof(*((yyvsp[0].str))));  }
#line 1790 "src/frontend/sysy.y.cpp"
    break;

  case 80: /* primary_expr: '(' expr ')'  */
#line 337 "src/frontend/sysy.y"
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 1796 "src/frontend/sysy.y.cpp"
    break;

  case 81: /* primary_expr: func_call  */
#line 339 "src/frontend/sysy.y"
    { (yyval.exp) = (yyvsp[0].exp); }
#line 1802 "src/frontend/sysy.y.cpp"
    break;

  case 82: /* func_call: IDENTIFIER '(' ')'  */
#line 343 "src/frontend/sysy.y"
    { (yyval.exp) = create_func_call(*((yyvsp[-2].str)),nullptr); }
#line 1808 "src/frontend/sysy.y.cpp"
    break;

  case 83: /* func_call: IDENTIFIER '(' expr_list ')'  */
#line 345 "src/frontend/sysy.y"
    { (yyval.exp) = create_func_call(*((yyvsp[-3].str)), (yyvsp[-1].exp)); }
#line 1814 "src/frontend/sysy.y.cpp"
    break;

  case 84: /* expr_list: expr  */
#line 349 "src/frontend/sysy.y"
    {   (yyval.exp) = (yyvsp[0].exp); }
#line 1820 "src/frontend/sysy.y.cpp"
    break;

  case 85: /* expr_list: expr_list ',' expr  */
#line 350 "src/frontend/sysy.y"
                        {   
        (yyval.exp) = (yyvsp[-2].exp); 
        (yyval.exp)->next=(yyvsp[0].exp);
    }
#line 1829 "src/frontend/sysy.y.cpp"
    break;

  case 86: /* const_exp: add_expr  */
#line 357 "src/frontend/sysy.y"
    { (yyval.exp) = (yyvsp[0].exp); }
#line 1835 "src/frontend/sysy.y.cpp"
    break;

  case 87: /* const_init_val: const_exp  */
#line 361 "src/frontend/sysy.y"
    {   
        (yyval.exp)=(yyvsp[0].exp);
    }
#line 1843 "src/frontend/sysy.y.cpp"
    break;

  case 88: /* const_init_val: '{' const_init_list '}'  */
#line 364 "src/frontend/sysy.y"
                             {
        (yyval.exp) = (yyvsp[-1].exp); 
    }
#line 1851 "src/frontend/sysy.y.cpp"
    break;

  case 89: /* const_init_list: const_init_val  */
#line 369 "src/frontend/sysy.y"
                                {   
        (yyval.exp) = (yyvsp[0].exp);
        create_var_init_list((yyval.exp));
    }
#line 1860 "src/frontend/sysy.y.cpp"
    break;

  case 90: /* const_init_list: const_init_list ',' const_init_val  */
#line 373 "src/frontend/sysy.y"
                                        {
        (yyval.exp) = (yyvsp[-2].exp);
        create_var_init_list((yyval.exp),(yyvsp[0].exp));
    }
#line 1869 "src/frontend/sysy.y.cpp"
    break;

  case 91: /* var_init_val: expr  */
#line 380 "src/frontend/sysy.y"
    {   
        (yyval.exp)=(yyvsp[0].exp);
    }
#line 1877 "src/frontend/sysy.y.cpp"
    break;

  case 92: /* $@3: %empty  */
#line 384 "src/frontend/sysy.y"
    {
        array_initial.push(array_init_idx);
    }
#line 1885 "src/frontend/sysy.y.cpp"
    break;

  case 93: /* var_init_val: '{' $@3 var_init_list '}'  */
#line 387 "src/frontend/sysy.y"
                     {
        reduce_var_init_list((yyvsp[-1].exp));
        (yyval.exp)=(yyvsp[-1].exp);
    }
#line 1894 "src/frontend/sysy.y.cpp"
    break;

  case 94: /* var_init_list: var_init_val  */
#line 393 "src/frontend/sysy.y"
                            {   
        (yyval.exp) = (yyvsp[0].exp);
        create_var_init_list((yyval.exp));
    }
#line 1903 "src/frontend/sysy.y.cpp"
    break;

  case 95: /* var_init_list: var_init_list ',' var_init_val  */
#line 397 "src/frontend/sysy.y"
                                    {
        (yyval.exp) = (yyvsp[-2].exp);
        create_var_init_list((yyval.exp),(yyvsp[0].exp));
    }
#line 1912 "src/frontend/sysy.y.cpp"
    break;


#line 1916 "src/frontend/sysy.y.cpp"

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

#line 403 "src/frontend/sysy.y"


void yyerror(const char *s) {
    fprintf(stderr, "Error: %s at line %d\n", s, yylineno);
    exit(1);
}
