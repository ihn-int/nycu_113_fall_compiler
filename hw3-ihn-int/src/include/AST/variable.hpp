#ifndef __AST_VARIABLE_NODE_H
#define __AST_VARIABLE_NODE_H

#include "AST/ast.hpp"
#include "AST/ConstantValue.hpp"
#include "visitor/AstNodeVisitor.hpp"
#include <string>
#include <memory>
#include <vector>

class VarType{
  public:
    // For scalar type
    VarType(
        ScalarType p_scalar_type
    );
    // For array type
    VarType(
        ScalarType p_scalar_type,
        std::vector<int>* p_array_dims
    );
    ~VarType() = default;

    ScalarType getType() const;
    std::vector<int> *getArrayDims() const;
  private:
    ScalarType type;
    std::vector<int> *array_dims;
};

class VariableNode : public AstNode {
  public:
    VariableNode(
        const uint32_t line,
        const uint32_t col,
        // TODO: variable name
        const char *const p_name
        // type
        // can't know at constructor, use set
        // constant value
        // can't know at constructor, use set
    );
    ~VariableNode() = default;

    void setTypeString(VarType* p_type);
    void setConstantValue(ConstantValueNode* p_constant_value);

    const char *getNameCString() const;
    const char *getTypeCString() const;
    std::string getTypeString() const;

    void print() override;

    void accept(AstNodeVisitor &p_visitor) override{ p_visitor.visit(*this); };
    void visitChildNodes(AstNodeVisitor &p_visitor) override;

  private:
    // TODO: variable name, type, constant value
    std::string name;
    std::string type_str;
    ConstantValueNode *constant_value;
};

#endif
