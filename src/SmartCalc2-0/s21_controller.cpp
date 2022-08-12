#include "s21_controller.h"

std::string s21::Controller::calc(std::string expresion, double x) { return model->calculate(expresion, x); }

std::vector<std::pair<double, double>> s21::Controller::getCoordinates(std::string expresion, double x_max) {
    return model->calcCoordinates(expresion, x_max);
}

s21::cr_t s21::Controller::calcCred(double sum, int month, double perc, credit_type type) {
    return model->creditCalc(sum, month, perc, type);
}

s21::dp_t s21::Controller::calcDepos(double sum, double perc, double tax, payment_period period, bool cap,
                                     std::vector<std::pair<int, double>> ev) {
    return model->depositCalc(sum, perc, tax, period, cap, ev);
}
