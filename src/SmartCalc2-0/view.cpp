#include "view.h"

#include <iostream>

#include "ui_view.h"

namespace s21 {
View::View(s21::Controller *ctrl, QWidget *parent) : QMainWindow(parent), ctrl(ctrl), ui(new Ui::View) {
    ui->setupUi(this);
    ui->doubleSpinBox_x->hide();
    scene = new QGraphicsScene(this);
    setFixedSize(this->width() - 533, this->height());
    QPen penGray(Qt::gray);
    scene->setSceneRect(0, 0, ui->graphicsView->width() - 10, ui->graphicsView->height() - 10);
    scene->addLine(0, scene->height() / 2, scene->width(), scene->height() / 2, penGray);
    scene->addLine(scene->width() / 2, 0, scene->width() / 2, scene->height(), penGray);
    ui->graphicsView->setScene(scene);
}

void View::connectSignals() {
    for (int i = 0; i < ui->gridLayout->count(); i++) {
        QPushButton *button = qobject_cast<QPushButton *>(ui->gridLayout->itemAt(i)->widget());
        if (button->text() == "=") {
            connect(button, SIGNAL(clicked()), this, SLOT(calculateResult()));
        } else if (button->text() == "График") {
            connect(button, SIGNAL(clicked()), this, SLOT(drawButtonClicked()));
        } else if (button->text() == "AC") {
            connect(button, SIGNAL(clicked()), this, SLOT(cleanButtonClicked()));
        } else if (button->text() == "<") {
            connect(button, SIGNAL(clicked()), this, SLOT(backspaceButtonClicked()));
        } else {
            connect(button, SIGNAL(clicked()), this, SLOT(editButtonClicked()));
        }
    }
    connect(ui->pushButton_calc_credit, SIGNAL(clicked()), this, SLOT(creditCalcButtonClicked()));
    connect(ui->pushButton_depos_res, SIGNAL(clicked()), this, SLOT(deposButtonClicked()));
    connect(ui->pushButton_detail, SIGNAL(clicked()), this, SLOT(detailButtonClicked()));
    connect(ui->pushButton_detail_2, SIGNAL(clicked()), this, SLOT(detailButtonClicked()));
    connect(ui->pushButton_detail_3, SIGNAL(clicked()), this, SLOT(detailButtonClicked()));
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(checkX()));
    connect(ui->pushButton_plus_dep, SIGNAL(clicked()), this, SLOT(addDepositEvent()));
    connect(ui->pushButton_minus_dep, SIGNAL(clicked()), this, SLOT(addDepositEvent()));
}

void View::cleanButtonClicked() { ui->lineEdit->clear(); }

void View::backspaceButtonClicked() { ui->lineEdit->backspace(); }

void View::addDepositEvent() {
    QPushButton *buttonSender = qobject_cast<QPushButton *>(sender());
    double number = ui->doubleSpinBox_3->value();
    QDate date = ui->dateEdit_3->date();
    if (buttonSender->text() == "+") {
        events.insert({date, number});
    } else {
        events.insert({date, -number});
    }
}

void View::checkX() {
    if (ui->lineEdit->text().contains("x")) {
        ui->doubleSpinBox_x->show();
    } else {
        ui->doubleSpinBox_x->hide();
    }
}

void View::detailButtonClicked() {
    if (stat == HIDE) {
        setFixedSize(this->width() + 533, this->height());
        stat = SHOW;
    } else {
        setFixedSize(this->width() - 533, this->height());
        stat = HIDE;
    }
}

void View::parsingDate(QDate &firstDate, QDate &lastDate, s21::payment_period period) {
    while (firstDate <= lastDate) {
        events.insert({firstDate, 0});
        switch (period) {
            case s21::DAY:
                firstDate = firstDate.addDays(1);
                break;
            case s21::WEEK:
                firstDate = firstDate.addDays(7);
                break;
            case s21::MONTH:
                firstDate = firstDate.addMonths(1);
                break;
            case s21::QUARTER:
                firstDate = firstDate.addMonths(3);
                break;
            case s21::HALF_YEAR:
                firstDate = firstDate.addMonths(6);
                break;
            case s21::YEAR:
                firstDate = firstDate.addYears(1);
                break;
            default:
                break;
        }
    }
    if (firstDate != lastDate) events.insert({lastDate, 0});
}

void View::fillVectorEvents(std::vector<std::pair<int, double>> &vectorEv) {
    for (auto i = events.begin(); i != prev(events.end()); i++) {
        QDate curr = i->first;
        i++;
        int daysCount = curr.daysTo(i->first);
        i--;
        vectorEv.push_back({daysCount, i->second});
    }
}

void View::fillModel(s21::dp_t dep, std::vector<std::pair<int, double>> &vectorEv, bool cap, double sum) {
    QList<QString> _sumLeft;
    QList<QString> _montlyPercent;
    QList<QString> _montlyPayment;

    for (int i = 0; i < static_cast<int>(dep.payments.size()); i++) {
        if (vectorEv[i].second != 0) {
            _montlyPercent.push_back("0");
            _montlyPayment.push_back(QString::number(vectorEv[i].second));
            _sumLeft.push_back(QString::number(sum + vectorEv[i].second));
        }
        _montlyPercent.push_back(QString::number(dep.payments[i]));
        if (cap) {
            sum += dep.payments[i];
            _montlyPayment.push_back(QString::number(dep.payments[i]));
        } else {
            _montlyPayment.push_back("0");
        }
        sum += vectorEv[i].second;
        _sumLeft.push_back(QString::number(sum));
    }

    CreditModel *crModel = new CreditModel(this);
    crModel->fillData(_sumLeft, _montlyPercent, _montlyPayment, 0);
    ui->tableView_2->setModel(crModel);
}

void View::deposButtonClicked() {
    double sum = ui->doubleSpinBox_sum_dep->value();
    double perc = ui->doubleSpinBox_perc_dep->value();
    double tax = ui->doubleSpinBox_tax_dep->value();
    s21::payment_period period = static_cast<s21::payment_period>(ui->comboBox->currentIndex());
    bool cap = ui->checkBox->isChecked();
    auto firstDate = ui->dateEdit->date();
    auto lastDate = ui->dateEdit_2->date();
    for (auto &i : events) {
        if (i.first < firstDate || i.first > lastDate) {
            events.clear();
            return;
        }
    }
    parsingDate(firstDate, lastDate, period);

    std::vector<std::pair<int, double>> vectorEv;
    fillVectorEvents(vectorEv);
    auto dep = ctrl->calcDepos(sum, perc, tax, period, cap, vectorEv);
    fillModel(dep, vectorEv, cap, sum);
    ui->tableView_2->horizontalHeader()->setVisible(true);
    ui->tableView_2->setColumnWidth(0, 500 / 3);
    ui->tableView_2->setColumnWidth(1, 500 / 3);
    ui->tableView_2->setColumnWidth(2, 500 / 3);

    ui->label_stack_percent->setText(QString::number(dep.stackPercent));
    ui->label_total_sum->setText(QString::number(dep.totalSum));
    events.clear();
}

void View::creditCalcButtonClicked() {
    double creditSum = ui->doubleSpinBox_sum_cred->value();
    double percent = ui->doubleSpinBox_perc_cred->value();
    int deadline = ui->spinBox_month_cred->value();
    auto credit_type = ui->radioButton_annuity->isChecked() ? s21::ANNUITY : s21::DIFFERENTIATED;
    auto result = ctrl->calcCred(creditSum, deadline, percent, credit_type);
    ui->label_monthly_payment->setText(QString::number(result.monthlyPayment));
    ui->label_overpayment->setText(QString::number(result.overpayment));
    ui->label_total_payment->setText(QString::number(result.totalPayment));

    QList<QString> sumLeft;
    QList<QString> montlyPercent;
    QList<QString> montlyPayment;

    double tempSum = result.creditSum;
    for (int i = 0; i < result.monthCount; i++) {
        tempSum -= (result.payment[i] - result.percentPayment[i]);
        sumLeft.append(QString::number(tempSum));
        montlyPayment.append(QString::number(result.payment[i]));
        montlyPercent.append(QString::number(result.percentPayment[i]));
    }
    CreditModel *crModel = new CreditModel(this);
    crModel->fillData(sumLeft, montlyPercent, montlyPayment, 1);
    ui->tableView->setModel(crModel);

    ui->tableView->horizontalHeader()->setVisible(true);
    ui->tableView->setColumnWidth(0, 500 / 3);
    ui->tableView->setColumnWidth(1, 500 / 3);
    ui->tableView->setColumnWidth(2, 500 / 3);
}

void View::drawNet(double x_max, double y_max) {
    QPen penLightGray(Qt::lightGray);
    QPen penGray(Qt::gray);

    double heightStep = scene->height() / 6;
    double widthStep = scene->width() / 6;
    int step = -3;
    for (int i = 0; i <= 6; i++) {
        scene->addLine(0, heightStep * i, scene->width(), heightStep * i, penLightGray);
        scene->addLine(widthStep * i, 0, widthStep * i, scene->height(), penLightGray);
        scene->addText(QString::number((x_max / 6) * step, 'g', 2))
            ->setPos(widthStep * i, scene->height() / 2);
        scene->addText(QString::number((y_max / 6) * step, 'g', 2))
            ->setPos(scene->width() / 2, heightStep * (6 - i));
        step++;
    }
    scene->addLine(0, scene->height() / 2, scene->width(), scene->height() / 2, penGray);
    scene->addText("Y")->setPos(scene->width() / 2 - 18, 0);
    scene->addText("X")->setPos(scene->width() - 18, scene->height() / 2);
    scene->addLine(scene->width() / 2, 0, scene->width() / 2, scene->height(), penGray);
}

void View::drawButtonClicked() {
    QPen pen(Qt::red);
    scene->clear();
    double x_max = 2 * ui->spinBox->value();
    double y_max = 2 * ui->spinBox_2->value();
    drawNet(x_max, y_max);

    std::string str = ui->lineEdit->displayText().toStdString();
    std::vector<std::pair<double, double>> coord = ctrl->getCoordinates(str, x_max);
    for (int i = 1; i < 10000; i++) {
        double x_prev, y_prev, x_curr, y_curr;
        x_prev = coord[i - 1].first * scene->width() / x_max + scene->width() / 2;
        y_prev = -coord[i - 1].second * scene->height() / y_max + scene->height() / 2;
        x_curr = coord[i].first * scene->width() / x_max + scene->width() / 2;
        y_curr = -coord[i].second * scene->height() / y_max + scene->height() / 2;
        scene->addLine(x_prev, y_prev, x_curr, y_curr, pen);
    }
    if (stat == HIDE) {
        setFixedSize(this->width() + 533, this->height());
        stat = SHOW;
    }
}

void View::editButtonClicked() {
    QString expresion = ui->lineEdit->displayText();
    QPushButton *buttonSender = qobject_cast<QPushButton *>(sender());
    expresion += buttonSender->text();
    ui->lineEdit->setText(expresion);
}

void View::calculateResult() {
    std::string str = ui->lineEdit->displayText().toStdString();
    double x = ui->doubleSpinBox_x->value();
    QString result(ctrl->calc(str, x).c_str());
    ui->lineEdit->setText(result);
}

View::~View() { delete ui; }
}  // namespace s21
