#ifndef SRC_SMARTCALC2_0_S21_DEPOSITMODEL_H_
#define SRC_SMARTCALC2_0_S21_DEPOSITMODEL_H_

#include <iostream>
#include <vector>

namespace s21 {
enum payment_period { DAY, WEEK, MONTH, QUARTER, HALF_YEAR, YEAR, END };

typedef struct deposit_st {
    double depSum = 0;
    double percent = 0;
    double taxPercent = 0;
    payment_period period = MONTH;
    bool capitalization = false;
    std::vector<std::pair<int, double>> events;
    double stackPercent = 0;
    double taxSum = 0;
    double totalSum = 0;
    std::vector<double> payments;
    std::vector<double> taxPayments;
} dp_t;

class Deposit {
    dp_t data;

 public:
    Deposit() {}
    ~Deposit() {}
    void calculate();
    void setDepos(double, double, double, payment_period, bool, std::vector<std::pair<int, double>>);
    dp_t getData() { return data; }
};
}  // namespace s21

#endif  // SRC_SMARTCALC2_0_S21_DEPOSITMODEL_H_
