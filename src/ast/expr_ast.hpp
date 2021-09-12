#ifndef EXPRAST_H
#define EXPRAST_H

#include <memory>
#include <string>
#include <vector>

#include "llvm/IR/Value.h"

/// ExprAST - Base class for all expression nodes.
class ExprAST
{
  public:
    virtual ~ExprAST() = default;

    virtual llvm::Value *codegen() = 0;
};

/// NumberExprAST - Expression class for numeric literals like "1".
class NumberExprAST : public ExprAST
{
    int Val;

  public:
    NumberExprAST(int Val)
        : Val(Val) {}

    llvm::Value *codegen() override;
};

/// VariableExprAST - Expression class for referencing a variable, like "a".
class VariableExprAST : public ExprAST
{
    std::string Name;

  public:
    VariableExprAST(const std::string &Name)
        : Name(Name) {}

    llvm::Value *codegen() override;
};

/// BinaryExprAST - Expression class for a binary operator.
class BinaryExprAST : public ExprAST
{
    char Op;
    std::unique_ptr<ExprAST> LHS, RHS;

  public:
    BinaryExprAST(char Op, std::unique_ptr<ExprAST> LHS,
                  std::unique_ptr<ExprAST> RHS)
        : Op(Op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}

    llvm::Value *codegen() override;
};

/// CallExprAST - Expression class for function calls.
class CallExprAST : public ExprAST
{
    std::string Callee;
    std::vector<std::unique_ptr<ExprAST>> Args;

  public:
    CallExprAST(const std::string &Callee,
                std::vector<std::unique_ptr<ExprAST>> Args)
        : Callee(Callee), Args(std::move(Args)) {}

    llvm::Value *codegen() override;
};

// TODO(sitow): get rid of this
void InitializeModule();
llvm::Module &getModule();

#endif