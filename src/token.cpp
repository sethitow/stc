#include "token.hpp"

#include <iomanip>
#include <iostream>

#include <boost/algorithm/string/replace.hpp>

std::string Token::to_string() const
{
    return getkey() + " " + getvalue();
}

std::string Token::getvalueprintable() const
{
    auto v = getvalue();
    boost::replace_all(v, "\r", R"(\r)");
    boost::replace_all(v, "\n", R"(\n)");
    return v;
}

void Token::print() const
{
    std::cout << std::left << std::setw(30) << getkey() << std::left
              << std::setw(16) << getvalueprintable() << std::endl;
}
