#ifndef SRC_SMARTCALC2_0_S21_MODEL_H_
#define SRC_SMARTCALC2_0_S21_MODEL_H_

#include "s21_creditModel.h"
#include "s21_depositModel.h"
#include "s21_polishModel.h"

namespace s21 {
class CalcModel {
    PolishNotationModel polModel;
    Credit credit;
    Deposit deposit;

 public:
    CalcModel() {}
    ~CalcModel() {}
    std::string calculate(std::string, double);
    std::vector<std::pair<double, double>> calcCoordinates(std::string expresion, double x_max);
    cr_t creditCalc(double, int, double, credit_type);
    dp_t depositCalc(double, double, double, payment_period, bool, std::vector<std::pair<int, double>>);

 private:
};
}  // namespace s21
#endif  // SRC_SMARTCALC2_0_S21_MODEL_H_
