#ifndef SRC_SMARTCALC2_0_S21_POLISHMODEL_H_
#define SRC_SMARTCALC2_0_S21_POLISHMODEL_H_

#include <cmath>
#include <iostream>
#include <regex>
#include <stack>
#include <string>
#include <vector>

namespace s21 {
typedef struct parserControlStatus {
    bool opers;
    bool unary_funcs;
    bool unknown_x;
    bool number;
    bool open_brackets;
    bool close_brackets;
} ctrl_stat;

class PolishNotationModel {
    std::string expresion;
    std::stack<std::string> operation;
    std::vector<std::string> notation;
    ctrl_stat pars_status = {false, true, true, true, true, false};

 public:
    PolishNotationModel() {}
    explicit PolishNotationModel(std::string);
    ~PolishNotationModel() {}

    double calculateExpresion(double x = 0);
    void set_expresion(std::string);

 private:
    bool checkNumericValidation();
    void convertExpresion();
    void workWithNumber(int &index);
    void workWithFunction(int &index);
    void workWithOperations(int &index);
    int workWithClosingBrackets();
    bool isfunction(int &index);
    int getPriorityOperation(std::string oper);
    void chooseAction(std::stack<double> &number, std::string action);
    void funcAction(std::stack<double> &number, std::string action);
    void operAction(std::stack<double> &number, std::string action);
    void pushOperation();
    bool stringIsNumber(std::string);
    void clearData();
};
}  // namespace s21

#endif  // SRC_SMARTCALC2_0_S21_POLISHMODEL_H_
