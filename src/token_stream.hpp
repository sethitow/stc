#include <vector>

#include "token.hpp"

class TokenStream
{
  public:
    void push(Token);
    void print();
    std::vector<Token> to_vec() { return tokens; };

  private:
    std::vector<Token> tokens;
};