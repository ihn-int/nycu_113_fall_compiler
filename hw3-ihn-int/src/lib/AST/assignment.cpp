#include "AST/assignment.hpp"

// TODO
AssignmentNode::AssignmentNode(
    const uint32_t line, 
    const uint32_t col, 
    VariableReferenceNode* p_variable_reference,
    ExpressionNode* p_expression
) : AstNode{line, col},
    variable_reference(p_variable_reference),
    expression(p_expression)
    {}

// TODO: You may use code snippets in AstDumper.cpp
void AssignmentNode::print() {}

void AssignmentNode::visitChildNodes(AstNodeVisitor &p_visitor) {
    if (variable_reference)
        variable_reference->accept(p_visitor);
    if (expression)
        expression->accept(p_visitor);
}
