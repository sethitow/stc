

#include "gtest/gtest.h"

#include "../src/lexer.hpp"
#include "../src/token.hpp"

TEST(Lexer, Function)
{
    std::string input = "FUNCTION F_Sample : INT"
                        "  VAR_INPUT"
                        "    x : INT;"
                        "    y : INT;"
                        "  END_VAR"
                        "  F_Sample := x + y;"
                        "END_FUNCTION;";

    auto tokens = tokenize(input);

    auto tok_vec = tokens.to_vec();

    std::vector<Token>
        expected_tok_vec{
            Token("KEYWORD", "FUNCTION"),
            Token("IDENTIFIER", "F_Sample"),
            Token("SPECIAL_CHARACTER", ":"),
            Token("KEYWORD", "INT"),
            Token("KEYWORD", "VAR_INPUT"),
            Token("IDENTIFIER", "x"),
            Token("SPECIAL_CHARACTER", ":"),
            Token("KEYWORD", "INT"),
            Token("SPECIAL_CHARACTER", ";"),
            Token("IDENTIFIER", "y"),
            Token("SPECIAL_CHARACTER", ":"),
            Token("KEYWORD", "INT"),
            Token("SPECIAL_CHARACTER", ";"),
            Token("KEYWORD", "END_VAR"),
            Token("IDENTIFIER", "F_Sample"),
            Token("OPERATOR", ":="),
            Token("IDENTIFIER", "x"),
            Token("OPERATOR", "+"),
            Token("IDENTIFIER", "y"),
            Token("SPECIAL_CHARACTER", ";"),
            Token("KEYWORD", "END_FUNCTION"),
            Token("SPECIAL_CHARACTER", ";"),
        };

    ASSERT_EQ(tok_vec.size(), expected_tok_vec.size());

    for (int i = 0; i < tok_vec.size(); ++i)
    {
        EXPECT_EQ(tok_vec[i], expected_tok_vec[i]) << "Vectors x and y differ at index " << i;
    }
}

TEST(Lexer, Assignment)
{
    auto tokens = tokenize(":=");
    auto tok_vec = tokens.to_vec();

    std::vector<Token>
        expected_tok_vec{Token("OPERATOR", ":=")};

    ASSERT_EQ(tok_vec.size(), expected_tok_vec.size());

    for (int i = 0; i < tok_vec.size(); ++i)
    {
        EXPECT_EQ(tok_vec[i], expected_tok_vec[i]) << "Vectors x and y differ at index " << i;
    }
}