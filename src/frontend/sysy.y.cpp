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
extern std::vector<int>dim_array;
extern int yylex(void);
extern int yylineno;
extern ModuleList* module_list;
extern int scope;
extern std::vector<std::unordered_map<std::string,int>> variable_rename_table;
extern std::vector<std::unordered_map<std::string,Symbol*>> variable_table;
extern std::stack<int>array_initial;
extern std::vector<int> array_init_idx;

#line 99 "src/frontend/sysy.y.cpp"

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
  YYSYMBOL_25_ = 25,                       /* '+'  */
  YYSYMBOL_26_ = 26,                       /* '-'  */
  YYSYMBOL_27_ = 27,                       /* '*'  */
  YYSYMBOL_28_ = 28,                       /* '/'  */
  YYSYMBOL_29_ = 29,                       /* '%'  */
  YYSYMBOL_IFX = 30,                       /* IFX  */
  YYSYMBOL_31_ = 31,                       /* ';'  */
  YYSYMBOL_32_ = 32,                       /* ','  */
  YYSYMBOL_33_ = 33,                       /* '['  */
  YYSYMBOL_34_ = 34,                       /* ']'  */
  YYSYMBOL_35_ = 35,                       /* '='  */
  YYSYMBOL_36_ = 36,                       /* '('  */
  YYSYMBOL_37_ = 37,                       /* ')'  */
  YYSYMBOL_38_ = 38,                       /* '{'  */
  YYSYMBOL_39_ = 39,                       /* '}'  */
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
  YYSYMBOL_51_1 = 51,                      /* $@1  */
  YYSYMBOL_var_def = 52,                   /* var_def  */
  YYSYMBOL_53_2 = 53,                      /* $@2  */
  YYSYMBOL_dim_list = 54,                  /* dim_list  */
  YYSYMBOL_func_def = 55,                  /* func_def  */
  YYSYMBOL_56_3 = 56,                      /* @3  */
  YYSYMBOL_func_params = 57,               /* func_params  */
  YYSYMBOL_func_param_list = 58,           /* func_param_list  */
  YYSYMBOL_func_param = 59,                /* func_param  */
  YYSYMBOL_block = 60,                     /* block  */
  YYSYMBOL_61_4 = 61,                      /* @4  */
  YYSYMBOL_block_items = 62,               /* block_items  */
  YYSYMBOL_block_item = 63,                /* block_item  */
  YYSYMBOL_stmt = 64,                      /* stmt  */
  YYSYMBOL_65_5 = 65,                      /* @5  */
  YYSYMBOL_LVal = 66,                      /* LVal  */
  YYSYMBOL_index_list = 67,                /* index_list  */
  YYSYMBOL_expr = 68,                      /* expr  */
  YYSYMBOL_cond = 69,                      /* cond  */
  YYSYMBOL_or_expr = 70,                   /* or_expr  */
  YYSYMBOL_and_expr = 71,                  /* and_expr  */
  YYSYMBOL_eq_expr = 72,                   /* eq_expr  */
  YYSYMBOL_rel_expr = 73,                  /* rel_expr  */
  YYSYMBOL_add_expr = 74,                  /* add_expr  */
  YYSYMBOL_mul_expr = 75,                  /* mul_expr  */
  YYSYMBOL_unary_expr = 76,                /* unary_expr  */
  YYSYMBOL_primary_expr = 77,              /* primary_expr  */
  YYSYMBOL_func_call = 78,                 /* func_call  */
  YYSYMBOL_expr_list = 79,                 /* expr_list  */
  YYSYMBOL_const_exp = 80,                 /* const_exp  */
  YYSYMBOL_const_init_val = 81,            /* const_init_val  */
  YYSYMBOL_82_6 = 82,                      /* $@6  */
  YYSYMBOL_const_init_list = 83,           /* const_init_list  */
  YYSYMBOL_var_init_val = 84,              /* var_init_val  */
  YYSYMBOL_85_7 = 85,                      /* $@7  */
  YYSYMBOL_var_init_list = 86              /* var_init_list  */
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
#define YYLAST   205

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  47
/* YYNRULES -- Number of rules.  */
#define YYNRULES  101
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  174

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
       2,     2,     2,     2,     2,     2,     2,    29,     2,     2,
      36,    37,    27,    25,    32,    26,     2,    28,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    31,
       2,    35,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    33,     2,    34,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    38,     2,    39,     2,     2,     2,     2,
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
      30
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    78,    78,    83,    85,    89,    91,    95,    97,   101,
     109,   117,   119,   121,   125,   130,   136,   141,   148,   147,
     153,   158,   162,   161,   171,   172,   184,   183,   198,   199,
     204,   208,   214,   220,   229,   228,   246,   247,   253,   255,
     259,   261,   263,   265,   267,   269,   272,   271,   275,   277,
     279,   281,   285,   291,   292,   299,   303,   307,   309,   313,
     315,   319,   321,   323,   327,   329,   331,   333,   335,   339,
     341,   343,   347,   349,   351,   353,   357,   359,   361,   363,
     367,   369,   371,   373,   375,   379,   381,   385,   387,   396,
     401,   402,   407,   406,   416,   420,   427,   428,   433,   432,
     442,   446
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
  "INT_CONST", "FLOAT_CONST", "'+'", "'-'", "'*'", "'/'", "'%'", "IFX",
  "';'", "','", "'['", "']'", "'='", "'('", "')'", "'{'", "'}'", "$accept",
  "comp_unit", "decl_or_func_list", "decl_or_func", "decl", "const_decl",
  "var_decl", "btype", "const_def_list", "var_def_list", "const_def",
  "$@1", "var_def", "$@2", "dim_list", "func_def", "@3", "func_params",
  "func_param_list", "func_param", "block", "@4", "block_items",
  "block_item", "stmt", "@5", "LVal", "index_list", "expr", "cond",
  "or_expr", "and_expr", "eq_expr", "rel_expr", "add_expr", "mul_expr",
  "unary_expr", "primary_expr", "func_call", "expr_list", "const_exp",
  "const_init_val", "$@6", "const_init_list", "var_init_val", "$@7",
  "var_init_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-142)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-26)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      67,  -142,  -142,    34,  -142,    10,    67,  -142,  -142,  -142,
    -142,    11,  -142,    19,  -142,  -142,   -19,    88,  -142,    12,
     112,  -142,    34,   -10,  -142,    44,    29,    51,  -142,    19,
      72,    64,    81,  -142,    38,    83,  -142,  -142,    38,    85,
    -142,  -142,    38,    38,    38,  -142,  -142,   -12,    87,  -142,
    -142,  -142,  -142,  -142,    38,  -142,    91,  -142,    34,   104,
      57,  -142,    66,   124,  -142,  -142,   121,   -12,    29,    38,
      38,    38,    38,    38,   125,   133,   131,  -142,  -142,  -142,
    -142,  -142,  -142,  -142,    -1,    38,  -142,  -142,   -13,    87,
      87,  -142,  -142,  -142,   137,  -142,  -142,  -142,    57,    38,
    -142,   138,    29,  -142,   136,   140,   130,  -142,    -5,  -142,
    -142,  -142,    29,   144,   145,   151,   152,    86,  -142,  -142,
      44,  -142,   146,   130,  -142,   155,   156,    57,  -142,  -142,
      38,    38,  -142,  -142,  -142,   157,  -142,  -142,    38,  -142,
    -142,   149,   172,   174,   132,    82,   -12,   158,  -142,   163,
     153,    38,    38,    38,    38,    38,    38,    38,    38,  -142,
    -142,   188,   174,   132,    82,    82,   -12,   -12,   -12,   -12,
     153,   153,  -142,  -142
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    11,    12,     0,    13,     0,     2,     3,     5,     7,
       8,     0,     6,     0,     1,     4,    24,     0,    16,    24,
       0,    14,    28,    21,    10,     0,    90,     0,     9,     0,
       0,     0,    29,    30,     0,     0,    24,    17,     0,    53,
      81,    82,     0,     0,     0,    92,    80,    89,    69,    72,
      76,    84,    91,    20,     0,    15,    32,    26,     0,     0,
      96,    79,     0,    52,    77,    78,     0,    55,    90,     0,
       0,     0,     0,     0,     0,     0,     0,    31,    25,    98,
      97,    23,    85,    87,     0,     0,    83,    94,     0,    70,
      71,    73,    74,    75,    18,    24,    34,    27,    96,     0,
      86,     0,    90,    93,     0,    33,    36,   100,     0,    88,
      54,    95,    90,     0,     0,     0,     0,     0,    42,    38,
       0,    43,     0,    36,    39,    80,     0,    96,    99,    19,
       0,     0,    48,    49,    51,     0,    35,    37,     0,    41,
     101,     0,    56,    57,    59,    61,    64,     0,    50,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    46,
      40,    44,    58,    60,    62,    63,    65,    66,    67,    68,
       0,     0,    47,    45
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -142,  -142,  -142,   191,   -99,  -142,  -142,     0,  -142,  -142,
     169,  -142,   175,  -142,   -18,  -142,  -142,  -142,  -142,   141,
     126,  -142,    78,  -142,  -141,  -142,  -102,  -142,   -42,    73,
    -142,    52,    53,    -6,   -26,    80,   -27,  -142,  -142,  -142,
     -22,   -63,  -142,  -142,   -92,  -142,  -142
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     5,     6,     7,     8,     9,    10,    11,    20,    17,
      21,   104,    18,    35,    23,    12,    76,    31,    32,    33,
     121,   106,   122,   123,   124,   170,    46,    63,   126,   141,
     142,   143,   144,   145,    67,    48,    49,    50,    51,    84,
      52,    53,    68,    88,    81,    98,   108
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      47,    27,    66,    13,   125,    87,   107,   119,    47,   161,
      14,    61,    59,    69,    70,    64,    65,    22,    80,   102,
      83,   125,    30,    34,   119,   -22,   103,   127,    47,   172,
     173,    99,    74,    16,   128,   140,   100,     1,     2,   111,
       4,    19,    47,   101,    91,    92,    93,    26,   125,   129,
      38,    39,    40,    41,    42,    43,    80,   109,    30,    38,
      39,    40,    41,    42,    43,    44,    36,    45,   125,   125,
       1,     2,     3,     4,    44,   135,    47,   105,    38,    39,
      40,    41,    42,    43,    54,    80,    47,    38,    39,    40,
      41,    42,    43,    44,    56,    79,   149,   155,   156,   157,
     158,    57,    44,    82,   146,   146,   120,    38,    39,    40,
      41,    42,    43,    58,    71,    72,    73,   134,    60,    24,
      25,    62,    44,   120,    75,   146,   146,   146,   146,   166,
     167,   168,   169,     1,     2,     3,     4,   113,    78,   114,
     115,   116,   117,    28,    29,   153,   154,   164,   165,    89,
      90,    38,    39,    40,    41,    42,    43,    85,    86,    94,
     113,   118,   114,   115,   116,   117,    44,    95,    96,    96,
     -25,   112,   110,    34,    38,    39,    40,    41,    42,    43,
     130,   131,   132,   133,   118,   136,   150,   139,   148,    44,
     138,    96,   151,   152,   160,   159,   171,    15,    55,    77,
      37,   137,    97,   162,   147,   163
};

static const yytype_uint8 yycheck[] =
{
      26,    19,    44,     3,   106,    68,    98,   106,    34,   150,
       0,    38,    34,    25,    26,    42,    43,    36,    60,    32,
      62,   123,    22,    33,   123,    35,    39,    32,    54,   170,
     171,    32,    54,    22,    39,   127,    37,     3,     4,   102,
       6,    22,    68,    85,    71,    72,    73,    35,   150,   112,
      21,    22,    23,    24,    25,    26,    98,    99,    58,    21,
      22,    23,    24,    25,    26,    36,    22,    38,   170,   171,
       3,     4,     5,     6,    36,   117,   102,    95,    21,    22,
      23,    24,    25,    26,    33,   127,   112,    21,    22,    23,
      24,    25,    26,    36,    22,    38,   138,    15,    16,    17,
      18,    37,    36,    37,   130,   131,   106,    21,    22,    23,
      24,    25,    26,    32,    27,    28,    29,    31,    35,    31,
      32,    36,    36,   123,    33,   151,   152,   153,   154,   155,
     156,   157,   158,     3,     4,     5,     6,     7,    34,     9,
      10,    11,    12,    31,    32,    13,    14,   153,   154,    69,
      70,    21,    22,    23,    24,    25,    26,    33,    37,    34,
       7,    31,     9,    10,    11,    12,    36,    34,    38,    38,
      33,    35,    34,    33,    21,    22,    23,    24,    25,    26,
      36,    36,    31,    31,    31,    39,    37,    31,    31,    36,
      35,    38,    20,    19,    31,    37,     8,     6,    29,    58,
      25,   123,    76,   151,   131,   152
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,    41,    42,    43,    44,    45,
      46,    47,    55,    47,     0,    43,    22,    49,    52,    22,
      48,    50,    36,    54,    31,    32,    35,    54,    31,    32,
      47,    57,    58,    59,    33,    53,    22,    52,    21,    22,
      23,    24,    25,    26,    36,    38,    66,    74,    75,    76,
      77,    78,    80,    81,    33,    50,    22,    37,    32,    80,
      35,    76,    36,    67,    76,    76,    68,    74,    82,    25,
      26,    27,    28,    29,    80,    33,    56,    59,    34,    38,
      68,    84,    37,    68,    79,    33,    37,    81,    83,    75,
      75,    76,    76,    76,    34,    34,    38,    60,    85,    32,
      37,    68,    32,    39,    51,    54,    61,    84,    86,    68,
      34,    81,    35,     7,     9,    10,    11,    12,    31,    44,
      47,    60,    62,    63,    64,    66,    68,    32,    39,    81,
      36,    36,    31,    31,    31,    68,    39,    62,    35,    31,
      84,    69,    70,    71,    72,    73,    74,    69,    31,    68,
      37,    20,    19,    13,    14,    15,    16,    17,    18,    37,
      31,    64,    71,    72,    73,    73,    74,    74,    74,    74,
      65,     8,    64,    64
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    40,    41,    42,    42,    43,    43,    44,    44,    45,
      46,    47,    47,    47,    48,    48,    49,    49,    51,    50,
      50,    52,    53,    52,    54,    54,    56,    55,    57,    57,
      58,    58,    59,    59,    61,    60,    62,    62,    63,    63,
      64,    64,    64,    64,    64,    64,    65,    64,    64,    64,
      64,    64,    66,    67,    67,    68,    69,    70,    70,    71,
      71,    72,    72,    72,    73,    73,    73,    73,    73,    74,
      74,    74,    75,    75,    75,    75,    76,    76,    76,    76,
      77,    77,    77,    77,    77,    78,    78,    79,    79,    80,
      81,    81,    82,    81,    83,    83,    84,    84,    85,    84,
      86,    86
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     4,
       3,     1,     1,     1,     1,     3,     1,     3,     0,     8,
       3,     2,     0,     5,     0,     4,     0,     7,     0,     1,
       1,     3,     2,     5,     0,     4,     0,     2,     1,     1,
       4,     2,     1,     1,     5,     7,     0,     6,     2,     2,
       3,     2,     2,     0,     4,     1,     1,     1,     3,     1,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     3,     1,     2,     2,     2,
       1,     1,     1,     3,     1,     3,     4,     1,     3,     1,
       0,     1,     0,     4,     1,     3,     0,     1,     0,     4,
       1,     3
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
#line 78 "src/frontend/sysy.y"
                             { 
    end_parser();
}
#line 1304 "src/frontend/sysy.y.cpp"
    break;

  case 3: /* decl_or_func_list: decl_or_func  */
#line 84 "src/frontend/sysy.y"
    {   module_list->InsertHead((yyvsp[0].llvm)); }
#line 1310 "src/frontend/sysy.y.cpp"
    break;

  case 4: /* decl_or_func_list: decl_or_func_list decl_or_func  */
#line 86 "src/frontend/sysy.y"
    {   module_list->InsertTail((yyvsp[0].llvm)); }
#line 1316 "src/frontend/sysy.y.cpp"
    break;

  case 5: /* decl_or_func: decl  */
#line 90 "src/frontend/sysy.y"
    { (yyval.llvm) = (yyvsp[0].llvm); }
#line 1322 "src/frontend/sysy.y.cpp"
    break;

  case 6: /* decl_or_func: func_def  */
#line 92 "src/frontend/sysy.y"
    { (yyval.llvm) = (yyvsp[0].llvm); }
#line 1328 "src/frontend/sysy.y.cpp"
    break;

  case 7: /* decl: const_decl  */
#line 96 "src/frontend/sysy.y"
    { (yyval.llvm) = (yyvsp[0].llvm); }
#line 1334 "src/frontend/sysy.y.cpp"
    break;

  case 8: /* decl: var_decl  */
#line 98 "src/frontend/sysy.y"
    { (yyval.llvm) = (yyvsp[0].llvm); }
#line 1340 "src/frontend/sysy.y.cpp"
    break;

  case 9: /* const_decl: CONST btype const_def_list ';'  */
#line 102 "src/frontend/sysy.y"
    { 
        if((yyvsp[-2].dtype)==VOID_TYPE)
            throw std::runtime_error("the variable is not allowed to be a void type");
        (yyval.llvm) = create_const_decl((yyvsp[-2].dtype), (yyvsp[-1].sym_vector)); 
    }
#line 1350 "src/frontend/sysy.y.cpp"
    break;

  case 10: /* var_decl: btype var_def_list ';'  */
#line 110 "src/frontend/sysy.y"
    { 
        if((yyvsp[-2].dtype)==VOID_TYPE)
            throw std::runtime_error("the variable is not allowed to be a void type");
        (yyval.llvm) = create_var_decl((yyvsp[-2].dtype), (yyvsp[-1].sym_vector)); 
    }
#line 1360 "src/frontend/sysy.y.cpp"
    break;

  case 11: /* btype: INT  */
#line 118 "src/frontend/sysy.y"
    { (yyval.dtype) = INT_TYPE; }
#line 1366 "src/frontend/sysy.y.cpp"
    break;

  case 12: /* btype: FLOAT  */
#line 120 "src/frontend/sysy.y"
    { (yyval.dtype) = FLOAT_TYPE; }
#line 1372 "src/frontend/sysy.y.cpp"
    break;

  case 13: /* btype: VOID  */
#line 122 "src/frontend/sysy.y"
    { (yyval.dtype) = VOID_TYPE;}
#line 1378 "src/frontend/sysy.y.cpp"
    break;

  case 14: /* const_def_list: const_def  */
#line 125 "src/frontend/sysy.y"
                          {
        std::vector<Symbol*>* syms=new std::vector<Symbol*>(0);
        syms->push_back((yyvsp[0].sym));
        (yyval.sym_vector)=syms;
    }
#line 1388 "src/frontend/sysy.y.cpp"
    break;

  case 15: /* const_def_list: const_def_list ',' const_def  */
#line 130 "src/frontend/sysy.y"
                                  { 
        (yyvsp[-2].sym_vector)->push_back((yyvsp[0].sym));
        (yyval.sym_vector) = (yyvsp[-2].sym_vector);
    }
#line 1397 "src/frontend/sysy.y.cpp"
    break;

  case 16: /* var_def_list: var_def  */
#line 136 "src/frontend/sysy.y"
                      {
        std::vector<Symbol*>* syms=new std::vector<Symbol*>(0);
        syms->push_back((yyvsp[0].sym));
        (yyval.sym_vector)=syms;
    }
#line 1407 "src/frontend/sysy.y.cpp"
    break;

  case 17: /* var_def_list: var_def_list ',' var_def  */
#line 141 "src/frontend/sysy.y"
                              { 
        (yyvsp[-2].sym_vector)->push_back((yyvsp[0].sym));
        (yyval.sym_vector) = (yyvsp[-2].sym_vector);
    }
#line 1416 "src/frontend/sysy.y.cpp"
    break;

  case 18: /* $@1: %empty  */
#line 148 "src/frontend/sysy.y"
    {
        reduce_var_def_left(*((yyvsp[-4].str)),(yyvsp[-3].int_vector),(yyvsp[-1].exp));
    }
#line 1424 "src/frontend/sysy.y.cpp"
    break;

  case 19: /* const_def: IDENTIFIER dim_list '[' const_exp ']' $@1 '=' const_init_val  */
#line 152 "src/frontend/sysy.y"
    {   (yyval.sym) = create_array_const_def(dynamic_cast<ArrayInitial*>((yyvsp[0].exp)->sym->data)); }
#line 1430 "src/frontend/sysy.y.cpp"
    break;

  case 20: /* const_def: IDENTIFIER '=' const_init_val  */
#line 153 "src/frontend/sysy.y"
                                   {
      (yyval.sym) = create_const_def(*((yyvsp[-2].str)), (yyvsp[0].exp)); 
    }
#line 1438 "src/frontend/sysy.y.cpp"
    break;

  case 21: /* var_def: IDENTIFIER dim_list  */
#line 158 "src/frontend/sysy.y"
                             { 
        (yyval.sym) = create_var_def(*((yyvsp[-1].str)), (yyvsp[0].int_vector)); 
    }
#line 1446 "src/frontend/sysy.y.cpp"
    break;

  case 22: /* $@2: %empty  */
#line 162 "src/frontend/sysy.y"
    {
        reduce_var_def_left((*(yyvsp[-1].str)),(yyvsp[0].int_vector));
    }
#line 1454 "src/frontend/sysy.y.cpp"
    break;

  case 23: /* var_def: IDENTIFIER dim_list $@2 '=' var_init_val  */
#line 165 "src/frontend/sysy.y"
                    { 
        (yyval.sym) = create_var_def((yyvsp[0].exp)); 
    }
#line 1462 "src/frontend/sysy.y.cpp"
    break;

  case 24: /* dim_list: %empty  */
#line 171 "src/frontend/sysy.y"
    { (yyval.int_vector) = new std::vector<int>(0); }
#line 1468 "src/frontend/sysy.y.cpp"
    break;

  case 25: /* dim_list: dim_list '[' const_exp ']'  */
#line 172 "src/frontend/sysy.y"
                                {  
        (yyval.int_vector) = (yyvsp[-3].int_vector);
        BasicSymbol* constSym;
        if((yyvsp[-1].exp)->sym->getType()==symType::constant_nonvar)
            constSym=dynamic_cast<ConstSymbol*>((yyvsp[-1].exp)->sym);
        else if((yyvsp[-1].exp)->sym->getType()==symType::constant_var)
            constSym=dynamic_cast<ConstVarSymbol*>((yyvsp[-1].exp)->sym);
        (yyval.int_vector)->push_back(std::get<int>(constSym->data->getValue()));
    }
#line 1482 "src/frontend/sysy.y.cpp"
    break;

  case 26: /* @3: %empty  */
#line 184 "src/frontend/sysy.y"
    {
        (yyval.llvm) = create_func_def((yyvsp[-4].dtype), *((yyvsp[-3].str)), (yyvsp[-1].sym_vector));
    }
#line 1490 "src/frontend/sysy.y.cpp"
    break;

  case 27: /* func_def: btype IDENTIFIER '(' func_params ')' @3 block  */
#line 188 "src/frontend/sysy.y"
    {
        scope=GLOBAL_SCOPE;
        while(variable_table.size()>1){
            variable_table.pop_back();
        }
        (yyval.llvm)=create_func_blk((yyvsp[-1].llvm),(yyvsp[0].llvm));
    }
#line 1502 "src/frontend/sysy.y.cpp"
    break;

  case 28: /* func_params: %empty  */
#line 198 "src/frontend/sysy.y"
    {   (yyval.sym_vector)=new std::vector<Symbol*>(0); create_null_param();}
#line 1508 "src/frontend/sysy.y.cpp"
    break;

  case 29: /* func_params: func_param_list  */
#line 199 "src/frontend/sysy.y"
                     {   
        (yyval.sym_vector)=(yyvsp[0].sym_vector);  
    }
#line 1516 "src/frontend/sysy.y.cpp"
    break;

  case 30: /* func_param_list: func_param  */
#line 204 "src/frontend/sysy.y"
                            { 
        (yyval.sym_vector)=new std::vector<Symbol*>(0);
        (yyval.sym_vector)->push_back((yyvsp[0].sym));
    }
#line 1525 "src/frontend/sysy.y.cpp"
    break;

  case 31: /* func_param_list: func_param_list ',' func_param  */
#line 208 "src/frontend/sysy.y"
                                    {
        (yyval.sym_vector) = (yyvsp[-2].sym_vector);
        (yyval.sym_vector)->push_back((yyvsp[0].sym));
    }
#line 1534 "src/frontend/sysy.y.cpp"
    break;

  case 32: /* func_param: btype IDENTIFIER  */
#line 215 "src/frontend/sysy.y"
    { 
        if((yyvsp[0].str)==VOID_TYPE)
            throw std::runtime_error("the variable is not allowed to be a void type");
        (yyval.sym) = create_param_nonarray((yyvsp[-1].dtype),*((yyvsp[0].str))); 
    }
#line 1544 "src/frontend/sysy.y.cpp"
    break;

  case 33: /* func_param: btype IDENTIFIER '[' ']' dim_list  */
#line 221 "src/frontend/sysy.y"
    { 
        if((yyvsp[-3].str)==VOID_TYPE)
            throw std::runtime_error("the variable is not allowed to be a void type");
        (yyval.sym) = create_param_array((yyvsp[-4].dtype),*((yyvsp[-3].str)),(yyvsp[0].int_vector));
    }
#line 1554 "src/frontend/sysy.y.cpp"
    break;

  case 34: /* @4: %empty  */
#line 229 "src/frontend/sysy.y"
    {
        scope+=1;
        variable_table.push_back(std::unordered_map<std::string,Symbol*>());
        while(variable_rename_table.size()<=scope)
            variable_rename_table.push_back(std::unordered_map<std::string,int>());
        (yyval.llvm)=new LLVMList();
    }
#line 1566 "src/frontend/sysy.y.cpp"
    break;

  case 35: /* block: '{' @4 block_items '}'  */
#line 236 "src/frontend/sysy.y"
                   { 
        (yyval.llvm)=(yyvsp[-2].llvm);
        (yyval.llvm)->InsertTail((yyvsp[-1].llvm));
        while(variable_table.size()>scope)
            variable_table.pop_back();
        scope-=1;
    }
#line 1578 "src/frontend/sysy.y.cpp"
    break;

  case 36: /* block_items: %empty  */
#line 246 "src/frontend/sysy.y"
    {   (yyval.llvm)=new LLVMList();}
#line 1584 "src/frontend/sysy.y.cpp"
    break;

  case 37: /* block_items: block_item block_items  */
#line 247 "src/frontend/sysy.y"
                            {  
        (yyval.llvm)=(yyvsp[0].llvm);
        (yyval.llvm)->InsertHead((yyvsp[-1].llvm));
    }
#line 1593 "src/frontend/sysy.y.cpp"
    break;

  case 38: /* block_item: decl  */
#line 254 "src/frontend/sysy.y"
    {   (yyval.llvm) = (yyvsp[0].llvm); }
#line 1599 "src/frontend/sysy.y.cpp"
    break;

  case 39: /* block_item: stmt  */
#line 256 "src/frontend/sysy.y"
    {   (yyval.llvm) = (yyvsp[0].llvm); }
#line 1605 "src/frontend/sysy.y.cpp"
    break;

  case 40: /* stmt: LVal '=' expr ';'  */
#line 260 "src/frontend/sysy.y"
    {   (yyval.llvm)=assign_array_item((yyvsp[-3].exp),(yyvsp[-1].exp));}
#line 1611 "src/frontend/sysy.y.cpp"
    break;

  case 41: /* stmt: expr ';'  */
#line 262 "src/frontend/sysy.y"
    {   (yyval.llvm)=(yyvsp[-1].exp)->llvmlist;}
#line 1617 "src/frontend/sysy.y.cpp"
    break;

  case 42: /* stmt: ';'  */
#line 264 "src/frontend/sysy.y"
    {   (yyval.llvm)=new LLVMList();}
#line 1623 "src/frontend/sysy.y.cpp"
    break;

  case 43: /* stmt: block  */
#line 266 "src/frontend/sysy.y"
    {   (yyval.llvm)=(yyvsp[0].llvm); }
#line 1629 "src/frontend/sysy.y.cpp"
    break;

  case 44: /* stmt: IF '(' cond ')' stmt  */
#line 268 "src/frontend/sysy.y"
    { (yyval.llvm) = create_if_stmt((yyvsp[-2].exp), (yyvsp[0].llvm)); }
#line 1635 "src/frontend/sysy.y.cpp"
    break;

  case 45: /* stmt: IF '(' cond ')' stmt ELSE stmt  */
#line 270 "src/frontend/sysy.y"
    { (yyval.llvm) = create_if_else_stmt((yyvsp[-4].exp), (yyvsp[-2].llvm), (yyvsp[0].llvm)); }
#line 1641 "src/frontend/sysy.y.cpp"
    break;

  case 46: /* @5: %empty  */
#line 272 "src/frontend/sysy.y"
    { (yyval.llvm) = create_while((yyvsp[-1].exp)); }
#line 1647 "src/frontend/sysy.y.cpp"
    break;

  case 47: /* stmt: WHILE '(' cond ')' @5 stmt  */
#line 274 "src/frontend/sysy.y"
    { (yyval.llvm) = create_while_stmt((yyvsp[-1].llvm),(yyvsp[0].llvm));}
#line 1653 "src/frontend/sysy.y.cpp"
    break;

  case 48: /* stmt: BREAK ';'  */
#line 276 "src/frontend/sysy.y"
    { (yyval.llvm) = create_break_stmt();}
#line 1659 "src/frontend/sysy.y.cpp"
    break;

  case 49: /* stmt: CONTINUE ';'  */
#line 278 "src/frontend/sysy.y"
    { (yyval.llvm) = create_continue_stmt();}
#line 1665 "src/frontend/sysy.y.cpp"
    break;

  case 50: /* stmt: RETURN expr ';'  */
#line 280 "src/frontend/sysy.y"
    { (yyval.llvm) = create_return_stmt((yyvsp[-1].exp)); }
#line 1671 "src/frontend/sysy.y.cpp"
    break;

  case 51: /* stmt: RETURN ';'  */
#line 282 "src/frontend/sysy.y"
    { (yyval.llvm) = create_return_stmt(nullptr); }
#line 1677 "src/frontend/sysy.y.cpp"
    break;

  case 52: /* LVal: IDENTIFIER index_list  */
#line 285 "src/frontend/sysy.y"
                            {
    (yyval.exp)=get_element(*((yyvsp[-1].str)),(yyvsp[0].exp_vector));
}
#line 1685 "src/frontend/sysy.y.cpp"
    break;

  case 53: /* index_list: %empty  */
#line 291 "src/frontend/sysy.y"
    {   (yyval.exp_vector)=new std::vector<Expression*>(0); }
#line 1691 "src/frontend/sysy.y.cpp"
    break;

  case 54: /* index_list: index_list '[' expr ']'  */
#line 292 "src/frontend/sysy.y"
                            {   
        (yyval.exp_vector)=(yyvsp[-3].exp_vector);
        (yyval.exp_vector)->push_back((yyvsp[-1].exp));
    }
#line 1700 "src/frontend/sysy.y.cpp"
    break;

  case 55: /* expr: add_expr  */
#line 300 "src/frontend/sysy.y"
    { (yyval.exp) = (yyvsp[0].exp); }
#line 1706 "src/frontend/sysy.y.cpp"
    break;

  case 56: /* cond: or_expr  */
#line 304 "src/frontend/sysy.y"
    { (yyval.exp) = (yyvsp[0].exp);}
#line 1712 "src/frontend/sysy.y.cpp"
    break;

  case 57: /* or_expr: and_expr  */
#line 308 "src/frontend/sysy.y"
    {   (yyval.exp) = (yyvsp[0].exp);  }
#line 1718 "src/frontend/sysy.y.cpp"
    break;

  case 58: /* or_expr: or_expr OR and_expr  */
#line 310 "src/frontend/sysy.y"
    { (yyval.exp) = create_binary_expr(BINARY_OR, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1724 "src/frontend/sysy.y.cpp"
    break;

  case 59: /* and_expr: eq_expr  */
#line 314 "src/frontend/sysy.y"
    { (yyval.exp)=(yyvsp[0].exp); }
#line 1730 "src/frontend/sysy.y.cpp"
    break;

  case 60: /* and_expr: and_expr AND eq_expr  */
#line 316 "src/frontend/sysy.y"
    { (yyval.exp) = create_binary_expr(BINARY_AND, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1736 "src/frontend/sysy.y.cpp"
    break;

  case 61: /* eq_expr: rel_expr  */
#line 320 "src/frontend/sysy.y"
    { (yyval.exp)=(yyvsp[0].exp); }
#line 1742 "src/frontend/sysy.y.cpp"
    break;

  case 62: /* eq_expr: eq_expr EQ rel_expr  */
#line 322 "src/frontend/sysy.y"
    { (yyval.exp) = create_binary_expr(BINARY_EQ, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1748 "src/frontend/sysy.y.cpp"
    break;

  case 63: /* eq_expr: eq_expr NE rel_expr  */
#line 324 "src/frontend/sysy.y"
    { (yyval.exp) = create_binary_expr(BINARY_NE, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1754 "src/frontend/sysy.y.cpp"
    break;

  case 64: /* rel_expr: add_expr  */
#line 328 "src/frontend/sysy.y"
    { (yyval.exp)=(yyvsp[0].exp); }
#line 1760 "src/frontend/sysy.y.cpp"
    break;

  case 65: /* rel_expr: rel_expr LT add_expr  */
#line 330 "src/frontend/sysy.y"
    { (yyval.exp) = create_binary_expr(BINARY_LT, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1766 "src/frontend/sysy.y.cpp"
    break;

  case 66: /* rel_expr: rel_expr GT add_expr  */
#line 332 "src/frontend/sysy.y"
    { (yyval.exp) = create_binary_expr(BINARY_GT, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1772 "src/frontend/sysy.y.cpp"
    break;

  case 67: /* rel_expr: rel_expr LE add_expr  */
#line 334 "src/frontend/sysy.y"
    { (yyval.exp) = create_binary_expr(BINARY_LE, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1778 "src/frontend/sysy.y.cpp"
    break;

  case 68: /* rel_expr: rel_expr GE add_expr  */
#line 336 "src/frontend/sysy.y"
    { (yyval.exp) = create_binary_expr(BINARY_GE, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1784 "src/frontend/sysy.y.cpp"
    break;

  case 69: /* add_expr: mul_expr  */
#line 340 "src/frontend/sysy.y"
    { (yyval.exp)=(yyvsp[0].exp); }
#line 1790 "src/frontend/sysy.y.cpp"
    break;

  case 70: /* add_expr: add_expr '+' mul_expr  */
#line 342 "src/frontend/sysy.y"
    { (yyval.exp) = create_binary_expr(BINARY_ADD, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1796 "src/frontend/sysy.y.cpp"
    break;

  case 71: /* add_expr: add_expr '-' mul_expr  */
#line 344 "src/frontend/sysy.y"
    { (yyval.exp) = create_binary_expr(BINARY_SUB, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1802 "src/frontend/sysy.y.cpp"
    break;

  case 72: /* mul_expr: unary_expr  */
#line 348 "src/frontend/sysy.y"
    { (yyval.exp)=(yyvsp[0].exp); }
#line 1808 "src/frontend/sysy.y.cpp"
    break;

  case 73: /* mul_expr: mul_expr '*' unary_expr  */
#line 350 "src/frontend/sysy.y"
    { (yyval.exp) = create_binary_expr(BINARY_MUL, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1814 "src/frontend/sysy.y.cpp"
    break;

  case 74: /* mul_expr: mul_expr '/' unary_expr  */
#line 352 "src/frontend/sysy.y"
    { (yyval.exp) = create_binary_expr(BINARY_DIV, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1820 "src/frontend/sysy.y.cpp"
    break;

  case 75: /* mul_expr: mul_expr '%' unary_expr  */
#line 354 "src/frontend/sysy.y"
    { (yyval.exp) = create_binary_expr(BINARY_REM, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1826 "src/frontend/sysy.y.cpp"
    break;

  case 76: /* unary_expr: primary_expr  */
#line 358 "src/frontend/sysy.y"
    { (yyval.exp) = (yyvsp[0].exp); }
#line 1832 "src/frontend/sysy.y.cpp"
    break;

  case 77: /* unary_expr: '+' unary_expr  */
#line 360 "src/frontend/sysy.y"
    { (yyval.exp) = create_unary_expr(SINGLE_POSITIVE, (yyvsp[0].exp)); }
#line 1838 "src/frontend/sysy.y.cpp"
    break;

  case 78: /* unary_expr: '-' unary_expr  */
#line 362 "src/frontend/sysy.y"
    { (yyval.exp) = create_unary_expr(SINGLE_NEGTIVE, (yyvsp[0].exp)); }
#line 1844 "src/frontend/sysy.y.cpp"
    break;

  case 79: /* unary_expr: NOT unary_expr  */
#line 364 "src/frontend/sysy.y"
    { (yyval.exp) = create_unary_expr(SINGLE_NOT, (yyvsp[0].exp)); }
#line 1850 "src/frontend/sysy.y.cpp"
    break;

  case 80: /* primary_expr: LVal  */
#line 368 "src/frontend/sysy.y"
    { (yyval.exp) = (yyvsp[0].exp);}
#line 1856 "src/frontend/sysy.y.cpp"
    break;

  case 81: /* primary_expr: INT_CONST  */
#line 370 "src/frontend/sysy.y"
    { (yyval.exp) = create_primary_INTCONST(std::stoi((*(yyvsp[0].str)), nullptr, 0));  }
#line 1862 "src/frontend/sysy.y.cpp"
    break;

  case 82: /* primary_expr: FLOAT_CONST  */
#line 372 "src/frontend/sysy.y"
    { (yyval.exp) = create_primary_FLOATCONST(std::stof(*((yyvsp[0].str))));}
#line 1868 "src/frontend/sysy.y.cpp"
    break;

  case 83: /* primary_expr: '(' expr ')'  */
#line 374 "src/frontend/sysy.y"
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 1874 "src/frontend/sysy.y.cpp"
    break;

  case 84: /* primary_expr: func_call  */
#line 376 "src/frontend/sysy.y"
    { (yyval.exp) = (yyvsp[0].exp); }
#line 1880 "src/frontend/sysy.y.cpp"
    break;

  case 85: /* func_call: IDENTIFIER '(' ')'  */
#line 380 "src/frontend/sysy.y"
    { (yyval.exp) = create_func_call(*((yyvsp[-2].str)),nullptr); }
#line 1886 "src/frontend/sysy.y.cpp"
    break;

  case 86: /* func_call: IDENTIFIER '(' expr_list ')'  */
#line 382 "src/frontend/sysy.y"
    { (yyval.exp) = create_func_call(*((yyvsp[-3].str)), (yyvsp[-1].exp)); }
#line 1892 "src/frontend/sysy.y.cpp"
    break;

  case 87: /* expr_list: expr  */
#line 386 "src/frontend/sysy.y"
    {   (yyval.exp) = (yyvsp[0].exp); }
#line 1898 "src/frontend/sysy.y.cpp"
    break;

  case 88: /* expr_list: expr_list ',' expr  */
#line 387 "src/frontend/sysy.y"
                        {   
        (yyval.exp) = (yyvsp[-2].exp); 
        Expression* exp=(yyval.exp);
        while(exp->next!=nullptr)
            exp=exp->next;
        exp->next=(yyvsp[0].exp);
    }
#line 1910 "src/frontend/sysy.y.cpp"
    break;

  case 89: /* const_exp: add_expr  */
#line 397 "src/frontend/sysy.y"
    { (yyval.exp) = (yyvsp[0].exp); }
#line 1916 "src/frontend/sysy.y.cpp"
    break;

  case 90: /* const_init_val: %empty  */
#line 401 "src/frontend/sysy.y"
    {   (yyval.exp)=new Expression(new LLVMList(),nullptr); }
#line 1922 "src/frontend/sysy.y.cpp"
    break;

  case 91: /* const_init_val: const_exp  */
#line 403 "src/frontend/sysy.y"
    {   
        (yyval.exp)=(yyvsp[0].exp);
    }
#line 1930 "src/frontend/sysy.y.cpp"
    break;

  case 92: /* $@6: %empty  */
#line 407 "src/frontend/sysy.y"
    {
        var_init_list_reduce_left();
    }
#line 1938 "src/frontend/sysy.y.cpp"
    break;

  case 93: /* const_init_val: '{' $@6 const_init_list '}'  */
#line 410 "src/frontend/sysy.y"
                       {
        reduce_var_init_list((yyvsp[-1].exp));
        (yyval.exp)=(yyvsp[-1].exp);
    }
#line 1947 "src/frontend/sysy.y.cpp"
    break;

  case 94: /* const_init_list: const_init_val  */
#line 416 "src/frontend/sysy.y"
                                {   
        (yyval.exp) = (yyvsp[0].exp);
        create_var_init_list((yyval.exp));
    }
#line 1956 "src/frontend/sysy.y.cpp"
    break;

  case 95: /* const_init_list: const_init_list ',' const_init_val  */
#line 420 "src/frontend/sysy.y"
                                        {
        (yyval.exp) = (yyvsp[-2].exp);
        create_var_init_list((yyval.exp),(yyvsp[0].exp));
    }
#line 1965 "src/frontend/sysy.y.cpp"
    break;

  case 96: /* var_init_val: %empty  */
#line 427 "src/frontend/sysy.y"
    {   (yyval.exp)=new Expression(new LLVMList(),nullptr); }
#line 1971 "src/frontend/sysy.y.cpp"
    break;

  case 97: /* var_init_val: expr  */
#line 429 "src/frontend/sysy.y"
    {   
        (yyval.exp)=(yyvsp[0].exp);
    }
#line 1979 "src/frontend/sysy.y.cpp"
    break;

  case 98: /* $@7: %empty  */
#line 433 "src/frontend/sysy.y"
    {
        var_init_list_reduce_left();
    }
#line 1987 "src/frontend/sysy.y.cpp"
    break;

  case 99: /* var_init_val: '{' $@7 var_init_list '}'  */
#line 436 "src/frontend/sysy.y"
                     {
        reduce_var_init_list((yyvsp[-1].exp));
        (yyval.exp)=(yyvsp[-1].exp);
    }
#line 1996 "src/frontend/sysy.y.cpp"
    break;

  case 100: /* var_init_list: var_init_val  */
#line 442 "src/frontend/sysy.y"
                            {   
        (yyval.exp) = (yyvsp[0].exp);
        create_var_init_list((yyval.exp));
    }
#line 2005 "src/frontend/sysy.y.cpp"
    break;

  case 101: /* var_init_list: var_init_list ',' var_init_val  */
#line 446 "src/frontend/sysy.y"
                                    {
        (yyval.exp) = (yyvsp[-2].exp);
        create_var_init_list((yyval.exp),(yyvsp[0].exp));
    }
#line 2014 "src/frontend/sysy.y.cpp"
    break;


#line 2018 "src/frontend/sysy.y.cpp"

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

#line 452 "src/frontend/sysy.y"


void yyerror(const char *s) {
    fprintf(stderr, "Error: %s at line %d\n", s, yylineno);
    exit(1);
}
