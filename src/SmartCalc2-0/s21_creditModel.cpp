#include "s21_creditModel.h"

void s21::Credit::calculate() {
    double P = data.percent / 100 / 12;
    double sumLeft = data.creditSum;
    double p;
    if (data.type == ANNUITY) {
        data.monthlyPayment = data.creditSum * (P + (P / (pow(1 + P, data.monthCount) - 1)));
        data.totalPayment = data.monthlyPayment * data.monthCount;
        for (int i = 0; i < data.monthCount; i++) {
            p = sumLeft * P;
            sumLeft -= data.monthlyPayment - p;
            data.percentPayment.push_back(p);
            data.payment.push_back(data.monthlyPayment);
        }
    } else {
        double b = data.creditSum / data.monthCount;
        for (int i = 0; i < data.monthCount; i++) {
            double tempMonthlyPayment;
            p = sumLeft * P;
            data.percentPayment.push_back(p);
            tempMonthlyPayment = p + b;
            data.payment.push_back(tempMonthlyPayment);
            data.totalPayment += tempMonthlyPayment;
            sumLeft -= b;
            data.monthlyPayment += tempMonthlyPayment;
        }
        data.monthlyPayment /= data.monthCount;
    }
    data.overpayment = data.totalPayment - data.creditSum;
}
void s21::Credit::setCred(double sum, int month, double perc, credit_type tp) {
    data.creditSum = sum;
    data.monthCount = month;
    data.percent = perc;
    data.type = tp;
    data.monthlyPayment = 0;
    data.overpayment = 0;
    data.totalPayment = 0;
    data.payment.clear();
    data.percentPayment.clear();
    calculate();
}
