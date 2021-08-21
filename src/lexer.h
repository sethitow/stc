#ifndef LEXER_H
#define LEXER_H
#include <string>
#include <vector>

#include "token.h"

#include "token_stream.hpp"

TokenStream tokenize(std::string input); // main lexer function

#endif
