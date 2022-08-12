#ifndef SRC_SMARTCALC2_0_VIEW_H_
#define SRC_SMARTCALC2_0_VIEW_H_

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMainWindow>

#include "s21_controller.h"
#include "s21_tableModel.h"

enum detailStatus { SHOW, HIDE };

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE
namespace s21 {
class View : public QMainWindow {
    Q_OBJECT
    s21::Controller *ctrl;

 public:
    explicit View(s21::Controller *ctrl, QWidget *parent = nullptr);
    ~View();
    void connectSignals();

 private slots:
    void editButtonClicked();
    void calculateResult();
    void drawButtonClicked();
    void creditCalcButtonClicked();
    void detailButtonClicked();
    void checkX();
    void deposButtonClicked();
    void addDepositEvent();
    void cleanButtonClicked();
    void backspaceButtonClicked();

 private:
    void parsingDate(QDate &, QDate &, s21::payment_period);
    void fillVectorEvents(std::vector<std::pair<int, double>> &vectorEv);
    void fillModel(s21::dp_t, std::vector<std::pair<int, double>> &, bool, double);
    void drawNet(double x_max, double y_max);
    detailStatus stat = HIDE;
    Ui::View *ui;
    QGraphicsScene *scene;
    std::multimap<QDate, long double> events;
};
}  // namespace s21
#endif  // SRC_SMARTCALC2_0_VIEW_H_
