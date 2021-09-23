#include "parse.hpp"
#include "lexer.hpp"
#include <iostream>
#include <stdexcept>

std::unique_ptr<FunctionAST> parseFunction(TokenStream &stream);
std::vector<std::string> parseVarInput(TokenStream &stream);

std::unique_ptr<FunctionAST> parse(TokenStream &stream)
{
    auto tok = stream.next();
    if (tok.getkey() == "KEYWORD" && tok.getvalue() == "FUNCTION")
    {
        std::cerr << "Parsing function..." << std::endl;
        return parseFunction(stream);
    }
    throw std::invalid_argument("Expected keyword FUNCTION, but got " + tok.getkey() + " " + tok.getvalue() + " instead");
}

std::unique_ptr<FunctionAST> parseFunction(TokenStream &stream)
{
    auto tok = stream.next();
    if (tok.getkey() != "IDENTIFIER")
    {
        throw std::invalid_argument("Expected function name identifier, but got token " + tok.getkey() + " instead");
    }
    auto functionName = tok.getvalue();

    tok = stream.next();
    if (tok.getkey() != "KEYWORD" || tok.getvalue() != "END_FUNCTION")
    {
        throw std::invalid_argument("Expected keyword END_FUNCTION but got " + tok.getkey() + " " + tok.getvalue() + " instead");
    }

    tok = stream.next();
    if (tok.getkey() != "SPECIAL_CHARACTER" || tok.getvalue() != ";")
    {
        throw std::invalid_argument("Expected special character ; but got " + tok.getkey() + " " + tok.getvalue() + " instead");
    }

    auto prototype = std::make_unique<PrototypeAST>(functionName, std::vector<std::string>());
    auto function = std::make_unique<FunctionAST>(std::move(prototype), nullptr);

    return function;
}

std::vector<std::string> parseVarInput(TokenStream &stream)
{
    return std::vector<std::string>();
}
