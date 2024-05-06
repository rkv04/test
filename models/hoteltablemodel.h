#ifndef HOTELTABLEMODEL_H
#define HOTELTABLEMODEL_H

#include <QAbstractTableModel>
#include <QSharedPointer>
#include <QStringList>

#include "hotel.h"
#include "city.h"

class HotelTableModel : public QAbstractTableModel
{
public:
    explicit HotelTableModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    void setHotelsList(const QVector<QSharedPointer<Hotel>> &hotels);
    void addHotel(const QSharedPointer<Hotel> &hotel);
    void removeHotelByIndexRow(const int row);
    void updateHotelByIndexRow(const int row, const QSharedPointer<Hotel> &updated_hotel);
    QVector<QSharedPointer<City>> getHotelCities();
    QSharedPointer<Hotel> getHotelByIndexRow(const int row);

private:
    QVector<QSharedPointer<Hotel>> hotels;
    const QStringList headers = {"Название", "Категория", "Город", "Адрес"};

};

#endif // HOTELTABLEMODEL_H
