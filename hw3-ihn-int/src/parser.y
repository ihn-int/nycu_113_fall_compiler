%{
#include "AST/AstDumper.hpp"
#include "AST/BinaryOperator.hpp"
#include "AST/CompoundStatement.hpp"
#include "AST/ConstantValue.hpp"
#include "AST/FunctionInvocation.hpp"
#include "AST/UnaryOperator.hpp"
#include "AST/VariableReference.hpp"
#include "AST/assignment.hpp"
#include "AST/ast.hpp"
#include "AST/decl.hpp"
#include "AST/expression.hpp"
#include "AST/for.hpp"
#include "AST/function.hpp"
#include "AST/if.hpp"
#include "AST/print.hpp"
#include "AST/program.hpp"
#include "AST/read.hpp"
#include "AST/return.hpp"
#include "AST/variable.hpp"
#include "AST/while.hpp"

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define YYLTYPE yyltype

typedef struct YYLTYPE {
    uint32_t first_line;
    uint32_t first_column;
    uint32_t last_line;
    uint32_t last_column;
} yyltype;

extern uint32_t line_num;   /* declared in scanner.l */
extern char current_line[]; /* declared in scanner.l */
extern FILE *yyin;          /* declared by lex */
extern char *yytext;        /* declared by lex */

static AstNode *root;

extern "C" int yylex(void);
static void yyerror(const char *msg);
extern int yylex_destroy(void);
%}

// This guarantees that headers do not conflict when included together.
%define api.token.prefix {TOK_}

%code requires {
    #include <vector>
    #include "AST/AstDumper.hpp"
    #include "AST/BinaryOperator.hpp"
    #include "AST/CompoundStatement.hpp"
    #include "AST/ConstantValue.hpp"
    #include "AST/FunctionInvocation.hpp"
    #include "AST/UnaryOperator.hpp"
    #include "AST/VariableReference.hpp"
    #include "AST/assignment.hpp"
    #include "AST/ast.hpp"
    #include "AST/decl.hpp"
    #include "AST/expression.hpp"
    #include "AST/for.hpp"
    #include "AST/function.hpp"
    #include "AST/if.hpp"
    #include "AST/print.hpp"
    #include "AST/program.hpp"
    #include "AST/read.hpp"
    #include "AST/return.hpp"
    #include "AST/variable.hpp"
    #include "AST/while.hpp"
}

    /* For yylval */
%union {
    /* basic semantic value */
    char* identifier;
    int int_value;
    float real_value;
    bool bool_value;
    const char* string_value;
    
    /* type  */
    ScalarType scalar_type;
    VarType* var_type;
    std::vector<int>* dims;

    /* node */
    AstNode *node;
    CompoundStatementNode* compound_stmt_node;
    ConstantValueNode* const_value_node;
    DeclNode* decl_node;
    ExpressionNode* expr_node;
    ForNode* for_node;
    FunctionNode* func_node;
    FunctionInvocationNode* func_invc_node;
    IfNode* if_node;
    ReturnNode* return_node;
    VariableReferenceNode* var_ref_node;
    WhileNode* while_node;
    
    /* node list */
    std::vector<AstNode*>* node_list;
    std::vector<DeclNode*>* decl_node_list;
    std::vector<VariableNode*>* var_node_list;
    std::vector<FunctionNode*>* func_node_list;
    std::vector<ExpressionNode*>* expr_node_list;
};

%type <identifier> ProgramName ID
%type <decl_node_list> DeclarationList
%type <decl_node_list> Declarations
%type <func_node_list> FunctionList
%type <func_node_list> Functions
%type <func_node> Function
%type <func_node> FunctionDeclaration
%type <func_node> FunctionDefinition
%type <identifier> FunctionName
%type <decl_node_list> FormalArgList
%type <decl_node_list> FormalArgs
%type <decl_node> FormalArg
%type <var_node_list> IdList
%type <var_type> ReturnType
%type <decl_node> Declaration
%type <var_type> Type
%type <scalar_type> ScalarType
%type <var_type> ArrType
%type <dims> ArrDecl
%type <const_value_node> LiteralConstant
%type <bool_value> NegOrNot
%type <const_value_node> StringAndBoolean
%type <const_value_node> IntegerAndReal
%type <node> Statement
%type <compound_stmt_node> CompoundStatement
%type <node> Simple
%type <var_ref_node> VariableReference
%type <expr_node_list> ArrRefList
%type <expr_node_list> ArrRefs
%type <if_node> Condition
%type <compound_stmt_node> ElseOrNot
%type <while_node> While
%type <for_node> For
%type <return_node> Return
%type <node> FunctionCall
%type <func_invc_node> FunctionInvocation
%type <expr_node_list> ExpressionList
%type <expr_node_list> Expressions
%type <node_list> StatementList
%type <node_list> Statements
%type <expr_node> Expression


    /* Follow the order in scanner.l */

    /* Delimiter */
%token COMMA SEMICOLON COLON
%token L_PARENTHESIS R_PARENTHESIS
%token L_BRACKET R_BRACKET

    /* Operator */
%token ASSIGN
    /* TODO: specify the precedence of the following operators */
%left OR 
%left AND 
%right NOT
%nonassoc LESS LESS_OR_EQUAL EQUAL GREATER GREATER_OR_EQUAL NOT_EQUAL
%left PLUS MINUS
%left MULTIPLY DIVIDE MOD
%right UNARY_MINUS

    /* Keyword */
%token ARRAY BOOLEAN INTEGER REAL STRING
%token END BEGIN
%token DO ELSE FOR IF THEN WHILE
%token DEF OF TO RETURN VAR
%token <bool_value> FALSE TRUE
%token PRINT READ

    /* Identifier */
%token ID

    /* Literal */
%token <int_value> INT_LITERAL
%token <real_value> REAL_LITERAL
%token <string_value> STRING_LITERAL

%%

ProgramUnit:
    Program
    |
    Function
;

Program:
    ProgramName SEMICOLON
    /* ProgramBody */
    DeclarationList FunctionList CompoundStatement
    /* End of ProgramBody */
    END {
        root = new ProgramNode(
            @1.first_line,
            @1.first_column,
            $1, // Program name
            $3, // DeclarationList
            $4, // FunctionList
            $5  // Compound Statement
        );

        free($1);
    }
;

ProgramName:
    ID {
        $$ = $1;
    }
;

DeclarationList:
    Epsilon {
        $$ = new std::vector<DeclNode*>(); // empty list
    }
    |
    Declarations {
        $$ = $1;  // initialize one entry
    }
;

Declarations:
    Declaration {
        $$ = new std::vector<DeclNode*>(1, $1);  // initialize one entry
    }
    |
    Declarations Declaration {
        $$ = $1;
        $$->push_back($2);  // add new entry
    }
;

FunctionList:
    Epsilon {
        $$ = new std::vector<FunctionNode*>(); // empty list
    }
    |
    Functions {
        $$ = $1; // assignment

    }
;

Functions:
    Function {
        $$ = new std::vector<FunctionNode*>(1, $1);
    }
    |
    Functions Function {
        $$ = $1;
        $$->push_back($2);
    }
;

Function:
    FunctionDeclaration {
        $$ = $1;
    }
    |
    FunctionDefinition {
        $$ = $1;
    }
;

FunctionDeclaration:
    FunctionName L_PARENTHESIS FormalArgList R_PARENTHESIS ReturnType SEMICOLON {
        $$ = new FunctionNode(
            @1.first_line,
            @1.first_column,
            $1, // function name
            $3, // args
            $5  // return type 
                // no function body
        );
    }
;

FunctionDefinition:
    FunctionName L_PARENTHESIS FormalArgList R_PARENTHESIS ReturnType
    CompoundStatement
    END {
        $$ = new FunctionNode(
            @1.first_line,
            @1.first_column,
            $1, // function name
            $3, // args
            $5, // return type 
            $6  // function body
        );
    }
;

FunctionName:
    ID {
        $$ = $1;
    }
;

FormalArgList:
    Epsilon {
        $$ = new std::vector<DeclNode*>();
    }
    |
    FormalArgs {
        $$ = $1;
    }
;

FormalArgs:
    FormalArg {
        $$ = new std::vector<DeclNode*>(1, $1);
    }
    |
    FormalArgs SEMICOLON FormalArg{
        $$ = $1;
        $$->push_back($3);
    }
;

FormalArg:
    IdList COLON Type {
        for(auto &var : *$1){
            var->setTypeString($3);
        }
        $$ = new DeclNode(
            @1.first_line,
            @1.first_column,
            $1  // id list
        );
    }
;

IdList:
    ID {
        $$ = new std::vector<VariableNode*>();
        $$->push_back(
            new VariableNode(
                @1.first_line,
                @1.first_column,
                $1  // var name
            )
        );
    }
    |
    IdList COMMA ID {
        $$ =$1;
        $$->push_back(
            new VariableNode(
                @3.first_line,
                @3.first_column,
                $3  // name
            )
        );
    }
;

ReturnType:
    COLON ScalarType {
        $$ = new VarType($2);
    }
    |
    Epsilon{
        $$ = new VarType(ScalarType::VOID);
    }
;

    /*
       Data Types and Declarations
                                   */

Declaration:
    VAR IdList COLON Type SEMICOLON {
        for (auto &var : *$2){
            var->setTypeString($4);
        }
        $$ = new DeclNode(
            @1.first_line,
            @1.first_column,
            $2  // id list
        );
    }
    |
    VAR IdList COLON LiteralConstant SEMICOLON {
        for (auto &var : *$2){
            var->setConstantValue($4);
        }
        $$ = new DeclNode(
            @1.first_line,
            @1.first_column,
            $2  // id list
        );
    }
;

Type:
    ScalarType {
        $$ = new VarType($1);
    }
    |
    ArrType {
        $$ = $1;
    }
;

ScalarType:
    INTEGER {
        $$ = ScalarType::INTEGER;
    }
    |
    REAL {
        $$ = ScalarType::REAL;
    }
    |
    STRING {
        $$ = ScalarType::STRING;
    }
    |
    BOOLEAN {
        $$ = ScalarType::BOOL;
    }
;

ArrType:
    ArrDecl ScalarType {
        $$ = new VarType($2, $1);
    }
;

ArrDecl:
    ARRAY INT_LITERAL OF {
        $$ = new std::vector<int>();
        $$->push_back($2);
    }
    |
    ArrDecl ARRAY INT_LITERAL OF {
        $$ = $1;
        $$->push_back($3);
    }
; 

LiteralConstant:
    NegOrNot INT_LITERAL {
        if ($1){
            $$ = new ConstantValueNode(
                @2.first_line,
                @2.first_column,
                $2  // int_value
            );
        }else{
            $$ = new ConstantValueNode(
                @1.first_line,
                @1.first_column,
                -$2 // negative int_value
            );
        }    
    }
    |
    NegOrNot REAL_LITERAL {
        if ($1){
            $$ = new ConstantValueNode(
                @2.first_line,
                @2.first_column,
                $2  // real_value
            );
        }else{
            $$ = new ConstantValueNode(
                @1.first_line,
                @1.first_column,
                -$2 // negative real value
            );
        }               
    }
    |
    StringAndBoolean {
        $$ = $1;
    }
;

NegOrNot:
    Epsilon {
        $$ = true;
    }
    |
    MINUS %prec UNARY_MINUS{
        $$ = false;
    }
;

StringAndBoolean:
    STRING_LITERAL {
        
        $$ = new ConstantValueNode(
            @1.first_line,
            @1.first_column,
            $1  // string_value
        );
    }
    |
    TRUE {
        $$ = new ConstantValueNode(
            @1.first_line,
            @1.first_column,
            $1  // bool_value
        );
    }
    |
    FALSE {
        $$ = new ConstantValueNode(
            @1.first_line,
            @1.first_column,
            $1  // bool_value
        );
    }
;

IntegerAndReal:
    INT_LITERAL {
        $$ = new ConstantValueNode(
            @1.first_line,
            @1.first_column, 
            $1  // int_value
        );
    }
    |
    REAL_LITERAL {
        $$ = new ConstantValueNode(
            @1.first_line,
            @1.first_column,
            $1  // real_value
        );
    }
;

    /*
       Statements
                  */

Statement:
    CompoundStatement {
        $$ = $1;
    }
    |
    Simple {
        $$ = $1;
    }
    |
    Condition {
        $$ = $1;
    }
    |
    While {
        $$ = $1;
    }
    |
    For {
        $$ = $1;
    }
    |
    Return {
        $$ = $1;
    }
    |
    FunctionCall {
        $$ = $1;
    }
;

CompoundStatement:
    BEGIN
    DeclarationList
    StatementList
    END {
        $$ = new CompoundStatementNode(
            @1.first_line,
            @1.first_column,
            $2, // Declaration List
            $3  // Statement List
        );
    }
;

Simple:
    VariableReference ASSIGN Expression SEMICOLON {
        $$ = new AssignmentNode(
            @2.first_line,
            @2.first_column,
            $1, // var reference
            $3  // expression
        );
    }
    |
    PRINT Expression SEMICOLON {
        $$ = new PrintNode(
            @1.first_line,
            @1.first_column,
            $2  // expression
        );
    }
    |
    READ VariableReference SEMICOLON {
        $$ = new ReadNode(
            @1.first_line,
            @1.first_column,
            $2  // variable reference
        );
    }
;

VariableReference:
    ID ArrRefList {
        $$ = new VariableReferenceNode(
            @1.first_line,
            @1.first_column,
            $1, // id
            $2  // reference list
        );
    }
;

ArrRefList:
    Epsilon {
        $$ = new std::vector<ExpressionNode*>();
    }
    |
    ArrRefs {
        $$ = $1;
    }
;

ArrRefs:
    L_BRACKET Expression R_BRACKET {
        $$ = new std::vector<ExpressionNode*>(1, $2);
    }
    |
    ArrRefs L_BRACKET Expression R_BRACKET {
        $$ = $1;
        $$->push_back($3);
    }
;

Condition:
    IF Expression THEN
    CompoundStatement
    ElseOrNot
    END IF {
        $$ = new IfNode(
            @1.first_line,
            @1.first_column,
            $2, // expression
            $4, // then statement
            $5  // else statement
        );
    }
;

ElseOrNot:
    ELSE
    CompoundStatement {
        $$ = $2;
    }
    |
    Epsilon {
        $$ = nullptr;   // no else statement
    }
;

While:
    WHILE Expression DO
    CompoundStatement
    END DO {
        $$ = new WhileNode(
            @1.first_line,
            @1.first_column,
            $2, // expression
            $4  // statements
        );
    }
;

For:
    FOR ID ASSIGN INT_LITERAL TO INT_LITERAL DO
    CompoundStatement
    END DO {
        // variable node
        VariableNode* var = new VariableNode(
            @2.first_line,
            @2.first_column,
            $2  // name
        );
        var->setTypeString(new VarType(ScalarType::INTEGER));

        // declaration node
        DeclNode* decl = new DeclNode(
            @2.first_line,
            @2.first_column,
            new std::vector<VariableNode*>{var} // id list
        );

        // assignment node
        AssignmentNode* asmt = new AssignmentNode(
            @3.first_line,
            @3.first_column,
            new VariableReferenceNode(
                @2.first_line,
                @2.first_column,
                $2 // var reference
            ),
            new ConstantValueNode(
                @4.first_line,
                @4.first_column,
                $4  // constant value
            )
        );

        // constant value node, as terminate 
        ConstantValueNode* cond = new ConstantValueNode(
            @6.first_line,
            @6.first_column,
            $6  // terminate
        );

        $$ = new ForNode(
            @1.first_line,
            @1.first_column,
            decl,   // declaration
            asmt,   // assignment
            cond,   // terminate
            $8      // body statement
        );
    }
;

Return:
    RETURN Expression SEMICOLON {
        $$ = new ReturnNode(
            @1.first_line,
            @1.first_column,
            $2  // expression
        );
    }
;

FunctionCall:
    FunctionInvocation SEMICOLON {
        $$ = $1;
    }
;

FunctionInvocation:
    ID L_PARENTHESIS ExpressionList R_PARENTHESIS {
        $$ = new FunctionInvocationNode(
            @1.first_line,
            @1.first_column,
            $1, // function name
            $3  // expression list
        );
    }
;

ExpressionList:
    Epsilon {
        $$ = new std::vector<ExpressionNode*>();
    }
    |
    Expressions {
        $$ = $1;
    }
;

Expressions:
    Expression {
        $$ = new std::vector<ExpressionNode*>(1, $1);
    }
    |
    Expressions COMMA Expression {
        $$ = $1;
        $$->push_back($3);
    }
;

StatementList:
    Epsilon {
        $$ = new std::vector<AstNode*>();
    }
    |
    Statements {
        $$ = $1;
    }
;

Statements:
    Statement{
        $$ = new std::vector<AstNode*>(1, $1);
    }
    |
    Statements Statement{
        $$ = $1;
        $$->push_back($2);
    }
;

Expression:
    L_PARENTHESIS Expression R_PARENTHESIS {
        $$ = $2;
    }
    |
    MINUS Expression %prec UNARY_MINUS {
        $$ = new UnaryOperatorNode(
            @1.first_line,
            @1.first_column,
            new Operator(OperatorType::NEG),
            $2
        );
    }
    |
    Expression MULTIPLY Expression {
        $$ = new BinaryOperatorNode(
            @1.first_line, 
            @2.first_column, 
            new Operator(OperatorType::MUL), 
            $1, 
            $3
        );
    }
    |
    Expression DIVIDE Expression {
        $$ = new BinaryOperatorNode(
            @1.first_line, 
            @2.first_column, 
            new Operator(OperatorType::DIV), 
            $1, 
            $3
        );
    }
    |
    Expression MOD Expression {
        $$ = new BinaryOperatorNode(
            @1.first_line, 
            @2.first_column, 
            new Operator(OperatorType::MOD),
            $1,
            $3
        );
    }
    |
    Expression PLUS Expression {
        $$ = new BinaryOperatorNode(
            @1.first_line, 
            @2.first_column,
            new Operator(OperatorType::ADD),
            $1,
            $3
        );
    }
    |
    Expression MINUS Expression {
        $$ = new BinaryOperatorNode(
            @1.first_line, 
            @2.first_column, 
            new Operator(OperatorType::SUB), 
            $1, 
            $3
        );
    }
    |
    Expression LESS Expression {
        $$ = new BinaryOperatorNode(
            @1.first_line, 
            @2.first_column, 
            new Operator(OperatorType::LT), 
            $1, 
            $3
        );
    }
    |
    Expression LESS_OR_EQUAL Expression {
        $$ = new BinaryOperatorNode(
            @1.first_line, 
            @2.first_column, 
            new Operator(OperatorType::LE), 
            $1,
            $3
        );
    }
    |
    Expression GREATER Expression {
        $$ = new BinaryOperatorNode(
            @1.first_line, 
            @2.first_column, 
            new Operator(OperatorType::GT),
            $1,  
            $3
        );
    }
    |
    Expression GREATER_OR_EQUAL Expression {
        $$ = new BinaryOperatorNode(
            @1.first_line, 
            @2.first_column, 
            new Operator(OperatorType::GE), 
            $1, 
            $3
        );
    }
    |
    Expression EQUAL Expression {
        $$ = new BinaryOperatorNode(
            @1.first_line, 
            @2.first_column, 
            new Operator(OperatorType::EQ),
            $1,
            $3
        );
    }
    |
    Expression NOT_EQUAL Expression {
        $$ = new BinaryOperatorNode(
            @1.first_line,
            @2.first_column,
            new Operator(OperatorType::NE),
            $1,
            $3
        );
    }
    |
    NOT Expression {
        $$ = new UnaryOperatorNode(
            @1.first_line,
            @1.first_column,
            new Operator(OperatorType::NOT),
            $2
        );
    }
    |
    Expression AND Expression {
        $$ = new BinaryOperatorNode(
            @1.first_line,
            @2.first_column,
            new Operator(OperatorType::AND),
            $1,
            $3
        );
    }
    |
    Expression OR Expression {
        $$ = new BinaryOperatorNode(
            @1.first_line,
            @2.first_column,
            new Operator(OperatorType::OR),
            $1,
            $3
        );
    }
    |
    IntegerAndReal {
        $$ = $1;
    }
    |
    StringAndBoolean {
        $$ = $1;
    }
    |
    VariableReference {
        $$ = $1;
    }
    |
    FunctionInvocation {
        $$ = $1;
    }
;

    /*
       misc
            */
Epsilon:
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
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename> [--dump-ast]\n", argv[0]);
        exit(-1);
    }

    yyin = fopen(argv[1], "r");
    if (yyin == NULL) {
        perror("fopen() failed");
        exit(-1);
    }

    yyparse();

    if (argc >= 3 && strcmp(argv[2], "--dump-ast") == 0) {
        //root->print();
        AstDumper ast_dumper;
        root->accept(ast_dumper);
    }

    printf("\n"
           "|--------------------------------|\n"
           "|  There is no syntactic error!  |\n"
           "|--------------------------------|\n");

    delete root;
    fclose(yyin);
    yylex_destroy();
    return 0;
}
