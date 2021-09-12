#pragma once

#include "expr_ast.hpp"

#include "llvm/IR/Value.h"

#include "../code_gen_context.hpp"

/// NumberExprAST - Expression class for numeric literals like "1".
class NumberExprAST : public ExprAST
{
    int Val;

  public:
    NumberExprAST(int Val)
        : Val(Val) {}

    llvm::Value *codegen(CodeGenContext &ctx) override;
};