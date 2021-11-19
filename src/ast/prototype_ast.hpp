#pragma once

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
    std::string return_type;

  public:
    PrototypeAST(const std::string &Name, std::vector<std::string> Args, const std::string &return_type)
        : Name(Name), Args(std::move(Args)), return_type(return_type) {}

    llvm::Function *codegen(CodeGenContext &ctx);
    const std::string &getName() const { return Name; }

    bool operator==(const PrototypeAST &other) const;
};
