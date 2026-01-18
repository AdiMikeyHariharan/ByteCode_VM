#pragma once
#include <memory>
#include <string>
#include <vector>

// =====================
// Base nodes
// =====================
struct ASTNode {
    virtual ~ASTNode() = default;
};

struct Expr : ASTNode {};
struct Stmt : ASTNode {};
struct Decl : ASTNode {};
struct LiteralExpr : Expr {
    std::string value;
    explicit LiteralExpr(std::string v) : value(std::move(v)) {}
};

struct VariableExpr : Expr {
    std::string name;
    explicit VariableExpr(std::string n) : name(std::move(n)) {}
};

struct UnaryExpr : Expr {
    std::string op;
    std::unique_ptr<Expr> expr;
};

struct BinaryExpr : Expr {
    std::string op;
    std::unique_ptr<Expr> left;
    std::unique_ptr<Expr> right;
};

struct CallExpr : Expr {
    std::string callee;
    std::vector<std::unique_ptr<Expr>> args;
};
struct ExprStmt : Stmt {
    std::unique_ptr<Expr> expr;
};

struct ReturnStmt : Stmt {
    std::unique_ptr<Expr> value;
};

struct BlockStmt : Stmt {
    std::vector<std::unique_ptr<Stmt>> statements;
};

struct IfStmt : Stmt {
    std::unique_ptr<Expr> condition;
    std::unique_ptr<Stmt> thenBranch;
    std::unique_ptr<Stmt> elseBranch;
};

struct WhileStmt : Stmt {
    std::unique_ptr<Expr> condition;
    std::unique_ptr<Stmt> body;
};
struct VarDecl : Decl, Stmt {
    std::string type;
    std::string name;
    std::unique_ptr<Expr> initializer;
};

struct FunctionDecl : Decl {
    std::string returnType;
    std::string name;
    std::vector<std::pair<std::string, std::string>> params;
    std::unique_ptr<BlockStmt> body;
};
