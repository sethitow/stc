#ifndef LEXER_H
#define LEXER_H
#include <string>
#include <vector>

#include "token.h"

std::vector<Token> tokenize(std::string input); // main lexer function
void display(std::vector<Token>);

#endif
