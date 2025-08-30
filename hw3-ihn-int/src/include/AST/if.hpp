#ifndef __AST_IF_NODE_H
#define __AST_IF_NODE_H

#include "AST/ast.hpp"
#include "AST/expression.hpp"
#include "AST/CompoundStatement.hpp"
#include "visitor/AstNodeVisitor.hpp"
#include <string>
#include <memory>

class IfNode : public AstNode {
  public:
    IfNode(
        const uint32_t line,
        const uint32_t col,
        // TODO: expression
        ExpressionNode *p_condition,
        // compound statement
        CompoundStatementNode *p_then_stmt,
        // compound statement, optional
        CompoundStatementNode *p_else_stmt
    );
    ~IfNode() = default;

    void print() override;

    void accept(AstNodeVisitor &p_visitor) override{ p_visitor.visit(*this); };
    void visitChildNodes(AstNodeVisitor &p_visitor) override;

  private:
    // TODO: expression
    ExpressionNode *condition;
    // compound statement
    CompoundStatementNode *then_stmt;
    // compound statement, optional
    CompoundStatementNode *else_stmt;
};

#endif
