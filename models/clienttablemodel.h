#ifndef CLIENTTABLEMODEL_H
#define CLIENTTABLEMODEL_H

#include <QAbstractTableModel>
#include <QSharedPointer>
#include <QVector>

#include "user.h"

class ClientTableModel : public QAbstractTableModel
{
public:
    explicit ClientTableModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    int getClientIdByIndexRow(int row);
    void setClientList(const QVector<QSharedPointer<User>> &clients);
    void refreshDiscountByIndex(const int index, const int discount);

private:
    QVector<QSharedPointer<User>> clients;
};

#endif // CLIENTTABLEMODEL_H
