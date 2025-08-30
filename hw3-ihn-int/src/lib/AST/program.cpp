#include "AST/program.hpp"
#include "AST/decl.hpp"
#include "AST/function.hpp"

// TODO
ProgramNode::ProgramNode(
    const uint32_t line,
    const uint32_t col,
    const char *const p_name,
    std::vector<DeclNode*>* p_declaration_list,
    std::vector<FunctionNode*>* p_function_list,
    CompoundStatementNode* p_compound_statement
) : AstNode{line, col}, 
    name(p_name), 
    declaration_list(p_declaration_list), 
    function_list(p_function_list),
    compound_statement(p_compound_statement)
    {}

// visitor pattern version: 
const char *ProgramNode::getNameCString() const { 
    return name.c_str();
}

void ProgramNode::print() {
    // TODO
    // outputIndentationSpace();

    std::printf("program <line: %u, col: %u> %s %s\n",
                location.line, location.col,
                name.c_str(), "void");

    // TODO
    // incrementIndentation();
    // visitChildNodes();
    // decrementIndentation();
}


void ProgramNode::visitChildNodes(AstNodeVisitor &p_visitor) {  // visitor pattern version
    // TODO

    // declarations
    if (declaration_list) {
        for (auto &decl : *declaration_list) {
            if (decl) decl->accept(p_visitor);
        }
    }
    // functions
    if (function_list) {
        for (auto &func : *function_list){
            if (func) func->accept(p_visitor);
        }
    }

    compound_statement->accept(p_visitor);
}
