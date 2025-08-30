#ifndef __AST_COMPOUND_STATEMENT_NODE_H
#define __AST_COMPOUND_STATEMENT_NODE_H

#include "AST/ast.hpp"
#include "AST/decl.hpp"
#include "visitor/AstNodeVisitor.hpp"
#include <string>
#include <memory>

class CompoundStatementNode : public AstNode {
  public:
    CompoundStatementNode(
        const uint32_t line,
        const uint32_t col,
        // TODO: declarations
        std::vector<DeclNode*>* p_declaration_list,
        // statements
        std::vector<AstNode*>* p_statement_list
    );
    ~CompoundStatementNode() = default;

    void print() override;

    // visitor pattern
    void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
    void visitChildNodes(AstNodeVisitor &p_visitor) override;

  private:
    // TODO: declarations, statements
    std::vector<DeclNode*>* declaration_list;
    std::vector<AstNode*>* statement_list;
};

#endif
