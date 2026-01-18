#include "Compiler.h"
#include "Instructions/Instructions.h"

ByteCode Compiler::compile(const std::vector<std::unique_ptr<Decl>>& ast) {
    for (auto& decl : ast) {
        compileDecl(decl.get());
    }

    emit(OP_HALT);
    return chunk;
}
void Compiler::compileExpr(Expr* expr) {

    if (auto* lit = dynamic_cast<LiteralExpr*>(expr)) {
        emitConst(std::stod(lit->value));
    }

    else if (auto* var = dynamic_cast<VariableExpr*>(expr)) {
        // Temporary stub
        // We will handle:
        // - FunctionDecl
        // - VarDecl
        // later
    }

    else if (auto* bin = dynamic_cast<BinaryExpr*>(expr)) {
        compileExpr(bin->left.get());
        compileExpr(bin->right.get());

        if (bin->op == "+") emit(OP_ADD);
        else if (bin->op == "-") emit(OP_SUB);
        else if (bin->op == "*") emit(OP_MUL);
        else if (bin->op == "/") emit(OP_DIV);
    }

    else if (auto* call = dynamic_cast<CallExpr*>(expr)) {
        // later: function calls
    }
}
void Compiler::compileStmt(Stmt* stmt) {

    if (auto* exprStmt = dynamic_cast<ExprStmt*>(stmt)) {
        compileExpr(exprStmt->expr.get());
    }

    else if (auto* ret = dynamic_cast<ReturnStmt*>(stmt)) {
        compileExpr(ret->value.get());
        // Temporary stub
        // We will handle:
        // - FunctionDecl
        // - VarDecl
        // later
    }

    else if (auto* block = dynamic_cast<BlockStmt*>(stmt)) {
        for (auto& s : block->statements) {
            compileStmt(s.get());
        }
    }
}
void Compiler::emitConst(double value) {
    chunk.constants.push_back(value);
    emit(OP_CONST);
    emit(chunk.constants.size() - 1);
}

void Compiler::emit(uint8_t opcode) {
    chunk.code.push_back(opcode);
}
void Compiler::compileDecl(Decl* decl) {
    // Temporary stub
    // We will handle:
    // - FunctionDecl
    // - VarDecl
    // later
}
