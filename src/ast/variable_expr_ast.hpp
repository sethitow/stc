#pragma once

#include "expr_ast.hpp"

#include "llvm/IR/Value.h"

/// VariableExprAST - Expression class for referencing a variable, like "a".
class VariableExprAST : public ExprAST
{
    std::string Name;

  public:
    VariableExprAST(const std::string &Name)
        : Name(Name) {}

    llvm::Value *codegen(CodeGenContext &ctx) override;
};