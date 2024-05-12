#ifndef CITYLISTMODEL_H
#define CITYLISTMODEL_H

#include <QAbstractListModel>

#include "city.h"

class CityListModel : public QAbstractListModel
{
public:

    enum Roles {
        CityPtrRole = Qt::UserRole,
        CityIdRole = Qt::UserRole + 1
    };

    explicit CityListModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    void setCityList(const QVector<QSharedPointer<City>> &cities);
    QSharedPointer<City> getCityByIndex(const int id);

private:
    QVector<QSharedPointer<City>> cities;
};

#endif // CITYLISTMODEL_H
