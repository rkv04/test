#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QMainWindow>
#include <QValidator>

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
    void back();

private slots:
    void onCancelButtonClicked();
    void onSaveButtonClicked();
    void onChangePasswordButtonClicked();

private:
    Ui::Account *ui;
    void handleAppError(const AppError &ex);
    bool dataIsValid();
    bool passwordIsValid();
    QSharedPointer<User> client;
    QSharedPointer<QValidator> phone_validator;
};
#endif // ACCOUNT_H
