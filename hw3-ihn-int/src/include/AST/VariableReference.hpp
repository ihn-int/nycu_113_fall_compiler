#ifndef __AST_VARIABLE_REFERENCE_NODE_H
#define __AST_VARIABLE_REFERENCE_NODE_H

#include "AST/expression.hpp"
#include "visitor/AstNodeVisitor.hpp"
#include <string>
#include <memory>
#include <vector>

class VariableReferenceNode : public ExpressionNode {
  public:
    // normal reference
    VariableReferenceNode(
        const uint32_t line,
        const uint32_t col,
        const char* const p_name
    );
    // array reference
    VariableReferenceNode(
        const uint32_t line,
        const uint32_t col,
        const char* const p_name,
        std::vector<ExpressionNode*>* p_expression_list
    );
    ~VariableReferenceNode() = default;

    const char* getNameCString() const;
    
    void print() override;

    void accept(AstNodeVisitor &p_visitor) override{ p_visitor.visit(*this); };
    void visitChildNodes(AstNodeVisitor &p_visitor) override;

  private:
    // TODO: variable name
    std::string name;
    // expressions
    std::vector<ExpressionNode*>* expression_list;
};

#endif
