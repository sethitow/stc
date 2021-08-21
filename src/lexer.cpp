#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "lexer.hpp"
#include "token.hpp"

const std::vector<std::string> keywords = {"PROGRAM", "VAR", "END_VAR", "END_PROGRAM", "BOOL", "TRUE", "FALSE"}; // keywords
const std::vector<std::string> operators = {"<", ">", "+", "-", "%", ":="};                                      // operators
const std::vector<std::string> special_characters = {"{", "}", "[", "]", ";", ":"};                              // special characters

TokenStream tokenize(std::string fileInput)
{
    TokenStream output_tokens;

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

        // Single line comments
        if (curr_char == '/' and fileInput[i + 1] == '/')
        {
            auto idx = fileInput.find("\n", i);
            if (idx != std::string::npos)
            {
                auto cmnt = fileInput.substr(i, idx - i);
                output_tokens.push(Token{"COMMENT_SINGLE_LINE", cmnt});
                i = idx;
                continue;
            }
        }

        // Multiline comments
        // TODO: support nested comments
        if (curr_char == '(' and fileInput[i + 1] == '*')
        {
            auto idx = fileInput.find("*)", i);
            if (idx != std::string::npos)
            {
                auto cmnt = fileInput.substr(i, idx - i + 2);
                output_tokens.push(Token{"COMMENT_MULTI_LINE", cmnt});
                i = idx + 1;
                continue;
            }
        }

        if (isalpha(curr_char))
        {
            //VARIABLES
            std::string lastChar = "";
            int position = fileInput.find_first_of(" \r\n", i); // returns index

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
                output_tokens.push((Token){"KEYWORD", curr_word});
            }
            else
            {
                output_tokens.push((Token){"IDENTIFIER", curr_word});
            }
            if (!(lastChar.empty()))
            {
                if (lastChar == "{") // Identify specific character & create object
                    output_tokens.push((Token){"Left Brace", lastChar});
                else if (lastChar == "}")
                    output_tokens.push((Token){"Right Brace", lastChar});
                else if (lastChar == "[")
                    output_tokens.push((Token){"Left Bracket", lastChar});
                else if (lastChar == "]")
                    output_tokens.push((Token){"Right Bracket", lastChar});
                else if (lastChar == ";")
                    output_tokens.push((Token){"Semi Colon", lastChar});
                else if (lastChar == ":")
                    output_tokens.push((Token){"Colon", lastChar});
                else
                    output_tokens.push((Token){"SPECIAL_CHARACTER", lastChar});
            }
            i += curr_word_len - 1; // begin next iteration at last index of current word
        }
        else
        {
            int position2 = fileInput.find(" ", i); // what to find, index to start finding at // return index
            curr_word = fileInput.substr(i, position2 - i);

            if (curr_word == "<") // Identify specific character & create object
                output_tokens.push((Token){"Less than", curr_word});
            else if (curr_word == ">")
                output_tokens.push((Token){"Greater then", curr_word});
            else if (curr_word == "+")
                output_tokens.push((Token){"Add", curr_word});
            else if (curr_word == "-")
                output_tokens.push((Token){"Subtract", curr_word});
            else if (curr_word == "%")
                output_tokens.push((Token){"Modulo", curr_word});
            else if (curr_word == ":=")
                output_tokens.push((Token){"Assignment ", curr_word});
            else if (curr_word == "{")
                output_tokens.push((Token){"Left Brace", curr_word});
            else if (curr_word == "}")
                output_tokens.push((Token){"Right Brace", curr_word});
            else if (curr_word == "[")
                output_tokens.push((Token){"Left Bracket", curr_word});
            else if (curr_word == "]")
                output_tokens.push((Token){"Right Bracket", curr_word});
            else if (curr_word == ";")
                output_tokens.push((Token){"Semi Colon", curr_word});
            else if (curr_word == ":")
                output_tokens.push((Token){"Colon", curr_word});
            else
                output_tokens.push((Token){"OPERATOR", curr_word});
            i += curr_word.length() - 1; // begin next iteration at last index of current word
        }
    }

    return output_tokens;
}
