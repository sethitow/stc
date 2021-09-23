#include "parse.hpp"

#include "lexer.hpp"

// TODO: This return type might need to change
unique_ptr<FunctionAST> parse(TokenStream stream)
{
    stream.next();
    return nullptr;
}
