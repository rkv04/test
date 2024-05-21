#ifndef TICKETDURATIONLISTMODEL_H
#define TICKETDURATIONLISTMODEL_H

#include <QAbstractListModel>
#include <QVector>

class TicketDurationListModel : public QAbstractListModel
{
public:
    enum Roles {
        DurationRole = Qt::UserRole
    };
    explicit TicketDurationListModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

private:
    struct Duration {
        Duration(const QString &t, int v) : title(t), value(v){}
        QString title;
        int value;
    };
    QVector<Duration> duration;
};

#endif // TICKETDURATIONLISTMODEL_H
