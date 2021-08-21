#include <vector>

#include "token.h"

class TokenStream
{
  public:
    void push(Token);
    void print();

  private:
    std::vector<Token> tokens;
};