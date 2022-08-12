#ifndef SRC_SMARTCALC2_0_S21_CREDITMODEL_H_
#define SRC_SMARTCALC2_0_S21_CREDITMODEL_H_

#include <cmath>
#include <iostream>
#include <vector>

namespace s21 {
enum credit_type { ANNUITY, DIFFERENTIATED };

typedef struct credit_st {
    double creditSum;
    int monthCount;
    double percent;
    credit_type type;
    double monthlyPayment;
    double overpayment;
    double totalPayment;
    std::vector<double> payment;
    std::vector<double> percentPayment;
} cr_t;

class Credit {
 private:
    cr_t data;

 public:
    Credit() {
        data.creditSum = 0;
        data.monthCount = 0;
        data.percent = 0;
        data.type = ANNUITY;
        data.monthlyPayment = 0;
        data.overpayment = 0;
        data.totalPayment = 0;
    }
    ~Credit() {}
    void calculate();
    void setCred(double, int, double, credit_type);
    cr_t getData() { return data; }
};
}  // namespace s21

#endif  // SRC_SMARTCALC2_0_S21_CREDITMODEL_H_
