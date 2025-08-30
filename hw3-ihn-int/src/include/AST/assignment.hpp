#ifndef __AST_ASSIGNMENT_NODE_H
#define __AST_ASSIGNMENT_NODE_H

#include "AST/ast.hpp"
#include "AST/VariableReference.hpp"
#include "AST/expression.hpp"
#include "visitor/AstNodeVisitor.hpp"
#include <string>
#include <memory>

class AssignmentNode : public AstNode {
  public:
    AssignmentNode(
        const uint32_t line, 
        const uint32_t col,
        // TODO: variable reference
        VariableReferenceNode* p_variable_reference,
        // expression
        ExpressionNode* p_expression
    );
    ~AssignmentNode() = default;

    void print() override;
    void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
    void visitChildNodes(AstNodeVisitor &p_visitor) override;

  private:
    // TODO: variable reference
    VariableReferenceNode* variable_reference;
    // expression
    ExpressionNode* expression;
};

#endif
