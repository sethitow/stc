#pragma once
#include <vector>

#include "token.hpp"

class TokenStream
{
  public:
    void push(Token);
    void print();
    Token next();
    std::vector<Token> to_vec() { return tokens; };

  private:
    std::vector<Token> tokens;
    int index = 0;
};