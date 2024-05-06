#ifndef HOTELCATEGORYLISTMODEL_H
#define HOTELCATEGORYLISTMODEL_H

#include <QAbstractListModel>

class HotelCategoryListModel : public QAbstractListModel
{
public:
    explicit HotelCategoryListModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    int getCategoryByIndex(const int index);
private:
    struct Category {
        QString title;
        int value;
        Category(const QString &t, const int v) : title(t), value(v){}
    };

    QVector<Category> categories;
};

#endif // HOTELCATEGORYLISTMODEL_H
