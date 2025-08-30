#ifndef __AST_DECL_NODE_H
#define __AST_DECL_NODE_H

#include "AST/ast.hpp"
#include "AST/variable.hpp"
#include "visitor/AstNodeVisitor.hpp"
#include <string>
#include <memory>
#include <vector>

class DeclNode : public AstNode {
  public:
    // variable declaration
    DeclNode(
        const uint32_t line,
        const uint32_t col,
        // TODO: identifiers
        std::vector<VariableNode*>* p_variable_list
        // TODO: type
        // in variables
    );

    // constant variable declaration
    DeclNode(
        const uint32_t line,
        const uint32_t col
        // TODO: identifiers
        // can't assign at constructor, use set
        // constant 
        // can't assign at constructor, use set
    );

    ~DeclNode() = default;

    std::string getTypeString() const;
    void setTypeString();

    void print() override;

    void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); };
    void visitChildNodes(AstNodeVisitor &p_visitor) override;

  private:
    // TODO: variables
    std::vector<VariableNode*>* variable_list;
    // string of types of vars
    std::string type_str;
};

#endif
