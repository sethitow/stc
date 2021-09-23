#include "gtest/gtest.h"

#include <llvm/IR/Module.h>

#include "../src/ast/binary_expr_ast.hpp"
#include "../src/ast/function_ast.hpp"
#include "../src/ast/prototype_ast.hpp"
#include "../src/ast/variable_expr_ast.hpp"
#include "../src/parse.hpp"
#include "../src/token.hpp"

TEST(Parse, DISABLED_Function)
{
    std::vector<Token>
        tok_vec{
            Token("KEYWORD", "FUNCTION"),
            Token("IDENTIFIER", "F_Sample"),
            Token("SPECIAL_CHARACTER", ":"),
            Token("KEYWORD", "INT"),
            Token("KEYWORD", "VAR_INPUT"),
            Token("IDENTIFIER", "x"),
            Token("SPECIAL_CHARACTER", ":"),
            Token("KEYWORD", "INT"),
            Token("SPECIAL_CHARACTER", ";"),
            Token("IDENTIFIER", "y"),
            Token("SPECIAL_CHARACTER", ":"),
            Token("KEYWORD", "INT"),
            Token("SPECIAL_CHARACTER", ";"),
            Token("KEYWORD", "END_VAR"),
            Token("IDENTIFIER", "F_Sample"),
            Token("OPERATOR", ":="),
            Token("IDENTIFIER", "x"),
            Token("OPERATOR", "+"),
            Token("IDENTIFIER", "y"),
            Token("SPECIAL_CHARACTER", ";"),
            Token("KEYWORD", "END_FUNCTION"),
            Token("SPECIAL_CHARACTER", ";"),
        };

    TokenStream stream;
    for (auto const &tok : tok_vec)
    {
        stream.push(tok);
    }

    auto ast = parse(stream);

    std::vector<std::string> arg_names = {"x", "y"};
    auto prototype = std::make_unique<PrototypeAST>("F_Sample", std::move(arg_names));
    auto lhs = std::make_unique<VariableExprAST>("x");
    auto rhs = std::make_unique<VariableExprAST>("y");
    auto expression = std::make_unique<BinaryExprAST>('+', std::move(lhs), std::move(rhs));
    auto function = std::make_unique<FunctionAST>(std::move(prototype), std::move(expression));

    ASSERT_EQ(*function, *ast);
};

TEST(Parse, Function_no_Arguments)
{
    std::vector<Token>
        tok_vec{
            Token("KEYWORD", "FUNCTION"),
            Token("IDENTIFIER", "F_Sample"),
            Token("KEYWORD", "END_FUNCTION"),
            Token("SPECIAL_CHARACTER", ";"),
        };

    TokenStream stream;
    for (auto const &tok : tok_vec)
    {
        stream.push(tok);
    }

    auto ast = parse(stream);

    std::vector<std::string> arg_names = {};
    auto prototype = std::make_unique<PrototypeAST>("F_Sample", std::move(arg_names));
    auto function = std::make_unique<FunctionAST>(std::move(prototype), nullptr);
    ASSERT_EQ(*function, *ast);
};