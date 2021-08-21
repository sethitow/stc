#include <vector>

#include "token.hpp"

class TokenStream
{
  public:
    void push(Token);
    void print();

  private:
    std::vector<Token> tokens;
};