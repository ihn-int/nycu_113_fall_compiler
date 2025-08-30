#ifndef __AST_FUNCTION_NODE_H
#define __AST_FUNCTION_NODE_H

#include "AST/ast.hpp"
#include "AST/decl.hpp"
#include "AST/CompoundStatement.hpp"
#include "AST/variable.hpp"
#include "visitor/AstNodeVisitor.hpp"
#include <string>
#include <memory>
#include <cstring>
#include <vector>

class FunctionNode : public AstNode {
  public:
    FunctionNode(
        const uint32_t line,
        const uint32_t col,
        // TODO: name
        const char* const p_name,
        // declarations
        std::vector<DeclNode*>* p_declaration_list,
        // return type
        VarType *p_return_type
    );

    FunctionNode(
        const uint32_t line, 
        const uint32_t col,
        // TODO: name
        const char* const p_name,
        // declarations
        std::vector<DeclNode *> *p_declaration_list,
        // return type
        VarType *p_return_type,
        // compound statement (optional)
        CompoundStatementNode *p_compound_statement
    );
    ~FunctionNode() = default;

    const char* getNameCString() const;
    const char* getTypeCString() const;

    void print() override;

    void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
    void visitChildNodes(AstNodeVisitor &p_visitor) override;
  private:
    // TODO: name
    std::string name;
    // declarations
    std::vector<DeclNode*>* declaration_list;
    // return type
    VarType* return_type;
    // compound statement
    CompoundStatementNode* compound_statement;
};

#endif
