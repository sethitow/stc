#pragma once

#include <string>

// where/how the keywords are going to be saved
struct Token
{
  public:
    Token(std::string key, std::string value)
        : _key(key), _value(value){};
    std::string to_string() const;
    void print() const;

    std::string key() const { return _key; }
    std::string value() const { return _value; }
    std::string value_printable() const;

    bool operator==(const Token &other) const;

  private:
    std::string _key, _value;
};
