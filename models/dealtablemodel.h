#ifndef DEALTABLEMODEL_H
#define DEALTABLEMODEL_H

#include <QAbstractTableModel>

#include "deal.h"

class DealTableModel : public QAbstractTableModel
{
public:
    explicit DealTableModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    void setDealsList(const QVector<QSharedPointer<Deal>> &deals);
    QSharedPointer<Deal> getDealByIndexRow(const int row);

private:
    QVector<QSharedPointer<Deal>> deals;
};

#endif // DEALTABLEMODEL_H
