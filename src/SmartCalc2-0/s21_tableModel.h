#ifndef SRC_SMARTCALC2_0_S21_TABLEMODEL_H_
#define SRC_SMARTCALC2_0_S21_TABLEMODEL_H_

#include <QAbstractTableModel>

namespace s21 {
class CreditModel : public QAbstractTableModel {
    Q_OBJECT

 public:
    explicit CreditModel(QObject *parent = 0);

    void fillData(const QList<QString> &sumLeft, const QList<QString> &montlyPercent,
                  const QList<QString> &montlyPayment, int);

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

 private:
    QList<QString> _sumLeft;
    QList<QString> _montlyPercent;
    QList<QString> _montlyPayment;
    int choose;
};
}  // namespace s21
#endif  // SRC_SMARTCALC2_0_S21_TABLEMODEL_H_
