/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
/* Tokens.  */
#define IF 258
#define ELSE 259
#define FOR 260
#define WHILE 261
#define ID 262
#define LPAREN 263
#define RPAREN 264
#define SEMICOLON 265
#define COMMA 266
#define LCURL 267
#define RCURL 268
#define INT 269
#define FLOAT 270
#define VOID 271
#define CONST_INT 272
#define LTHIRD 273
#define RTHIRD 274
#define PRINTLN 275
#define RETURN 276
#define NOT 277
#define CONST_FLOAT 278
#define INCOP 279
#define DECOP 280
#define ADDOP 281
#define MULOP 282
#define ASSIGNOP 283
#define LOGICOP 284
#define RELOP 285
#define LOWER_THAN_ELSE 286

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
