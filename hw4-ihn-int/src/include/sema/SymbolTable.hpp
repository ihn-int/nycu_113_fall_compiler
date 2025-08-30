#ifndef SEMA_SYMBOL_YABLE_H
#define SEMA_SYMBOL_YABLE_H

// for symbol entry
#include "AST/utils.hpp"    // for IdInfo
#include "AST/PType.hpp"    // for Type
#include "AST/constant.hpp" // for attribute
#include "AST/function.hpp" // for attribute

// for symbol table
#include <vector>

// for symbol manager
#include <stack>

enum class SymbolKind_e {
    PROGRAM,
    FUNCTION,
    PARAMETER,
    VARIABLE,
    LOOP_VAR,
    CONSTANT
};

typedef union _attribute {
        const Constant *constant;
        const FunctionNode* function;
} Attribute;

class SymbolEntry {
  public:
    SymbolEntry(
        IdInfo _id,
        SymbolKind_e _kind,
        int _scope,
        PTypeSharedPtr _type
        // union cannot be an argument
    );
    SymbolEntry(
        const char* _name,
        Location _location,
        SymbolKind_e _kind,
        int _scope,
        PTypeSharedPtr _type
    );

    ~SymbolEntry() = default;

    // dump function
    void dumpEntry();

    // set function
    void setConstAttr(const Constant* attr);
    void setFuncAttr(const FunctionNode* attr);
    void setError(bool _error);

    // get function
    const std::string getNameString() const;
    const Location &getLocation() const;
    const int getLevel() const;
    const SymbolKind_e getKind() const;
    const std::string getKindString() const;
    const PTypeSharedPtr getType() const;
    const bool getError() const;
    const Constant* getConstAttr() const;
    const FunctionNode* getFuncAttr() const;

    static std::string ktos(SymbolKind_e kind) {
        switch (kind) {
            case SymbolKind_e::PROGRAM :
                return "program";
            case SymbolKind_e::FUNCTION :
                return "function";
            case SymbolKind_e::PARAMETER :
                return "parameter";
            case SymbolKind_e::VARIABLE :
                return "variable";
            case SymbolKind_e::LOOP_VAR :
                return "loop var";
            case SymbolKind_e::CONSTANT :
                return "constant";
            default: return "";
        }
    }

  private:
    // Name
    IdInfo id;
    // Kind
    SymbolKind_e kind;
    // Level
    int scope;
    // Type
    PTypeSharedPtr type;
    // Attribute
    Attribute attribute;
    // Error, in case some error need to be record
    bool error;

}; // class SymbolEntry

class SymbolTable {
  public:
    SymbolTable(int _scope);
    ~SymbolTable() = default;

    // insert
    void addEntry(SymbolEntry* _new_entry);
    
    // lookup
    SymbolEntry* getEntryByName(std::string name);

    // dump function
    void dumpTable();

    // I think it should be static or a utility, but whatever
    void dumpDemacration(const char ch);

  private:
    std::vector<SymbolEntry*> entries;
    int scope;
}; // class SymbolTable


class SymbolManager {
  public:
    SymbolManager();
    ~SymbolManager() = default;
    // table maintain
    void pushScope(SymbolTable* new_scope);
    void popScope();

    // get function
    const int getScope() const;
    
    // dump
    void dumpTopTable();

    SymbolTable* getTopTable();
    SymbolEntry* getEntryByName(std::string name);


  private:
    std::stack<SymbolTable*> tables;
    int scope;
}; // class SymbolManager

#endif