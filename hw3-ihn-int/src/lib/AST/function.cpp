#include "AST/function.hpp"

// TODO
FunctionNode::FunctionNode(
    const uint32_t line,
    const uint32_t col,
    const char* const p_name,
    std::vector<DeclNode*>* p_declaration_list,
    VarType *p_return_type
) : AstNode{line, col},
    name(p_name),
    declaration_list(p_declaration_list),
    return_type(p_return_type),
    compound_statement(nullptr)
    {}

FunctionNode::FunctionNode(
    const uint32_t line,
    const uint32_t col,
    const char* const p_name,
    std::vector<DeclNode*>* p_declaration_list,
    VarType* p_return_type,
    CompoundStatementNode* p_compound_statement
) : AstNode{line, col},
    name(p_name),
    declaration_list(p_declaration_list),
    return_type(p_return_type),
    compound_statement(p_compound_statement)
    {}

// TODO: You may use code snippets in AstDumper.cpp
void FunctionNode::print() {}

void FunctionNode::visitChildNodes(AstNodeVisitor &p_visitor) {
    // TODO
    for(auto &decl : *declaration_list){
        if (decl) decl->accept(p_visitor);
    }
    if(compound_statement)
        compound_statement->accept(p_visitor);
}

const char* FunctionNode::getNameCString() const{
    return name.c_str();
}

const char* FunctionNode::getTypeCString() const{
    std::string return_str = "";
    switch (return_type->getType()) {
        case ScalarType::INTEGER: 
            return_str = "integer";
            break;
        case ScalarType::REAL:
            return_str = "real";
            break;
        case ScalarType::STRING:
            return_str = "string";
            break;
        case ScalarType::BOOL:
            return_str = "boolean";
            break;
        case ScalarType::VOID:
            return_str = "void";
            break;
        default: return_str = "";
    }

    std::string args_str = " (";
    for (auto &decl : *declaration_list){
        if (decl)
            args_str += decl->getTypeString();
    }
    if (!declaration_list->empty()){
        // pop out ", "
        args_str.pop_back();
        args_str.pop_back();
    }
    args_str += ")";

    std::string str = return_str + args_str;
    char* ret = new char[str.size() + 1];
    strcpy(ret, str.c_str());
    return ret;
}


