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
#line 1 "1605042.y" /* yacc.c:339  */

#include "1605042_Symbol_Table.cpp"
#define YYSTYPE SymbolInfo*
int line_count=1;
int yyparse(void);
int yylex(void);
extern FILE *yyin;
string argument;
int error_count=0;
SymbolTable *table;
vector<string> declarationList;
vector<string> parameterList;
vector<string> returnList;
vector<string> variable_for_asm;
vector<pair<string,string> > parameterNames;
vector<pair<string,string> > array_for_asm;
FILE *fp,*fp3;
int i=0;
string current_function="";

int labelCount=0;
int tempCount=0;

void yyerror(const char* st)
{
	error_count++;
	fprintf(fp3,"Error at Line No %d :%s\n\n",line_count,st);
}

char *newLabel()
{
	char *lb= new char[4];
	strcpy(lb,"L");
	char b[3];
	sprintf(b,"%d", labelCount);
	labelCount++;
	strcat(lb,b);
	return lb;
}

char *newTemp()
{
	char *t= new char[4];
	strcpy(t,"t");
	char b[3];
	sprintf(b,"%d", tempCount);
	tempCount++;
	strcat(t,b);
	return t;
}

string Symbolmaker(string s,int num)
{
	char a[1];
    a[0]='0'+num;
	s=s+a;
	return s;
}

void optimize()
{
    ofstream ofs("Code.asm",ofstream::out);
    ifstream code("code.asm");
    string line,saveline;
    getline(code, line);
    saveline=line;
    string op1,a1,b1,op2,a2,b2,temp;
    stringstream check(line);
    getline(check,op1,' ');
    if(op1.compare("\tMOV")==0)
    {
        getline(check,temp,' ');
        stringstream check(temp);
        getline(check,a1,',');
        getline(check,b1,',');
    }
    ofs<<saveline<<endl;
    while(getline(code, line))
    {
        saveline=line;
        stringstream check(line);
        getline(check,op2,' ');
        if(op2.compare("\tMOV")==0)
        {
            getline(check,temp,' ');
            stringstream check(temp);
            getline(check,a2,',');
            getline(check,b2,',');
            if(op1.compare("\tMOV")==0)
            {
                if((a1.compare(a2)==0&&b1.compare(b2)==0)||((a1.compare(b2)==0&&b1.compare(a2)==0)))
                {

                }
                else
                {
                    ofs<<saveline<<endl;
                    op1=op2;
                    a1=a2;
                    b1=b2;
                }

            }
            else
            {
                ofs<<saveline<<endl;
                op1=op2;
                a1=a2;
                b1=b2;
            }
        }
        else
        {
            ofs<<saveline<<endl;
            op1=op2;
        }

    }
	ofs.close();
}



#line 190 "1605042.tab.c" /* yacc.c:339  */

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
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "1605042.tab.h".  */
#ifndef YY_YY_1605042_TAB_H_INCLUDED
# define YY_YY_1605042_TAB_H_INCLUDED
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
    IF = 258,
    ELSE = 259,
    FOR = 260,
    WHILE = 261,
    ID = 262,
    LPAREN = 263,
    RPAREN = 264,
    SEMICOLON = 265,
    COMMA = 266,
    LCURL = 267,
    RCURL = 268,
    INT = 269,
    FLOAT = 270,
    VOID = 271,
    CONST_INT = 272,
    LTHIRD = 273,
    RTHIRD = 274,
    PRINTLN = 275,
    RETURN = 276,
    NOT = 277,
    CONST_FLOAT = 278,
    INCOP = 279,
    DECOP = 280,
    ADDOP = 281,
    MULOP = 282,
    ASSIGNOP = 283,
    LOGICOP = 284,
    RELOP = 285,
    LOWER_THAN_ELSE = 286
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_1605042_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 273 "1605042.tab.c" /* yacc.c:358  */

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
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   152

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  70
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  126

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   286

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
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   139,   139,   171,   182,   195,   206,   217,   230,   260,
     285,   284,   412,   411,   505,   513,   520,   528,   538,   538,
     554,   554,   569,   572,   585,   592,   599,   608,   636,   661,
     687,   715,   726,   739,   744,   756,   768,   790,   807,   828,
     848,   865,   896,   899,   908,   925,   958,   993,  1005,  1055,
    1070,  1123,  1138,  1192,  1206,  1244,  1257,  1314,  1331,  1347,
    1363,  1394,  1494,  1508,  1520,  1532,  1564,  1598,  1620,  1625,
    1651
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "FOR", "WHILE", "ID",
  "LPAREN", "RPAREN", "SEMICOLON", "COMMA", "LCURL", "RCURL", "INT",
  "FLOAT", "VOID", "CONST_INT", "LTHIRD", "RTHIRD", "PRINTLN", "RETURN",
  "NOT", "CONST_FLOAT", "INCOP", "DECOP", "ADDOP", "MULOP", "ASSIGNOP",
  "LOGICOP", "RELOP", "LOWER_THAN_ELSE", "$accept", "start", "program",
  "unit", "func_declaration", "func_definition", "$@1", "$@2",
  "parameter_list", "compound_statement", "$@3", "$@4", "var_declaration",
  "type_specifier", "declaration_list", "statements", "statement",
  "expression_statement", "variable", "expression", "logic_expression",
  "rel_expression", "simple_expression", "term", "unary_expression",
  "factor", "argument_list", "arguments", YY_NULLPTR
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
     285,   286
};
# endif

#define YYPACT_NINF -73

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-73)))

#define YYTABLE_NINF -21

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      39,   -73,   -73,   -73,    29,    39,   -73,   -73,   -73,   -73,
      28,   -73,   -73,     3,    49,    18,    31,   -73,    44,    56,
      47,    50,    54,    57,   -73,     7,    78,    39,   -73,   -73,
      51,    79,    84,   -73,   -73,     7,    92,    82,   -73,    88,
      93,   -73,   -73,   -73,    36,    99,   108,   109,     4,   112,
     -73,   -73,   110,   112,   112,   -73,   112,   -73,   -73,   114,
      64,   -73,   -73,    19,   113,   -73,    95,   -10,    98,   -73,
     -73,   -73,   -73,   112,   105,   112,   112,   112,   117,   123,
     122,    58,   -73,   -73,   115,   -73,   -73,   -73,   -73,   112,
     -73,   112,   112,   112,   112,   127,   105,   128,   -73,   130,
     129,   124,   -73,   132,   -73,   -73,   -73,    98,   116,   -73,
      88,   112,    88,   -73,   112,   -73,   134,   141,   137,   -73,
     -73,   -73,    88,    88,   -73,   -73
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    24,    25,    26,     0,     2,     4,     6,     7,     5,
       0,     1,     3,    29,     0,     0,     0,    23,     0,    12,
       0,    17,     0,    27,     9,     0,    10,     0,    16,    30,
       0,     0,    18,    13,     8,     0,    15,     0,    22,     0,
       0,    11,    14,    28,     0,     0,     0,     0,    45,     0,
      43,    63,     0,     0,     0,    64,     0,    35,    33,     0,
       0,    31,    34,    60,     0,    47,    49,    51,    53,    55,
      59,    21,    42,     0,     0,     0,    68,     0,     0,     0,
       0,    60,    58,    57,    29,    19,    32,    65,    66,     0,
      44,     0,     0,     0,     0,     0,     0,     0,    70,     0,
      67,     0,    62,     0,    41,    48,    50,    54,    52,    56,
       0,     0,     0,    61,     0,    46,     0,    37,     0,    39,
      69,    40,     0,     0,    38,    36
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -73,   -73,   -73,   142,   -73,   -73,   -73,   -73,   -73,   -11,
     -73,   -73,    13,    10,   -73,   -73,   -60,   -65,   -53,   -47,
     -72,    59,    55,    60,   -49,   -73,   -73,   -73
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,     7,     8,    35,    25,    20,    57,
      39,    40,    58,    59,    14,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    99,   100
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      86,    81,    78,    81,    98,    82,    80,    83,    31,    96,
      10,    15,    76,     9,    33,    10,    92,   105,     9,    32,
      93,    16,    77,    81,    41,    21,    95,    19,    97,    11,
     101,   111,     1,     2,     3,    13,    81,    36,    81,    81,
      81,    81,   120,    87,    88,   109,    72,    89,    22,    38,
     117,    23,   119,     1,     2,     3,    26,    28,    27,    17,
      18,    81,   124,   125,   118,    44,    24,    45,    37,    46,
      47,    48,    49,    29,    50,    30,    32,    85,     1,     2,
       3,    51,    87,    88,    52,    53,    54,    55,    34,    44,
      56,    45,    38,    46,    47,    48,    49,   -20,    50,    42,
      32,    43,     1,     2,     3,    51,    71,    73,    52,    53,
      54,    55,    48,    49,    56,    50,    74,    75,    79,    48,
      49,    84,    51,    90,    91,    94,   102,    54,    55,    51,
     103,    56,   104,    16,    54,    55,   110,   112,    56,   113,
     114,   116,    92,   115,   121,   122,   123,    12,   108,     0,
     106,     0,   107
};

static const yytype_int8 yycheck[] =
{
      60,    54,    49,    56,    76,    54,    53,    56,     1,    74,
       0,     8,     8,     0,    25,     5,    26,    89,     5,    12,
      30,    18,    18,    76,    35,    15,    73,     9,    75,     0,
      77,    96,    14,    15,    16,     7,    89,    27,    91,    92,
      93,    94,   114,    24,    25,    94,    10,    28,    17,    13,
     110,     7,   112,    14,    15,    16,     9,     7,    11,    10,
      11,   114,   122,   123,   111,     1,    10,     3,    17,     5,
       6,     7,     8,    19,    10,    18,    12,    13,    14,    15,
      16,    17,    24,    25,    20,    21,    22,    23,    10,     1,
      26,     3,    13,     5,     6,     7,     8,    13,    10,     7,
      12,    19,    14,    15,    16,    17,    13,     8,    20,    21,
      22,    23,     7,     8,    26,    10,     8,     8,     8,     7,
       8,     7,    17,    10,    29,    27,     9,    22,    23,    17,
       7,    26,    10,    18,    22,    23,     9,     9,    26,     9,
      11,     9,    26,    19,    10,     4,     9,     5,    93,    -1,
      91,    -1,    92
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    14,    15,    16,    33,    34,    35,    36,    37,    44,
      45,     0,    35,     7,    46,     8,    18,    10,    11,     9,
      40,    45,    17,     7,    10,    39,     9,    11,     7,    19,
      18,     1,    12,    41,    10,    38,    45,    17,    13,    42,
      43,    41,     7,    19,     1,     3,     5,     6,     7,     8,
      10,    17,    20,    21,    22,    23,    26,    41,    44,    45,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    13,    10,     8,     8,     8,     8,    18,    51,     8,
      51,    50,    56,    56,     7,    13,    48,    24,    25,    28,
      10,    29,    26,    30,    27,    51,    49,    51,    52,    58,
      59,    51,     9,     7,    10,    52,    53,    55,    54,    56,
       9,    49,     9,     9,    11,    19,     9,    48,    51,    48,
      52,    10,     4,     9,    48,    48
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    32,    33,    34,    34,    35,    35,    35,    36,    36,
      38,    37,    39,    37,    40,    40,    40,    40,    42,    41,
      43,    41,    41,    44,    45,    45,    45,    46,    46,    46,
      46,    47,    47,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    49,    49,    50,    50,    51,    51,    52,
      52,    53,    53,    54,    54,    55,    55,    56,    56,    56,
      57,    57,    57,    57,    57,    57,    57,    58,    58,    59,
      59
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     6,     5,
       0,     7,     0,     6,     4,     3,     2,     1,     0,     4,
       0,     3,     2,     3,     1,     1,     1,     3,     6,     1,
       4,     1,     2,     1,     1,     1,     7,     5,     7,     5,
       5,     3,     2,     1,     2,     1,     4,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     2,     2,     1,
       1,     4,     3,     1,     1,     2,     2,     1,     0,     3,
       1
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
#line 140 "1605042.y" /* yacc.c:1646  */
    {

		if(error_count==0)
		{
			string temp=(yyvsp[0])->code;
			(yyval)->code=".MODEL SMALL\n\.STACK 100H\n\.DATA \n";
			(yyval)->code+="RESULT DB ?,?,?,?,?,?,?,?,?\nFINAL DB ?,?,?,?,?,?,?,?,?\n";
			for(i=0;i<variable_for_asm.size();i++)
			{
				(yyval)->code+=variable_for_asm[i]+" DW ?\n";
			}
			for(i=0;i<array_for_asm.size();i++)
			{
				(yyval)->code+=array_for_asm[i].first+" DW "+array_for_asm[i].second+" DUP(?)\n";
			}
			(yyval)->code+="DISPLAY PROC\n\tPUSH AX\n\tPUSH BX\n\tPUSH CX\n\tPUSH DX\n\tMOV BX,AX\n\tCMP AX,0\n\tJGE POS\n\tMOV AH,2\n\tMOV DL,45\n\tINT 21H\n\tMOV AX,BX \n\tNEG AX\n\tPOS\:\n\tMOV SI,0\n\tWHILE_LOOP\:\n\tMOV DX,0\n\tMOV BX,10\n\tDIV BX\n\tADD DX,'0'\n\tMOV RESULT+SI,DL\n \tADD SI,1\n \tCMP AX,0\n\tJNZ WHILE_LOOP\n\tEND_LOOP\:\n\tMOV RESULT+SI,'$'\n\tMOV FINAL+SI,'$'\n\tMOV CX,SI\n\tMOV DI,SI\n\tSUB DI,1\n\tMOV SI,0\n\tREVERSE\:\n\tMOV BL,RESULT+DI\n\tMOV FINAL+SI,BL\n\tSUB DI,1\n\tADD SI,1\n\tLOOP REVERSE\n\tMOV AH,9\n\tLEA DX,FINAL\n\tINT 21H\n\tMOV AH,2\n\tMOV DL,0DH\n\tINT 21H\n\tMOV DL,0AH\n\tINT 21H\n\tPOP DX\n\tPOP CX\n\tPOP BX\n\tPOP AX\n\tret\nDISPLAY ENDP\n";
			(yyval)->code+=temp;
			ofstream fout;
			fout.open("code.asm");
			fout << (yyval)->code;
			fout.close();
			optimize();
		}

		//fprintf(fp2,"At line No %d start : program\n",line_count);
		(yyval)->setName((yyvsp[0])->getName());
		//fprintf(fp2,"%s\n\n",$$->getName().c_str());

	}
#line 1472 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 172 "1605042.y" /* yacc.c:1646  */
    {
		//fprintf(fp2,"At line No %d program : program unit\n",line_count);
		(yyval)->setName((yyvsp[-1])->getName()+(yyvsp[0])->getName());
		//fprintf(fp2,"%s\n\n",$$->getName().c_str());

		if(error_count==0)
		{
			(yyval)->code=(yyvsp[-1])->code+(yyvsp[0])->code;
		}
	}
#line 1487 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 183 "1605042.y" /* yacc.c:1646  */
    {
		//fprintf(fp2,"At line No %d program : unit\n",line_count);
		(yyval)->setName((yyvsp[0])->getName());
		//fprintf(fp2,"%s\n\n",$$->getName().c_str());
		
		if(error_count==0)
		{
			(yyval)->code=(yyvsp[0])->code;
		}
	}
#line 1502 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 196 "1605042.y" /* yacc.c:1646  */
    {
		//fprintf(fp2,"At line No %d unit : var_declaration\n",line_count);
		(yyval)->setName((yyvsp[0])->getName());
		//fprintf(fp2,"%s\n\n",$$->getName().c_str());

		if(error_count==0)
		{
			(yyval)->code=(yyvsp[0])->code;
		}
	}
#line 1517 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 207 "1605042.y" /* yacc.c:1646  */
    {
		//fprintf(fp2,"At line No %d unit : func_declaration\n",line_count);
		(yyval)->setName((yyvsp[0])->getName());
		//fprintf(fp2,"%s\n\n",$$->getName().c_str());

		if(error_count==0)
		{
			(yyval)->code=(yyvsp[0])->code;
		}
	}
#line 1532 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 218 "1605042.y" /* yacc.c:1646  */
    {
		//fprintf(fp2,"At line No %d unit : func_definition\n",line_count);
		(yyval)->setName((yyvsp[0])->getName());
		//fprintf(fp2,"%s\n\n",$$->getName().c_str());

		if(error_count==0)
		{
			(yyval)->code=(yyvsp[0])->code;
		}
	}
#line 1547 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 231 "1605042.y" /* yacc.c:1646  */
    {
		if(table->currentScope->id!=1)
		{
			fprintf(fp3,"Error at Line No %d : Function should be declared in global scope \n\n",line_count);
			error_count++;
		}
		else if(table->Lookup((yyvsp[-4])->getName())==0)
		{
			table->Insert((yyvsp[-4])->getName(),(yyvsp[-4])->getType());
			table->Lookup((yyvsp[-4])->getName())->is_function=true;
			table->Lookup((yyvsp[-4])->getName())->return_type=(yyvsp[-5])->getType();
			for(i=0;i<parameterList.size();i++)
				{
					table->Lookup((yyvsp[-4])->getName())->parameter_list.push_back(parameterList[i]);
				} 
			parameterList.clear();
		}
		else
		{
			fprintf(fp3,"Error at Line No %d : Redeclaration of function %s \n\n",line_count,(yyvsp[-4])->getName().c_str());
			error_count++;
			parameterList.clear();
		}
		//fprintf(fp2,"At line No %d func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON\n",line_count);
		(yyval)->setName((yyvsp[-5])->getName()+" "+(yyvsp[-4])->getName()+" "+(yyvsp[-3])->getName()+" "+(yyvsp[-2])->getName()+" "+(yyvsp[-1])->getName()+" "+(yyvsp[0])->getName());
		//fprintf(fp2,"%s\n\n",$$->getName().c_str());
		parameterNames.clear();
	
	}
#line 1581 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 261 "1605042.y" /* yacc.c:1646  */
    {
				if(table->currentScope->id!=1)
				{
					fprintf(fp3,"Error at Line No %d : Function should be declared in global scope \n\n",line_count);
					error_count++;
				}
				else if(table->Lookup((yyvsp[-3])->getName())==0)
				{
					table->Insert((yyvsp[-3])->getName(),(yyvsp[-3])->getType());
					table->Lookup((yyvsp[-3])->getName())->is_function=true;
					table->Lookup((yyvsp[-3])->getName())->return_type=(yyvsp[-4])->getType();
				}
				else
				{
					fprintf(fp3,"Error at Line No %d : Redeclaration of function %s \n\n",line_count,(yyvsp[-3])->getName().c_str());
					error_count++;
				}
				//fprintf(fp2,"At line No %d func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON\n",line_count);
				(yyval)->setName((yyvsp[-4])->getName()+" "+(yyvsp[-3])->getName()+" "+(yyvsp[-2])->getName()+" "+(yyvsp[-1])->getName()+" "+(yyvsp[0])->getName());
				//fprintf(fp2,"%s\n\n",$$->getName().c_str());
			}
#line 1607 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 285 "1605042.y" /* yacc.c:1646  */
    {
		if(table->currentScope->id!=1)
		{
			fprintf(fp3,"Error at Line No %d : Function should be declared in global scope \n\n",line_count);
			error_count++;
			parameterList.clear(); 
		}
		else if(table->Lookup((yyvsp[-3])->getName())==0)
		{
			table->Insert((yyvsp[-3])->getName(),(yyvsp[-3])->getType());
			table->Lookup((yyvsp[-3])->getName())->return_type=(yyvsp[-4])->getType();
				for(i=0;i<parameterList.size();i++)
				{
						table->Lookup((yyvsp[-3])->getName())->parameter_list.push_back(parameterList[i]);
				} 
				parameterList.clear();
			table->Lookup((yyvsp[-3])->getName())->is_function=true;
			table->Lookup((yyvsp[-3])->getName())->is_defined=true;
			returnList.push_back((yyvsp[-4])->getType());
		}
		else
		{
			if(table->Lookup((yyvsp[-3])->getName())->is_defined)
			{
				fprintf(fp3,"Error at Line No %d : Function is already defined\n\n",line_count);
				error_count++;
				parameterList.clear(); 
			}
			else
			{
					bool t=false;
					if(table->Lookup((yyvsp[-3])->getName())->return_type!=(yyvsp[-4])->getType())
					{
						fprintf(fp3,"Error at Line No %d : Function defination doesn't match with declaration\n\n",line_count);
						error_count++;
						t=true;
					}
					else
					{
						if(parameterList.size()!=table->Lookup((yyvsp[-3])->getName())->parameter_list.size())
						{
							fprintf(fp3,"Error at Line No %d : Function defination doesn't match with declaration\n\n",line_count);
							error_count++;
							t=true;
						}
						else{
								for(i=0;i<parameterList.size();i++)
								{
										if(table->Lookup((yyvsp[-3])->getName())->parameter_list[i]!=parameterList[i])
										{
											fprintf(fp3,"Error at Line No %d : Function defination doesn't match with declaration\n\n",line_count);
											error_count++;
											t=true;
											break;
										}
								}
							}

					}
					if(!t)
					{
						table->Lookup((yyvsp[-3])->getName())->is_defined=true;

					}
					parameterList.clear(); 
			}
			returnList.push_back((yyvsp[-4])->getType());

			
		}
		if(error_count==0)
			{
				current_function=(yyvsp[-3])->getName();
				variable_for_asm.push_back(current_function+"_return");
				for(i=0;i<parameterNames.size();i++)
				{
					table->Lookup((yyvsp[-3])->getName())->parameterNames.push_back(Symbolmaker(parameterNames[i].second,table->scopeid.sequence));
					variable_for_asm.push_back(Symbolmaker(parameterNames[i].second,table->scopeid.sequence));
				}
			}
	}
#line 1693 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 366 "1605042.y" /* yacc.c:1646  */
    {
		//fprintf(fp2,"At line No %d func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement\n",line_count);
		(yyval)->setName((yyvsp[-6])->getName()+" "+(yyvsp[-5])->getName()+" "+(yyvsp[-4])->getName()+" "+(yyvsp[-3])->getName()+" "+(yyvsp[-2])->getName()+" "+(yyvsp[0])->getName());
		//fprintf(fp2,"%s\n\n",$$->getName().c_str());

		if(error_count==0)
		{
			(yyval)->code=(yyvsp[-5])->getName()+" PROC\n";
			if((yyvsp[-5])->getName()=="main")
			{
				(yyval)->code+="\tMOV AX,@DATA\n\tMOV DS,AX \n"+(yyvsp[0])->code+"Return_"+current_function+":\n\tMOV AH,4CH\n\tINT 21H\nEND MAIN\n";
			}
			else
			{
				/*for(i=0;i<table->Lookup($2->getName())->parameterNames.size();i++)
				{
					$$->code+="\tPUSH "+table->Lookup($2->getName())->parameterNames[i]+"\n";
				}
				for(i=0;i<table->Lookup(current_function)->variableNames.size();i++)
				{
					$$->code+="\tPUSH "+table->Lookup(current_function)->variableNames[i]+"\n";
				}*/
				(yyval)->code+="\tPUSH AX\n\tPUSH BX \n\tPUSH CX \n\tPUSH DX\n";
				(yyval)->code+=(yyvsp[0])->code;
				(yyval)->code+="Return_"+current_function+":\n";
				(yyval)->code+="\tPOP DX\n\tPOP CX\n\tPOP BX\n\tPOP AX\n";
				/*for(i=table->Lookup(current_function)->variableNames.size()-1;i>=0;i--)
				{
					$$->code+="\tPOP "+table->Lookup(current_function)->variableNames[i]+"\n";
				}
				for(i=table->Lookup($2->getName())->parameterNames.size()-1;i>=0;i--)
				{
					$$->code+="\tPOP "+table->Lookup($2->getName())->parameterNames[i]+"\n";
				}*/
				(yyval)->code+="\tret\n";
				(yyval)->code+=(yyvsp[-5])->getName()+" ENDP\n";
			}
			parameterNames.clear();
		}
		else
		{
			parameterNames.clear();
		}
		//current_function="";
	}
#line 1743 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 412 "1605042.y" /* yacc.c:1646  */
    {
				if(table->currentScope->id!=1)
				{
					fprintf(fp3,"Error at Line No %d : Function should be declared in global scope \n\n",line_count);
					error_count++;
					parameterList.clear(); 
				}
				else if(table->Lookup((yyvsp[-2])->getName())==0)
				{
					table->Insert((yyvsp[-2])->getName(),(yyvsp[-2])->getType());
					table->Lookup((yyvsp[-2])->getName())->return_type=(yyvsp[-3])->getType();
					table->Lookup((yyvsp[-2])->getName())->is_function=true;
					table->Lookup((yyvsp[-2])->getName())->is_defined=true;
					returnList.push_back((yyvsp[-3])->getType());
					parameterList.clear();
				}
				else
				{
					bool t=false;
						if(table->Lookup((yyvsp[-2])->getName())->is_defined)
						{
							fprintf(fp3,"Error at Line No %d : Function is already defined\n\n",line_count);
							t=true;
							error_count++;
						}
						else if(parameterList.size()!=table->Lookup((yyvsp[-2])->getName())->parameter_list.size())
						{
							fprintf(fp3,"Error at Line No %d : Function defination doesn't match with declaration\n\n",line_count);
							t=true;
							error_count++;
						}
						else if(table->Lookup((yyvsp[-2])->getName())->return_type!=(yyvsp[-3])->getType())
						{
							fprintf(fp3,"Error at Line No %d : Function defination doesn't match with declaration\n\n",line_count);
							t=true;
							error_count++;
						}
						if(!t)
						{
							table->Lookup((yyvsp[-2])->getName())->is_defined=true;

						}
						parameterList.clear();
				}
				returnList.push_back((yyvsp[-3])->getType());

				if(error_count==0)
				{
					current_function=(yyvsp[-2])->getName();
					variable_for_asm.push_back(current_function+"_return");
				}
			}
#line 1800 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 464 "1605042.y" /* yacc.c:1646  */
    {
			//fprintf(fp2,"At line No %d func_definition : type_specifier ID LPAREN RPAREN compound_statement\n",line_count);
			(yyval)->setName((yyvsp[-5])->getName()+" "+(yyvsp[-4])->getName()+" "+(yyvsp[-3])->getName()+" "+(yyvsp[-2])->getName()+" "+(yyvsp[0])->getName());
			//fprintf(fp2,"%s\n\n",$$->getName().c_str());

			if(error_count==0)
			{
				(yyval)->code=(yyvsp[-4])->getName()+" PROC\n";
				if((yyvsp[-4])->getName()=="main")
				{
					(yyval)->code+="\tMOV AX,@DATA\n\tMOV DS,AX \n"+(yyvsp[0])->code+"Return_"+current_function+":\n\tMOV AH,4CH\n\tINT 21H\nEND MAIN\n";
				}
				else
				{
					/*for(i=0;i<table->Lookup(current_function)->variableNames.size();i++)
					{
						$$->code+="\tPUSH "+table->Lookup(current_function)->variableNames[i]+"\n";
					}*/
					(yyval)->code+="\tPUSH AX\n\tPUSH BX \n\tPUSH CX \n\tPUSH DX\n";
					(yyval)->code+=(yyvsp[0])->code;
					(yyval)->code+="Return_"+current_function+":\n";
					(yyval)->code+="\tPOP DX\n\tPOP CX\n\tPOP BX\n\tPOP AX\n";
					/*for(i=table->Lookup(current_function)->variableNames.size()-1;i>=0;i--)
					{
						$$->code+="\tPOP "+table->Lookup(current_function)->variableNames[i]+"\n";
					}*/
					(yyval)->code+="\tret\n";
					(yyval)->code+=(yyvsp[-4])->getName()+" ENDP\n";
				}
				parameterNames.clear();
			}
			else
			{
				parameterNames.clear();
			}
			//current_function="";
			
		}
#line 1843 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 506 "1605042.y" /* yacc.c:1646  */
    {
		//fprintf(fp2,"At line No %d parameter_list  : parameter_list COMMA type_specifier ID\n",line_count);
		(yyval)->setName((yyvsp[-3])->getName()+" "+(yyvsp[-2])->getName()+" "+(yyvsp[-1])->getName()+" "+(yyvsp[0])->getName());
		//fprintf(fp2,"%s\n\n",$$->getName().c_str());
		parameterList.push_back((yyvsp[-1])->getType());
		parameterNames.push_back(make_pair((yyvsp[-1])->getType(),(yyvsp[0])->getName()));
	}
#line 1855 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 514 "1605042.y" /* yacc.c:1646  */
    {
			//fprintf(fp2,"At line No %d parameter_list  : parameter_list COMMA type_specifier\n",line_count);
			(yyval)->setName((yyvsp[-2])->getName()+" "+(yyvsp[-1])->getName()+" "+(yyvsp[0])->getName());
			//fprintf(fp2,"%s\n\n",$$->getName().c_str());
			parameterList.push_back((yyvsp[0])->getType());
		}
#line 1866 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 521 "1605042.y" /* yacc.c:1646  */
    {
			// fprintf(fp2,"At line No %d parameter_list  : type_specifier ID\n",line_count);
			 (yyval)->setName((yyvsp[-1])->getName()+" "+(yyvsp[0])->getName());
			//fprintf(fp2,"%s\n\n",$$->getName().c_str());
			parameterList.push_back((yyvsp[-1])->getType());
			parameterNames.push_back(make_pair((yyvsp[-1])->getType(),(yyvsp[0])->getName()));
			}
#line 1878 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 529 "1605042.y" /* yacc.c:1646  */
    {
				//fprintf(fp2,"At line No %d parameter_list  : type_specifier\n",line_count);
				(yyval)->setName((yyvsp[0])->getName());
				//fprintf(fp2,"%s\n\n",$$->getName().c_str());
				parameterList.push_back((yyvsp[0])->getType());
			}
#line 1889 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 538 "1605042.y" /* yacc.c:1646  */
    {table->EnterScope(11);
for(i=0;i<parameterNames.size();i++)
{
	table->Insert(parameterNames[i].second,"ID");
	table->Lookup(parameterNames[i].second)->data_type=parameterNames[i].first;
	table->Lookup(parameterNames[i].second)->Symbol=Symbolmaker(parameterNames[i].second,table->currentScope->id);
	parameterNames[i].second=Symbolmaker(parameterNames[i].second,table->currentScope->id);
}
}
#line 1903 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 547 "1605042.y" /* yacc.c:1646  */
    {
		//fprintf(fp2,"At line No %d compound_statement : LCURL statements RCURL\n",line_count);
		(yyval)->setName((yyvsp[-3])->getName()+" "+(yyvsp[-1])->getName()+" "+(yyvsp[0])->getName());
		//fprintf(fp2,"%s\n\n",$$->getName().c_str());
		(yyval)->code=(yyvsp[-1])->code;
		table->ExitScope();
	}
#line 1915 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 554 "1605042.y" /* yacc.c:1646  */
    {table->EnterScope(11);
			 for(i=0;i<parameterNames.size();i++)
				{
					table->Insert(parameterNames[i].second,"ID");
					table->Lookup(parameterNames[i].second)->data_type=parameterNames[i].first;
					table->Lookup(parameterNames[i].second)->Symbol=Symbolmaker(parameterNames[i].second,table->currentScope->id);
					parameterNames[i].second=Symbolmaker(parameterNames[i].second,table->currentScope->id);
				}
			}
#line 1929 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 563 "1605042.y" /* yacc.c:1646  */
    {
				 //fprintf(fp2,"At line No %d compound_statement : LCURL RCURL	compound_statement\n",line_count);
				 (yyval)->setName((yyvsp[-2])->getName()+" "+(yyvsp[0])->getName());
				//fprintf(fp2,"%s\n\n",$$->getName().c_str());
				table->ExitScope();
			 }
#line 1940 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 569 "1605042.y" /* yacc.c:1646  */
    {yyerrok;}
#line 1946 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 573 "1605042.y" /* yacc.c:1646  */
    {
		while(!declarationList.empty())
		{
			table->Lookup(declarationList.back())->data_type=(yyvsp[-2])->getType();
			declarationList.pop_back();
		}
		//fprintf(fp2,"At line No %d var_declaration : type_specifier declaration_list SEMICOLON\n",line_count);
		(yyval)->setName((yyvsp[-2])->getName()+" "+(yyvsp[-1])->getName()+" "+(yyvsp[0])->getName());
		//fprintf(fp2,"%s\n\n",$$->getName().c_str());
	}
#line 1961 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 586 "1605042.y" /* yacc.c:1646  */
    {
		//fprintf(fp2,"At line No %d type_specifier	: INT\n",line_count);
		(yyval)->setName((yyvsp[0])->getName());
		(yyval)->setType("INT");
		//fprintf(fp2,"%s\n\n",$$->getName().c_str());
	}
#line 1972 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 593 "1605042.y" /* yacc.c:1646  */
    {
				// fprintf(fp2,"At line No %d type_specifier	:  FLOAT\n",line_count);
				 (yyval)->setName((yyvsp[0])->getName());
				 (yyval)->setType("FLOAT");
				//fprintf(fp2,"%s\n\n",$$->getName().c_str());
			}
#line 1983 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 600 "1605042.y" /* yacc.c:1646  */
    {
			// fprintf(fp2,"At line No %d type_specifier	: VOID\n",line_count);
			 (yyval)->setName((yyvsp[0])->getName());
			 (yyval)->setType("VOID");
				//fprintf(fp2,"%s\n\n",$$->getName().c_str());
		}
#line 1994 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 609 "1605042.y" /* yacc.c:1646  */
    {
		if(!table->Insert((yyvsp[0])->getName(),(yyvsp[0])->getType()))
		{
			fprintf(fp3,"Error at Line No %d : Multiple declaration of %s \n\n",line_count,(yyvsp[0])->getName().c_str());
			error_count++;
		}
		else
		{
			
			declarationList.push_back((yyvsp[0])->getName());
		}

		if(error_count==0)
		{
			variable_for_asm.push_back(Symbolmaker((yyvsp[0])->getName(),table->currentScope->id));
			if(current_function.compare("main")!=0 && current_function.compare("")!=0)
			{
				table->Lookup(current_function)->variableNames.push_back(Symbolmaker((yyvsp[0])->getName(),table->currentScope->id));
			}
			table->Lookup((yyvsp[0])->getName())->Symbol=Symbolmaker((yyvsp[0])->getName(),table->currentScope->id);
		}
		
		//fprintf(fp2,"At line No %d declaration_list : declaration_list COMMA ID\n",line_count);
		(yyval)->setName((yyvsp[-2])->getName()+" "+(yyvsp[-1])->getName()+" "+(yyvsp[0])->getName());
		//fprintf(fp2,"%s\n\n",$$->getName().c_str());
		
	}
#line 2026 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 637 "1605042.y" /* yacc.c:1646  */
    {
			    if(!table->Insert((yyvsp[-3])->getName(),(yyvsp[-3])->getType()))
				{
					fprintf(fp3,"Error at Line No %d : Multiple declaration of %s \n\n",line_count,(yyvsp[-3])->getName().c_str());
					error_count++;
				}
				else
				{
					table->Lookup((yyvsp[-3])->getName())->is_array=true;
					table->Lookup((yyvsp[-3])->getName())->array_size=atoi((yyvsp[-1])->getName().c_str());
					declarationList.push_back((yyvsp[-3])->getName());
					array_for_asm.push_back(make_pair(Symbolmaker((yyvsp[-3])->getName(),table->currentScope->id),(yyvsp[-1])->getName()));
					if(current_function.compare("main")!=0 && current_function.compare("")!=0)
					{
						table->Lookup(current_function)->variableNames.push_back(Symbolmaker((yyvsp[-3])->getName(),table->currentScope->id));
					}
					table->Lookup((yyvsp[-3])->getName())->Symbol=Symbolmaker((yyvsp[-3])->getName(),table->currentScope->id);
				}
			  // fprintf(fp2,"At line No %d declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD\n",line_count);
			   (yyval)->setName((yyvsp[-5])->getName()+" "+(yyvsp[-4])->getName()+" "+(yyvsp[-3])->getName()+" "+(yyvsp[-2])->getName()+" "+(yyvsp[-1])->getName()+" "+(yyvsp[0])->getName());
			//fprintf(fp2,"%s\n\n",$$->getName().c_str());
				

		   }
#line 2055 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 662 "1605042.y" /* yacc.c:1646  */
    {
			   if(!table->Insert((yyvsp[0])->getName(),(yyvsp[0])->getType()))
			   {
				   fprintf(fp3,"Error at Line No %d : Multiple declaration of %s \n\n",line_count,(yyvsp[0])->getName().c_str());
					error_count++;
			   }
			   else
			   {
				   declarationList.push_back((yyvsp[0])->getName());
			   }

			   if(error_count==0)
				{
					variable_for_asm.push_back(Symbolmaker((yyvsp[0])->getName(),table->currentScope->id));
					if(current_function.compare("main")!=0 && current_function.compare("")!=0)
					{
						table->Lookup(current_function)->variableNames.push_back(Symbolmaker((yyvsp[0])->getName(),table->currentScope->id));
					}
					table->Lookup((yyvsp[0])->getName())->Symbol=Symbolmaker((yyvsp[0])->getName(),table->currentScope->id);
				}
				
			  // fprintf(fp2,"At line No %d declaration_list : ID\n",line_count);
			   (yyval)->setName((yyvsp[0])->getName());
				//fprintf(fp2,"%s\n\n",$$->getName().c_str());
		   }
#line 2085 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 688 "1605042.y" /* yacc.c:1646  */
    {
			   if(!table->Insert((yyvsp[-3])->getName(),(yyvsp[-3])->getType()))
			   {
				   fprintf(fp3,"Error at Line No %d : Multiple declaration of %s \n\n",line_count,(yyvsp[-3])->getName().c_str());
					error_count++;
			   }
			   else
			   {
				    table->Lookup((yyvsp[-3])->getName())->is_array=true;
					table->Lookup((yyvsp[-3])->getName())->array_size=atoi((yyvsp[-1])->getName().c_str());
					declarationList.push_back((yyvsp[-3])->getName());
					array_for_asm.push_back(make_pair(Symbolmaker((yyvsp[-3])->getName(),table->currentScope->id),(yyvsp[-1])->getName()));
					if(current_function.compare("main")!=0 && current_function.compare("")!=0)
					{
						table->Lookup(current_function)->variableNames.push_back(Symbolmaker((yyvsp[-3])->getName(),table->currentScope->id));
					}
					table->Lookup((yyvsp[-3])->getName())->Symbol=Symbolmaker((yyvsp[-3])->getName(),table->currentScope->id);
			   }
				
			  // fprintf(fp2,"At line No %d declaration_list :ID LTHIRD CONST_INT RTHIRD\n",line_count);
			   (yyval)->setName((yyvsp[-3])->getName()+" "+(yyvsp[-2])->getName()+" "+(yyvsp[-1])->getName()+" "+(yyvsp[0])->getName());
				//fprintf(fp2,"%s\n\n",$$->getName().c_str());
				
				
		   }
#line 2115 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 716 "1605042.y" /* yacc.c:1646  */
    {
	//fprintf(fp2,"At line No %d statements : statement\n",line_count);
	(yyval)->setName((yyvsp[0])->getName());
	//fprintf(fp2,"%s\n\n",$$->getName().c_str());

	if(error_count==0)
	{
		(yyval)->code=(yyvsp[0])->code;
	}
	}
#line 2130 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 727 "1605042.y" /* yacc.c:1646  */
    {
		   //fprintf(fp2,"At line No %d statements : statements statement\n",line_count);
	   		(yyval)->setName((yyvsp[-1])->getName()+" "+(yyvsp[0])->getName());
			//fprintf(fp2,"%s\n\n",$$->getName().c_str());

			if(error_count==0)
		{
			(yyval)->code=(yyvsp[-1])->code+(yyvsp[0])->code;
		}
			}
#line 2145 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 739 "1605042.y" /* yacc.c:1646  */
    {
							//fprintf(fp2,"At line No %d statement : var_declaration\n",line_count);
							(yyval)->setName((yyvsp[0])->getName());
							//fprintf(fp2,"%s\n\n",$$->getName().c_str());
							}
#line 2155 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 744 "1605042.y" /* yacc.c:1646  */
    {
		  						//fprintf(fp2,"At line No %d statement : expression_statement\n",line_count);
	  							(yyval)->setName((yyvsp[0])->getName());
								//fprintf(fp2,"%s\n\n",$$->getName().c_str());
								
								if(error_count==0)
								{
									(yyval)->code=(yyvsp[0])->code;
									(yyval)->Symbol=(yyvsp[0])->Symbol;
									(yyval)->setType((yyvsp[0])->getType());
								}
							}
#line 2172 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 756 "1605042.y" /* yacc.c:1646  */
    {
		  					//fprintf(fp2,"At line No %d statement : compound_statement\n",line_count);
	  						(yyval)->setName((yyvsp[0])->getName());
							//fprintf(fp2,"%s\n\n",$$->getName().c_str());
							
							if(error_count==0)
								{
									(yyval)->code=(yyvsp[0])->code;
									(yyval)->Symbol=(yyvsp[0])->Symbol;
									(yyval)->setType((yyvsp[0])->getType());
								}
							}
#line 2189 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 769 "1605042.y" /* yacc.c:1646  */
    {
		 // fprintf(fp2,"At line No %d statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement\n",line_count);
	  	(yyval)->setName((yyvsp[-6])->getName()+" "+(yyvsp[-5])->getName()+" "+(yyvsp[-4])->getName()+" "+(yyvsp[-3])->getName()+" "+(yyvsp[-2])->getName()+" "+(yyvsp[-1])->getName()+" "+(yyvsp[0])->getName());
		//fprintf(fp2,"%s\n\n",$$->getName().c_str());

		if(error_count==0)
		{
			(yyval)->code=(yyvsp[-4])->code;
			char *label1=newLabel();
			char *label2=newLabel();
			(yyval)->code+=string(label1)+":\n";
			(yyval)->code+=(yyvsp[-3])->code;
			(yyval)->code+="\tMOV AX,"+(yyvsp[-3])->Symbol+"\n";
			(yyval)->code+="\tCMP AX,0\n";
			(yyval)->code+="\tJE "+string(label2)+"\n";
			(yyval)->code+=(yyvsp[0])->code;
			(yyval)->code+=(yyvsp[-2])->code;
			(yyval)->code+="\tJMP "+string(label1)+"\n";
			(yyval)->code+=string(label2)+":\n";
		}
	}
#line 2215 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 791 "1605042.y" /* yacc.c:1646  */
    {
		 // fprintf(fp2,"At line No %d statement : IF LPAREN expression RPAREN statement\n",line_count);
	  		(yyval)->setName((yyvsp[-4])->getName()+" "+(yyvsp[-3])->getName()+" "+(yyvsp[-2])->getName()+" "+(yyvsp[-1])->getName()+" "+(yyvsp[0])->getName());
			//fprintf(fp2,"%s\n\n",$$->getName().c_str());

			if(error_count==0)
			{
				(yyval)->code=(yyvsp[-2])->code;
				char *label=newLabel();
				(yyval)->code+="\tMOV AX,"+(yyvsp[-2])->Symbol+"\n";
				(yyval)->code+="\tCMP AX,0\n";
				(yyval)->code+="\tJE "+string(label)+"\n";
				(yyval)->code+=(yyvsp[0])->code;
				(yyval)->code+=string(label)+":\n";
			}
		}
#line 2236 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 808 "1605042.y" /* yacc.c:1646  */
    {
		  														//fprintf(fp2,"At line No %d statement : IF LPAREN expression RPAREN statement ELSE statement\n",line_count);
	  															(yyval)->setName((yyvsp[-6])->getName()+" "+(yyvsp[-5])->getName()+" "+(yyvsp[-4])->getName()+" "+(yyvsp[-3])->getName()+" "+(yyvsp[-2])->getName()+" "+(yyvsp[-1])->getName()+" "+(yyvsp[0])->getName());
																//fprintf(fp2,"%s\n\n",$$->getName().c_str());

																if(error_count==0)
																{
																	(yyval)->code=(yyvsp[-4])->code;
																	char *label1=newLabel();
																	char *label2=newLabel();
																	(yyval)->code+="\tMOV AX,"+(yyvsp[-4])->Symbol+"\n";
																	(yyval)->code+="\tCMP AX, 0\n";
																	(yyval)->code+="\tJE "+string(label1)+"\n";
																	(yyval)->code+=(yyvsp[-2])->code;
																	(yyval)->code+="\tJMP "+string(label2)+"\n";
																	(yyval)->code+=string(label1)+":\n";
																	(yyval)->code+=(yyvsp[0])->code;
																	(yyval)->code+=string(label2)+":\n";
																}
															}
#line 2261 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 829 "1605042.y" /* yacc.c:1646  */
    {
													// fprintf(fp2,"At line No %d statement : WHILE LPAREN expression RPAREN statement\n",line_count);
	  												(yyval)->setName((yyvsp[-4])->getName()+" "+(yyvsp[-3])->getName()+" "+(yyvsp[-2])->getName()+" "+(yyvsp[-1])->getName()+" "+(yyvsp[0])->getName());
													//fprintf(fp2,"%s\n\n",$$->getName().c_str());
													
													if(error_count==0)
													{
														char *label1=newLabel();
														char *label2=newLabel();
														(yyval)->code+=string(label1)+":\n";
														(yyval)->code+=(yyvsp[-2])->code;
														(yyval)->code+="\tMOV AX,"+(yyvsp[-2])->Symbol+"\n";
														(yyval)->code+="\tCMP AX,0\n";
														(yyval)->code+="\tJE "+string(label2)+"\n";
														(yyval)->code+=(yyvsp[0])->code;
														(yyval)->code+="\tJMP "+string(label1)+"\n";
														(yyval)->code+=string(label2)+":\n";
													}
												}
#line 2285 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 849 "1605042.y" /* yacc.c:1646  */
    {
		  	 if(table->Lookup((yyvsp[-2])->getName())==0)
			   {
				   fprintf(fp3,"Error at Line No %d : Undeclared Variable : %s \n\n",line_count,(yyvsp[-2])->getName().c_str());
				   error_count++;
			   }
		    //fprintf(fp2,"At line No %d statement : PRINTLN LPAREN ID RPAREN SEMICOLON\n",line_count);
	  		(yyval)->setName((yyvsp[-4])->getName()+" "+(yyvsp[-3])->getName()+" "+(yyvsp[-2])->getName()+" "+(yyvsp[-1])->getName()+" "+(yyvsp[0])->getName());
			//fprintf(fp2,"%s\n\n",$$->getName().c_str());

			if(error_count==0)
			{
				(yyval)->code+="\tMOV AX,"+table->Lookup((yyvsp[-2])->getName())->Symbol+"\n";
				(yyval)->code+="\tCALL DISPLAY\n";
			}
		}
#line 2306 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 866 "1605042.y" /* yacc.c:1646  */
    {
		  if(!returnList.empty())
		  {
			  if((yyvsp[-1])->data_type!=returnList.back())
			  {
				  if(!(((yyvsp[-1])->data_type=="INT")&&(returnList.back()=="FLOAT")))
				  {
					  fprintf(fp3,"Error at Line No %d : Return type doesn't match with declaration \n\n",line_count);
						error_count++;
						returnList.pop_back();

				  }
			  }
			  else
			  {
				  returnList.pop_back();
			  }
		  }
		 // fprintf(fp2,"At line No %d statement : RETURN expression SEMICOLON\n",line_count);
	  		(yyval)->setName((yyvsp[-2])->getName()+" "+(yyvsp[-1])->getName()+" "+(yyvsp[0])->getName());
			//fprintf(fp2,"%s\n\n",$$->getName().c_str());

			if(error_count==0)
			{
				(yyval)->code=(yyvsp[-1])->code;
				(yyval)->code+="\tMOV AX,"+(yyvsp[-1])->Symbol+"\n";
				(yyval)->code+="\tMOV "+current_function+"_return"+",AX\n";
				(yyval)->code+="\tJMP Return_"+current_function+"\n";
			}
		}
#line 2341 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 896 "1605042.y" /* yacc.c:1646  */
    {yyerrok;}
#line 2347 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 899 "1605042.y" /* yacc.c:1646  */
    {
										//fprintf(fp2,"At line No %d expression_statement 	: SEMICOLON\n",line_count);
										(yyval)->setName((yyvsp[0])->getName());
										//fprintf(fp2,"%s\n\n",$$->getName().c_str());
										if(error_count==0)
										{
											(yyval)->code="";
										}
										}
#line 2361 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 909 "1605042.y" /* yacc.c:1646  */
    {
				(yyval)->data_type=(yyvsp[-1])->data_type;
				//fprintf(fp2,"At line No %d expression_statement 	: expression SEMICOLON\n",line_count);
				(yyval)->setName((yyvsp[-1])->getName()+" "+(yyvsp[0])->getName());
				//fprintf(fp2,"%s\n\n",$$->getName().c_str());

				if(error_count==0)
				{
					(yyval)->code=(yyvsp[-1])->code;
					(yyval)->Symbol=(yyvsp[-1])->Symbol;
					(yyval)->setType((yyvsp[-1])->getType());
				}
				
			}
#line 2380 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 925 "1605042.y" /* yacc.c:1646  */
    {
					string tt=(yyvsp[0])->getName();
					if(table->Lookup((yyvsp[0])->getName())==0)
					{
						fprintf(fp3,"Error at Line No %d : Undeclared variable :  %s \n\n",line_count,(yyvsp[0])->getName().c_str());
						error_count++;
					}
					else
					{
						(yyval)->data_type=table->Lookup((yyvsp[0])->getName())->data_type;
						if(table->Lookup((yyvsp[0])->getName())->is_array)
						{
							fprintf(fp3,"Error at Line No %d : Type mismatch\n\n",line_count);
							error_count++;
						}

						else if(error_count==0)
						{
							(yyval)->Symbol=table->Lookup(tt)->Symbol;
						}
					}
					//fprintf(fp2,"At line No %d variable : ID \n",line_count);
					(yyval)->setName((yyvsp[0])->getName());
					//fprintf(fp2,"%s\n\n",$$->getName().c_str());

					if(error_count==0)
					{
						(yyval)->setType("notarray");
						(yyval)->code="";
						
					}
					
				}
#line 2418 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 958 "1605042.y" /* yacc.c:1646  */
    {
		 							string tt=(yyvsp[-3])->getName();
		 							if(table->Lookup((yyvsp[-3])->getName())==0)
									{
										fprintf(fp3,"Error at Line No %d : Variable %s is  not declared in this scope\n\n",line_count,(yyvsp[-3])->getName().c_str());
										error_count++;
									}
									else if(!(table->Lookup((yyvsp[-3])->getName())->is_array))
									 {
										 fprintf(fp3,"Error at Line No %d : Variable %s is not an array\n\n",line_count,(yyvsp[-3])->getName().c_str());
										 error_count++;
									 }
		 							else if((yyvsp[-1])->data_type!="INT")
									 {
										fprintf(fp3,"Error at Line No %d : Non-integer Array Index \n\n",line_count);	
										error_count++; 
									 }
									 if(table->Lookup((yyvsp[-3])->getName())!=0)
									 {
										(yyval)->data_type=table->Lookup((yyvsp[-3])->getName())->data_type;
										(yyval)->is_array=true;
									 }
									if(error_count==0)
									{
										(yyval)->setType("array");
										(yyval)->Symbol=table->Lookup(tt)->Symbol;
										(yyval)->code=(yyvsp[-1])->code+"MOV BX," +(yyvsp[-1])->Symbol +"\nADD BX, BX\n";
									}
									//fprintf(fp2,"At line No %d variable : ID LTHIRD expression RTHIRD\n",line_count);
	 								(yyval)->setName((yyvsp[-3])->getName()+" "+(yyvsp[-2])->getName()+" "+(yyvsp[-1])->getName()+" "+(yyvsp[0])->getName());
									//fprintf(fp2,"%s\n\n",$$->getName().c_str());
										
								}
#line 2456 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 993 "1605042.y" /* yacc.c:1646  */
    {
	 							(yyval)->data_type=(yyvsp[0])->data_type;
	 							//fprintf(fp2,"At line No %d expression : logic_expression\n",line_count);
 								(yyval)->setName((yyvsp[0])->getName());
								//fprintf(fp2,"%s\n\n",$$->getName().c_str());
								if(error_count==0)
								{
									(yyval)->code=(yyvsp[0])->code;
									(yyval)->Symbol=(yyvsp[0])->Symbol;
									(yyval)->setType((yyvsp[0])->getType());
								}
							}
#line 2473 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 1006 "1605042.y" /* yacc.c:1646  */
    {
		   if((yyvsp[-2])->data_type!=(yyvsp[0])->data_type)
		   {
			   if((yyvsp[-2])->data_type=="FLOAT"&&(yyvsp[0])->data_type=="INT")
				{
					(yyval)->data_type="FLOAT";
				}
				else if((yyvsp[-2])->data_type=="INT"&&(yyvsp[0])->data_type=="FLOAT")
				{
					fprintf(fp3,"Error at Line No %d : Type Mismatch\n\n",line_count);
					   error_count++;
				}
				else if((yyvsp[-2])->data_type==""||(yyvsp[0])->data_type=="")
				{

				}
				else
				{
			   		fprintf(fp3,"Error at Line No %d : Two operands of assign operator doesn't match\n\n",line_count);
					   error_count++;
				}
		   }
		   else
		   {
			   (yyval)->data_type=(yyvsp[-2])->data_type;
		   }
		  // fprintf(fp2,"At line No %d expression : variable ASSIGNOP logic_expression\n",line_count);
	   		(yyval)->setName((yyvsp[-2])->getName()+" "+(yyvsp[-1])->getName()+" "+(yyvsp[0])->getName());
			//fprintf(fp2,"%s\n\n",$$->getName().c_str());

			if(error_count==0)
			{
				(yyval)->code=(yyvsp[0])->code+(yyvsp[-2])->code;
				(yyval)->Symbol=(yyvsp[-2])->Symbol;
				(yyval)->setType((yyvsp[-2])->getType());
				(yyval)->code+="\tMOV AX,"+(yyvsp[0])->Symbol+"\n";
				if((yyval)->getType()=="array")
				{
					(yyval)->code+= "\tMOV  "+(yyvsp[-2])->Symbol+"[BX],AX\n";
				}
				else
				{
					(yyval)->code+= "\tMOV "+(yyvsp[-2])->Symbol+",AX\n";
				}
				
			}
		}
#line 2525 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 1056 "1605042.y" /* yacc.c:1646  */
    {
		(yyval)->is_array=(yyvsp[0])->is_array;
		(yyval)->data_type=(yyvsp[0])->data_type;
		//fprintf(fp2,"At line No %d logic_expression : rel_expression\n",line_count);
		(yyval)->setName((yyvsp[0])->getName());
		//fprintf(fp2,"%s\n\n",$$->getName().c_str());

		if(error_count==0)
		{
			(yyval)->code=(yyvsp[0])->code;
			(yyval)->Symbol=(yyvsp[0])->Symbol;
			(yyval)->setType((yyvsp[0])->getType());
		}
	}
#line 2544 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 1071 "1605042.y" /* yacc.c:1646  */
    {
			(yyval)->data_type="INT";
			//fprintf(fp2,"At line No %d logic_expression : rel_expression LOGICOP rel_expression\n",line_count);
		 	(yyval)->setName((yyvsp[-2])->getName()+" "+(yyvsp[-1])->getName()+" "+(yyvsp[0])->getName());
			//fprintf(fp2,"%s\n\n",$$->getName().c_str());

			if(error_count==0)
			{
				(yyval)->code=(yyvsp[-2])->code;
				(yyval)->code+=(yyvsp[0])->code;
				char *temp=newTemp();
				
				(yyval)->Symbol=string(temp);
				variable_for_asm.push_back((yyval)->Symbol);
				if(current_function.compare("main")!=0 && current_function.compare("")!=0)
				{
					table->Lookup(current_function)->variableNames.push_back((yyval)->Symbol);
				}
				char *label1=newLabel();
				char *label2=newLabel();
				if((yyvsp[-1])->getName()=="&&"){
					(yyval)->code+="\tMOV AX,"+(yyvsp[-2])->Symbol+"\n";
					(yyval)->code+="\tCMP AX,0\n";
					(yyval)->code+="\tJE "+string(label1)+"\n";
					(yyval)->code+="\tMOV AX,"+(yyvsp[0])->Symbol+"\n";
					(yyval)->code+="\tCMP AX,0\n";
					(yyval)->code+="\tJE "+string(label1)+"\n";
					(yyval)->code+="\tMOV "+(yyval)->Symbol+",1\n";
					(yyval)->code+="\tJMP "+string(label2)+"\n";
					(yyval)->code+=string(label1)+":\n";
					(yyval)->code+="\tMOV "+(yyval)->Symbol+",0\n";		
					(yyval)->code+=string(label2)+":\n";

				}
				else if((yyvsp[-1])->getName()=="||"){
					(yyval)->code+="\tMOV AX,"+(yyvsp[-2])->Symbol+"\n";
					(yyval)->code+="\tCMP AX,1\n";
					(yyval)->code+="\tJE "+string(label1)+"\n";
					(yyval)->code+="\tMOV AX,"+(yyvsp[0])->Symbol+"\n";
					(yyval)->code+="\tCMP AX,1\n";
					(yyval)->code+="\tJE "+string(label1)+"\n";
					(yyval)->code+="\tMOV "+(yyval)->Symbol+",0\n";
					(yyval)->code+="\tJMP "+string(label2)+"\n";
					(yyval)->code+=string(label1)+":\n";
					(yyval)->code+="\tMOV "+(yyval)->Symbol+",1\n";		
					(yyval)->code+=string(label2)+":\n";

				}
			}
		}
#line 2599 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 1124 "1605042.y" /* yacc.c:1646  */
    {
		(yyval)->is_array=(yyvsp[0])->is_array;
		(yyval)->data_type=(yyvsp[0])->data_type;
		//fprintf(fp2,"At line No %d rel_expression	: simple_expression\n",line_count);
		(yyval)->setName((yyvsp[0])->getName());
		//fprintf(fp2,"%s\n\n",$$->getName().c_str());

		if(error_count==0)
		{
			(yyval)->code=(yyvsp[0])->code;
			(yyval)->Symbol=(yyvsp[0])->Symbol;
			(yyval)->setType((yyvsp[0])->getType());
		}
		}
#line 2618 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 1139 "1605042.y" /* yacc.c:1646  */
    {
			(yyval)->data_type="INT";
			//fprintf(fp2,"At line No %d rel_expression	: simple_expression RELOP simple_expression\n",line_count);
			(yyval)->setName((yyvsp[-2])->getName()+" "+(yyvsp[-1])->getName()+" "+(yyvsp[0])->getName());
			//fprintf(fp2,"%s\n\n",$$->getName().c_str());

			if(error_count==0)
			{
				(yyval)->code=(yyvsp[-2])->code;
				(yyval)->code+=(yyvsp[0])->code;
				(yyval)->code+="\tMOV AX," + (yyvsp[-2])->Symbol+"\n";
				(yyval)->code+="\tCMP AX," + (yyvsp[0])->Symbol+"\n";
				char *temp=newTemp();
				char *label1=newLabel();
				char *label2=newLabel();
				if((yyvsp[-1])->getName()=="<")
				{
					(yyval)->code+="\tJL " + string(label1)+"\n";
				}
				else if((yyvsp[-1])->getName()=="<=")
				{
					(yyval)->code+="\tJLE " + string(label1)+"\n";
				}
				else if((yyvsp[-1])->getName()==">")
				{
					(yyval)->code+="\tJG " + string(label1)+"\n";
				}
				else if((yyvsp[-1])->getName()==">=")
				{
					(yyval)->code+="\tJGE " + string(label1)+"\n";
				}
				else if((yyvsp[-1])->getName()=="==")
				{
					(yyval)->code+="\tJE " + string(label1)+"\n";
				}
				else if((yyvsp[-1])->getName()=="!=")
				{
					(yyval)->code+="\tJNE " + string(label1)+"\n";
				}
				(yyval)->code+="\tMOV "+string(temp) +",0\n";
				(yyval)->code+="\tJMP "+string(label2) +"\n";
				(yyval)->code+=string(label1)+":\n\tMOV "+string(temp)+",1\n";
				(yyval)->code+=string(label2)+":\n";
				(yyval)->Symbol=string(temp);
				variable_for_asm.push_back((yyval)->Symbol);
				if(current_function.compare("main")!=0 && current_function.compare("")!=0)
				{
					table->Lookup(current_function)->variableNames.push_back((yyval)->Symbol);
				}
			}
		}
#line 2674 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 1192 "1605042.y" /* yacc.c:1646  */
    {
								(yyval)->is_array=(yyvsp[0])->is_array;
								(yyval)->data_type=(yyvsp[0])->data_type;
								//fprintf(fp2,"At line No %d simple_expression : term \n",line_count);
								(yyval)->setName((yyvsp[0])->getName());
								//fprintf(fp2,"%s\n\n",$$->getName().c_str());

								if(error_count==0)
								{
									(yyval)->code=(yyvsp[0])->code;
									(yyval)->Symbol=(yyvsp[0])->Symbol;
									(yyval)->setType((yyvsp[0])->getType());
								}							
							}
#line 2693 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 1206 "1605042.y" /* yacc.c:1646  */
    {
			if((yyvsp[-2])->data_type!=(yyvsp[0])->data_type)
			{
				if(((yyvsp[-2])->data_type=="INT"&&(yyvsp[0])->data_type=="FLOAT")||((yyvsp[-2])->data_type=="FLOAT"&&(yyvsp[0])->data_type=="INT"))
				{
					(yyval)->data_type="FLOAT";
				}
			}
			else{(yyval)->data_type=(yyvsp[-2])->data_type;}
			//fprintf(fp2,"At line No %d simple_expression : simple_expression ADDOP term \n",line_count);
		  	(yyval)->setName((yyvsp[-2])->getName()+" "+(yyvsp[-1])->getName()+" "+(yyvsp[0])->getName());
			//fprintf(fp2,"%s\n\n",$$->getName().c_str());

			if(error_count==0)
			{
				(yyval)->code=(yyvsp[-2])->code;
				(yyval)->code+=(yyvsp[0])->code;
				char *temp=newTemp();
				(yyval)->code+="\tMOV AX,"+(yyvsp[-2])->Symbol+"\n";
				if((yyvsp[-1])->getName()=="+")
				{
					(yyval)->code+="\tADD AX,"+(yyvsp[0])->Symbol+"\n";
				}
				else
				{
					(yyval)->code+="\tSUB AX,"+(yyvsp[0])->Symbol+"\n";
				}
				(yyval)->code+="\tMOV "+string(temp)+",AX\n";
				(yyval)->Symbol=string(temp);
				variable_for_asm.push_back((yyval)->Symbol);
				if(current_function.compare("main")!=0 && current_function.compare("")!=0)
				{
					table->Lookup(current_function)->variableNames.push_back((yyval)->Symbol);
				}
			}
		}
#line 2734 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 1244 "1605042.y" /* yacc.c:1646  */
    {
							(yyval)->data_type=(yyvsp[0])->data_type;
							//fprintf(fp2,"At line No %d term :	unary_expression\n",line_count);
							(yyval)->setName((yyvsp[0])->getName());
							//fprintf(fp2,"%s\n\n",$$->getName().c_str());

							if(error_count==0)
								{
									(yyval)->code=(yyvsp[0])->code;
									(yyval)->Symbol=(yyvsp[0])->Symbol;
									(yyval)->setType((yyvsp[0])->getType());
								}	
							}
#line 2752 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 1258 "1605042.y" /* yacc.c:1646  */
    {
			if((yyvsp[-1])->getName()=="%")
			 {
				 if((yyvsp[-2])->data_type!="INT"||(yyvsp[0])->data_type!="INT")
				 {
					 fprintf(fp3,"Error at Line No %d : Non-integer operand on modulus operator\n\n",line_count);
					 error_count++;
				 }
			 }
			 else if((yyvsp[-2])->data_type!=(yyvsp[0])->data_type)
			 {
				 if(((yyvsp[-2])->data_type=="INT"&&(yyvsp[0])->data_type=="FLOAT")||((yyvsp[-2])->data_type=="FLOAT"&&(yyvsp[0])->data_type=="INT"))
				 {
					 (yyval)->data_type="FLOAT";
				 }
			 }
			 else{(yyval)->data_type=(yyvsp[-2])->data_type;}
		 	//fprintf(fp2,"At line No %d term :	term MULOP unary_expression\n",line_count);
	 		(yyval)->setName((yyvsp[-2])->getName()+" "+(yyvsp[-1])->getName()+" "+(yyvsp[0])->getName());
			//fprintf(fp2,"%s\n\n",$$->getName().c_str());

			if(error_count==0)
			{
				(yyval)->code=(yyvsp[-2])->code;
				(yyval)->code += (yyvsp[0])->code;
				(yyval)->code += "\tMOV AX,"+ (yyvsp[-2])->Symbol+"\n";
				(yyval)->code += "\tMOV BX,"+ (yyvsp[0])->Symbol+"\n";
				char *temp=newTemp();
				if((yyvsp[-1])->getName()=="*")
				{
					(yyval)->code += "\tMUL BX\n";
					(yyval)->code += "\tMOV "+ string(temp) + ",AX\n";
				}
				else if((yyvsp[-1])->getName()=="/")
				{
					(yyval)->code += "\tMOV DX,0\n";
					(yyval)->code += "\tDIV BX\n";
					(yyval)->code += "\tMOV "+ string(temp) + ",AX\n";
				}
				else
				{
					(yyval)->code += "\tMOV DX,0\n";
					(yyval)->code += "\tDIV BX\n";
					(yyval)->code += "\tMOV "+ string(temp) + ",DX\n";
				}
				(yyval)->Symbol=string(temp);
				variable_for_asm.push_back((yyval)->Symbol);
				if(current_function.compare("main")!=0 && current_function.compare("")!=0)
				{
					table->Lookup(current_function)->variableNames.push_back((yyval)->Symbol);
				}
			}
			
		}
#line 2811 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 1314 "1605042.y" /* yacc.c:1646  */
    {
												string tt=(yyvsp[-1])->getName();
												(yyval)->data_type=(yyvsp[0])->data_type;
												//fprintf(fp2,"At line No %d unary_expression : ADDOP unary_expression\n",line_count);
												(yyval)->setName((yyvsp[-1])->getName()+" "+(yyvsp[0])->getName());
												//fprintf(fp2,"%s\n\n",$$->getName().c_str());

												if(error_count==0)
												{
													(yyval)->code=(yyvsp[0])->code;
													(yyval)->Symbol=(yyvsp[0])->Symbol;
													if(tt=="-")
													{
														(yyval)->Symbol="-"+(yyval)->Symbol;
													}
												}
											}
#line 2833 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 1331 "1605042.y" /* yacc.c:1646  */
    {
			 						(yyval)->data_type=(yyvsp[0])->data_type;
			 						//fprintf(fp2,"At line No %d unary_expression : NOT unary_expression\n",line_count);
		 							(yyval)->setName((yyvsp[-1])->getName()+" "+(yyvsp[0])->getName());
									//fprintf(fp2,"%s\n\n",$$->getName().c_str());

									if(error_count==0)
									{
										(yyval)->code=(yyvsp[0])->code;
										(yyval)->Symbol=(yyvsp[0])->Symbol;
										(yyval)->code+="\tMOV AX,"+(yyval)->Symbol+"\n";
										(yyval)->code+="\tNOT AX\n";
										(yyval)->code+="\tMOV "+(yyval)->Symbol+",AX\n";
									}
									
								}
#line 2854 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 1347 "1605042.y" /* yacc.c:1646  */
    {
			 		(yyval)->is_array=(yyvsp[0])->is_array;
			 		(yyval)->data_type=(yyvsp[0])->data_type;
			 		//fprintf(fp2,"At line No %d unary_expression :factor\n",line_count);
		 			(yyval)->setName((yyvsp[0])->getName());
					//fprintf(fp2,"%s\n\n",$$->getName().c_str());
					
					if(error_count==0)
					{
						(yyval)->code=(yyvsp[0])->code;
						(yyval)->Symbol=(yyvsp[0])->Symbol;
						(yyval)->setType((yyvsp[0])->getType());
					}
				}
#line 2873 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 1363 "1605042.y" /* yacc.c:1646  */
    {
						(yyval)->is_array=(yyvsp[0])->is_array;
						(yyval)->data_type=(yyvsp[0])->data_type;
						//fprintf(fp2,"At line No %d factor	: variable\n",line_count);
						(yyval)->setName((yyvsp[0])->getName()); 
						//fprintf(fp2,"%s\n\n",$$->getName().c_str());

						if(error_count==0)
						{
							(yyval)->setType((yyvsp[0])->getType());
							(yyval)->code=(yyvsp[0])->code;
							if((yyval)->getType()=="notarray")
							{
								(yyval)->Symbol=(yyvsp[0])->Symbol;
							}
							else
							{
								char *temp= newTemp();
								(yyval)->code+="\tMOV AX," + (yyvsp[0])->Symbol + "[BX]\n";
								(yyval)->code+= "\tMOV " + string(temp) + ",AX\n";
								(yyval)->Symbol=string(temp);
								variable_for_asm.push_back((yyval)->Symbol);
								if(current_function.compare("main")!=0 && current_function.compare("")!=0)
								{
									table->Lookup(current_function)->variableNames.push_back((yyval)->Symbol);
								}
							}
						}
						

					}
#line 2909 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 1395 "1605042.y" /* yacc.c:1646  */
    {
		bool allIsWell=true;
		SymbolInfo *temp=table->Lookup((yyvsp[-3])->getName());
		if(temp==0)	
		{
			fprintf(fp3,"Error at Line No %d : Function is not defined\n\n",line_count);
			error_count++;
			allIsWell=false;
		}
		else if(!(temp->is_defined))
		{
			fprintf(fp3,"Error at Line No %d : Function is not defined\n\n",line_count);
			error_count++;
			allIsWell=false;
		}
		else if(!temp->is_function)
		{
			fprintf(fp3,"Error at Line No %d : %s is not a Function \n\n",line_count,(yyvsp[-3])->getName().c_str());
			error_count++;
			allIsWell=false;
		}
		else if(temp->parameter_list.size()!=(yyvsp[-1])->argumentList.size())
		{
			fprintf(fp3,"Error at Line No %d : Number of arguments doesn't match with defination\n\n",line_count);
			error_count++;
			allIsWell=false;
		}
		else if(temp->parameter_list.size()!=0)
		{
			for(i=0;i<temp->parameter_list.size();i++)
			{
				if(temp->parameter_list[i]!=(yyvsp[-1])->argumentList[i])
				{
					if(!(temp->parameter_list[i]=="FLOAT"&&(yyvsp[-1])->argumentList[i]=="INT"))
					{
						fprintf(fp3,"Error at Line No %d : Argument doesn't match with defination \n\n",line_count,temp->parameter_list[i].c_str());
						allIsWell=false;
						error_count++;
						break;
					}
				}
			}
		}
		if(allIsWell)
		{
			(yyval)->data_type=table->Lookup((yyvsp[-3])->getName())->return_type;

		}
		

		if(error_count==0)
		{
			(yyval)->code=(yyvsp[-1])->code;
			if(current_function.compare("main")!=0)
			{
				for(i=0;i<table->Lookup((yyvsp[-3])->getName())->parameterNames.size();i++)
				{
					(yyval)->code+="\tPUSH "+table->Lookup((yyvsp[-3])->getName())->parameterNames[i]+"\n";
				}
				for(i=0;i<table->Lookup((yyvsp[-3])->getName())->variableNames.size();i++)
				{
					(yyval)->code+="\tPUSH "+table->Lookup((yyvsp[-3])->getName())->variableNames[i]+"\n";
				}
			}
			for(i=0;i<(yyvsp[-1])->argumentNames.size();i++)
			{
				(yyval)->code+="\tMOV AX,"+(yyvsp[-1])->argumentNames[i]+"\n";
				(yyval)->code+="\tMOV "+table->Lookup((yyvsp[-3])->getName())->parameterNames[i]+",AX\n";

			}
			(yyval)->code+="\tCALL "+(yyvsp[-3])->getName()+"\n";
			(yyval)->code+="\tMOV AX,"+(yyvsp[-3])->getName()+"_return\n";
			char *temp=newTemp();
			(yyval)->code+="\tMOV "+string(temp)+",AX\n";
			if(current_function.compare("main")!=0)
			{
				for(i=table->Lookup((yyvsp[-3])->getName())->variableNames.size()-1;i>=0;i--)
					{
						(yyval)->code+="\tPOP "+table->Lookup((yyvsp[-3])->getName())->variableNames[i]+"\n";
					}
					for(i=table->Lookup((yyvsp[-3])->getName())->parameterNames.size()-1;i>=0;i--)
					{
						(yyval)->code+="\tPOP "+table->Lookup((yyvsp[-3])->getName())->parameterNames[i]+"\n";
					}
			}
			(yyval)->Symbol=string(temp);
			variable_for_asm.push_back((yyval)->Symbol);
			if(current_function.compare("main")!=0 && current_function.compare("")!=0)
			{
				table->Lookup(current_function)->variableNames.push_back((yyval)->Symbol);
			}
		}

		//fprintf(fp2,"At line No %d factor	: ID LPAREN argument_list RPAREN\n",line_count);
	  	(yyval)->setName((yyvsp[-3])->getName()+" "+(yyvsp[-2])->getName()+" "+(yyvsp[-1])->getName()+" "+(yyvsp[0])->getName());
		//fprintf(fp2,"%s\n\n",$$->getName().c_str());

		
	}
#line 3013 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 1494 "1605042.y" /* yacc.c:1646  */
    {
		(yyval)->data_type=(yyvsp[-1])->data_type;
		//fprintf(fp2,"At line No %d factor	: LPAREN expression RPAREN\n",line_count);
		(yyval)->setName((yyvsp[-2])->getName()+" "+(yyvsp[-1])->getName()+" "+(yyvsp[0])->getName());
		//fprintf(fp2,"%s\n\n",$$->getName().c_str());

		if(error_count==0)
		{
			(yyval)->code=(yyvsp[-1])->code;
			(yyval)->Symbol=(yyvsp[-1])->Symbol;
			(yyval)->setType((yyvsp[-1])->getType());
		}
	}
#line 3031 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 1508 "1605042.y" /* yacc.c:1646  */
    {
					(yyval)->data_type="INT";
					//fprintf(fp2,"At line No %d factor	: CONST_INT\n",line_count);
					(yyval)->setName((yyvsp[0])->getName());
					//fprintf(fp2,"%s\n\n",$$->getName().c_str());

					if(error_count==0)
					{
						(yyval)->code="";
						(yyval)->Symbol=(yyvsp[0])->Symbol;
					}
					}
#line 3048 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 1520 "1605042.y" /* yacc.c:1646  */
    {
					(yyval)->data_type="FLOAT";
					//fprintf(fp2,"At line No %d factor	: CONST_FLOAT\n",line_count);
					(yyval)->setName((yyvsp[0])->getName()); 
					//fprintf(fp2,"%s\n\n",$$->getName().c_str());
					
					if(error_count==0)
					{
						(yyval)->code="";
						(yyval)->Symbol=(yyvsp[0])->Symbol;
					}
				}
#line 3065 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 1532 "1605042.y" /* yacc.c:1646  */
    {
						(yyval)->data_type=(yyvsp[-1])->data_type;
						//fprintf(fp2,"At line No %d factor	: variable INCOP\n",line_count);
						(yyval)->setName((yyvsp[-1])->getName()+" "+(yyvsp[0])->getName());
						//fprintf(fp2,"%s\n\n",$$->getName().c_str());

						if(error_count==0)
						{
							(yyval)->code="";
							char *temp=newTemp();
							if((yyvsp[-1])->getType()=="array")
							{
								(yyval)->code+="\tMOV AX,"+(yyvsp[-1])->Symbol+"[BX]\n";
								(yyval)->code+="\tMOV "+string(temp)+",AX\n";
								(yyval)->code+="\tINC AX\n";
								(yyval)->code+="\tMOV "+(yyvsp[-1])->Symbol+"[BX],AX\n";
							}
							else
							{
								(yyval)->code+="\tMOV AX,"+(yyvsp[-1])->Symbol+"\n";
								(yyval)->code+="\tMOV "+string(temp)+",AX\n";
								(yyval)->code+="\tINC "+(yyvsp[-1])->Symbol+"\n";
							}
							(yyval)->Symbol=string(temp);
							variable_for_asm.push_back((yyval)->Symbol);
							if(current_function.compare("main")!=0 && current_function.compare("")!=0)
							{
								table->Lookup(current_function)->variableNames.push_back((yyval)->Symbol);
							}
							
						}
					}
#line 3102 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 1564 "1605042.y" /* yacc.c:1646  */
    {
						(yyval)->data_type=(yyvsp[-1])->data_type;
						//fprintf(fp2,"At line No %d factor	: variable DECOP\n",line_count);
						(yyval)->setName((yyvsp[-1])->getName()+" "+(yyvsp[0])->getName());
						//fprintf(fp2,"%s\n\n",$$->getName().c_str());

						if(error_count==0)
						{
							(yyval)->code="";
							char *temp=newTemp();
							if((yyvsp[-1])->getType()=="array")
							{
								(yyval)->code+="\tMOV AX,"+(yyvsp[-1])->Symbol+"[BX]\n";
								(yyval)->code+="\tMOV "+string(temp)+",AX\n";
								(yyval)->code+="\tDEC AX\n";
								(yyval)->code+="\tMOV "+(yyvsp[-1])->Symbol+"[BX],AX\n";
							}
							else
							{
								(yyval)->code+="\tMOV AX,"+(yyvsp[-1])->Symbol+"\n";
								(yyval)->code+="\tMOV "+string(temp)+",AX\n";
								(yyval)->code+="\tDEC "+(yyvsp[-1])->Symbol+"\n";
							}
							(yyval)->Symbol=string(temp);
							variable_for_asm.push_back((yyval)->Symbol);
							if(current_function.compare("main")!=0 && current_function.compare("")!=0)
							{
								table->Lookup(current_function)->variableNames.push_back((yyval)->Symbol);
							}
							
						}
					}
#line 3139 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 1599 "1605042.y" /* yacc.c:1646  */
    {
	i=0;
	while(i<(yyvsp[0])->argumentList.size())
		{
			(yyval)->argumentList[i]=(yyvsp[0])->argumentList[i];
			if(error_count==0)
			{
				(yyval)->argumentNames[i]=(yyvsp[0])->argumentNames[i];
			}
			i++;
		}
	
	//fprintf(fp2,"At line No %d argument_list : arguments\n",line_count);
	(yyval)->setName((yyvsp[0])->getName());
	//fprintf(fp2,"%s\n\n",$$->getName().c_str());

	if(error_count==0)
	{
		(yyval)->code=(yyvsp[0])->code;
	}
}
#line 3165 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 1620 "1605042.y" /* yacc.c:1646  */
    {
				  //fprintf(fp2,"At line No %d argument_list : \n",line_count);
				  }
#line 3173 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 1626 "1605042.y" /* yacc.c:1646  */
    {
			
			i=0;
			while(i<(yyvsp[-2])->argumentList.size())
			{
				argument=(yyvsp[-2])->argumentList[i];
				(yyval)->argumentList[i]=argument;
				if(error_count==0)
				{
					argument=(yyvsp[-2])->argumentNames[i];
					(yyval)->argumentNames[i]=argument;
				}
				i++;
			}
			(yyval)->argumentList.push_back((yyvsp[0])->data_type);
			if(error_count==0)
			{
				(yyval)->argumentNames.push_back((yyvsp[0])->Symbol);
				(yyval)->code=(yyvsp[-2])->code+(yyvsp[0])->code;
			}
			//fprintf(fp2,"At line No %d arguments : arguments COMMA logic_expression\n",line_count);
			(yyval)->setName((yyvsp[-2])->getName()+" "+(yyvsp[-1])->getName()+" "+(yyvsp[0])->getName());
			//fprintf(fp2,"%s\n\n",$$->getName().c_str());
	}
#line 3202 "1605042.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 1652 "1605042.y" /* yacc.c:1646  */
    {
				(yyval)->argumentList.push_back((yyvsp[0])->data_type);
				if(error_count==0)
				{
					(yyval)->argumentNames.push_back((yyvsp[0])->Symbol);
					(yyval)->code=(yyvsp[0])->code;
				}
				//fprintf(fp2,"At line No %d arguments : logic_expression\n",line_count);
				(yyval)->setName((yyvsp[0])->getName()); 
				//fprintf(fp2,"%s\n\n",$$->getName().c_str());
				}
#line 3218 "1605042.tab.c" /* yacc.c:1646  */
    break;


#line 3222 "1605042.tab.c" /* yacc.c:1646  */
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
#line 1666 "1605042.y" /* yacc.c:1906  */

int main(int argc,char *argv[])
{

	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File.\n");
		exit(1);
	}
	
	//fp2= fopen(argv[2],"w");
	//fp3= fopen(argv[3],"w");
	fp3= fopen(argv[2],"w");
	table=new SymbolTable(11);

	yyin=fp;
	yyparse();
	//fprintf(fp2,"			Symbol Table\n\n");
	//table->PrintAll();
	fprintf(fp3,"Total Lines: %d \n",--line_count);
	fprintf(fp3,"Total Errors: %d \n",error_count);	
	//fprintf(fp2,"Total Errors: %d \n",error_count);	
	//fprintf(fp2,"Total Lines: %d \n",--line_count);	


	//fclose(fp2);
	fclose(fp3);
	
	return 0;
}

