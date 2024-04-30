#ifndef CITYLISTMODEL_H
#define CITYLISTMODEL_H

#include <QAbstractListModel>

#include "city.h"

class CityListModel : public QAbstractListModel
{
public:
    explicit CityListModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    void setCityList(const QVector<QSharedPointer<City>> &cities);

private:
    QVector<QSharedPointer<City>> cities;
};

#endif // CITYLISTMODEL_H
