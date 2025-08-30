#include "AST/CompoundStatement.hpp"
#include "AST/for.hpp"
#include "AST/function.hpp"
#include "AST/program.hpp"
#include "codegen/CodeGenerator.hpp"
#include "sema/SemanticAnalyzer.hpp"
#include "sema/SymbolTable.hpp"
#include "visitor/AstNodeInclude.hpp"

#include <algorithm>
#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

CodeGenerator::CodeGenerator(const std::string &source_file_name,
                             const std::string &save_path,
                             std::unordered_map<SemanticAnalyzer::AstNodeAddr,
                                                      SymbolManager::Table>
                                 &&p_symbol_table_of_scoping_nodes)
    : m_symbol_manager(false /* no dump */),
      m_source_file_path(source_file_name),
      m_symbol_table_of_scoping_nodes(std::move(p_symbol_table_of_scoping_nodes)) {
    // FIXME: assume that the source file is always xxxx.p
    const auto &real_path =
        save_path.empty() ? std::string{"."} : save_path;
    auto slash_pos = source_file_name.rfind('/');
    auto dot_pos = source_file_name.rfind('.');

    if (slash_pos != std::string::npos) {
        ++slash_pos;
    } else {
        slash_pos = 0;
    }
    auto output_file_path{
        real_path + "/" +
        source_file_name.substr(slash_pos, dot_pos - slash_pos) + ".S"};
    m_output_file.reset(fopen(output_file_path.c_str(), "w"));

    // Initiate other fields
    stack_pointer = 0;
    frame_pointer = 0;
    access_offset = -12;  // Follow the hint from the vedio
    // -4 is for old return address
    // -8 is for the old s0, the old sp is stored in new s0
    //     The s0 register works as frame pointer
    label_count = 0;      // no label at first;
    ref_side = RefSide::kLHS;
    table_found = true;   // assume the table always exist

    assert(m_output_file.get() && "Failed to open output file");
}

static void dumpInstructions(FILE *p_out_file, const char *format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(p_out_file, format, args);
    va_end(args);
}

//==========================================================
// Other functions
void CodeGenerator::allocateFrame() {
        constexpr const char* const prologue = 
        "# Allocate a frame\n"
        "    addi sp, sp, -128\n"
        "    sw ra, 124(sp)\n"
        "    sw s0, 120(sp)\n"
        "    addi s0, sp, 128\n"
        "\n";
    dumpInstructions(m_output_file.get(), prologue);
}

void CodeGenerator::pushStack() {
    stack_pointer -= 128;   // downward growth
    frame_pointer = stack_pointer + 128;
    access_offset = -12;    // reset the offset
}

void CodeGenerator::releaseFrame() {
    constexpr const char* const epilogue = 
        "# Release a frame\n"
        "    lw ra, 124(sp)\n"
        "    lw s0, 120(sp)\n"
        "    addi sp, sp, 128\n"
        "    jr ra\n"
        "\n";
    dumpInstructions(m_output_file.get(), epilogue);
}

void CodeGenerator::popStack() {
    stack_pointer += 128;
    frame_pointer = stack_pointer + 128;
    access_offset = -12;    // reset the offset
}

std::string CodeGenerator::getLabel() {
    label_count += 1;
    return std::string("L") + std::to_string(label_count - 1);
}

// Other constant value
const char* AXREG[] = {"a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7",
                       "t3", "t4", "t5", "t6" };

//==========================================================

void CodeGenerator::visit(ProgramNode &p_program) {
    // Generate RISC-V instructions for program header
    // clang-format off
    constexpr const char *const riscv_assembly_file_prologue =
        "    .file \"%s\"\n"
        "    .option nopic\n";
    // clang-format on
    dumpInstructions(m_output_file.get(), riscv_assembly_file_prologue,
                     m_source_file_path.c_str());

    // Reconstruct the scope for looking up the symbol entry.
    // Hint: Use m_symbol_manager->lookup(symbol_name) to get the symbol entry.

    // Check if the table exist
    if (m_symbol_table_of_scoping_nodes.find(&p_program) == 
        m_symbol_table_of_scoping_nodes.end()) {
            table_found = false;
    }
    else {
        table_found = true;
    }
    if (table_found) {
        m_symbol_manager.pushScope(
            std::move(m_symbol_table_of_scoping_nodes.at(&p_program)));
    }

    auto visit_ast_node = [&](auto &ast_node) { ast_node->accept(*this); };
    for_each(p_program.getDeclNodes().begin(), p_program.getDeclNodes().end(),
             visit_ast_node);
    for_each(p_program.getFuncNodes().begin(), p_program.getFuncNodes().end(),
             visit_ast_node);

    // Dump the prologue of the main function (at compound statement)
    dumpInstructions(m_output_file.get(),
                     "# The main function\n"
                     ".section    .text\n"
                     "    .align 2\n"
                     "    .globl main\n"
                     "    .type main, @function\n"
                     "main: \n");
    // The whole program should be viewed as the main function
    // Allocate frame here but not at compound statement node
    allocateFrame();
    pushStack();

    const_cast<CompoundStatementNode &>(p_program.getBody()).accept(*this);
    
    releaseFrame();
    popStack();

    // Dump the epilogue of the main function
    dumpInstructions(m_output_file.get(), 
                     "    .size main, .-main\n"
                     "# The end of main function");
    if (table_found) {
        m_symbol_manager.popScope();
    }
}

void CodeGenerator::visit(DeclNode &p_decl) {
    p_decl.visitChildNodes(*this);
    // Check var nodes
}

void CodeGenerator::visit(VariableNode &p_variable) {
    const char* var_id = p_variable.getNameCString();
    SymbolEntry* var = const_cast<SymbolEntry*>(m_symbol_manager.lookup(var_id));

    // Check if global variable
    if (var->getLevel() == 0) {
        // Check if constant since we don't have something like
        // 'getFunctionPtr'
        if (p_variable.getConstantPtr() != nullptr) {
            // Dump to readonly section
            dumpInstructions(
                m_output_file.get(),
                ".section    .rodata\n"
                "    .align 2\n"
                "    .globl %s\n"
                "    .type %s, @object\n"
                "%s:\n"
                "    .word %s\n",
                var_id,
                var_id,
                var_id,
                p_variable.getConstantPtr()->getConstantValueCString()
            );
        }
        else {  // varaible declaration
            dumpInstructions(m_output_file.get(),
                             ".comm %s, %d, %d\n", var_id, 4, 4);
        }
        return;
    }

    // Check if local varaible
    if (var->getLevel() > 0) {
        // We must save the address and reuse it when referencing it
        var->setAddress(frame_pointer + access_offset);
        std::string value;

        // Try to get constant value
        if (p_variable.getConstantPtr() != nullptr) {
            value = p_variable.getConstantPtr()->getConstantValueCString();
        }
        // local variable declaration without initialization
        // Initiate to 0
        else {
            value = "0";
        }

        // The local variable should be dumped to text section
        // and be allocated to temporary part of frame when executed
        dumpInstructions(m_output_file.get(),
                         "# Assign a constant to local variable\n"
                         "    addi t0, s0, %d\n" // get var address
                         "    addi sp, sp, -4\n" // allocate temp stack
                         "    sw t0, 0(sp)\n"    // store address to top
                         "    li t0, %s\n"       // load imm
                         "    addi sp, sp, -4\n" // allocate temp stack
                         "    sw t0, 0(sp)\n"    // store imm to top
                         "    lw t0, 0(sp)\n"    // load imm to t0
                         "    addi sp, sp, 4\n"  // release stack top
                         "    lw t1, 0(sp)\n"    // load address to t1
                         "    addi sp, sp, 4\n"  // release stack top
                         "    sw t0, 0(t1)\n"    // store the imm via address
                         "\n",
                         access_offset, value.c_str());
        access_offset -= 4; // Move to the next variable address
        return;
    }
    
    // Check if function parameters
    if (var->getKind() == SymbolEntry::KindEnum::kParameterKind) {
        // Set the address of the varaible
        var->setAddress(frame_pointer + access_offset);
        dumpInstructions(m_output_file.get(),
                         "    sw %s, %d(s0)\n",
                         AXREG[-(access_offset+12) / 4],
                         access_offset);
        access_offset -= 4;
        return;          
    }
}

void CodeGenerator::visit(ConstantValueNode &p_constant_value) {
    const char* const_value = p_constant_value.getConstantValueCString();

    // Check if boolean type variable
    if (p_constant_value.getTypePtr()->isBool()) {
        const_value = p_constant_value.getConstantPtr()->boolean() ? "1" : "0";
    }

    // Dump load var instructions
    dumpInstructions(m_output_file.get(),
                     "# Load a constant value\n"
                     "    li t0, %s\n"
                     "    addi sp, sp, -4\n"
                     "    sw t0, 0(sp)\n"
                     "\n",
                     const_value);
    // access_offset -= 4;
    stack_pointer -= 4;
}

void CodeGenerator::visit(FunctionNode &p_function) {
    // Reconstruct the scope for looking up the symbol entry.

    // Check if the table exist
    if (m_symbol_table_of_scoping_nodes.find(&p_function) ==
        m_symbol_table_of_scoping_nodes.end()) {
        table_found = false;
    }
    else {
        table_found = true;
    }
    if (table_found) {
        m_symbol_manager.pushScope(
            std::move(m_symbol_table_of_scoping_nodes.at(&p_function)));
    }
    
    // Dump function prologue
    dumpInstructions(
        m_output_file.get(),
        "# Declare a new function\n"
        ".section    .text\n"
        "    .align 2\n"
        "    .globl %s\n"
        "    .type %s, @function\n"
        "%s:\n",
        p_function.getName().c_str(),
        p_function.getName().c_str(),
        p_function.getName().c_str());
    allocateFrame();
    pushStack();
    
    // p_function.visitChildNodes(*this);
    
    // Traverse the parameters
    int idx = 0;
    for (const auto &parameter : p_function.getParameters()) {
        parameter->accept(*this);
        // Move the argument in ax register to frame
        for (int i = 0; i < parameter->getVariables().size(); i++) {
            dumpInstructions(m_output_file.get(),
                             "# Move ax register to %dst parameter\n"
                             "    sw %s, %d(s0)\n",
                             idx,
                             AXREG[idx],
                             -12 - (4*idx));
            idx++;
        }
    }
    dumpInstructions(m_output_file.get(),
                     "\n# Below are function body\n");
    p_function.visitBodyChildNodes(*this);
    
    // The frame is freed by return;
    popStack();
    // Dump function epilogue
    dumpInstructions(
        m_output_file.get(),
        "    .size %s, .-%s\n",
        p_function.getName().c_str(), 
        p_function.getName().c_str());

    // Remove the entries in the hash table
    if (table_found) {
        m_symbol_manager.popScope();
    }
}

//###
void CodeGenerator::visit(CompoundStatementNode &p_compound_statement) {
    // Reconstruct the scope for looking up the symbol entry.

    // Check if the table exist
    if (m_symbol_table_of_scoping_nodes.find(&p_compound_statement) ==
        m_symbol_table_of_scoping_nodes.end()) {
        table_found = false;
    }
    else {
        table_found = true;
    }
    if (table_found) {
        m_symbol_manager.pushScope(
            std::move(m_symbol_table_of_scoping_nodes.at(&p_compound_statement)));
    }
    /**/
    // Compound statement needn't dump

    p_compound_statement.visitChildNodes(*this);
    /**/
    if (table_found) {
        m_symbol_manager.popScope();
    }
    /**/
}

void CodeGenerator::visit(PrintNode &p_print) {
    // Visit right
    ref_side = RefSide::kRHS;
    p_print.visitChildNodes(*this);

    // Dump instructions, use jal
    dumpInstructions(m_output_file.get(),
                     "# Load stack top and call print\n"
                     "    lw a0, 0(sp)\n"
                     "    addi sp, sp, 4\n"
                     "    jal ra, printInt\n"
                     "\n");
    // access_offset += 4;
    stack_pointer += 4;
}

void CodeGenerator::visit(BinaryOperatorNode &p_bin_op) {
    ref_side = RefSide::kRHS;

    // Postorder traversal
    p_bin_op.visitChildNodes(*this);

    // Read operands from t0 and t1
    dumpInstructions(m_output_file.get(),
                     "# Load 2 operand and calculate\n"
                     "    lw t0, 0(sp)\n"       // Second operand
                     "    addi sp, sp, 4\n"
                     "    lw t1, 0(sp)\n"       // First operand
                     "    addi sp, sp, 4\n");
    // Operates based on the operator
    switch (p_bin_op.getOp()) {
        case Operator::kPlusOp:
            dumpInstructions(m_output_file.get(),
                             "    add t0, t1, t0\n");
            break;
        case Operator::kMinusOp:
            dumpInstructions(m_output_file.get(),
                             "    sub t0, t1, t0\n");
            break;
        case Operator::kMultiplyOp:
            dumpInstructions(m_output_file.get(),
                             "    mul t0, t1, t0\n");
            break;
        case Operator::kDivideOp:
            dumpInstructions(m_output_file.get(),
                             "    div t0, t1, t0\n");
            break;
        case Operator::kModOp:
            dumpInstructions(m_output_file.get(),
                             "    rem t0, t1, t0\n");
            break;
        case Operator::kLessOp:
            dumpInstructions(m_output_file.get(),
                             "    slt t0, t1, t0\n");
            break;
        case Operator::kLessOrEqualOp:
            dumpInstructions(m_output_file.get(),
                             "    slt t0, t0, t1\n" // Test greater
                             "    seqz t0, t0\n");  // Reverse
            break;
        case Operator::kGreaterOp:
            dumpInstructions(m_output_file.get(),
                             "    slt t0, t0, t1\n");
            break;
        case Operator::kGreaterOrEqualOp:
            dumpInstructions(m_output_file.get(),
                             "    slt t0, t1, t0\n" // Test less
                             "    seqz t0, t0\n");  // Reverse
            break;
        case Operator::kEqualOp:
            dumpInstructions(m_output_file.get(),
                             "    sub t0, t1, t0\n"
                             "    seqz t0, t0\n");
            break;
        case Operator::kNotEqualOp:
            dumpInstructions(m_output_file.get(),
                             "    sub t0, t1, t0\n"
                             "    snez t0, t0\n");
            break;
        case Operator::kAndOp:
            dumpInstructions(m_output_file.get(),
                             "    and t0, t1, t0\n");
            break;
        case Operator::kOrOp:
            dumpInstructions(m_output_file.get(),
                             "    or t0, t1, t0\n");
            break;
        default: break; // other may be NOT or NEG operator
    }

    // Dump the epilogue
    dumpInstructions(m_output_file.get(),
                     "\n# Store the value to top\n"
                     "    addi sp, sp, -4\n"
                     "    sw t0, 0(sp)\n"
                     "\n");
    // access_offset += 4;
    stack_pointer += 4;
}

void CodeGenerator::visit(UnaryOperatorNode &p_un_op) {
    ref_side = RefSide::kRHS;

    // Postorder traversal
    p_un_op.visitChildNodes(*this);

    // Check only the unary operators
    if (p_un_op.getOp() == Operator::kNegOp) {
        dumpInstructions(m_output_file.get(),
                         "# Load 1 operand and calculate\n"
                         "    lw t0, 0(sp)\n"
                         "    addi sp, sp, 4\n"
                         "    sub t0, zero, t0\n"
                         "    addi sp, sp, -4\n"
                         "    sw t0, 0(sp)\n"
                         "\n");
    }
    else if (p_un_op.getOp() == Operator::kNotOp) {
        dumpInstructions(m_output_file.get(),
                         "# Load 1 operand and calculate\n"
                         "    lw t0, 0(sp)\n"
                         "    addi sp, sp, 4\n"
                         "    seqz t0, t0\n"
                         "    addi sp, sp, -4\n"
                         "    sw t0,0(sp)\n"
                         "\n");
    }
}

void CodeGenerator::visit(FunctionInvocationNode &p_func_invocation) {
    // Postorder traversal
    p_func_invocation.visitChildNodes(*this);

    // Dump arguements to AX registers
    // The arguments are push to the stack from a0 to ax
    // We need to pop them and assign to ax to a0
    for (int i = p_func_invocation.getArguments().size()-1; i >= 0; i--) {
        dumpInstructions(m_output_file.get(),
                         "# Load %dst argument\n"
                         "    lw %s, 0(sp)\n"
                         "    addi sp, sp, 4\n",
                         i,
                         AXREG[i]);
        stack_pointer += 4; // Pop the stack top
    }

    dumpInstructions(m_output_file.get(),
                     "# Call the function and move return value to stack top\n"
                     "    jal ra, %s\n"
                     "    mv t0, a0\n"
                     "    addi sp, sp, -4\n"
                     "    sw t0, 0(sp)\n"
                     "\n",
                     p_func_invocation.getName().c_str());
    stack_pointer -= 4; // Push the result to stack top
}

void CodeGenerator::visit(VariableReferenceNode &p_variable_ref) {
    const auto var_id = p_variable_ref.getName();
    const auto var = m_symbol_manager.lookup(var_id);

    // Check if left
    if (ref_side == RefSide::kLHS) {
        // Get variable address
        // Check if global variable
        if (var->getLevel() == 0) {
            dumpInstructions(m_output_file.get(),
                             "    la t0, %s\n",
                             var->getNameCString());
        }
        else {  // Local variable
            dumpInstructions(m_output_file.get(),
                             "    addi t0, s0, %d\n",
                             var->getAddress() + frame_pointer);
        }
        // Push the variable value to stack top
        dumpInstructions(m_output_file.get(),
                         "    addi sp, sp, -4\n"
                         "    sw t0, 0(sp)\n");
        stack_pointer -= 4;
        return;
    }
    // Check if right
    else if (ref_side == RefSide::kRHS) {
        // Get variable address
        // Check if global variable
        if (var->getLevel() == 0) {
            dumpInstructions(m_output_file.get(),
                             "    la t0, %s\n"
                             "    lw t1, 0(t0)\n"
                             "    mv t0, t1\n",
                             var->getNameCString());
        }
        else {  // Local variable
            dumpInstructions(m_output_file.get(),
                             "    lw t0, %d(s0)\n",
                             var->getAddress() - frame_pointer);
        }
        // Push the variable to stack top
        dumpInstructions(m_output_file.get(),
                         "    addi sp, sp, -4\n"
                         "    sw t0, 0(sp)\n");
        stack_pointer -= 4;
        return;
    }
    return;
}

void CodeGenerator::visit(AssignmentNode &p_assignment) {
    // Visit left
    ref_side = RefSide::kLHS;
    const_cast<VariableReferenceNode&>(p_assignment.getLvalue()).accept(*this);

    // Visit right
    ref_side = RefSide::kRHS;
    const_cast<ExpressionNode&>(p_assignment.getExpr()).accept(*this);

    dumpInstructions(m_output_file.get(),
                     "# Load 2 value and assign\n"
                     "    lw t0, 0(sp)\n"
                     "    addi sp, sp, 4\n"
                     "    lw t1, 0(sp)\n"
                     "    addi sp, sp, 4\n"
                     "    sw t0, 0(t1)\n"
                     "\n");
    stack_pointer += 8; // Pop left and right
}

void CodeGenerator::visit(ReadNode &p_read) {
    // Visit left
    ref_side = RefSide::kLHS;
    const_cast<VariableReferenceNode&>(p_read.getTarget()).accept(*this);

    dumpInstructions(m_output_file.get(),
                     "# Call read and move return value to stack top\n"
                     "    jal ra, readInt\n"
                     "    lw t0, 0(sp)\n"
                     "    addi sp, sp, 4\n"
                     "    sw a0, 0(t0)\n"
                     "\n"); // Return value is stored in a0
    stack_pointer += 4; // Pop the stack top
}

void CodeGenerator::visit(IfNode &p_if) {
    // Visit the condition list
    // It should save the result at stack top
    const_cast<ExpressionNode&>(p_if.getCondition()).accept(*this);

    const std::string true_label = getLabel();
    const std::string false_label = getLabel();
    const std::string end_label = getLabel();

    // Dump the condition block
    // load condition and:
    //   jump if false
    //   fall through if true
    dumpInstructions(m_output_file.get(),
                     "# Make if prologue\n"
                     "    lw t0, 0(sp)\n"
                     "    addi sp, sp, 4\n"   // Pop the stack top
                     "    beqz t0, %s\n"
                     "# True Label:\n"
                     "%s:\n",
                     false_label.c_str(),
                     true_label.c_str());
    stack_pointer += 4; // Release the stack top

    // Traverse the true block
    const_cast<CompoundStatementNode*>(p_if.getBody())->accept(*this);

    // Dump the true block epilogue
    dumpInstructions(m_output_file.get(),
                     "    j %s\n" // End block
                     "# False label:\n"
                     "%s:\n",     // False block
                     end_label.c_str(),
                     false_label.c_str());

    // Traverse the false block
    if (p_if.getElseBody()) {
        const_cast<CompoundStatementNode*>(p_if.getElseBody())->accept(*this);
    }
    // Dump the false block epilogue (end label)
    dumpInstructions(m_output_file.get(),
                     "%s:\n",
                     end_label.c_str());
}

void CodeGenerator::visit(WhileNode &p_while) {
    const std::string enter_label = getLabel();
    const std::string body_label = getLabel();
    const std::string exit_label = getLabel();

    // Dump the while loop prologue
    dumpInstructions(m_output_file.get(),
                     "%s:\n",
                     enter_label.c_str());

    // Traverse the while loop condition
    const_cast<ExpressionNode&>(p_while.getCondition()).accept(*this);

    // Dump the condition block
    dumpInstructions(m_output_file.get(),
                     "    lw t0, 0(sp)\n"
                     "    addi sp, sp, 4\n" // Pop the stack
                     "    beqz t0, %s\n"
                     "%s:\n",
                     exit_label.c_str(),
                     body_label.c_str());
    stack_pointer += 4;

    // Traverse the while loop body
    // The instructions of body should be dump while traversed
    const_cast<CompoundStatementNode&>(p_while.getBody()).accept(*this);

    // Dump the body epilogue
    dumpInstructions(m_output_file.get(),
                     "    j %s\n"
                     "%s:\n",
                     enter_label.c_str(),
                     exit_label.c_str());
}

void CodeGenerator::visit(ForNode &p_for) {
    // Reconstruct the scope for looking up the symbol entry.

    // Check if the table exist
    if (m_symbol_table_of_scoping_nodes.find(&p_for) == 
        m_symbol_table_of_scoping_nodes.end()) {
        table_found = false;
    }
    else {
        table_found = true;
    }
    if (table_found) {
        m_symbol_manager.pushScope(
            std::move(m_symbol_table_of_scoping_nodes.at(&p_for)));
    }

    // p_for.visitChildNodes(*this);

    // Traverse the for loop variable
    // The declaration and initialization should be done before the loop
    const_cast<DeclNode&>(p_for.getLoopVarDecl()).accept(*this);
    const_cast<AssignmentNode&>(p_for.getInitStmt()).accept(*this);

    // Get the for loop label
    const std::string cond_label = getLabel();
    const std::string body_label = getLabel();
    const std::string exit_label = getLabel();

    // Dump the condition label
    dumpInstructions(m_output_file.get(),
                     "%s:\n",
                     cond_label.c_str());

    // Check the iteration bound
    ref_side = RefSide::kRHS;
    const_cast<VariableReferenceNode&>(p_for.getInitStmt().getLvalue()).accept(*this);
    const_cast<ConstantValueNode&>(p_for.getUpperBound()).accept(*this);

    dumpInstructions(m_output_file.get(),
                     "    lw t0, 0(sp)\n"   // Upperbound
                     "    addi sp, sp, 4\n"
                     "    lw t1, 0(sp)\n"   // Iteration variable
                     "    addi sp, sp, 4\n"
                     "    bge t1, t0, %s\n" // var > bound -> exit
                     "%s:\n",   // else -> fall through
                     exit_label.c_str(),
                     body_label.c_str());
    stack_pointer += 8;

    // Traverse the for loop body
    const_cast<CompoundStatementNode&>(p_for.getBody()).accept(*this);

    // Increment the iteration variable
    // The statement is like 'i = i + 1', thus, get left value twice
    ref_side = RefSide::kLHS;
    const_cast<VariableReferenceNode&>(p_for.getInitStmt().getLvalue()).accept(*this);
    ref_side = RefSide::kRHS;
    const_cast<VariableReferenceNode&>(p_for.getInitStmt().getLvalue()).accept(*this);

    dumpInstructions(m_output_file.get(),
                     "    li t0, 1\n"
                     "    lw t1, 0(sp)\n"   // RHS
                     "    addi sp, sp, 4\n"
                     "    add t0, t1, t0\n" // RHS + 1
                     "    lw t1, 0(sp)\n"   // LHS
                     "    addi sp, sp, 4\n"
                     "    sw t0, 0(t1)\n"
                     "    j %s\n"
                     "%s:\n",
                     cond_label.c_str(),
                     exit_label.c_str());
    stack_pointer += 8;

    // Remove the entries in the hash table
    if (table_found) {
        m_symbol_manager.popScope();
    }
}

void CodeGenerator::visit(ReturnNode &p_return) {
    // Traverse the return value
    ref_side = RefSide::kRHS;
    p_return.visitChildNodes(*this);

    // The return value should be assigned to a0
    dumpInstructions(m_output_file.get(),
                     "# Load value from stack top and return\n"
                     "    lw t0, 0(sp)\n"
                     "    addi sp, sp, 4\n"
                     "    mv a0, t0\n"
                     "\n");
    releaseFrame();
    //popStack();
    stack_pointer += 4;
}
