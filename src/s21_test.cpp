#include <gtest/gtest.h>

#include "SmartCalc2-0/s21_model.h"

TEST(PolishNotation, ReadAndCalculate) {
    s21::CalcModel model;
    std::string expresion = "tan(1)";
    std::string result = model.calculate(expresion, 0);
    ASSERT_EQ("1.557408", result);
    expresion = "tan(1+2)";
    result = model.calculate(expresion, 0);
    ASSERT_EQ("-0.142547", result);
    expresion = "son(1+2)";
    result = model.calculate(expresion, 0);
    ASSERT_EQ("nan", result);
    expresion = "-1";
    result = model.calculate(expresion, 0);
    ASSERT_EQ("-1.000000", result);
    expresion = "a";
    result = model.calculate(expresion, 0);
    ASSERT_EQ("nan", result);
    expresion = "+1.2";
    result = model.calculate(expresion, 0);
    ASSERT_EQ("1.200000", result);
    expresion = "2.2.";
    result = model.calculate(expresion, 0);
    ASSERT_EQ("nan", result);
    expresion = "ln(2*2-2)";
    result = model.calculate(expresion, 0);
    ASSERT_EQ("0.693147", result);
    expresion = "ln";
    result = model.calculate(expresion, 0);
    ASSERT_EQ("nan", result);
    expresion = "8ln";
    result = model.calculate(expresion, 0);
    ASSERT_EQ("nan", result);
    expresion = "8+-";
    result = model.calculate(expresion, 0);
    ASSERT_EQ("nan", result);
    expresion = "(8))";
    result = model.calculate(expresion, 0);
    ASSERT_EQ("nan", result);
    expresion = "((8+6)";
    result = model.calculate(expresion, 0);
    ASSERT_EQ("nan", result);
    expresion = "(9 9 +)";
    result = model.calculate(expresion, 0);
    ASSERT_EQ("nan", result);
    expresion = "2^2";
    result = model.calculate(expresion, 0);
    ASSERT_EQ("4.000000", result);
    expresion = "cos(sin(3))";
    result = model.calculate(expresion, 0);
    ASSERT_EQ("0.990059", result);
    expresion = "asin(1)";
    result = model.calculate(expresion, 0);
    ASSERT_EQ("1.570796", result);
    expresion = "acos(0.23)";
    result = model.calculate(expresion, 0);
    ASSERT_EQ("1.338719", result);
    expresion = "tan(0.4125)";
    result = model.calculate(expresion, 0);
    ASSERT_EQ("0.437607", result);
    expresion = "atan(-0.241)";
    result = model.calculate(expresion, 0);
    ASSERT_EQ("-0.236490", result);
    expresion = "sqrt(421)";
    result = model.calculate(expresion, 0);
    ASSERT_EQ("20.518285", result);
    expresion = "log(23.342)";
    result = model.calculate(expresion, 0);
    ASSERT_EQ("1.368138", result);
    expresion = "x*132";
    result = model.calculate(expresion, 0.3);
    ASSERT_EQ("39.600000", result);
    expresion = "8x";
    result = model.calculate(expresion, 0);
    ASSERT_EQ("nan", result);
    expresion = "2/2";
    result = model.calculate(expresion, 0);
    ASSERT_EQ("1.000000", result);
    expresion = "2%2";
    result = model.calculate(expresion, 0);
    ASSERT_EQ("0.000000", result);
}

TEST(CreditCalculation, Test) {
    s21::CalcModel model;
    s21::cr_t credit = model.creditCalc(2000, 2, 12, s21::ANNUITY);
    ASSERT_TRUE(fabs(credit.overpayment - 30.049751) < 1e-6);
    ASSERT_TRUE(fabs(credit.totalPayment - 2030.05) < 1e-2);
    ASSERT_TRUE(fabs(credit.monthlyPayment - 1015.02) < 1e-2);

    ASSERT_TRUE(fabs(credit.payment[0] - 1015.02) < 1e-2);
    ASSERT_TRUE(fabs(credit.payment[1] - 1015.02) < 1e-2);

    ASSERT_TRUE(fabs(credit.percentPayment[0] - 20) < 1e-2);
    ASSERT_TRUE(fabs(credit.percentPayment[1] - 10.0498) < 1e-4);

    credit = model.creditCalc(2000, 2, 12, s21::DIFFERENTIATED);
    ASSERT_TRUE(fabs(credit.overpayment - 30) < 1e-1);
    ASSERT_TRUE(fabs(credit.totalPayment - 2030) < 1e-1);
    ASSERT_TRUE(fabs(credit.monthlyPayment - 1015) < 1e-1);

    ASSERT_TRUE(fabs(credit.payment[0] - 1020) < 1e-1);
    ASSERT_TRUE(fabs(credit.payment[1] - 1010) < 1e-1);

    ASSERT_TRUE(fabs(credit.percentPayment[0] - 20) < 1e-1);
    ASSERT_TRUE(fabs(credit.percentPayment[1] - 10) < 1e-1);
}

TEST(DepositCalculation, Test) {
    s21::CalcModel model;
    auto deposit = model.depositCalc(1000, 12, 0, s21::MONTH, true, {{31, 0}, {30, 0}});

    ASSERT_TRUE(fabs(deposit.stackPercent - 20.1553) < 1e-4);
    ASSERT_TRUE(fabs(deposit.totalSum - 1020.16) < 1e-2);

    ASSERT_TRUE(fabs(deposit.payments[0] - 10.1918) < 1e-4);
    ASSERT_TRUE(fabs(deposit.payments[1] - 9.96354) < 1e-5);

    deposit = model.depositCalc(1000, 12, 0, s21::MONTH, false, {{31, 0}, {30, 0}});
    ASSERT_TRUE(fabs(deposit.stackPercent - 20.0548) < 1e-4);
    ASSERT_TRUE(fabs(deposit.totalSum - 1000.0) < 1e-1);

    ASSERT_TRUE(fabs(deposit.payments[0] - 10.1918) < 1e-4);
    ASSERT_TRUE(fabs(deposit.payments[1] - 9.86301) < 1e-5);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
