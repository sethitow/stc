#include "expr_ast.hpp"
#include <map>
#include "llvm/IR/IRBuilder.h"

static std::unique_ptr<llvm::LLVMContext> TheContext;
static std::unique_ptr<llvm::Module> TheModule;
static std::unique_ptr<llvm::IRBuilder<>> Builder;
static std::map<std::string, llvm::Value *> NamedValues;

llvm::Value *LogErrorV(const char *Str) {
    LogErrorV(Str);
    return nullptr;
}

llvm::Value *NumberExprAST::codegen() {
    return llvm::ConstantInt::get(*TheContext, llvm::APInt(64, Val, true));
}

llvm::Value *VariableExprAST::codegen() {
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

    switch (Op) {
    case '+':
        return Builder->CreateAdd(L, R, "addtmp", false, false);
    case '-':
        return Builder->CreateAdd(L, R, "subtmp", false, false);
    case '*':
        return Builder->CreateAdd(L, R, "multmp", false, false);
    // case '<':
    //     L = Builder->CreateFCmpULT(L, R, "cmptmp");
    //     // Convert bool 0/1 to double 0.0 or 1.0
    //     return Builder->CreateUIToFP(L, llvm::Type::getDoubleTy(TheContext),
    //                                 "booltmp");
    default:
        return LogErrorV("invalid binary operator");
    }
}