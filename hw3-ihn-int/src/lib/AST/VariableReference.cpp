#include "AST/VariableReference.hpp"

// TODO, normal reference
VariableReferenceNode::VariableReferenceNode(
    const uint32_t line,
    const uint32_t col,
    const char* const p_name
) : ExpressionNode{line, col},
    name(p_name),
    expression_list(
        // it might be an array reference later
        new std::vector<ExpressionNode*>()
    )
    {}

// TODO, array reference
VariableReferenceNode::VariableReferenceNode(
    const uint32_t line,
    const uint32_t col,
    const char* const p_name,
    std::vector<ExpressionNode*>* p_expression_list
) : ExpressionNode{line, col},
    name(p_name),
    expression_list(p_expression_list)
    {}

// TODO: You may use code snippets in AstDumper.cpp
void VariableReferenceNode::print() {}

void VariableReferenceNode::visitChildNodes(AstNodeVisitor &p_visitor) {
    // TODO
    for (auto &expr : *expression_list){
        if (expr)
            expr->accept(p_visitor);
    }
}

const char* VariableReferenceNode::getNameCString() const{
    return name.c_str();
}
