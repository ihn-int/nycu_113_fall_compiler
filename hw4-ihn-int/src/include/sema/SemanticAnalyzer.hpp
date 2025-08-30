#ifndef SEMA_SEMANTIC_ANALYZER_H
#define SEMA_SEMANTIC_ANALYZER_H

#include "sema/ErrorPrinter.hpp"
#include "visitor/AstNodeVisitor.hpp"
// For Symbol Table related
#include "sema/SymbolTable.hpp"
#include <stack>

class SemanticAnalyzer final : public AstNodeVisitor {
  private:
    ErrorPrinter m_error_printer{stderr};
    // TODO: something like symbol manager (manage symbol tables)
    //       context manager, return type manager
    const uint32_t opt_dmp;
    SymbolManager symbol_manager;
    std::stack<SymbolEntry*> function_stack;
    Attribute current_attribute;
    SymbolKind_e current_kind;
    bool has_error;
    bool is_in_loop = false;

  public:
    ~SemanticAnalyzer() = default;

    // use opt_dmp
    SemanticAnalyzer(const uint32_t _opt_dmp);
    const bool getError() const { return has_error; }

    void visit(ProgramNode &p_program) override;
    void visit(DeclNode &p_decl) override;
    void visit(VariableNode &p_variable) override;
    void visit(ConstantValueNode &p_constant_value) override;
    void visit(FunctionNode &p_function) override;
    void visit(CompoundStatementNode &p_compound_statement) override;
    void visit(PrintNode &p_print) override;
    void visit(BinaryOperatorNode &p_bin_op) override;
    void visit(UnaryOperatorNode &p_un_op) override;
    void visit(FunctionInvocationNode &p_func_invocation) override;
    void visit(VariableReferenceNode &p_variable_ref) override;
    void visit(AssignmentNode &p_assignment) override;
    void visit(ReadNode &p_read) override;
    void visit(IfNode &p_if) override;
    void visit(WhileNode &p_while) override;
    void visit(ForNode &p_for) override;
    void visit(ReturnNode &p_return) override;
};

#endif
