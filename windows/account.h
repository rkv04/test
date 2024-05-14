#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QMainWindow>

#include "user.h"
#include "apperror.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Account;
}
QT_END_NAMESPACE

class Account : public QMainWindow
{
    Q_OBJECT

public:
    Account(QWidget *parent = nullptr);
    ~Account();

    void init();

signals:
    void closed();

private slots:
    void onCancelButtonClicked();
    void onSaveButtonClicked();
    void onChangePasswordButtonClicked();

private:
    Ui::Account *ui;

    void handleAppError(const AppError &ex);

    QSharedPointer<User> client;
};
#endif // ACCOUNT_H
