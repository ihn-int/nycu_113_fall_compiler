#include "AST/CompoundStatement.hpp"

// TODO
CompoundStatementNode::CompoundStatementNode(
    const uint32_t line,
    const uint32_t col, 
    std::vector<DeclNode*>* p_declaration_list,
    std::vector<AstNode*>* p_statement_list
) : AstNode{line, col},
    declaration_list(p_declaration_list),
    statement_list(p_statement_list)
    {}

// TODO: You may use code snippets in AstDumper.cpp
void CompoundStatementNode::print() {}

void CompoundStatementNode::visitChildNodes(AstNodeVisitor &p_visitor) {
    // TODO
    if (declaration_list){
        for (auto &decl : *declaration_list) {
            if (decl) decl->accept(p_visitor);
        }
    }
    if (statement_list) {
        for (auto &stmt : *statement_list){
            if (stmt) stmt->accept(p_visitor);
        }
    }
}
