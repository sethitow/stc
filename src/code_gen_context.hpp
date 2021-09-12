#pragma once

#include <map>
#include <memory>

#include "llvm/IR/IRBuilder.h"

class CodeGenContext
{
  public:
    std::unique_ptr<llvm::LLVMContext> llvm_context;
    std::unique_ptr<llvm::Module> llvm_module;
    std::unique_ptr<llvm::IRBuilder<>> ir_builder;
    std::map<std::string, llvm::Value *> named_values;

    CodeGenContext(std::string module_id)
        : llvm_context(std::make_unique<llvm::LLVMContext>()),
          llvm_module(std::make_unique<llvm::Module>(module_id, *llvm_context)),
          ir_builder(std::make_unique<llvm::IRBuilder<>>(*llvm_context))
    {
    }
};