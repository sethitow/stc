#ifndef PARSE_HPP
#define PARSE_HPP

#include <vector>

#include "ast/function_ast.hpp"
#include "token.hpp"

std::unique_ptr<FunctionAST> parse(std::vector<Token>);

#endif
