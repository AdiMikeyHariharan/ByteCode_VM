#pragma once
#include "AST.h"
#include "ByteCode/ByteCode.h"

class Compiler {
public:
    ByteCode compile(const std::vector<std::unique_ptr<Decl>>& ast);

private:
    void compileDecl(Decl* decl);
    void compileStmt(Stmt* stmt);
    void compileExpr(Expr* expr);

    void emit(uint8_t opcode);
    void emitConst(double value);

private:
    ByteCode chunk;
};
