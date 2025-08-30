#include "AST/BinaryOperator.hpp"

// TODO
BinaryOperatorNode::BinaryOperatorNode(
    const uint32_t line,
    const uint32_t col,
    Operator* p_op,
    ExpressionNode* p_left_expression,
    ExpressionNode* p_right_expression
) : ExpressionNode{line, col}, 
    op(p_op), 
    left_expression(p_left_expression), 
    right_expression(p_right_expression)
    {}

const char* BinaryOperatorNode::getOperatorCString() const{
    return op->getTypeCString();
};

// TODO: You may use code snippets in AstDumper.cpp
void BinaryOperatorNode::print() {}

void BinaryOperatorNode::visitChildNodes(AstNodeVisitor &p_visitor) {
    // TODO
    if (left_expression)
        left_expression->accept(p_visitor);
    if (right_expression)
        right_expression->accept(p_visitor);
};
