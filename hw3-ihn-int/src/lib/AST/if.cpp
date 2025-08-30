#include "AST/if.hpp"

// TODO
IfNode::IfNode(
    const uint32_t line,
    const uint32_t col,
    ExpressionNode *p_condition,
    CompoundStatementNode *p_then_stmt,
    CompoundStatementNode *p_else_stmt
) : AstNode{line, col}, 
    condition(p_condition), 
    then_stmt(p_then_stmt),
    else_stmt(p_else_stmt)
    {}

// TODO: You may use code snippets in AstDumper.cpp
void IfNode::print() {}

void IfNode::visitChildNodes(AstNodeVisitor &p_visitor) {
    if (condition)
        condition->accept(p_visitor);
    if (then_stmt)
        then_stmt->accept(p_visitor);
    if (else_stmt)
        else_stmt->accept(p_visitor);
}
