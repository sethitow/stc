#include "gtest/gtest.h"

#include "../src/token.hpp"

TEST(ToString, ToString)
{
    Token tok("KEY", "VAL");
    EXPECT_EQ(tok.to_string(), "KEY VAL");
};

TEST(PrintableValue, CarriageReturn)
{
    Token tok_cr("return", "\r");

    EXPECT_EQ(tok_cr.getvalueprintable(), R"(\r)");
};

TEST(PrintableValue, LineFeed)
{
    Token tok_lf("newline", "\n");

    EXPECT_EQ(tok_lf.getvalueprintable(), R"(\n)");
};

TEST(EQOperator, DifferentKeys)
{
    Token tok1("KEY1", "VAL1");
    Token tok2("KEY1", "VAL1");
    Token tok3("KEY2", "VAL1");

    EXPECT_EQ(tok1, tok2);
    EXPECT_FALSE(tok1 == tok3);
};

TEST(EQOperator, DifferentValues)
{
    Token tok1("KEY1", "VAL1");
    Token tok2("KEY1", "VAL1");
    Token tok3("KEY1", "VAL2");

    EXPECT_EQ(tok1, tok2);
    EXPECT_FALSE(tok1 == tok3);
};