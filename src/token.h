#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <vector>

// where/how the keywords are going to be saved
struct Token{ 
    public:
        Token(std::string key = "", std::string value = "");
        std::string to_string();
        void print();

        void setkey(std::string key){this->key = key;}
        void setvalue(std::string value){this->value = value;}
        std::string getkey()const{return key;}
        std::string getvalue()const{return value;}
        
    private:
        std::string key,value;
};
#endif /* TOKEN_H */