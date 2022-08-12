#include <QApplication>

#include "s21_controller.h"
#include "s21_model.h"
#include "view.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    s21::CalcModel model;
    s21::Controller ctrl(&model);
    s21::View w(&ctrl);
    w.connectSignals();
    w.show();
    return a.exec();
}
