#include "AST/expression.hpp"

ExpressionNode::ExpressionNode(
    const uint32_t line,
    const uint32_t col
) : AstNode{line, col}
    {}

Operator::Operator(OperatorType type)
    : type_str("") {
        switch(type){
            case OperatorType::NEG:
                type_str = "neg";
                break;
            case OperatorType::MUL:
                type_str = "*";
                break;
            case OperatorType::DIV:
                type_str = "/";
                break;
            case OperatorType::MOD:
                type_str = "mod";
                break;
            case OperatorType::ADD:
                type_str = "+";
                break;
            case OperatorType::SUB:
                type_str = "-";
                break;
            case OperatorType::LT:
                type_str = "<";
                break;
            case OperatorType::LE:
                type_str = "<=";
                break;
            case OperatorType::GT:
                type_str = ">";
                break;
            case OperatorType::GE:
                type_str = ">=";
                break;
            case OperatorType::EQ:
                type_str = "=";
                break;
            case OperatorType::NE:
                type_str = "<>";
                break;
            case OperatorType::NOT:
                type_str = "not";
                break;
            case OperatorType::AND:
                type_str = "and";
                break;
            case OperatorType::OR:
                type_str = "or";
                break;
            default: type_str = "";
        }
    }

const char* Operator::getTypeCString(){
    return type_str.c_str();
}