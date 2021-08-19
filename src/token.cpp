#include "token.h"
#include <iostream>
#include <iomanip>

Token::Token(std::string init_key, std::string init_value){
    key = init_key;
    value = init_value;
}
std::string Token::to_string (){
    return getkey() + " " + getvalue();
}
void Token::print(){
    std::cout << std::left << std::setw(20) << getkey() << std::left << std::setw(16) << getvalue() << std::endl;
}