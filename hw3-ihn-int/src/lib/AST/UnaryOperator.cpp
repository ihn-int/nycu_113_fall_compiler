#include "AST/UnaryOperator.hpp"

// TODO
UnaryOperatorNode::UnaryOperatorNode(
    const uint32_t line,
    const uint32_t col,
    Operator *p_op,
    ExpressionNode *p_expression
) : ExpressionNode{line, col},
    op(p_op),
    expression(p_expression)
    {}

// TODO: You may use code snippets in AstDumper.cpp
void UnaryOperatorNode::print() {}

void UnaryOperatorNode::visitChildNodes(AstNodeVisitor &p_visitor) {
    // TODO
    if (expression)
        expression->accept(p_visitor);
};

const char* UnaryOperatorNode::getOperatorCString() const{
    return op->getTypeCString();
};