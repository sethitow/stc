#pragma once

#include "llvm/IR/Value.h"

inline __attribute__((always_inline)) std::unique_ptr<ExprAST> LogError(const char *Str)
{
    fprintf(stderr, "Error: %s\n", Str);
    return nullptr;
}

inline __attribute__((always_inline)) llvm::Value *LogErrorV(const char *Str)
{
    LogError(Str);
    return nullptr;
}
