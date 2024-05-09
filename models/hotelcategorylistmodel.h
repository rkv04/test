#ifndef HOTELCATEGORYLISTMODEL_H
#define HOTELCATEGORYLISTMODEL_H

#include <QAbstractListModel>

class HotelCategoryListModel : public QAbstractListModel
{
public:
    explicit HotelCategoryListModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    QString getCategoryByIndex(const int index);
private:
    struct Category {
        QString title;
        QString value;
        Category(const QString &t, QString v) : title(t), value(v){}
    };

    QVector<Category> categories;
};

#endif // HOTELCATEGORYLISTMODEL_H
