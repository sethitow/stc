#ifndef EXPRAST_H
#define EXPRAST_H

#include <memory>
#include <string>
#include <vector>

#include "llvm/IR/Value.h"

#include "../code_gen_context.hpp"

/// ExprAST - Base class for all expression nodes.
class ExprAST
{
  public:
    virtual ~ExprAST() = default;

    virtual llvm::Value *codegen(CodeGenContext &) = 0;
};

#endif