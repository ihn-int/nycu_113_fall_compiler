#include "AST/decl.hpp"

// TODO
DeclNode::DeclNode(
    const uint32_t line,
    const uint32_t col,
    std::vector<VariableNode*>* p_variable_list
) : AstNode{line, col},
    variable_list(p_variable_list),
    type_str("")
    {
        setTypeString();
    }

// TODO
DeclNode::DeclNode(
    const uint32_t line,
    const uint32_t col
) : AstNode{line, col},
    variable_list(nullptr),
    type_str("")
    {}

// TODO: You may use code snippets in AstDumper.cpp
void DeclNode::print() {}

void DeclNode::visitChildNodes(AstNodeVisitor &p_visitor) {
    for (auto &var : *variable_list) {
        if (var) var->accept(p_visitor);
    }
}

std::string DeclNode::getTypeString() const{
    return type_str;
};

void DeclNode::setTypeString(){
    type_str = "";
    for (auto &var : *variable_list) {
        type_str += var->getTypeString() + ", ";
    }
};

