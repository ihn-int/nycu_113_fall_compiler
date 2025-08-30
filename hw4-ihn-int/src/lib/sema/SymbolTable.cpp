#include "sema/SymbolTable.hpp"

//==========================================================
// Symbol Entry
SymbolEntry::SymbolEntry(
    IdInfo _id,
    SymbolKind_e _kind,
    int _scope,
    PTypeSharedPtr _type
    // union cannot be an argumnt
) : id(_id),
    kind(_kind),
    scope(_scope),
    type(_type),
    error(false)
    {}

SymbolEntry::SymbolEntry(
    const char* _name,
    Location _location,
    SymbolKind_e _kind,
    int _scope,
    PTypeSharedPtr _type
) : id(_location.line, _location.col, _name),
    kind(_kind),
    scope(_scope),
    type(_type),
    error(false)
    {}

// dump function
void SymbolEntry::dumpEntry() {
    // order: name -> kind -> level -> type -> attribute
    // Name, use IdInfo
    std::printf("%-33s", id.id.c_str());
    // kind, use function
    std::printf("%-11s", this->getKindString().c_str());
    // level
    std::printf("%d%-10s", scope, scope ? "(local)" : "(global)");
    // type, use function
    std::printf("%-17s", type->getPTypeCString());
    // attribute, use switch
    switch(kind) {
        case SymbolKind_e::CONSTANT:
            std::printf("%-11s", attribute.constant->getConstantValueCString());
            break;
        case SymbolKind_e::FUNCTION:
            std::printf("%-11s", attribute.function->getParametersTypeCString());
            break;
        default:
            std::printf("%-11s", "");
            break;
    }

    puts("");
}

// set function
void SymbolEntry::setConstAttr(const Constant* attr) {
    attribute.constant = attr;
}
void SymbolEntry::setFuncAttr(const FunctionNode* attr) {
    attribute.function = attr;
}
void SymbolEntry::setError(bool _error) {
    error = _error;
}

// get function
const std::string SymbolEntry::getNameString() const {
    return id.id;
}
const Location &SymbolEntry::getLocation() const {
    return id.location;
}
const int SymbolEntry::getLevel() const {
    return scope;
}
const SymbolKind_e SymbolEntry::getKind() const {
    return kind;
}
const std::string SymbolEntry::getKindString() const {
    switch(kind) {
        case SymbolKind_e::PROGRAM:
            return "program";
            break;
        case SymbolKind_e::FUNCTION:
            return "function";
            break;
        case SymbolKind_e::PARAMETER:
            return "parameter";
            break;
        case SymbolKind_e::VARIABLE:
            return "variable";
            break;
        case SymbolKind_e::LOOP_VAR:
            return "loop_var";
            break;
        case SymbolKind_e::CONSTANT:
            return "constant";
            break;
        default:
            return "";
    }
}
const PTypeSharedPtr SymbolEntry::getType() const {
    return type;
}
const bool SymbolEntry::getError() const {
    return error;
}
const Constant* SymbolEntry::getConstAttr() const {
    return attribute.constant;
}
const FunctionNode* SymbolEntry::getFuncAttr() const {
    return attribute.function;
}

// end of Symbol Entry
//==========================================================

//==========================================================
// Symbol Table
SymbolTable::SymbolTable(
    int _scope
) : scope(_scope)
    {}

// insert
void SymbolTable::addEntry(SymbolEntry* _new_entry) {
    entries.emplace_back(_new_entry);
}

// lookup
SymbolEntry* SymbolTable::getEntryByName(std::string name) {
    for (auto entry : entries) {
        if (entry->getNameString() == name) {
            return entry;
        }
    }
    return nullptr;
}

// dump function
void SymbolTable::dumpTable() {
    dumpDemacration('=');
    printf("%-33s%-11s%-11s%-17s%-11s\n",
        "Name", "Kind", "Level", "Type", "Attribute");
    dumpDemacration('-');
    for (auto entry : entries) {
        entry->dumpEntry();
    }
    dumpDemacration('-');
}
void SymbolTable::dumpDemacration(const char ch) {
    for (size_t i = 0; i < 110; ++i) {
        printf("%c", ch);
    }
    puts("");
}
// end of Symbol Table
//==========================================================

//==========================================================
// Symbol Manager
SymbolManager::SymbolManager() : scope(-1) {}
void SymbolManager::pushScope(SymbolTable* new_scope) {
    tables.push(new_scope);
    scope++;
}
void SymbolManager::popScope() {
    tables.pop();
    scope--;
}
const int SymbolManager::getScope() const {
    return scope;
}
void SymbolManager::dumpTopTable() {
    tables.top()->dumpTable();
}
SymbolTable* SymbolManager::getTopTable() {
    return tables.top();
}
SymbolEntry* SymbolManager::getEntryByName(std::string name) {
    // temp stack for stack maintain
    std::stack<SymbolTable*> checked_table;
    SymbolTable* top_table;
    SymbolEntry* entry = nullptr;

    while(!tables.empty()) {
        // A table exit
        top_table = tables.top();
        entry = top_table->getEntryByName(name);
        if (entry == nullptr) {
            // not in this scope, pop out the table and find at next one
            checked_table.push(top_table);
            tables.pop();
            continue;
        }
        else {
            // found the entry
            break;
        }    
    }

    // restore stack
    while(!checked_table.empty()) {
        top_table = checked_table.top();
        tables.push(top_table);
        checked_table.pop();
    }

    return entry;
}
// end of Symbol Manager
//==========================================================
