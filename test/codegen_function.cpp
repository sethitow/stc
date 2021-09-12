#include "gtest/gtest.h"

#include "llvm/Support/raw_ostream.h"

#include "../src/ast/binary_expr_ast.hpp"
#include "../src/ast/function_ast.hpp"
#include "../src/ast/prototype_ast.hpp"
#include "../src/ast/variable_expr_ast.hpp"

TEST(CodeGen, Function)
{
    std::vector<std::string> arg_names = {"x", "y"};
    auto prototype = std::make_unique<PrototypeAST>("F_Sample", std::move(arg_names));
    auto lhs = std::make_unique<VariableExprAST>("x");
    auto rhs = std::make_unique<VariableExprAST>("y");
    auto expression = std::make_unique<BinaryExprAST>('+', std::move(lhs), std::move(rhs));
    auto function = std::make_unique<FunctionAST>(std::move(prototype), std::move(expression));

    auto ctx = CodeGenContext("source.st");
    function->codegen(ctx);

    std::string out_str;
    llvm::raw_string_ostream ss(out_str);
    ctx.llvm_module->print(ss, nullptr);

    std::string expected = "; ModuleID = 'source.st'\n"
                           "source_filename = \"source.st\"\n"
                           "\n"
                           "define i64 @F_Sample(i64 %x, i64 %y) {\n"
                           "entry:\n"
                           "  %addtmp = add i64 %x, %y\n"
                           "  ret i64 %addtmp\n"
                           "}\n";

    ASSERT_EQ(expected, out_str);
}