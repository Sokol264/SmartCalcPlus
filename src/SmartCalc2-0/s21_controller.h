#ifndef SRC_SMARTCALC2_0_S21_CONTROLLER_H_
#define SRC_SMARTCALC2_0_S21_CONTROLLER_H_

#include <iostream>
#include <string>

#include "s21_model.h"
namespace s21 {
class Controller {
    CalcModel *model;

 public:
    Controller() : model(nullptr) {}
    explicit Controller(CalcModel *model) : model(model) {}
    ~Controller() {}
    std::string calc(std::string expresion, double x = 0.0);
    std::vector<std::pair<double, double>> getCoordinates(std::string expresion, double x_max);
    cr_t calcCred(double sum, int month, double perc, credit_type type);
    dp_t calcDepos(double sum, double perc, double tax, payment_period period, bool cap,
                   std::vector<std::pair<int, double>> ev);
};
}  // namespace s21
#endif  // SRC_SMARTCALC2_0_S21_CONTROLLER_H_
