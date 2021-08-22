#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <vector>

// where/how the keywords are going to be saved
struct Token
{
  public:
    Token(std::string key, std::string value)
        : key(key), value(value){};
    std::string to_string() const;
    void print() const;

    std::string getkey() const { return key; }
    std::string getvalue() const { return value; }
    std::string getvalueprintable() const;

    bool operator==(const Token &other) const;

  private:
    std::string key, value;
};
#endif /* TOKEN_H */