#include "function_ast.hpp"

#include "llvm/IR/Verifier.h"

llvm::Function *FunctionAST::codegen(CodeGenContext &ctx)
{
    // First, check for an existing function from a previous 'extern' declaration.
    llvm::Function *TheFunction = ctx.llvm_module->getFunction(Proto->getName());

    if (!TheFunction)
        TheFunction = Proto->codegen(ctx);

    if (!TheFunction)
        return nullptr;

    // Create a new basic block to start insertion into.
    llvm::BasicBlock *BB = llvm::BasicBlock::Create(*ctx.llvm_context, "entry", TheFunction);
    ctx.ir_builder->SetInsertPoint(BB);

    // Record the function arguments in the NamedValues map.
    ctx.named_values.clear();
    for (auto &Arg : TheFunction->args())
        ctx.named_values[std::string(Arg.getName())] = &Arg;

    if (llvm::Value *RetVal = Body->codegen(ctx))
    {
        // Finish off the function.
        ctx.ir_builder->CreateRet(RetVal);

        // Validate the generated code, checking for consistency.
        llvm::verifyFunction(*TheFunction);

        return TheFunction;
    }

    // Error reading body, remove function.
    TheFunction->eraseFromParent();
    return nullptr;
}

bool FunctionAST::operator==(const FunctionAST &other) const
{
    // TODO(sitow): Check function body
    return *Proto == *other.Proto;
}
