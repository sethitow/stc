#include <algorithm>
#include <iostream>
#include <iterator>
#include <cstdlib>
#include <string>
#include <vector>

#include "lexer.h"


//using namespace std; std::

//VARIABLES
std::vector<std::string> all_types = {"PROGRAM", "VAR", "END_VAR", "END_PROGRAM", "BOOL", "TRUE", "FALSE"}; //keywords
std::vector<std::string> operators = {"<", ">", "+", "-", "%", ":="}; // operators
std::vector<std::string> all_sc = {"{", "}", "[", "]", ";", ":"}; // special characters
std::vector<Token> fin_tokens;
void display(){
    for(int i = 0; i < fin_tokens.size(); i++){
        fin_tokens[i].print();
    }
}

void tokenizerFunc (std::string fileInput){
    // Will correct this to consider comments
    std::replace( fileInput.begin(), fileInput.end(), '\n', ' ' ); // find newlines & replace with space

    // Iterate through string & begin identifiying tokens
    for(int i = 0; i < fileInput.length(); i++){ 
        // VARIABLES
        int curr_word_len = 0; 
        std::string curr_word = "";
        char curr_char = fileInput[i];

        if(curr_char == ' '){
            continue;
        }
        else if(isalpha(curr_char)){
            //VARIABLES
            std::string lastChar = "";
            int position = fileInput.find(" ", i); // returns index

            curr_word = fileInput.substr(i, position-i); //Creates string from current index to next space found
            curr_word_len = curr_word.length();

            // checks if last char is non-alphabetic
            if(!(isalpha(curr_word.back()))){ 
                lastChar = curr_word.back();
                if(find(all_sc.begin(), all_sc.end(), lastChar) != all_sc.end()){ // if lastCchar exist in the special character (sc) vector
                    curr_word.pop_back(); 
                }
            }
            // check if the current word is a keyword or not
            if(find(all_types.begin(), all_types.end(), curr_word) != all_types.end()){
                fin_tokens.push_back((Token){"KEYWORD",curr_word});
            }
            else{
                fin_tokens.push_back((Token){"IDENTIFIER",curr_word});
            }
            if(!(lastChar.empty())){
                if(lastChar == "{") // Identify specific character & create object
                    fin_tokens.push_back((Token){"Left Brace",lastChar});
                else if(lastChar == "}")
                    fin_tokens.push_back((Token){"Right Brace",lastChar});
                else if(lastChar == "[")
                    fin_tokens.push_back((Token){"Left Bracket",lastChar});
                else if(lastChar == "]")
                    fin_tokens.push_back((Token){"Right Bracket",lastChar});
                else if(lastChar == ";")
                    fin_tokens.push_back((Token){"Semi Colon",lastChar});
                else if(lastChar == ":")
                        fin_tokens.push_back((Token){"Colon",lastChar});
                else
                    fin_tokens.push_back((Token){"SPECIAL_CHARACTER",lastChar});
            }
            i += curr_word_len-1; // begin next iteration at last index of current word   
        }
        else{
            int position2 = fileInput.find(" ", i); // what to find, index to start finding at // return index
            curr_word = fileInput.substr(i, position2-i); 

            if(curr_word == "<") // Identify specific character & create object
                fin_tokens.push_back((Token){"Less than",curr_word});
            else if(curr_word == ">")
                fin_tokens.push_back((Token){"Greater then",curr_word});
            else if(curr_word == "+")
                fin_tokens.push_back((Token){"Add",curr_word});
            else if(curr_word ==  "-")
                fin_tokens.push_back((Token){"Subtract",curr_word});
            else if(curr_word == "%")
                fin_tokens.push_back((Token){"Modulo",curr_word});
            else if(curr_word == ":=")
                fin_tokens.push_back((Token){"Assignment ",curr_word});
            else if(curr_word == "{")
                fin_tokens.push_back((Token){"Left Brace",curr_word});
            else if(curr_word == "}")
                fin_tokens.push_back((Token){"Right Brace",curr_word});
            else if(curr_word == "[")
                fin_tokens.push_back((Token){"Left Bracket",curr_word});
            else if(curr_word == "]")
                fin_tokens.push_back((Token){"Right Bracket",curr_word});
            else if(curr_word == ";")
                fin_tokens.push_back((Token){"Semi Colon",curr_word});
            else if(curr_word == ":")
                    fin_tokens.push_back((Token){"Colon",curr_word});
            else
                fin_tokens.push_back((Token){"OPERATOR",curr_word});
            i += curr_word.length()-1; // begin next iteration at last index of current word 
        }
    }
}