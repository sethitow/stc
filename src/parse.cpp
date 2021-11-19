#include "parse.hpp"

#include <iostream>
#include <stdexcept>

#include "ast/number_expr_ast.hpp"
#include "lexer.hpp"

std::unique_ptr<FunctionAST> parseFunction(TokenStream &stream);
std::vector<std::string> parseVarInput(TokenStream &stream);

std::unique_ptr<FunctionAST> parse(TokenStream &stream)
{
    auto tok = stream.next();
    if (tok.key() == "KEYWORD" && tok.value() == "FUNCTION")
    {
        std::cerr << "Parsing function..." << std::endl;
        return parseFunction(stream);
    }
    throw std::invalid_argument("Expected keyword FUNCTION, but got " + tok.key() + " " + tok.value() + " instead");
}

std::unique_ptr<FunctionAST> parseFunction(TokenStream &stream)
{
    auto tok = stream.next();
    if (tok.key() != "IDENTIFIER")
    {
        throw std::invalid_argument("Expected function name identifier, but got token " + tok.key() + " instead");
    }
    auto functionName = tok.value();

    tok = stream.next();
    if (tok.key() != "KEYWORD" || tok.value() != "END_FUNCTION")
    {
        throw std::invalid_argument("Expected keyword END_FUNCTION but got " + tok.key() + " " + tok.value() + " instead");
    }

    tok = stream.next();
    if (tok.key() != "SPECIAL_CHARACTER" || tok.value() != ";")
    {
        throw std::invalid_argument("Expected special character ; but got " + tok.key() + " " + tok.value() + " instead");
    }

    auto prototype = std::make_unique<PrototypeAST>(functionName, std::vector<std::string>());
    auto body = std::make_unique<NumberExprAST>(0);
    auto function = std::make_unique<FunctionAST>(std::move(prototype), std::move(body));

    return function;
}

std::vector<std::string> parseVarInput(TokenStream &stream)
{
    return std::vector<std::string>();
}
