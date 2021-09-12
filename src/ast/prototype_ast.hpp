#ifndef PROTOTYPEAST_H
#define PROTOTYPEAST_H

#include <memory>
#include <string>
#include <vector>

#include "llvm/IR/Function.h"

#include "expr_ast.hpp"

/// PrototypeAST - This class represents the "prototype" for a function,
/// which captures its name, and its argument names (thus implicitly the number
/// of arguments the function takes).
class PrototypeAST
{
    std::string Name;
    std::vector<std::string> Args;

  public:
    PrototypeAST(const std::string &Name, std::vector<std::string> Args)
        : Name(Name), Args(std::move(Args)) {}

    llvm::Function *codegen(CodeGenContext &ctx);
    const std::string &getName() const { return Name; }

    bool operator==(const PrototypeAST &other) const;
};

#endif