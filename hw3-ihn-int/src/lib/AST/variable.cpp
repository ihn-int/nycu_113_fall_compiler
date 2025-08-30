#include "AST/variable.hpp"

// VarType class
// For scalar type
VarType::VarType(
    ScalarType p_scalar_type
) : type(p_scalar_type),
    array_dims(nullptr)
    {}

// For array type
VarType::VarType(
    ScalarType p_scalar_type,
    std::vector<int>* p_array_dims
) : type(p_scalar_type),
    array_dims(p_array_dims)
    {}

ScalarType VarType::getType() const{
    return type;
};

std::vector<int> *VarType::getArrayDims() const{
    return array_dims;
};

// End of VarType class

// TODO
VariableNode::VariableNode(
    const uint32_t line,
    const uint32_t col,
    const char *const p_name
) : AstNode{line, col},
    name(p_name),
    type_str(""),
    constant_value(nullptr)
    {}

// TODO: You may use code snippets in AstDumper.cpp
void VariableNode::print() {}

void VariableNode::visitChildNodes(AstNodeVisitor &p_visitor){
    if (constant_value){
        constant_value->accept(p_visitor);
    }
};

void VariableNode::setTypeString(VarType* p_type) {
    std::string str = "";
    switch (p_type->getType()) {
        case ScalarType::INTEGER: 
            str = "integer";
            break;
        case ScalarType::REAL:
            str = "real";
            break;
        case ScalarType::STRING:
            str = "string";
            break;
        case ScalarType::BOOL:
            str = "boolean";
            break;
        default: str = "";
    }

    if (p_type->getArrayDims() != nullptr){
        str += " ";
		for (int index : *p_type->getArrayDims()) {
			str += "[" + std::to_string(index) + "]";
		}
    }
    this->type_str = str;
};

void VariableNode::setConstantValue(ConstantValueNode *p_constant_value){
    this->type_str = p_constant_value->getTypeString();
    this->constant_value = p_constant_value;
};

const char *VariableNode::getTypeCString() const{
    return type_str.c_str();
}

const char *VariableNode::getNameCString() const{
    return name.c_str();
};

std::string VariableNode::getTypeString() const{
    return type_str;
};
