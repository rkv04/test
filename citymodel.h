#ifndef CITYMODEL_H
#define CITYMODEL_H

#include <QAbstractTableModel>
#include <QSharedPointer>
#include <QVector>
#include <QStringList>

#include "city.h"

class CityModel : public QAbstractTableModel
{
public:
    explicit CityModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    void setCityList(const QVector<QSharedPointer<City>> &cities);
    void addCity(const QSharedPointer<City> city);

private:
    QVector<QSharedPointer<City>> cities;
    QStringList headers = {"Название", "Описание климата"};
};

#endif // CITYMODEL_H
