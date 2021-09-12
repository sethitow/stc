#include "prototype_ast.hpp"

llvm::Function *PrototypeAST::codegen(CodeGenContext &ctx)
{
    // Make the function type:  double(double,double) etc.
    std::vector<llvm::Type *> Int64s(Args.size(), llvm::Type::getInt64Ty(*ctx.llvm_context));
    llvm::FunctionType *FT =
        llvm::FunctionType::get(llvm::Type::getInt64Ty(*ctx.llvm_context), Int64s, false);

    llvm::Function *F =
        llvm::Function::Create(FT, llvm::Function::ExternalLinkage, Name, ctx.llvm_module.get());

    // Set names for all arguments.
    unsigned Idx = 0;
    for (auto &Arg : F->args())
        Arg.setName(Args[Idx++]);

    return F;
}

bool PrototypeAST::operator==(const PrototypeAST &other) const
{
    return Name == other.Name && Args == other.Args;
}