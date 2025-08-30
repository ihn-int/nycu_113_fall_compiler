%{
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
%}

/* delimeters */
%token COMMA SEMICOLON COLON LEFT_PAREN RIGHT_PAREN LEFT_BRACKET RIGHT_BRACKET

/* identifier */
%token IDENTIFIER

/* numbers */
%token DECIMAL OCTAL FLOAT SCIENTIFIC

/* keywords */
%token KW_VAR KW_DEF
%token KW_ARRAY KW_OF KW_BOOL KW_INT KW_REAL KW_STR
%token KW_TRUE KW_FALSE
%token KW_WHILE KW_DO KW_IF KW_THEN KW_ELSE KW_FOR KW_TO
%token KW_BEGIN KW_END
%token KW_PRINT KW_READ KW_RETURN

/* string and characters */
%token CHAR STRING SPACE

/* operators */
%right ASSIGNMENT
%left OR
%left AND
%right NOT
%nonassoc LT GT EQ LE GE NE
%left ADD SUB
%left MUL DIV MOD
%nonassoc NEG

/* type => nonterminal */

/* Program Units */
%type NT_PROGRAM
%type NT_DECLARATION_LIST_OPT
%type NT_DECLARATION_LIST
%type NT_FUNCTION_LIST_OPT
%type NT_FUNCTION_LIST

/* Functions */
%type NT_FUNCTION
%type NT_FUNCTION_DECLARATION
%type NT_FUNCTION_DEFINITION
%type NT_FUNCTION_HEADER
%type NT_FORMAL_ARG_LIST_OPT
%type NT_FORMAL_ARG_LIST
%type NT_FORMAL_ARG
%type NT_RETURN_TYPE

/* Declarations */
%type NT_DECLARATION
%type NT_VARIABLE_DECLARATION
%type NT_CONSTANT_DECLARATION

/* Identifier List */
%type NT_IDENTIFIER_LIST

/* Types */
%type NT_TYPE
%type NT_SCALAR_TYPE
%type NT_ARRAY_TYPE

/* Statements */
%type NT_STATEMENT
%type NT_SIMPLE_STATEMENT
%type NT_ASSIGNMENT
%type NT_PRINT_STATEMENT
%type NT_READ_STATEMENT
%type NT_CONDITIONAL_STATEMENT
%type NT_FUNCTION_CALL_STATEMENT
%type NT_LOOP_STATEMENT
%type NT_RETURN_STATEMENT
%type NT_COMPOUND_STATEMENT
%type NT_STATEMENT_LIST_OPT
%type NT_STATEMENT_LIST

/* Expressions */
%type NT_EXPRESSION
%type NT_LITERAL_CONSTANT
%type NT_VARIABLE_REFERENCE
%type NT_BRACKET_EXPRESSION_LIST_OPT
%type NT_BRACKET_EXPRESSION_LIST
%type NT_BRACKET_EXPRESSION
%type NT_FUNCTION_CALL
%type NT_EXPRESSION_LIST_OPT
%type NT_EXPRESSION_LIST
%type NT_BINARY_OPERATION
%type NT_RELATIONAL_OPERATOR
%type NT_UNARY_OPERATION

%type NT_INTEGER_LITERAL
%type NT_REAL_LITERAL
%type NT_STRING_LITERAL
%type NT_BOOLEAN_LITERAL

%%

/* Based on the syntactic definition */

/* Program Units */
NT_PROGRAM : IDENTIFIER SEMICOLON
             NT_DECLARATION_LIST_OPT
             NT_FUNCTION_LIST_OPT
             NT_COMPOUND_STATEMENT
             KW_END
            ;

NT_DECLARATION_LIST_OPT :
                        | NT_DECLARATION_LIST
                        ;
NT_DECLARATION_LIST : NT_DECLARATION NT_DECLARATION_LIST
                    | NT_DECLARATION
                    ;

NT_FUNCTION_LIST_OPT :
                     | NT_FUNCTION_LIST
                     ;

NT_FUNCTION_LIST : NT_FUNCTION NT_FUNCTION_LIST
                 | NT_FUNCTION
                 ;
/* Function */
NT_FUNCTION : NT_FUNCTION_DECLARATION
            | NT_FUNCTION_DEFINITION
            ;

NT_FUNCTION_HEADER : IDENTIFIER LEFT_PAREN NT_FORMAL_ARG_LIST_OPT RIGHT_PAREN NT_RETURN_TYPE
                   ;

NT_FORMAL_ARG_LIST_OPT :
                       | NT_FORMAL_ARG_LIST
                       ;

NT_FORMAL_ARG_LIST : NT_FORMAL_ARG SEMICOLON NT_FORMAL_ARG_LIST
                   | NT_FORMAL_ARG
                   ;

NT_RETURN_TYPE :
               | COLON NT_SCALAR_TYPE
               ;

NT_FUNCTION_DECLARATION : NT_FUNCTION_HEADER SEMICOLON
                        ;

NT_FUNCTION_DEFINITION : NT_FUNCTION_HEADER
                         NT_COMPOUND_STATEMENT
                         KW_END
                       ;

NT_FORMAL_ARG : NT_IDENTIFIER_LIST COLON NT_TYPE
              ;


/* Declarations */
NT_DECLARATION : NT_VARIABLE_DECLARATION
               | NT_CONSTANT_DECLARATION
               ;

NT_VARIABLE_DECLARATION : KW_VAR NT_IDENTIFIER_LIST COLON NT_TYPE SEMICOLON
                        ;

NT_CONSTANT_DECLARATION : KW_VAR NT_IDENTIFIER_LIST COLON SUB NT_INTEGER_LITERAL SEMICOLON
                      | KW_VAR NT_IDENTIFIER_LIST COLON NT_INTEGER_LITERAL SEMICOLON
                      | KW_VAR NT_IDENTIFIER_LIST COLON SUB NT_REAL_LITERAL SEMICOLON
                      | KW_VAR NT_IDENTIFIER_LIST COLON NT_REAL_LITERAL SEMICOLON
                      | KW_VAR NT_IDENTIFIER_LIST COLON NT_STRING_LITERAL SEMICOLON
                      | KW_VAR NT_IDENTIFIER_LIST COLON NT_BOOLEAN_LITERAL SEMICOLON
                      ;

/* Identifier List */
NT_IDENTIFIER_LIST : IDENTIFIER COMMA NT_IDENTIFIER_LIST
                   | IDENTIFIER
                   ;

/* Types */
NT_TYPE : NT_SCALAR_TYPE
        | NT_ARRAY_TYPE
        ;

NT_SCALAR_TYPE : KW_INT
               | KW_REAL
               | KW_STR
               | KW_BOOL
               ;

NT_ARRAY_TYPE : KW_ARRAY NT_INTEGER_LITERAL KW_OF NT_TYPE
              ;

/* Statements */
NT_STATEMENT : NT_SIMPLE_STATEMENT
             | NT_CONDITIONAL_STATEMENT
             | NT_FUNCTION_CALL_STATEMENT
             | NT_LOOP_STATEMENT
             | NT_RETURN_STATEMENT
             | NT_COMPOUND_STATEMENT
             ;

NT_SIMPLE_STATEMENT : NT_ASSIGNMENT
                    | NT_PRINT_STATEMENT
                    | NT_READ_STATEMENT
                    ;

NT_ASSIGNMENT : NT_VARIABLE_REFERENCE ASSIGNMENT NT_EXPRESSION SEMICOLON
              ;

NT_PRINT_STATEMENT : KW_PRINT NT_EXPRESSION SEMICOLON
                   ;

NT_READ_STATEMENT : KW_READ NT_EXPRESSION SEMICOLON
                  ;

NT_CONDITIONAL_STATEMENT : KW_IF NT_EXPRESSION KW_THEN
                           NT_COMPOUND_STATEMENT
                           KW_ELSE
                           NT_COMPOUND_STATEMENT
                           KW_END KW_IF
                         | KW_IF NT_EXPRESSION KW_THEN
                           NT_COMPOUND_STATEMENT
                           KW_END KW_IF
                         ;

NT_FUNCTION_CALL_STATEMENT : NT_FUNCTION_CALL SEMICOLON
                           ;

NT_LOOP_STATEMENT : KW_WHILE NT_EXPRESSION KW_DO
                    NT_COMPOUND_STATEMENT
                    KW_END KW_DO
                  | KW_FOR IDENTIFIER ASSIGNMENT NT_INTEGER_LITERAL KW_TO NT_INTEGER_LITERAL KW_DO
                    NT_COMPOUND_STATEMENT
                    KW_END KW_DO
                  ;

NT_RETURN_STATEMENT : KW_RETURN NT_EXPRESSION SEMICOLON
                    ;

NT_COMPOUND_STATEMENT : KW_BEGIN
                        NT_DECLARATION_LIST_OPT
                        NT_STATEMENT_LIST_OPT
                        KW_END
                      ;

NT_STATEMENT_LIST_OPT :
                      | NT_STATEMENT_LIST
                      ;

NT_STATEMENT_LIST : NT_STATEMENT NT_STATEMENT_LIST
                  | NT_STATEMENT
                  ;

/* Expression */
NT_EXPRESSION : NT_LITERAL_CONSTANT
              | NT_VARIABLE_REFERENCE
              | NT_FUNCTION_CALL
              | NT_BINARY_OPERATION
              | NT_UNARY_OPERATION
              | LEFT_PAREN NT_EXPRESSION RIGHT_PAREN
              ;

NT_LITERAL_CONSTANT : NT_INTEGER_LITERAL
                    | NT_REAL_LITERAL
                    | NT_STRING_LITERAL
                    | NT_BOOLEAN_LITERAL
                    ;
NT_INTEGER_LITERAL : DECIMAL
                   | OCTAL
                   ;

NT_REAL_LITERAL : FLOAT
                | SCIENTIFIC
                ;

NT_STRING_LITERAL : STRING
                  ;

NT_BOOLEAN_LITERAL : KW_TRUE
                   | KW_FALSE
                   ;

NT_VARIABLE_REFERENCE : IDENTIFIER NT_BRACKET_EXPRESSION_LIST_OPT
                      ;

NT_BRACKET_EXPRESSION_LIST_OPT : 
                               | NT_BRACKET_EXPRESSION_LIST
                               ;

NT_BRACKET_EXPRESSION_LIST : NT_BRACKET_EXPRESSION NT_BRACKET_EXPRESSION_LIST
                           | NT_BRACKET_EXPRESSION
                           ;

NT_BRACKET_EXPRESSION : LEFT_BRACKET NT_EXPRESSION RIGHT_BRACKET
                      ;

NT_FUNCTION_CALL : IDENTIFIER LEFT_PAREN NT_EXPRESSION_LIST_OPT RIGHT_PAREN
                 ;

NT_EXPRESSION_LIST_OPT :
                       | NT_EXPRESSION_LIST
                       ;

NT_EXPRESSION_LIST : NT_EXPRESSION COMMA NT_EXPRESSION_LIST
                   | NT_EXPRESSION
                   ;

NT_BINARY_OPERATION : NT_EXPRESSION OR NT_EXPRESSION
                    | NT_EXPRESSION AND NT_EXPRESSION
                    | NT_EXPRESSION NT_RELATIONAL_OPERATOR NT_EXPRESSION
                    | NT_EXPRESSION SUB NT_EXPRESSION
                    | NT_EXPRESSION ADD NT_EXPRESSION
                    | NT_EXPRESSION DIV NT_EXPRESSION
                    | NT_EXPRESSION MOD NT_EXPRESSION
                    | NT_EXPRESSION MUL NT_EXPRESSION
                    ;

NT_RELATIONAL_OPERATOR : LT
                       | LE
                       | NE
                       | GE
                       | GT
                       | EQ
                       ;

NT_UNARY_OPERATION : NOT NT_EXPRESSION
                   | SUB NT_EXPRESSION  %prec NEG
                   ;


%%

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
