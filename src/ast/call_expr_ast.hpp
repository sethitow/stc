#pragma once

#include "expr_ast.hpp"

#include "llvm/IR/Value.h"

/// CallExprAST - Expression class for function calls.
class CallExprAST : public ExprAST
{
    std::string Callee;
    std::vector<std::unique_ptr<ExprAST>> Args;

  public:
    CallExprAST(const std::string &Callee,
                std::vector<std::unique_ptr<ExprAST>> Args)
        : Callee(Callee), Args(std::move(Args)) {}

    llvm::Value *codegen(CodeGenContext &ctx) override;
};