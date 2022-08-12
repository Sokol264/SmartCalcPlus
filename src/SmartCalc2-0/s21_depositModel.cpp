#include "s21_depositModel.h"

void s21::Deposit::setDepos(double sum, double perc, double tax, payment_period period, bool cap,
                            const std::vector<std::pair<int, double>> ev) {
    data.depSum = sum;
    data.percent = perc;
    data.taxPercent = tax;
    data.period = period;
    data.capitalization = cap;
    data.events.clear();
    data.events = ev;
    data.payments.clear();
    data.taxPayments.clear();
    data.totalSum = 0;
    data.stackPercent = 0;
    calculate();
}
void s21::Deposit::calculate() {
    double totalSum = data.depSum;
    for (int i = 0; i < static_cast<int>(data.events.size()); i++) {
        double payment = totalSum * data.percent * data.events[i].first / 365 / 100;
        if (data.events[i].second != 0) {
            totalSum += data.events[i++].second;
            payment += totalSum * data.percent * data.events[i].first / 365 / 100;
        }
        if (data.capitalization == true) totalSum += payment;
        data.stackPercent += payment;
        data.payments.push_back(payment);
    }
    data.totalSum = totalSum;
}
