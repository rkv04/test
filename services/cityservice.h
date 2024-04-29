#ifndef CITYSERVICE_H
#define CITYSERVICE_H

#include <QSharedPointer>
#include <QVector>
#include <QSqlQuery>

#include "city.h"

class CityService
{
public:
    CityService();
    int addCity(const QSharedPointer<City> city);
    void removeCityById(const int id);
    void updateCity(const QSharedPointer<City> city);
    QVector<QSharedPointer<City>> getCityList();
private:
    QSharedPointer<City> createCityByRow(const QSqlRecord &record);
    QVector<QSharedPointer<City>> getCityListByQuery(QSqlQuery &query);
    int getIdLastAddedCity();
};

#endif // CITYSERVICE_H
