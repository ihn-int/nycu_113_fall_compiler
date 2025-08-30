#include "AST/FunctionInvocation.hpp"

// TODO
FunctionInvocationNode::FunctionInvocationNode(
    const uint32_t line,
    const uint32_t col,
    const char* const p_func_name,
    std::vector<ExpressionNode*>* p_argument_list
) : ExpressionNode{line, col},
    func_name(p_func_name),
    argument_list(p_argument_list)
    {}

const char *FunctionInvocationNode::getNameCString() const{
    return func_name.c_str();
}
// TODO: You may use code snippets in AstDumper.cpp
void FunctionInvocationNode::print() {}

void FunctionInvocationNode::visitChildNodes(AstNodeVisitor &p_visitor) {
    // TODO
    for( auto &arg : *argument_list){
        if (arg) arg->accept(p_visitor);
    }
}
