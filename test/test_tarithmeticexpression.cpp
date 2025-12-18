#include "tarithmeticexpression.h"
#include <gtest/gtest.h>  // »À» #include "gtest/gtest.h"

TEST(TArithmeticExpression, can_create_expression_from_string)
{
    ASSERT_NO_THROW(TArithmeticExpression expr("2+2"));
}

TEST(TArithmeticExpression, can_get_infix_form)
{
    TArithmeticExpression expr("2+2");
    EXPECT_EQ("2+2", expr.GetInfix());
}

TEST(TArithmeticExpression, can_get_postfix_form)
{
    TArithmeticExpression expr("2+2");
    EXPECT_EQ("2 2 +", expr.GetPostfix());
}

TEST(TArithmeticExpression, can_calculate_simple_expression)
{
    TArithmeticExpression expr("2+2");
    EXPECT_EQ(4.0, expr.calculate());
}

TEST(TArithmeticExpression, can_calculate_expression_with_multiply)
{
    TArithmeticExpression expr("2*3");
    EXPECT_EQ(6.0, expr.calculate());
}

TEST(TArithmeticExpression, can_calculate_expression_with_parentheses)
{
    TArithmeticExpression expr("(2+3)*4");
    EXPECT_EQ(20.0, expr.calculate());
}

TEST(TArithmeticExpression, can_calculate_complex_expression)
{
    TArithmeticExpression expr("(2+3)*(4-1)/2");
    EXPECT_EQ(7.5, expr.calculate());
}

TEST(TArithmeticExpression, can_handle_whitespace)
{
    TArithmeticExpression expr(" 2 + 3 * 4 ");
    EXPECT_EQ(14.0, expr.calculate());
}

TEST(TArithmeticExpression, can_handle_negative_numbers)
{
    TArithmeticExpression expr("-2+3");
    EXPECT_EQ(1.0, expr.calculate());
}

TEST(TArithmeticExpression, throws_when_invalid_expression)
{
    ASSERT_ANY_THROW(TArithmeticExpression expr("2++2"));
}

TEST(TArithmeticExpression, throws_when_division_by_zero)
{
    TArithmeticExpression expr("2/0");
    ASSERT_ANY_THROW(expr.calculate());
}

TEST(TArithmeticExpression, can_calculate_expression_with_variables)
{
    TArithmeticExpression expr("a+b*c");
    std::map<char, double> values = {{'a', 2}, {'b', 3}, {'c', 4}};
    EXPECT_EQ(14.0, expr.calculate(values));
}