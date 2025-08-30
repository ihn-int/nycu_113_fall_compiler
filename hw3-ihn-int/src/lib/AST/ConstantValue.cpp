#include "AST/ConstantValue.hpp"

// TODO
// integer
ConstantValueNode::ConstantValueNode(
    const uint32_t line,
    const uint32_t col,
    int p_int_value
) : ExpressionNode{line, col},
    int_value(p_int_value),
    type(ScalarType::INTEGER)
    {}

// real
ConstantValueNode::ConstantValueNode(
    const uint32_t line,
    const uint32_t col,
    float p_real_value
) : ExpressionNode{line, col},
    real_value(p_real_value),
    type(ScalarType::REAL)
    {}

// string
ConstantValueNode::ConstantValueNode(
    const uint32_t line,
    const uint32_t col,
    const char* const p_string_value
) : ExpressionNode{line, col},
    string_value(p_string_value),
    type(ScalarType::STRING)
    {}

// boolean
ConstantValueNode::ConstantValueNode(
    const uint32_t line,
    const uint32_t col,
    bool p_bool_value
) : ExpressionNode{line, col},
    bool_value(p_bool_value),
    type(ScalarType::BOOL)
    {}

const char *ConstantValueNode::getValueCString() const{
    const char* str;
    switch (type) {
        case ScalarType::INTEGER:
            str = std::to_string(int_value).c_str();
            break;
        case ScalarType::REAL:
            str = std::to_string(real_value).c_str();
            break;
        case ScalarType::STRING:
            str = string_value.c_str();
            break;
        case ScalarType::BOOL:
            str = bool_value ? "true" : "false";
            break;
        default: str = "";
    }

    return str;
}


std::string ConstantValueNode::getTypeString() const{
    switch (type) {
        case ScalarType::INTEGER: 
            return "integer";
        case ScalarType::REAL:
            return "real";
        case ScalarType::STRING:
            return "string";
        case ScalarType::BOOL:
            return "boolean";
        default: return "";
    }
}

// TODO: You may use code snippets in AstDumper.cpp
void ConstantValueNode::print() {}
