#include "employeetablemodel.h"

EmployeeTableModel::EmployeeTableModel(QObject *parent)
    : QAbstractTableModel{parent}
{}

int EmployeeTableModel::rowCount(const QModelIndex &) const {
    return this->employees.size();
}

int EmployeeTableModel::columnCount(const QModelIndex &) const {
    return 5;
}

QVariant EmployeeTableModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        int i = index.row();
        switch(index.column()) {
        case 0:
            return this->employees.at(i)->surname;
        case 1:
            return this->employees.at(i)->name;
        case 2:
            return this->employees.at(i)->patronymic;
        case 3:
            return this->employees.at(i)->phone;
        case 4:
            return this->employees.at(i)->role == User::Employee ? "Сотрудник" : "Администратор";
        }
    }
    return QVariant();
}

QVariant EmployeeTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch(section) {
            case 0:
                return "Фамилия";
            case 1:
                return "Имя";
            case 2:
                return "Отчество";
            case 3:
                return "Номер телефона";
            case 4:
                return "Статус";
            }
        }
        if (orientation == Qt::Vertical) {
            return QString::number(section + 1);
        }
    }
    return QVariant();
}

void EmployeeTableModel::addEmployee(const QSharedPointer<User> &employee) {
    this->employees.append(employee);
    emit layoutChanged();
}

void EmployeeTableModel::setEmployeeList(const QVector<QSharedPointer<User>> &employees) {
    this->beginResetModel();
    this->employees = employees;
    this->endResetModel();
}
