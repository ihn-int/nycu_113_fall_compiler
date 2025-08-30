#ifndef __AST_CONSTANT_VALUE_NODE_H
#define __AST_CONSTANT_VALUE_NODE_H

#include "AST/expression.hpp"
#include "visitor/AstNodeVisitor.hpp"
#include <string>
#include <memory>

enum class ScalarType {
    INTEGER,
    REAL,
    STRING,
    BOOL,
    VOID,
    UNDEFINED   // UNKNOWN is used at the other class
};

class ConstantValueNode : public ExpressionNode {
  public:
    ConstantValueNode(
        const uint32_t line,
        const uint32_t col,
        // TODO: constant value, integer
        int p_int_value
    );
    ConstantValueNode(
        const uint32_t line,
        const uint32_t col,
        // TODO: constant value, real
        float p_real_value
    );
    ConstantValueNode(
        const uint32_t line,
        const uint32_t col,
        // TODO: constant value, boolean
        bool p_bool_value
    );
    ConstantValueNode(
        const uint32_t line,
        const uint32_t col,
        // TODO: constant value, string
        const char* const p_string_value
    );
    ~ConstantValueNode() = default;

    const char *getValueCString() const;
    std::string getTypeString() const;

    void print() override;

    void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
    // no child nodes
    void visitChildNodes(AstNodeVisitor &p_visitor) override { } 


  private:
    // TODO: constant value
    int int_value;
    float real_value;
    bool bool_value;
    std::string string_value;
    ScalarType type;

};

#endif
