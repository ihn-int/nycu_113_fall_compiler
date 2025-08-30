#ifndef AST_EXPRESSION_NODE_H
#define AST_EXPRESSION_NODE_H

#include "AST/ast.hpp"
// for type of result
#include "AST/PType.hpp"

class ExpressionNode : public AstNode {
  public:
    ~ExpressionNode() = default;
    ExpressionNode(const uint32_t line, const uint32_t col)
        : AstNode{line, col} {}

    // functions of next assignment
    const PType* getReturnType() const { return type.get(); }
    void setReturnType(PType* ptype) { type.reset(ptype); }
    void setReturnType(const PType::PrimitiveTypeEnum ptype) {
        type.reset(new PType(ptype));
    }

  protected:
    // for carrying type of result of an expression
    // TODO: for next assignment
    PTypeSharedPtr type = nullptr;
};

#endif
