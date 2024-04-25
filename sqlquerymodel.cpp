#include "sqlquerymodel.h"

SqlQueryModel::SqlQueryModel(QObject *parent)
    : QSqlQueryModel{parent}
{

}

QVariant SqlQueryModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }
    if (role == Qt::DisplayRole) {
        return QSqlQueryModel::data(this->index(index.row(), index.column() + 1), role);
    }
    if (role == Qt::UserRole) {
        return QSqlQueryModel::data(index, Qt::DisplayRole);
    }
    return QVariant();
}

QVariant SqlQueryModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return QSqlQueryModel::headerData(section + 1, orientation, role);
    }
    return QVariant();
}

int SqlQueryModel::columnCount(const QModelIndex &) const {
    return QSqlQueryModel::columnCount() - 1;
}
