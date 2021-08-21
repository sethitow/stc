#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "lexer.hpp"
#include "token.hpp"

const std::vector<std::string> KEYWORDS = {"PROGRAM", "VAR", "END_VAR", "END_PROGRAM", "BOOL", "TRUE", "FALSE"};
const auto IDENTIFIER_CHARACTERS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890_";

TokenStream tokenize(std::string fileInput)
{
    TokenStream output_tokens;

    // Iterate through string & begin identifiying tokens
    for (int i = 0; i < fileInput.length(); i++)
    {
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

        // Operators
        if (curr_char == '>')
        {
            output_tokens.push((Token){"OPERATOR", std::string(1, curr_char)});
            continue;
        }
        if (curr_char == '<')
        {
            output_tokens.push((Token){"OPERATOR", std::string(1, curr_char)});
            continue;
        }
        if (curr_char == '+')
        {
            output_tokens.push((Token){"OPERATOR", std::string(1, curr_char)});
            continue;
        }
        if (curr_char == '-')
        {
            output_tokens.push((Token){"OPERATOR", std::string(1, curr_char)});
            continue;
        }
        if (curr_char == ':' and fileInput[i + 1] == '=')
        {
            output_tokens.push((Token){"OPERATOR", ":="});
            i++;
            continue;
        }
        if (curr_char == '=' and fileInput[i + 1] == '>')
        {
            output_tokens.push((Token){"OPERATOR", "=>"});
            i++;
            continue;
        }

        // Special characters (scoping, subscripting, etc)
        if (curr_char == '{')
        {
            output_tokens.push((Token){"SPECIAL_CHARACTER", std::string(1, curr_char)});
            continue;
        }
        if (curr_char == '}')
        {
            output_tokens.push((Token){"SPECIAL_CHARACTER", std::string(1, curr_char)});
            continue;
        }
        if (curr_char == '[')
        {
            output_tokens.push((Token){"SPECIAL_CHARACTER", std::string(1, curr_char)});
            continue;
        }
        if (curr_char == ']')
        {
            output_tokens.push((Token){"SPECIAL_CHARACTER", std::string(1, curr_char)});
            continue;
        }
        if (curr_char == ';')
        {
            output_tokens.push((Token){"SPECIAL_CHARACTER", std::string(1, curr_char)});
            continue;
        }
        if (curr_char == ':')
        {
            output_tokens.push((Token){"SPECIAL_CHARACTER", std::string(1, curr_char)});
            continue;
        }

        if (isalpha(curr_char))
        {
            auto position = fileInput.find_first_not_of(IDENTIFIER_CHARACTERS, i);
            auto curr_word = fileInput.substr(i, position - i);

            // check if the current word is a keyword or not
            if (std::find(KEYWORDS.begin(), KEYWORDS.end(), curr_word) != KEYWORDS.end())
            {
                output_tokens.push((Token){"KEYWORD", curr_word});
            }
            else
            {
                output_tokens.push((Token){"IDENTIFIER", curr_word});
            }
            i += curr_word.length() - 1; // begin next iteration at last index of current word
            continue;
        }
        std::cerr << "Unknown character: <" << curr_char << ">" << std::endl;
    }

    return output_tokens;
}
