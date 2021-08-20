#include "token.h"
#include <iomanip>
#include <iostream>

Token::Token(std::string init_key, std::string init_value)
{
    key = init_key;
    value = init_value;
}

std::string Token::to_string() const
{
    return getkey() + " " + getvalue();
}

void Token::print() const
{
    std::cout << std::left << std::setw(20) << getkey() << std::left
              << std::setw(16) << getvalue() << std::endl;
}
