#ifndef CITYTABLEMODEL_H
#define CITYTABLEMODEL_H

#include <QAbstractTableModel>
#include <QSharedPointer>
#include <QVector>
#include <QStringList>

#include "city.h"

class CityTableModel : public QAbstractTableModel
{
public:
    explicit CityTableModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    void setCityList(const QVector<QSharedPointer<City>> &cities);
    void addCity(const QSharedPointer<City> city);
    void removeCityByIndexRow(const int row);
    void updateCityByIndexRow(const int row, const QSharedPointer<City> updated_city);
    QSharedPointer<City> getCityByIndexRow(const int row);

private:
    QVector<QSharedPointer<City>> cities;
    QStringList headers = {"Название", "Описание климата"};
};

#endif // CITYTABLEMODEL_H
