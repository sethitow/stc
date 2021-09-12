#include "number_expr_ast.hpp"

llvm::Value *NumberExprAST::codegen(CodeGenContext &ctx)
{
    return llvm::ConstantInt::get(*ctx.llvm_context, llvm::APInt(64, Val, true));
}