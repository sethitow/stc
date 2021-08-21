#include "token_stream.hpp"

void TokenStream::push(Token t)
{
    t.print();
    tokens.push_back(t);
}

void TokenStream::print()
{
    for (const auto &token : tokens)
    {
        token.print();
    }
}