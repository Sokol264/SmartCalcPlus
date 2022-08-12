#include "s21_tableModel.h"
namespace s21 {
CreditModel::CreditModel(QObject *parent) : QAbstractTableModel(parent), choose(0) {}

void CreditModel::fillData(const QList<QString> &sumLeft, const QList<QString> &montlyPercent,
                           const QList<QString> &montlyPayment, int ch) {
    _sumLeft.clear();
    _sumLeft = sumLeft;
    _montlyPercent.clear();
    _montlyPercent = montlyPercent;
    _montlyPayment.clear();
    _montlyPayment = montlyPayment;
    choose = ch;
    return;
}

int CreditModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return _sumLeft.length();
}

int CreditModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 3;
}

QVariant CreditModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant();
    }
    if (index.column() == 0) {
        return _sumLeft[index.row()];
    } else if (index.column() == 1) {
        return _montlyPercent[index.row()];
    } else if (index.column() == 2) {
        return _montlyPayment[index.row()];
    }
    return QVariant();
}

QVariant CreditModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        if (choose) {
            if (section == 0) {
                return QString("Остаток");
            } else if (section == 1) {
                return QString("Проценты");
            } else if (section == 2) {
                return QString("Платеж");
            }
        } else {
            if (section == 0) {
                return QString("Всего");
            } else if (section == 1) {
                return QString("Начисленно процентов");
            } else if (section == 2) {
                return QString("Вклад пополнен");
            }
        }
    }
    return QVariant();
}
}  // namespace s21
