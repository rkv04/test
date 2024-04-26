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
    QVector<QSharedPointer<City>> getCityList();
private:
    QSharedPointer<City> createCityByRow(const QSqlRecord &record);
    QVector<QSharedPointer<City>> getCityListByQuery(QSqlQuery &query);
};

#endif // CITYSERVICE_H
