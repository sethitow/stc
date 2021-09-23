#ifndef PARSE_HPP
#define PARSE_HPP

#include "ast/function_ast.hpp"
#include "token.hpp"
#include "token_stream.hpp"

std::unique_ptr<FunctionAST> parse(TokenStream &);

#endif
