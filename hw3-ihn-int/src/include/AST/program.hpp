#ifndef AST_PROGRAM_NODE_H
#define AST_PROGRAM_NODE_H

#include "AST/ast.hpp"

#include "AST/CompoundStatement.hpp"
#include "visitor/AstNodeVisitor.hpp"
#include <memory>
#include <string>
#include <vector>

class ProgramNode final : public AstNode {
  private:
    std::string name;
    // TODO: return type
    // return type always be void
    // declarations, use _list as suffix
    std::vector<DeclNode*>* declaration_list;
    std::vector<FunctionNode*>* function_list;
    CompoundStatementNode *compound_statement;

  public:
    ~ProgramNode() = default;
    ProgramNode(
        const uint32_t line,
        const uint32_t col,
        const char *const p_name,
        // TODO: 
        // return type
        // return type always be void
        // declarations
        std::vector<DeclNode*>* p_declaration_list,
        // functions
        std::vector<FunctionNode*>* p_function_list,
        // compound statement
        CompoundStatementNode* p_compound_statement
    );

    // visitor pattern version: const char *getNameCString() const;
    const char *getNameCString() const;

    void print() override;
    
    void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
    void visitChildNodes(AstNodeVisitor &p_visitor) override;
};

#endif
