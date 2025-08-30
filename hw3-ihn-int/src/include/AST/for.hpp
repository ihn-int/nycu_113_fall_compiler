#ifndef __AST_FOR_NODE_H
#define __AST_FOR_NODE_H

#include "AST/ast.hpp"
#include "AST/decl.hpp"
#include "AST/assignment.hpp"
#include "AST/expression.hpp"
#include "AST/CompoundStatement.hpp"
#include "visitor/AstNodeVisitor.hpp"
#include <string>
#include <memory>

class ForNode : public AstNode {
  public:
    ForNode(
        const uint32_t line,
        const uint32_t col,
        // TODO: declaration
        DeclNode* p_declaration,
        // assignment
        AssignmentNode* p_assignment,
        // constant value
        ExpressionNode* p_condition,
        // compound statement
        CompoundStatementNode* p_compound_statement
    );
    ~ForNode() = default;

    void print() override;

    void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
    void visitChildNodes(AstNodeVisitor &p_visitor) override;

  private:
    // TODO: declaration
    DeclNode* declaration;
    // assignment
    AssignmentNode* assignment;
    // constant value
    ExpressionNode* condition;
    // compound statement
    CompoundStatementNode* compound_statement;
};

#endif
