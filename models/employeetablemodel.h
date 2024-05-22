#ifndef EMPLOYEETABLEMODEL_H
#define EMPLOYEETABLEMODEL_H

#include <QAbstractTableModel>

#include "user.h"

class EmployeeTableModel : public QAbstractTableModel
{
public:
    explicit EmployeeTableModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    QSharedPointer<User> getEmployeeByIndexRow(const int row);
    void removeEmployeeByIndexRow(const int row);
    void addEmployee(const QSharedPointer<User> &employee);
    void setEmployeeList(const QVector<QSharedPointer<User>> &employees);

private:
    QVector<QSharedPointer<User>> employees;
};

#endif // EMPLOYEETABLEMODEL_H
