#ifndef HOTELMODEL_H
#define HOTELMODEL_H

#include <QAbstractTableModel>
#include <QSharedPointer>
#include <QStringList>

#include "hotel.h"
#include "city.h"

class HotelModel : public QAbstractTableModel
{
public:
    explicit HotelModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    void setHotelsList(const QVector<QSharedPointer<Hotel>> &hotels);
    void addHotel(const QSharedPointer<Hotel> &hotel);
    QVector<QSharedPointer<City>> getHotelCities();

private:
    QVector<QSharedPointer<Hotel>> hotels;
    const QStringList headers = {"Название", "Категория", "Город", "Адрес"};

};

#endif // HOTELMODEL_H
