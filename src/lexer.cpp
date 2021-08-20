#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "lexer.h"
#include "token.h"

//VARIABLES
const std::vector<std::string> keywords = {"PROGRAM", "VAR", "END_VAR", "END_PROGRAM", "BOOL", "TRUE", "FALSE"}; //keywords
const std::vector<std::string> operators = {"<", ">", "+", "-", "%", ":="};                                      // operators
const std::vector<std::string> special_characters = {"{", "}", "[", "]", ";", ":"};                              // special characters

void display(std::vector<Token> tokens)
{
    for (const auto &token : tokens)
    {
        token.print();
    }
}

std::vector<Token> tokenize(std::string fileInput)
{
    std::vector<Token> output_tokens;

    // Will correct this to consider comments
    std::replace(fileInput.begin(), fileInput.end(), '\n', ' '); // find newlines & replace with space

    // Iterate through string & begin identifiying tokens
    for (int i = 0; i < fileInput.length(); i++)
    {
        // VARIABLES
        int curr_word_len = 0;
        std::string curr_word = "";
        char curr_char = fileInput[i];

        if (isspace(curr_char))
        {
            continue;
        }
        else if (isalpha(curr_char))
        {
            //VARIABLES
            std::string lastChar = "";
            int position = fileInput.find(" ", i); // returns index

            curr_word = fileInput.substr(i, position - i); //Creates string from current index to next space found
            curr_word_len = curr_word.length();

            // checks if last char is non-alphabetic
            if (!(isalpha(curr_word.back())))
            {
                lastChar = curr_word.back();
                if (find(special_characters.begin(), special_characters.end(), lastChar) != special_characters.end())
                { // if lastCchar exist in the special character (sc) vector
                    curr_word.pop_back();
                }
            }
            // check if the current word is a keyword or not
            if (find(keywords.begin(), keywords.end(), curr_word) != keywords.end())
            {
                output_tokens.push_back((Token){"KEYWORD", curr_word});
            }
            else
            {
                output_tokens.push_back((Token){"IDENTIFIER", curr_word});
            }
            if (!(lastChar.empty()))
            {
                if (lastChar == "{") // Identify specific character & create object
                    output_tokens.push_back((Token){"Left Brace", lastChar});
                else if (lastChar == "}")
                    output_tokens.push_back((Token){"Right Brace", lastChar});
                else if (lastChar == "[")
                    output_tokens.push_back((Token){"Left Bracket", lastChar});
                else if (lastChar == "]")
                    output_tokens.push_back((Token){"Right Bracket", lastChar});
                else if (lastChar == ";")
                    output_tokens.push_back((Token){"Semi Colon", lastChar});
                else if (lastChar == ":")
                    output_tokens.push_back((Token){"Colon", lastChar});
                else
                    output_tokens.push_back((Token){"SPECIAL_CHARACTER", lastChar});
            }
            i += curr_word_len - 1; // begin next iteration at last index of current word
        }
        else
        {
            int position2 = fileInput.find(" ", i); // what to find, index to start finding at // return index
            curr_word = fileInput.substr(i, position2 - i);

            if (curr_word == "<") // Identify specific character & create object
                output_tokens.push_back((Token){"Less than", curr_word});
            else if (curr_word == ">")
                output_tokens.push_back((Token){"Greater then", curr_word});
            else if (curr_word == "+")
                output_tokens.push_back((Token){"Add", curr_word});
            else if (curr_word == "-")
                output_tokens.push_back((Token){"Subtract", curr_word});
            else if (curr_word == "%")
                output_tokens.push_back((Token){"Modulo", curr_word});
            else if (curr_word == ":=")
                output_tokens.push_back((Token){"Assignment ", curr_word});
            else if (curr_word == "{")
                output_tokens.push_back((Token){"Left Brace", curr_word});
            else if (curr_word == "}")
                output_tokens.push_back((Token){"Right Brace", curr_word});
            else if (curr_word == "[")
                output_tokens.push_back((Token){"Left Bracket", curr_word});
            else if (curr_word == "]")
                output_tokens.push_back((Token){"Right Bracket", curr_word});
            else if (curr_word == ";")
                output_tokens.push_back((Token){"Semi Colon", curr_word});
            else if (curr_word == ":")
                output_tokens.push_back((Token){"Colon", curr_word});
            else
                output_tokens.push_back((Token){"OPERATOR", curr_word});
            i += curr_word.length() - 1; // begin next iteration at last index of current word
        }
    }

    return output_tokens;
}
