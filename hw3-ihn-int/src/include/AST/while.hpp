#ifndef __AST_WHILE_NODE_H
#define __AST_WHILE_NODE_H

#include "AST/ast.hpp"
#include "AST/expression.hpp"
#include "AST/CompoundStatement.hpp"
#include "visitor/AstNodeVisitor.hpp"
#include <string>
#include <memory>

class WhileNode : public AstNode {
  public:
    WhileNode(
        const uint32_t line,
        const uint32_t col,
        ExpressionNode *p_expression,
        CompoundStatementNode *p_compound_statement
    );
    ~WhileNode() = default;

    void print() override;
    
    void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
    void visitChildNodes(AstNodeVisitor &p_visitor) override;

  private:
    // TODO: expression
    ExpressionNode *expression;
    // compound statement
    CompoundStatementNode *compound_statement;
};

#endif
