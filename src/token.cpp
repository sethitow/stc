#include "token.hpp"

#include <iomanip>
#include <iostream>

#include <boost/algorithm/string/replace.hpp>

std::string Token::to_string() const
{
    return key() + " " + value();
}

std::string Token::value_printable() const
{
    auto v = value();
    boost::replace_all(v, "\r", R"(\r)");
    boost::replace_all(v, "\n", R"(\n)");
    return v;
}

void Token::print() const
{
    std::cout << std::left << std::setw(30) << key() << std::left
              << std::setw(16) << value_printable() << std::endl;
}

bool Token::operator==(const Token &other) const
{
    return _key == other._key and _value == other._value;
}

bool Token::operator!=(const Token &other) const
{
    return !(*this == other);
}