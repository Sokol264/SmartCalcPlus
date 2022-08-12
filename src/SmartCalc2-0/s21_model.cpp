#include "s21_model.h"

#include <stdio.h>

std::string s21::CalcModel::calculate(std::string expresion, double x) {
    polModel.set_expresion(expresion);
    double num = polModel.calculateExpresion(x);
    std::string result = std::to_string(num);
    return result;
}
std::vector<std::pair<double, double>> s21::CalcModel::calcCoordinates(std::string expresion, double x_max) {
    polModel.set_expresion(expresion);
    double x = -x_max;
    double step = (x_max * 2) / 10000;
    std::vector<std::pair<double, double>> coord(10000);
    for (int i = 0; i < 10000; i++) {
        coord[i].first = x;
        coord[i].second = polModel.calculateExpresion(x);
        x += step;
    }
    return coord;
}
s21::cr_t s21::CalcModel::creditCalc(double sum, int month, double perc, credit_type tp) {
    credit.setCred(sum, month, perc, tp);
    return credit.getData();
}
s21::dp_t s21::CalcModel::depositCalc(double sum, double perc, double tax_perc, payment_period period,
                                      bool cap, std::vector<std::pair<int, double>> events) {
    deposit.setDepos(sum, perc, tax_perc, period, cap, events);
    return deposit.getData();
}
