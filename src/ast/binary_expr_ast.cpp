#include "binary_expr_ast.hpp"

#include "logging.h"

llvm::Value *BinaryExprAST::codegen(CodeGenContext &ctx)
{
    llvm::Value *L = LHS->codegen(ctx);
    llvm::Value *R = RHS->codegen(ctx);
    if (!L || !R)
        return nullptr;

    switch (Op)
    {
    case '+':
        return ctx.ir_builder->CreateAdd(L, R, "addtmp", false, false);
    case '-':
        return ctx.ir_builder->CreateSub(L, R, "subtmp", false, false);
    case '*':
        return ctx.ir_builder->CreateMul(L, R, "multmp", false, false);
    // case '<':
    //     L = ctx.ir_builder->CreateFCmpULT(L, R, "cmptmp");
    //     // Convert bool 0/1 to double 0.0 or 1.0
    //     return ctx.ir_builder->CreateUIToFP(L, llvm::Type::getDoubleTy(TheContext),
    //                                 "booltmp");
    default:
        return LogErrorV("invalid binary operator");
    }
}