#ifndef __AST_BINARY_OPERATOR_NODE_H
#define __AST_BINARY_OPERATOR_NODE_H

#include "AST/expression.hpp"
#include "visitor/AstNodeVisitor.hpp"
#include <string>
#include <memory>

class BinaryOperatorNode : public ExpressionNode {
  public:
    BinaryOperatorNode(
        const uint32_t line,
        const uint32_t col,
        // TODO: operator
        Operator* p_op,
        // expressions
        ExpressionNode* p_left_expression,
        ExpressionNode* p_right_expression);
    ~BinaryOperatorNode() = default;

    const char* getOperatorCString() const;

    void print() override;
    void accept(AstNodeVisitor &p_visitor) override{ p_visitor.visit(*this); }
    void visitChildNodes(AstNodeVisitor &p_visitor) override;

  private:
    // TODO: operator
    Operator* op;
    // expressions
    ExpressionNode* left_expression;
    ExpressionNode* right_expression;
};

#endif
