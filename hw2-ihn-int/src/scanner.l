%option never-interactive
%option nounput
%option noinput

%{
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "parser.h"

#define MAX_LINE_LEN 512
/* Code runs each time a token is matched. */
#define YY_USER_ACTION updateCurrentLine(yytext);

uint32_t line_num = 1;
uint32_t col_num = 1;
char current_line[MAX_LINE_LEN];
static uint32_t opt_src = 1;
static uint32_t opt_tok = 1;
static char string_literal[MAX_LINE_LEN];

static void updateCurrentLine(const char *source);
static void listToken(const char *name);
static void listLiteral(const char *name, const char *literal);

%}

integer 0|[1-9][0-9]*
float {integer}\.(0|[0-9]*[1-9])
nonzero_integer [1-9][0-9]*
/* If the integral part is nonzero, then the fractional part can be either zero
    or not. However, if the integral part is zero, the fractional part cannot be zero. */
nonzero_float ({nonzero_integer}\.(0|[0-9]*[1-9]))|(0\.([0-9]*[1-9]))

/* exclusive start condition */
%x CCOMMENT

%%
    /* Delimiter */
"," { listToken(","); return COMMA; }
";" { listToken(";"); return SEMICOLON; }
":" { listToken(":"); return COLON; }
"(" { listToken("("); return LEFT_PAREN; }
")" { listToken(")"); return RIGHT_PAREN; }
"[" { listToken("["); return LEFT_BRACKET; }
"]" { listToken("]"); return RIGHT_BRACKET; }

    /* Operator */
"+"   { listToken("+"); return ADD; }
"-"   { listToken("-"); return SUB; }
"*"   { listToken("*"); return MUL; }
"/"   { listToken("/"); return DIV; }
"mod" { listToken("mod"); return MOD; }
":="  { listToken(":="); return ASSIGNMENT; }
"<"   { listToken("<"); return LT; }
"<="  { listToken("<="); return LE; }
"<>"  { listToken("<>"); return NE; }
">="  { listToken(">="); return GE; }
">"   { listToken(">"); return GT; }
"="   { listToken("="); return EQ; }
"and" { listToken("and"); return AND; }
"or"  { listToken("or"); return OR; }
"not" { listToken("not"); return NOT; }

    /* Reserved Word */
"var"     { listToken("KWvar"); return KW_VAR; }
"array"   { listToken("KWarray"); return KW_ARRAY; }
"of"      { listToken("KWof"); return KW_OF; }
"boolean" { listToken("KWboolean"); return KW_BOOL; }
"integer" { listToken("KWinteger"); return KW_INT; }
"real"    { listToken("KWreal"); return KW_REAL; }
"string"  { listToken("KWstring"); return KW_STR; }

"true"    { listToken("KWtrue"); return KW_TRUE; }
"false"   { listToken("KWfalse"); return KW_FALSE; }

"def"     { listToken("KWdef"); return KW_DEF; }
"return"  { listToken("KWreturn"); return KW_RETURN; }

"begin"   { listToken("KWbegin"); return KW_BEGIN; }
"end"     { listToken("KWend"); return KW_END; }

"while"   { listToken("KWwhile"); return KW_WHILE; }
"do"      { listToken("KWdo"); return KW_DO; }

"if"      { listToken("KWif"); return KW_IF; }
"then"    { listToken("KWthen"); return KW_THEN; }
"else"    { listToken("KWelse"); return KW_ELSE; }

"for"     { listToken("KWfor"); return KW_FOR; }
"to"      { listToken("KWto"); return KW_TO; }

"print"   { listToken("KWprint"); return KW_PRINT; }
"read"    { listToken("KWread"); return KW_READ; }

    /* Identifier */
[a-zA-Z][a-zA-Z0-9]* { listLiteral("id", yytext); return IDENTIFIER; }

    /* Integer (decimal/octal) */
{integer} { listLiteral("integer", yytext); return DECIMAL; }
0[0-7]+   { listLiteral("oct_integer", yytext); return OCTAL; }

    /* Floating-Point */
{float} { listLiteral("float", yytext); return FLOAT; }

    /* Scientific Notation [Ee][+-]?[0-9]+ */
({nonzero_integer}|{nonzero_float})[Ee][+-]?({integer}) { listLiteral("scientific", yytext); return SCIENTIFIC; }

    /* String */
\"([^"\n]|\"\")*\" {
    char *yyt_ptr = yytext + 1;  // +1 for skipping the first double quote "
    char *str_ptr = string_literal;

    while (*yyt_ptr) {
        if (*yyt_ptr == '"') {
            // Handle the situation of two double quotes "" in string literal
            if (*(yyt_ptr + 1) == '"') {
                *str_ptr = *yyt_ptr;
                ++str_ptr;
                yyt_ptr += 2; // move to the next character of ""
            } else {
                ++yyt_ptr;
            }
        } else {  // normal character
            *str_ptr = *yyt_ptr;
            ++str_ptr;
            ++yyt_ptr;
        }
    }
    *str_ptr = '\0';
    listLiteral("string", string_literal);
    return STRING;
}

    /* space, comments needn't parse */

    /* Whitespace and Newline */
[ \t\n]+ { }

    /* Pseudocomment */
"//&"[ST][+-].* {
    char option = yytext[3];
    switch (option) {
    case 'S':
        opt_src = (yytext[4] == '+') ? 1 : 0;
        break;
    case 'T':
        opt_tok = (yytext[4] == '+') ? 1 : 0;
        break;
    }
}

    /* C++ Style Comment */
"//".* { }

    /* C Style Comment */
"/*"           { BEGIN(CCOMMENT); }
<CCOMMENT>"*/" { BEGIN(INITIAL); }
<CCOMMENT>.|\n { }

    /* Catch the character which is not accepted by all rules above */
. {
    printf("Error at line %d: bad character \"%s\"\n", line_num, yytext);
    exit(-1);
}

%%

/** @note The line is printed out and flushed when a newline character is encountered. */
static void updateCurrentLine(const char *source) {
    /* col_num is one-based */
    for (const char *c = source; *c; ++c) {
        if (*c == '\n') {
            if (opt_src) {
                printf("%d: %s\n", line_num, current_line);
            }
            ++line_num;
            col_num = 1;
            current_line[0] = '\0';
        } else {
            if (col_num < MAX_LINE_LEN) {
                current_line[col_num - 1] = *c;
                current_line[col_num] = '\0';
            } else {
                /* Truncate silently; doesn't affect the program's correctness. */
            }
            ++col_num;
        }
    }
}

static void listToken(const char *name) {
    if (opt_tok) {
        printf("<%s>\n", name);
    }
}

static void listLiteral(const char *name, const char *literal) {
    if (opt_tok) {
        printf("<%s: %s>\n", name, literal);
    }
}

/** @note This function is not required if the input file is guaranteed to end
 * with a newline. However, students may find it useful to handle the case where
 * the input file does not end with a newline, as it has been reported several
 * times in the past.
 */
int yywrap(void) {
    /* If the file is not ended with a newline, fake it to print out the last line. */
    if (col_num > 1) {
        updateCurrentLine("\n");
    }
    /* no more input file */
    return 1;
}
