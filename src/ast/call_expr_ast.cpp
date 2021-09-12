#include "variable_expr_ast.hpp"

#include "logging.h"

llvm::Value *VariableExprAST::codegen(CodeGenContext &ctx)
{
    llvm::Value *V = ctx.named_values[Name];
    if (!V)
        return LogErrorV("Unknown variable name");
    return V;
}
