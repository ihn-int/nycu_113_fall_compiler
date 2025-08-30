/* A Bison parser, made by GNU Bison 3.8.2.  */

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

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
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
    COMMA = 258,                   /* COMMA  */
    SEMICOLON = 259,               /* SEMICOLON  */
    COLON = 260,                   /* COLON  */
    LEFT_PAREN = 261,              /* LEFT_PAREN  */
    RIGHT_PAREN = 262,             /* RIGHT_PAREN  */
    LEFT_BRACKET = 263,            /* LEFT_BRACKET  */
    RIGHT_BRACKET = 264,           /* RIGHT_BRACKET  */
    IDENTIFIER = 265,              /* IDENTIFIER  */
    DECIMAL = 266,                 /* DECIMAL  */
    OCTAL = 267,                   /* OCTAL  */
    FLOAT = 268,                   /* FLOAT  */
    SCIENTIFIC = 269,              /* SCIENTIFIC  */
    KW_VAR = 270,                  /* KW_VAR  */
    KW_DEF = 271,                  /* KW_DEF  */
    KW_ARRAY = 272,                /* KW_ARRAY  */
    KW_OF = 273,                   /* KW_OF  */
    KW_BOOL = 274,                 /* KW_BOOL  */
    KW_INT = 275,                  /* KW_INT  */
    KW_REAL = 276,                 /* KW_REAL  */
    KW_STR = 277,                  /* KW_STR  */
    KW_TRUE = 278,                 /* KW_TRUE  */
    KW_FALSE = 279,                /* KW_FALSE  */
    KW_WHILE = 280,                /* KW_WHILE  */
    KW_DO = 281,                   /* KW_DO  */
    KW_IF = 282,                   /* KW_IF  */
    KW_THEN = 283,                 /* KW_THEN  */
    KW_ELSE = 284,                 /* KW_ELSE  */
    KW_FOR = 285,                  /* KW_FOR  */
    KW_TO = 286,                   /* KW_TO  */
    KW_BEGIN = 287,                /* KW_BEGIN  */
    KW_END = 288,                  /* KW_END  */
    KW_PRINT = 289,                /* KW_PRINT  */
    KW_READ = 290,                 /* KW_READ  */
    KW_RETURN = 291,               /* KW_RETURN  */
    CHAR = 292,                    /* CHAR  */
    STRING = 293,                  /* STRING  */
    SPACE = 294,                   /* SPACE  */
    ASSIGNMENT = 295,              /* ASSIGNMENT  */
    OR = 296,                      /* OR  */
    AND = 297,                     /* AND  */
    NOT = 298,                     /* NOT  */
    LT = 299,                      /* LT  */
    GT = 300,                      /* GT  */
    EQ = 301,                      /* EQ  */
    LE = 302,                      /* LE  */
    GE = 303,                      /* GE  */
    NE = 304,                      /* NE  */
    ADD = 305,                     /* ADD  */
    SUB = 306,                     /* SUB  */
    MUL = 307,                     /* MUL  */
    DIV = 308,                     /* DIV  */
    MOD = 309,                     /* MOD  */
    NEG = 310                      /* NEG  */
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


#endif /* !YY_YY_PARSER_H_INCLUDED  */
