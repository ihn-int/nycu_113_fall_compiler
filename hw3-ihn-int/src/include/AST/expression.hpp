#ifndef __AST_EXPRESSION_NODE_H
#define __AST_EXPRESSION_NODE_H

#include "AST/ast.hpp"
#include "visitor/AstNodeVisitor.hpp"
#include <string>
#include <memory>

enum class OperatorType {
    NEG,
    MUL,
    DIV,
    MOD,
    ADD,
    SUB,
    LT,
    LE,
    GT,
    GE,
    EQ,
    NE,
    NOT,
    AND,
    OR,
    UNKNOWN
};

class ExpressionNode : public AstNode {
  public:
    ExpressionNode(
        const uint32_t line,
        const uint32_t col
    );
    ~ExpressionNode() = default;
    
  protected:
    // for carrying type of result of an expression
    // TODO: for next assignment
};



class Operator {
    public:
      Operator(OperatorType type);
      const char *getTypeCString();
    private:
      std::string type_str;
};

#endif
