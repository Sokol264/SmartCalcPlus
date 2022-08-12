#include "s21_polishModel.h"

s21::PolishNotationModel::PolishNotationModel(const std::string expresion) : expresion(expresion) {
    convertExpresion();
}
void s21::PolishNotationModel::convertExpresion() {
    bool validation = true;
    if (checkNumericValidation()) validation = false;
    for (int i = 0; i < static_cast<int>(expresion.size()) && validation; i++) {
        if (isdigit(expresion[i]) && pars_status.number) {
            workWithNumber(i);
            pars_status = {true, false, false, false, false, true};
        } else if (expresion[i] == '(' && pars_status.open_brackets) {
            operation.push("(");
            pars_status = {true, true, true, true, true, false};
        } else if (getPriorityOperation(expresion.substr(i, 1)) && pars_status.opers && expresion[i] != '(') {
            workWithOperations(i);
            pars_status = {false, true, true, true, true, false};
        } else if (expresion[i] == ')' && pars_status.close_brackets) {
            validation = workWithClosingBrackets() ? false : true;
            pars_status = {true, false, false, false, false, true};
        } else if (expresion[i] == 'x' && pars_status.unknown_x) {
            notation.push_back("x");
            pars_status = {true, false, false, false, false, true};
        } else if ((getPriorityOperation(expresion.substr(i, 1)) == 4 ||
                    getPriorityOperation(expresion.substr(i, 4)) == 1) &&
                   pars_status.unary_funcs) {
            workWithFunction(i);
            pars_status = {true, true, false, true, true, false};
        } else {
            validation = false;
        }
        if (i == -1) validation = false;
    }
    if (pars_status.number) validation = false;
    if (validation)
        pushOperation();
    else
        clearData();
}
bool s21::PolishNotationModel::checkNumericValidation() {
    bool result = false;
    std::regex regular(R"(^\.|\.$|[0-9][a-zA-Z]|[a-zA-Z][0-9]|[0-9]\.[^0-9]|[0-9]\.[0-9]+\.)");
    std::smatch match;
    result = std::regex_search(expresion, match, regular);
    return result;
}
void s21::PolishNotationModel::workWithNumber(int &index) {
    int len = 0;
    while (isdigit(expresion[index + len]) || expresion[index + len] == '.') len++;
    std::string number = expresion.substr(index, len);
    notation.push_back(number);
    index += len - 1;
}
void s21::PolishNotationModel::workWithOperations(int &index) {
    int newOperPrior = getPriorityOperation(expresion.substr(index, 1));
    if (newOperPrior == 4 && !isdigit(expresion[index - 1]) && expresion[index - 1] != ')' &&
        expresion[index - 1] != 'x') {
        workWithFunction(index);
    } else {
        while (!operation.empty()) {
            int prior = getPriorityOperation(operation.top());
            if (prior <= newOperPrior) {
                notation.push_back(operation.top());
                operation.pop();
            } else {
                break;
            }
        }
        operation.push(expresion.substr(index, 1));
    }
}
int s21::PolishNotationModel::workWithClosingBrackets() {
    int error = 0;
    while (!operation.empty() && operation.top() != "(") {
        notation.push_back(operation.top());
        operation.pop();
    }
    if (!operation.empty())
        operation.pop();
    else
        error = 1;
    return error;
}
void s21::PolishNotationModel::workWithFunction(int &index) {
    if (expresion.substr(index, 3) == "sin") {
        operation.push("sin");
        index += 2;
    } else if (expresion.substr(index, 3) == "cos") {
        operation.push("cos");
        index += 2;
    } else if (expresion.substr(index, 3) == "tan") {
        operation.push("tan");
        index += 2;
    } else if (expresion.substr(index, 4) == "acos") {
        operation.push("acos");
        index += 3;
    } else if (expresion.substr(index, 4) == "asin") {
        operation.push("asin");
        index += 3;
    } else if (expresion.substr(index, 4) == "atan") {
        operation.push("atan");
        index += 3;
    } else if (expresion.substr(index, 4) == "sqrt") {
        operation.push("sqrt");
        index += 3;
    } else if (expresion.substr(index, 2) == "ln") {
        operation.push("ln");
        index += 1;
    } else if (expresion.substr(index, 3) == "log") {
        operation.push("log");
        index += 2;
    } else if (expresion.substr(index, 1) == "-") {
        operation.push("unary_minus");
    } else if (expresion.substr(index, 1) == "+") {
        operation.push("unary_plus");
    } else {
        index = -1;
    }
}
void s21::PolishNotationModel::pushOperation() {
    while (!operation.empty()) {
        if (operation.top() == "(") {
            clearData();
        } else {
            notation.push_back(operation.top());
            operation.pop();
        }
    }
}
int s21::PolishNotationModel::getPriorityOperation(std::string oper) {
    int result = 0;
    if (oper.size() > 1)
        result = 1;
    else if (oper == "^")
        result = 2;
    else if (oper == "*" || oper == "/" || oper == "%")
        result = 3;
    else if (oper == "+" || oper == "-")
        result = 4;
    else if (oper == "(")
        result = 5;
    return result;
}
bool s21::PolishNotationModel::stringIsNumber(std::string str) {
    bool result = true;
    if ((str[0] == '-' && str.size() > 1) || isdigit(str[0])) {
        for (int i = 1; i < static_cast<int>(str.size()) && result; i++) {
            if (!isdigit(str[i]) && str[i] != '.') result = false;
        }
    } else {
        result = false;
    }
    return result;
}
void s21::PolishNotationModel::funcAction(std::stack<double> &number, const std::string action) {
    double num = number.top();
    number.pop();
    if (action == "sin")
        number.push(sin(num));
    else if (action == "cos")
        number.push(cos(num));
    else if (action == "asin")
        number.push(asin(num));
    else if (action == "acos")
        number.push(acos(num));
    else if (action == "tan")
        number.push(tan(num));
    else if (action == "atan")
        number.push(atan(num));
    else if (action == "log")
        number.push(log10(num));
    else if (action == "ln")
        number.push(log(num));
    else if (action == "sqrt")
        number.push(sqrt(num));
    else if (action == "unary_minus")
        number.push(-num);
    else if (action == "unary_plus")
        number.push(num);
}
void s21::PolishNotationModel::operAction(std::stack<double> &number, const std::string action) {
    double second = number.top();
    number.pop();
    double first = number.top();
    number.pop();
    if (action == "+")
        number.push(first + second);
    else if (action == "-")
        number.push(first - second);
    else if (action == "*")
        number.push(first * second);
    else if (action == "/")
        number.push(first / second);
    else if (action == "%")
        number.push(fmod(first, second));
    else if (action == "^")
        number.push(powl(first, second));
}
void s21::PolishNotationModel::chooseAction(std::stack<double> &number, const std::string action) {
    if (getPriorityOperation(action) > 1) {
        operAction(number, action);
    } else {
        funcAction(number, action);
    }
}
double s21::PolishNotationModel::calculateExpresion(double x) {
    std::stack<double> numbers;
    double result = NAN;
    if (notation.size() != 0) {
        for (auto iter = notation.begin(); iter < notation.end(); iter++) {
            if (stringIsNumber(*iter)) {
                numbers.push(std::stod(*iter));
            } else if (*iter == "x") {
                numbers.push(x);
            } else {
                chooseAction(numbers, *iter);
            }
        }
        result = numbers.top();
        numbers.pop();
    }
    return result;
}
void s21::PolishNotationModel::set_expresion(const std::string expresion) {
    this->expresion = expresion;
    clearData();
    convertExpresion();
}
void s21::PolishNotationModel::clearData() {
    while (operation.size() != 0) operation.pop();
    pars_status = {false, true, true, true, true, false};
    notation.clear();
}
