#include "sema/Error.hpp"
#include "sema/SemanticAnalyzer.hpp"
#include "visitor/AstNodeInclude.hpp"


SemanticAnalyzer::SemanticAnalyzer(
    const uint32_t _opt_dmp
) : opt_dmp(_opt_dmp),
    has_error(false)
    {}

// TODO:
    // 1. Push a new symbol table if this node forms a scope.
    // 2. Insert the symbol into current symbol table if this node is related to
    //    declaration (ProgramNode, VariableNode, FunctionNode).
    // 3. Traverse child nodes of this node.
    // 4. Perform semantic analyses of this node.
    // 5. Pop the symbol table pushed at the 1st step.

void SemanticAnalyzer::visit(ProgramNode &p_program) {
    // TODO:
    // 1. Push a new symbol table if this node forms a scope.
    // ProgramNode forms a scope
    // Create a new table
    current_kind = SymbolKind_e::PROGRAM;
    PTypeSharedPtr prog_type = std::make_shared<PType>(PType::PrimitiveTypeEnum::kVoidType);
    int scope = symbol_manager.getScope();

    SymbolTable* new_table = new SymbolTable(scope);
    SymbolEntry* new_entry = new SymbolEntry (
        p_program.getNameCString(),  // IdInfo name
        p_program.getLocation(),    // IdInfo location
        SymbolKind_e::PROGRAM,
        0,  // The scope of program is always 0
        prog_type
    );
    new_table->addEntry(new_entry);
    symbol_manager.pushScope(new_table);
    // Since we set the original scope to be -1, the scope is 0 (global) now.
    // 2. Insert the symbol into current symbol table if this node is related to
    //    declaration (ProgramNode, VariableNode, FunctionNode).
    // ProgramNode is not related to decalration, I guess
    // 3. Traverse child nodes of this node.
    function_stack.push(new_entry);
    p_program.visitChildNodes(*this);
    function_stack.pop();
    // 4. Perform semantic analyses of this node.
    
    // 5. Pop the symbol table pushed at the 1st step.    
    if (opt_dmp) {
        symbol_manager.dumpTopTable();
    }
    symbol_manager.popScope();
}

void SemanticAnalyzer::visit(DeclNode &p_decl) {
    p_decl.visitChildNodes(*this);
}

void SemanticAnalyzer::visit(VariableNode &p_variable) {
    // TODO:
    // 1. Push a new symbol table if this node forms a scope.
    // VariableNode doesn't form a scope

    // 2. Insert the symbol into current symbol table if this node is related to
    //    declaration (ProgramNode, VariableNode, FunctionNode).
    SymbolTable* current_table = symbol_manager.getTopTable();
    int scope = symbol_manager.getScope();
    SymbolKind_e var_kind;
    bool semantic_error = false;

    // traverse child nodes first
    p_variable.visitChildNodes(*this);

    // different type should be set under different kind of table
    switch(current_kind) {
        case SymbolKind_e::PROGRAM :  // Under a program, variable
            var_kind = SymbolKind_e::VARIABLE;
            break;
        case SymbolKind_e::FUNCTION : // Under a function, parameter
            var_kind = SymbolKind_e::PARAMETER;
            break;
        default: var_kind = current_kind;
    }
    SymbolEntry* new_entry = new SymbolEntry(
        p_variable.getNameCString(),
        p_variable.getLocation(),
        var_kind,
        scope,
        p_variable.getType()
    );
    if (current_kind == SymbolKind_e::CONSTANT) {
        // set constant attribute
        new_entry->setConstAttr(current_attribute.constant);
        current_kind = SymbolKind_e::VARIABLE;
    }

    // 3. Traverse child nodes of this node.
    // 4. Perform semantic analyses of this node.
    // Redeclaration Error, check if current table exists a variable
    SymbolEntry* redecl_entry = symbol_manager.getEntryByName(p_variable.getNameString());
    //SymbolEntry* redecl_entry = current_table->getEntryByName(p_variable.getNameString());

    if (redecl_entry != nullptr) {
        // The entry is already exist, further check the scope
        if (redecl_entry->getLevel() == symbol_manager.getScope() ||
            redecl_entry->getKind() == SymbolKind_e::LOOP_VAR) {
            has_error = true;
            semantic_error = true;
            // Since the constructor is deleted, we use new here
            SymbolRedeclarationError* redecl_err = new SymbolRedeclarationError(
                p_variable.getLocation(),
                p_variable.getNameString()
            );
            m_error_printer.print(*redecl_err);
            delete redecl_err;
        }
    }

    // Size of array must be greater than 0
    if (p_variable.getType()->getDimension() > 0) {
        // array type
        auto dimensions = p_variable.getType()->getDimensionArray();
        for (auto dim : dimensions) {
            if (dim <= 0) { // Error! set entry error
                new_entry->setError(true);
                has_error = true;
                //semantic_error = true;
                NonPositiveArrayDimensionError* dim_err = new NonPositiveArrayDimensionError(
                    p_variable.getLocation(),
                    p_variable.getNameString()
                );
                m_error_printer.print(*dim_err);
                delete dim_err;
            }
        }
    }
    // add this entry to table
    // We shall move the add operation here, otherwise it will be confused
    // with the previously added one.
    if (!semantic_error) {
        current_table->addEntry(new_entry);
    }

    // 5. Pop the symbol table pushed at the 1st step.
    // VariableNode doesn't form a scope

}

void SemanticAnalyzer::visit(ConstantValueNode &p_constant_value) {
    // TODO:
    // 1. Push a new symbol table if this node forms a scope.
    // ConstantValueNode doesn't forms a scope
    // 2. Insert the symbol into current symbol table if this node is related to
    //    declaration (ProgramNode, VariableNode, FunctionNode).
    // ConstantValueNode isn't related to declaration
    // But we need to set the constatn attribute and return
    current_kind = SymbolKind_e::CONSTANT;
    current_attribute.constant = p_constant_value.getConstant();
    p_constant_value.setReturnType(
        p_constant_value.getTypeSharedPtr()->getPrimitiveType()
    );
    // 3. Traverse child nodes of this node.
    // No child nodes of ConstantValueNode
    // 4. Perform semantic analyses of this node.
    // No sematic analyses of this node
    // 5. Pop the symbol table pushed at the 1st step.
    // ConstantValueNode doesn't form a scope
}

void SemanticAnalyzer::visit(FunctionNode &p_function) {
    // TODO:
    // 1. Push a new symbol table if this node forms a scope.
    // FunctionNode forms a scope, itself is in current scope
    int scope = symbol_manager.getScope();
    current_kind = SymbolKind_e::FUNCTION;
    bool semantic_error = false;
    SymbolTable* new_table = new SymbolTable(scope);
    SymbolTable* current_table = symbol_manager.getTopTable();

    // Perform redeclaration checking first
    SymbolEntry* redecl_entry = symbol_manager.getEntryByName(p_function.getNameString());
    //SymbolEntry* redecl_entry = current_table->getEntryByName(p_function.getNameString());
    if (redecl_entry != nullptr) {
        // The entry is already exist, further check the entry
        if (redecl_entry->getLevel() == symbol_manager.getScope() || 
            redecl_entry->getKind() == SymbolKind_e::LOOP_VAR) {
            has_error = true;
            semantic_error = true;
            SymbolRedeclarationError* redecl_err = new SymbolRedeclarationError(
                p_function.getLocation(),
                p_function.getNameString()
            );
            m_error_printer.print(*redecl_err);
            delete redecl_err;
        }
    }
    // Push new scope, parameters and function body should be recorded here
    symbol_manager.pushScope(new_table);

    // 2. Insert the symbol into current symbol table if this node is related to
    //    declaration (ProgramNode, VariableNode, FunctionNode).
    // Create function symbol entry
    SymbolEntry* new_entry = new SymbolEntry(
        p_function.getNameCString(),
        p_function.getLocation(),
        SymbolKind_e::FUNCTION,
        scope,
        p_function.getReturnType()
    );
    new_entry->setFuncAttr(&p_function);
    // FunctionNode is inserted to current table
    if (!semantic_error) {
        current_table->addEntry(new_entry);
    }

    // 3. Traverse child nodes of this node.
    function_stack.push(new_entry);
    p_function.visitParameters(*this);

    current_kind = SymbolKind_e::FUNCTION;
    p_function.visitFuncBody(*this);
    function_stack.pop();
    // 4. Perform semantic analyses of this node.
    // Performed before
    // 5. Pop the symbol table pushed at the 1st step.
    if (opt_dmp) {
        symbol_manager.dumpTopTable();
    }
    symbol_manager.popScope();
}

void SemanticAnalyzer::visit(CompoundStatementNode &p_compound_statement) {
    // TODO:
    // 1. Push a new symbol table if this node forms a scope.
    // CompoundStatementNode forms a scope
    int scope = symbol_manager.getScope();
    SymbolTable* new_table;
    bool call_from_function = (current_kind == SymbolKind_e::FUNCTION);
    if (call_from_function) {
        new_table = symbol_manager.getTopTable();
    }
    else {
        new_table = new SymbolTable(scope);
        symbol_manager.pushScope(new_table);
    }
    // 2. Insert the symbol into current symbol table if this node is related to
    //    declaration (ProgramNode, VariableNode, FunctionNode).
    // CompoundStatementNode isn't related to declaration
    // 3. Traverse child nodes of this node.
    current_kind = SymbolKind_e::VARIABLE;
    p_compound_statement.visitChildNodes(*this);
    // 4. Perform semantic analyses of this node.
    // No semantic analyses of this node
    // 5. Pop the symbol table pushed at the 1st step.
    // For function definition, the compound statement will be print by FunctionNode
    if (!call_from_function) {
        if (opt_dmp) {
            symbol_manager.dumpTopTable();
        }
        symbol_manager.popScope();
    }
    
}

void SemanticAnalyzer::visit(PrintNode &p_print) {
    // TODO:
    // 1. Push a new symbol table if this node forms a scope.
    // PrintNode doesn't form a scope
    // 2. Insert the symbol into current symbol table if this node is related to
    //    declaration (ProgramNode, VariableNode, FunctionNode).
    // PrintNode isn't related to declaration
    // 3. Traverse child nodes of this node.
    p_print.visitChildNodes(*this);
    // 4. Perform semantic analyses of this node.
    const PType* return_type = p_print.getTarget().getReturnType();
    if (return_type && !return_type->isScalar()) {
        // Error: print target isn't a scalar type
        has_error = true;
        PrintOutNonScalarTypeError* print_err = new PrintOutNonScalarTypeError(
            p_print.getTarget().getLocation()
        );
        m_error_printer.print(*print_err);
        delete print_err;
    }
    // 5. Pop the symbol table pushed at the 1st step.
    // No scope needs to be popped
}

void SemanticAnalyzer::visit(BinaryOperatorNode &p_bin_op) {
    // TODO:
    // 1. Push a new symbol table if this node forms a scope.
    // 2. Insert the symbol into current symbol table if this node is related to
    //    declaration (ProgramNode, VariableNode, FunctionNode).
    // 3. Traverse child nodes of this node.
    p_bin_op.visitChildNodes(*this);
    // 4. Perform semantic analyses of this node.
    const PType* left_type = p_bin_op.getLeftOperandType();
    const PType* right_type = p_bin_op.getRightOperandType();
    Operator op = p_bin_op.getOperator();

    // No operand 
    if (!left_type || !right_type) {
        return;
    }

    // Check if operand can be casted
    switch(op) {
        case Operator::kPlusOp:
            if (left_type->isString() && right_type->isString()) {
                // set type string
                p_bin_op.setReturnType(PType::PrimitiveTypeEnum::kStringType);
                return;
            }
        case Operator::kMinusOp:
        case Operator::kMultiplyOp:
        case Operator::kDivideOp:
            if (!(left_type->isInteger()  || left_type->isReal()) ||
                !(right_type->isInteger() || right_type->isReal()))
                // Error, not expected type
                break;
            p_bin_op.setReturnType(
                (left_type->isReal() || right_type->isReal()) ?
                    PType::PrimitiveTypeEnum::kRealType :
                    PType::PrimitiveTypeEnum::kIntegerType
            );
            return;
        // Mod Operator
        case Operator::kModOp:
            if (!left_type->isInteger() || !right_type->isInteger())
                // mod is only for integer
                break;
            p_bin_op.setReturnType(PType::PrimitiveTypeEnum::kIntegerType);
            return;
        // Bool Operator
        case Operator::kAndOp:
        case Operator::kOrOp:
            if (!(left_type->isBool() && right_type->isBool()))
                // Error, not expected type
                break;
            p_bin_op.setReturnType(PType::PrimitiveTypeEnum::kBoolType);
            return;
        // Relational Operator
        case Operator::kLessOp:
        case Operator::kLessOrEqualOp:
        case Operator::kGreaterOp:
        case Operator::kGreaterOrEqualOp:
        case Operator::kEqualOp:
        case Operator::kNotEqualOp:
            if (!(left_type->isInteger()  || left_type->isReal()) || 
                !(right_type->isInteger() || right_type->isReal()))
                break;
            p_bin_op.setReturnType(PType::PrimitiveTypeEnum::kBoolType);
            return;
        default: break;
    }
    has_error = true;
    InvalidBinaryOperandError* bin_op_err = new InvalidBinaryOperandError(
        p_bin_op.getLocation(),
        op,
        left_type,
        right_type
    );
    m_error_printer.print(*bin_op_err);
    delete bin_op_err;
    // A null return type will be given to an expresion if there is an error
    // 5. Pop the symbol table pushed at the 1st step.
    // No needs to pop scope
}

void SemanticAnalyzer::visit(UnaryOperatorNode &p_un_op) {
    // TODO:
    // 1. Push a new symbol table if this node forms a scope.
    // 2. Insert the symbol into current symbol table if this node is related to
    //    declaration (ProgramNode, VariableNode, FunctionNode).
    // 3. Traverse child nodes of this node.
    p_un_op.visitChildNodes(*this);
    // 4. Perform semantic analyses of this node.
    const PType* operand_type = p_un_op.getOperandType();
    Operator op = p_un_op.getOperator();
    if (!operand_type) {
        // I guess it's because of variable reference
        return;
    }
    if (operand_type) {
        switch(op) {
            case Operator::kNegOp:
                if (!(operand_type->isInteger() || operand_type->isReal())) {
                    has_error = true;
                    InvalidUnaryOperandError* un_op_err = new InvalidUnaryOperandError(
                        p_un_op.getLocation(),
                        op,
                        operand_type
                    );
                    m_error_printer.print(*un_op_err);
                    delete un_op_err;
                    break;
                }
                break;
            case Operator::kNotOp:
                if (!operand_type->isBool()) {
                    has_error = true;
                    InvalidUnaryOperandError* un_op_err = new InvalidUnaryOperandError(
                        p_un_op.getLocation(),
                        op,
                        operand_type
                    );
                    m_error_printer.print(*un_op_err);
                    delete un_op_err;
                    break;
                }
                return;
            default:
                break;
        }
    }
    
    // 5. Pop the symbol table pushed at the 1st step.
    // No needs to pop scope.
}

void SemanticAnalyzer::visit(FunctionInvocationNode &p_func_invocation) {
    // TODO:
    // 1. Push a new symbol table if this node forms a scope.
    // 2. Insert the symbol into current symbol table if this node is related to
    //    declaration (ProgramNode, VariableNode, FunctionNode).
    // 3. Traverse child nodes of this node.
    p_func_invocation.visitChildNodes(*this);
    // 4. Perform semantic analyses of this node.
    SymbolEntry* func_entry = symbol_manager.getEntryByName(p_func_invocation.getNameString());
    if (func_entry == nullptr) {
        // undeclaration Error
        has_error = true;
        UndeclaredSymbolError* udfunc_err = new UndeclaredSymbolError(
            p_func_invocation.getLocation(),
            p_func_invocation.getNameString()
        );
        m_error_printer.print(*udfunc_err);
        delete udfunc_err;
        return;
    }

    if (func_entry->getKind() != SymbolKind_e::FUNCTION) {
        // nonfunction Error
        has_error = true;
        NonFunctionSymbolError* nonfunc_err = new NonFunctionSymbolError(
            p_func_invocation.getLocation(),
            p_func_invocation.getNameString()
        );
        m_error_printer.print(*nonfunc_err);
        delete nonfunc_err;
        return;
    }

    const FunctionNode* func_def = func_entry->getFuncAttr();
    const auto &arguments = p_func_invocation.getArgs();
    const auto &parameters = func_def->getParameters();

    if (arguments.size() != parameters.size()) {
        // arguments number mismatch Error
        has_error = true;
        ArgumentNumberMismatchError* nmiss_err = new ArgumentNumberMismatchError(
            p_func_invocation.getLocation(),
            p_func_invocation.getNameString()
        );
        m_error_printer.print(*nmiss_err);
        delete nmiss_err;
        return;
    }

    for (size_t i = 0; i < arguments.size(); i++) {
        auto arg_type = arguments[i]->getReturnType();
        auto prm_type = parameters[i]->getVariables()[0]->getType();
        if (arg_type == nullptr) {
            // Skip
            continue;
        }
        if (arg_type->isInteger() && prm_type->isReal())
            continue;   // casting is allowed
        if (!(*arg_type == *prm_type.get())) {
            // one of the arguments mismatched
            has_error = true;
            IncompatibleArgumentTypeError* incarg_err = new IncompatibleArgumentTypeError(
                arguments[i]->getLocation(),
                prm_type.get(),
                arg_type
            );
            m_error_printer.print(*incarg_err);
            delete incarg_err;
            return;
        }
    }
    p_func_invocation.setReturnType(func_entry->getType()->getPrimitiveType());
    // 5. Pop the symbol table pushed at the 1st step.
    // No needs to pop scope
}

void SemanticAnalyzer::visit(VariableReferenceNode &p_variable_ref) {
    // TODO:
    // 1. Push a new symbol table if this node forms a scope.
    // VariableReferenceNode doesn't form a scope
    // 2. Insert the symbol into current symbol table if this node is related to
    //    declaration (ProgramNode, VariableNode, FunctionNode).
    // VariableReferenceNode is not related to declaration
    // 3. Traverse child nodes of this node.
    p_variable_ref.visitChildNodes(*this);
    // 4. Perform semantic analyses of this node.
    // Check undefined Error
    SymbolEntry* ref_entry = symbol_manager.getEntryByName(p_variable_ref.getNameString());
    if (ref_entry == nullptr) {
        // Undefined Error
        has_error = true;
        UndeclaredSymbolError* udvar_err = new UndeclaredSymbolError (
            p_variable_ref.getLocation(),
            p_variable_ref.getNameString()
        );
        m_error_printer.print(*udvar_err);
        delete udvar_err;
        return;
    }

    // Check if use non variable symbol
    if (ref_entry->getKind() != SymbolKind_e::VARIABLE && 
        ref_entry->getKind() != SymbolKind_e::PARAMETER &&
        ref_entry->getKind() != SymbolKind_e::LOOP_VAR &&
        ref_entry->getKind() != SymbolKind_e::CONSTANT) {
        // Non variable symbol Error
        has_error = true;
        NonVariableSymbolError* nvar_err = new NonVariableSymbolError(
            p_variable_ref.getLocation(),
            p_variable_ref.getNameString()
        );
        m_error_printer.print(*nvar_err);
        delete nvar_err;
        return;
    }

    if (ref_entry->getError()) {
        // skip if the entry contains error
        return;
    }

    // Check array index
    for (auto &idx : p_variable_ref.getIndices()) {
        if (idx->getReturnType() == nullptr)
            return;
        if (!idx->getReturnType()->isInteger()) {
            // Non integer array index Error
            has_error = true;
            NonIntegerArrayIndexError* niidx_err = new NonIntegerArrayIndexError(
                idx->getLocation()
            );
            m_error_printer.print(*niidx_err);
            delete niidx_err;
            return;
        }
    }

    if (p_variable_ref.getDimension() > ref_entry->getType()->getDimension()) {
        // Over array subscript Error
        has_error = true;
        OverArraySubscriptError* ovarr_err = new OverArraySubscriptError(
            p_variable_ref.getLocation(),
            p_variable_ref.getNameString()
        );
        m_error_printer.print(*ovarr_err);
        delete ovarr_err;
        return;
    }
    auto var_ref_type = ref_entry->getType()->getArrayReferenceType(p_variable_ref.getDimension());
    PType* ptype = new PType(ref_entry->getType()->getPrimitiveType());
    ptype->setDimensions(var_ref_type->getDimensionArray());
    p_variable_ref.setReturnType(ptype);
    // 5. Pop the symbol table pushed at the 1st step.
    // No needs to pop scope
}

void SemanticAnalyzer::visit(AssignmentNode &p_assignment) {
    // TODO:
    // 1. Push a new symbol table if this node forms a scope.
    // 2. Insert the symbol into current symbol table if this node is related to
    //    declaration (ProgramNode, VariableNode, FunctionNode).
    // 3. Traverse child nodes of this node.
    p_assignment.visitChildNodes(*this);
    // 4. Perform semantic analyses of this node.
    const VariableReferenceNode* lhs_value = p_assignment.getLeftVarRef();
    SymbolEntry* lhs_entry = symbol_manager.getEntryByName(lhs_value->getNameString());
    if (lhs_entry == nullptr) {
        // Undefined symbol Error
        return;
    }

    if (lhs_value->getReturnType()->isArray()) {
        // assign with array Error
        has_error = true;
        AssignWithArrayTypeError* warr_err = new AssignWithArrayTypeError(
            lhs_value->getLocation()
        );
        m_error_printer.print(*warr_err);
        delete warr_err;
        return;
    }
    if (lhs_entry->getKind() == SymbolKind_e::CONSTANT) {
        // Assign to constant Error
        has_error = true;
        AssignToConstantError* atoc_err = new AssignToConstantError(
            lhs_value->getLocation(),
            lhs_value->getNameString()
        );
        m_error_printer.print(*atoc_err);
        delete atoc_err;
        return;
    }
    if (is_in_loop && lhs_entry->getKind() == SymbolKind_e::LOOP_VAR) {
        // Assign to loop var Error
        has_error = true;
        AssignToLoopVarError* atol_err = new AssignToLoopVarError(
            lhs_value->getLocation()
        );
        m_error_printer.print(*atol_err);
        delete atol_err;
        return;
    }
    const ExpressionNode* rhs_value = p_assignment.getRightExpr();
    if (rhs_value == nullptr) {
        // Skip
        return;
    }
    if (rhs_value->getReturnType() == nullptr) return;
    if (rhs_value->getReturnType()->isArray()) {
        // Assign with array Error
        has_error = true;
        AssignWithArrayTypeError* warr_err = new AssignWithArrayTypeError(
            rhs_value->getLocation()
        );
        m_error_printer.print(*warr_err);
        delete warr_err;
        return;
    }
    if (rhs_value->getReturnType()->isInteger() && lhs_value->getReturnType()->isReal())
        return;
    if (!(*rhs_value->getReturnType() == *lhs_value->getReturnType())) {
        // Incompatible assignment Error
        has_error = true;
        IncompatibleAssignmentError* icass_err = new IncompatibleAssignmentError(
            p_assignment.getLocation(),
            lhs_value->getReturnType(),
            rhs_value->getReturnType()
        );
        m_error_printer.print(*icass_err);
        delete icass_err;
        return;
    }

    // 5. Pop the symbol table pushed at the 1st step.
}

void SemanticAnalyzer::visit(ReadNode &p_read) {
    // TODO:
    // 1. Push a new symbol table if this node forms a scope.
    // 2. Insert the symbol into current symbol table if this node is related to
    //    declaration (ProgramNode, VariableNode, FunctionNode).
    // 3. Traverse child nodes of this node.
    p_read.visitChildNodes(*this);
    // 4. Perform semantic analyses of this node.
    const PType* return_type = p_read.getTarget()->getReturnType();
    if (return_type == nullptr) return;
    if (return_type->isArray()) {
        // Read non scalar Error
        has_error = true;
        ReadToNonScalarTypeError* rarr_err = new ReadToNonScalarTypeError(
            p_read.getTarget()->getLocation()
        );
        m_error_printer.print(*rarr_err);
        delete rarr_err;
        return;
    }
    SymbolEntry* lhs_entry = symbol_manager.getEntryByName(p_read.getTarget()->getNameString());
    if (lhs_entry->getKind() == SymbolKind_e::CONSTANT ||
        lhs_entry->getKind() == SymbolKind_e::LOOP_VAR) {
        // Assign to cnostant or loop var Error
        has_error = true;
        ReadToConstantOrLoopVarError* rtocl_err = new ReadToConstantOrLoopVarError(
            p_read.getTarget()->getLocation()
        );
        m_error_printer.print(*rtocl_err);
        delete rtocl_err;
        return;
    }

    // 5. Pop the symbol table pushed at the 1st step.
}

void SemanticAnalyzer::visit(IfNode &p_if) {
    // TODO:
    // 1. Push a new symbol table if this node forms a scope.
    // 2. Insert the symbol into current symbol table if this node is related to
    //    declaration (ProgramNode, VariableNode, FunctionNode).
    // 3. Traverse child nodes of this node.
    p_if.visitChildNodes(*this);
    // 4. Perform semantic analyses of this node.
    const ExpressionNode* condition = p_if.getCondition();
    if (condition->getReturnType() == nullptr) return;
    if (condition->getReturnType()->isBool()) return;
    // Reach here means the type is wrong
    // Non boolean conditional error
    has_error = true;
    NonBooleanConditionError* nbool_err = new NonBooleanConditionError (
        condition->getLocation()
    );
    m_error_printer.print(*nbool_err);
    delete nbool_err;
    return;
    // 5. Pop the symbol table pushed at the 1st step.
}

void SemanticAnalyzer::visit(WhileNode &p_while) {
    // TODO:
    // 1. Push a new symbol table if this node forms a scope.
    // 2. Insert the symbol into current symbol table if this node is related to
    //    declaration (ProgramNode, VariableNode, FunctionNode).
    // 3. Traverse child nodes of this node.
    p_while.visitChildNodes(*this);
    // 4. Perform semantic analyses of this node.
    // 5. Pop the symbol table pushed at the 1st step.
}

void SemanticAnalyzer::visit(ForNode &p_for) {
    // TODO:
    // 1. Push a new symbol table if this node forms a scope.
    // ForNode forms a scope
    int scope = symbol_manager.getScope();
    SymbolTable* new_table = new SymbolTable(scope);
    symbol_manager.pushScope(new_table);
    // 2. Insert the symbol into current symbol table if this node is related to
    //    declaration (ProgramNode, VariableNode, FunctionNode).
    // 3. Traverse child nodes of this node.
    current_kind = SymbolKind_e::LOOP_VAR;
    is_in_loop = false;
    p_for.visitLoopVar(*this);
    is_in_loop = true;
    current_kind = SymbolKind_e::VARIABLE;
    p_for.visitLoopBody(*this);
    is_in_loop = false;

    // 4. Perform semantic analyses of this node.
    
    // 5. Pop the symbol table pushed at the 1st step.
    if (opt_dmp) {
        symbol_manager.dumpTopTable();
    }
    symbol_manager.popScope();
    
    const ExpressionNode* init_stmt_expr = p_for.getInitStmt()->getRightExpr();
    const ExpressionNode* end_condition = p_for.getEndCondition();
    uint64_t init_value = dynamic_cast<const ConstantValueNode*>(init_stmt_expr)->getConstant()->getConstantValue().integer;
    uint64_t end_value = dynamic_cast<const ConstantValueNode*>(end_condition)->getConstant()->getConstantValue().integer;
    if (init_value >= end_value) {
        // No increment Error
        has_error = true;
        NonIncrementalLoopVariableError* nincr_err = new NonIncrementalLoopVariableError(
            p_for.getLocation()
        );
        m_error_printer.print(*nincr_err);
        delete nincr_err;
    }
}

void SemanticAnalyzer::visit(ReturnNode &p_return) {
    // TODO:
    // 1. Push a new symbol table if this node forms a scope.
    // 2. Insert the symbol into current symbol table if this node is related to
    //    declaration (ProgramNode, VariableNode, FunctionNode).
    // 3. Traverse child nodes of this node.
    SymbolKind_e original_kind = current_kind;
    p_return.visitChildNodes(*this);
    current_kind = original_kind;
    // 4. Perform semantic analyses of this node.
    // Check if top is Program
    if (function_stack.top()->getKind() == SymbolKind_e::PROGRAM) {
        // Return from void Error
        has_error = true;
        ReturnFromVoidError* retvoid_err = new ReturnFromVoidError(
            p_return.getLocation()
        );    
        m_error_printer.print(*retvoid_err);
        delete retvoid_err;
        return;

    }
    auto func_return_type = function_stack.top()->getFuncAttr()->getReturnType();
    if (func_return_type->isVoid()) {
        // Return from void Error
        has_error = true;
        ReturnFromVoidError* retvoid_err = new ReturnFromVoidError(
            p_return.getLocation()
        );    
        m_error_printer.print(*retvoid_err);
        delete retvoid_err;
        return;
    }
    auto* return_type = p_return.getReturnValue()->getReturnType();
    if (return_type == nullptr) return;
    if(*return_type == *func_return_type) return;
    // Further check return a integer in a real function
    if (return_type->isInteger() && func_return_type->isReal()) return;
    // Reach here means the type is mismatched
    has_error = true;
    IncompatibleReturnTypeError* iret_err = new IncompatibleReturnTypeError(
        p_return.getReturnValue()->getLocation(),
        func_return_type.get(),
        return_type
    );
    m_error_printer.print(*iret_err);
    delete iret_err;
    // 5. Pop the symbol table pushed at the 1st step.
}
