#ifndef FUNCTIONAST_H
#define FUNCTIONAST_H

#include "llvm/IR/Function.h"

#include "expr_ast.hpp"
#include "prototype_ast.hpp"

/// FunctionAST - This class represents a function definition itself.
class FunctionAST
{
    std::unique_ptr<PrototypeAST> Proto;
    std::unique_ptr<ExprAST> Body;

  public:
    FunctionAST(std::unique_ptr<PrototypeAST> Proto,
                std::unique_ptr<ExprAST> Body)
        : Proto(std::move(Proto)), Body(std::move(Body)) {}

    bool operator==(const FunctionAST &other) const;

    llvm::Function *codegen(CodeGenContext &ctx);
};

#endif