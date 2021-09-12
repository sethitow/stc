#include "expr_ast.hpp"
#include "function_ast.hpp"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Verifier.h"
#include <map>

static std::unique_ptr<llvm::LLVMContext> TheContext;
static std::unique_ptr<llvm::Module> TheModule;
static std::unique_ptr<llvm::IRBuilder<>> Builder;
static std::map<std::string, llvm::Value *> NamedValues;

llvm::Value *LogErrorV(const char *Str)
{
    LogErrorV(Str);
    return nullptr;
}

llvm::Value *NumberExprAST::codegen()
{
    return llvm::ConstantInt::get(*TheContext, llvm::APInt(64, Val, true));
}

llvm::Value *VariableExprAST::codegen()
{
    llvm::Value *V = NamedValues[Name];
    if (!V)
        return LogErrorV("Unknown variable name");
    return V;
}

llvm::Value *BinaryExprAST::codegen()
{
    llvm::Value *L = LHS->codegen();
    llvm::Value *R = RHS->codegen();
    if (!L || !R)
        return nullptr;

    switch (Op)
    {
    case '+':
        return Builder->CreateAdd(L, R, "addtmp", false, false);
    case '-':
        return Builder->CreateSub(L, R, "subtmp", false, false);
    case '*':
        return Builder->CreateMul(L, R, "multmp", false, false);
    // case '<':
    //     L = Builder->CreateFCmpULT(L, R, "cmptmp");
    //     // Convert bool 0/1 to double 0.0 or 1.0
    //     return Builder->CreateUIToFP(L, llvm::Type::getDoubleTy(TheContext),
    //                                 "booltmp");
    default:
        return LogErrorV("invalid binary operator");
    }
}

// TODO(sitow): Move into function_ast.cpp
llvm::Function *FunctionAST::codegen()
{
    // First, check for an existing function from a previous 'extern' declaration.
    llvm::Function *TheFunction = TheModule->getFunction(Proto->getName());

    if (!TheFunction)
        TheFunction = Proto->codegen();

    if (!TheFunction)
        return nullptr;

    // Create a new basic block to start insertion into.
    llvm::BasicBlock *BB = llvm::BasicBlock::Create(*TheContext, "entry", TheFunction);
    Builder->SetInsertPoint(BB);

    // Record the function arguments in the NamedValues map.
    NamedValues.clear();
    for (auto &Arg : TheFunction->args())
        NamedValues[std::string(Arg.getName())] = &Arg;

    if (llvm::Value *RetVal = Body->codegen())
    {
        // Finish off the function.
        Builder->CreateRet(RetVal);

        // Validate the generated code, checking for consistency.
        llvm::verifyFunction(*TheFunction);

        return TheFunction;
    }

    // Error reading body, remove function.
    TheFunction->eraseFromParent();
    return nullptr;
}

// TODO(sitow): Move into prototype_ast.cpp
llvm::Function *PrototypeAST::codegen()
{
    // Make the function type:  double(double,double) etc.
    std::vector<llvm::Type *> Int64s(Args.size(), llvm::Type::getInt64Ty(*TheContext));
    llvm::FunctionType *FT =
        llvm::FunctionType::get(llvm::Type::getInt64Ty(*TheContext), Int64s, false);

    llvm::Function *F =
        llvm::Function::Create(FT, llvm::Function::ExternalLinkage, Name, TheModule.get());

    // Set names for all arguments.
    unsigned Idx = 0;
    for (auto &Arg : F->args())
        Arg.setName(Args[Idx++]);

    return F;
}

void InitializeModule()
{
    // Open a new context and module.
    TheContext = std::make_unique<llvm::LLVMContext>();
    TheModule = std::make_unique<llvm::Module>("source.st", *TheContext);

    // Create a new builder for the module.
    Builder = std::make_unique<llvm::IRBuilder<>>(*TheContext);
}

llvm::Module &getModule()
{
    return *TheModule;
}