#ifndef __AST_FUNCTION_INVOCATION_NODE_H
#define __AST_FUNCTION_INVOCATION_NODE_H

#include "AST/expression.hpp"
#include "visitor/AstNodeVisitor.hpp"
#include <string>
#include <memory>
#include <vector>
#include <string>

class FunctionInvocationNode : public ExpressionNode {
  public:
    FunctionInvocationNode(
        const uint32_t line,
        const uint32_t col,
        // TODO: function name
        const char* const p_func_name,
        //expressions
        std::vector<ExpressionNode*>* p_argument_list
    );
    ~FunctionInvocationNode() = default;

    const char *getNameCString() const;

    void print() override;
    void accept(AstNodeVisitor &p_visitor) override{ p_visitor.visit(*this); }
    void visitChildNodes(AstNodeVisitor &p_visitor) override;

  private:
    // TODO: function name
    std::string func_name;
    // expressions
    std::vector<ExpressionNode*>* argument_list;
};

#endif
