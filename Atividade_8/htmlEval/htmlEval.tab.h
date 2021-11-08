/* A Bison parser, made by GNU Bison 3.7.6.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_HTMLEVAL_TAB_H_INCLUDED
# define YY_YY_HTMLEVAL_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    DOCTYPE = 258,                 /* DOCTYPE  */
    IMAGE = 259,                   /* IMAGE  */
    ALT = 260,                     /* ALT  */
    WIDTH = 261,                   /* WIDTH  */
    HEIGHT = 262,                  /* HEIGHT  */
    GENERALTAGCLOSE = 263,         /* GENERALTAGCLOSE  */
    STRING = 264,                  /* STRING  */
    PARAGRAPH_O = 265,             /* PARAGRAPH_O  */
    PARAGRAPH_C = 266,             /* PARAGRAPH_C  */
    LINK_O = 267,                  /* LINK_O  */
    LINK_C = 268,                  /* LINK_C  */
    HEADER1_O = 269,               /* HEADER1_O  */
    HEADER1_C = 270,               /* HEADER1_C  */
    HEADER2_O = 271,               /* HEADER2_O  */
    HEADER2_C = 272,               /* HEADER2_C  */
    HEADER3_O = 273,               /* HEADER3_O  */
    HEADER3_C = 274,               /* HEADER3_C  */
    HEADER4_O = 275,               /* HEADER4_O  */
    HEADER4_C = 276,               /* HEADER4_C  */
    HEADER5_O = 277,               /* HEADER5_O  */
    HEADER5_C = 278,               /* HEADER5_C  */
    HEADER6_O = 279,               /* HEADER6_O  */
    HEADER6_C = 280,               /* HEADER6_C  */
    BODY_O = 281,                  /* BODY_O  */
    BODY_C = 282,                  /* BODY_C  */
    HTML_O = 283,                  /* HTML_O  */
    HTML_C = 284,                  /* HTML_C  */
    UL_LIST_O = 285,               /* UL_LIST_O  */
    UL_LIST_C = 286,               /* UL_LIST_C  */
    OL_LIST_O = 287,               /* OL_LIST_O  */
    OL_LIST_C = 288,               /* OL_LIST_C  */
    LIST_O = 289,                  /* LIST_O  */
    LIST_C = 290,                  /* LIST_C  */
    BUTTON_O = 291,                /* BUTTON_O  */
    BUTTON_C = 292                 /* BUTTON_C  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_HTMLEVAL_TAB_H_INCLUDED  */
