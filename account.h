#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QMainWindow>

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

private:
    Ui::Account *ui;
};
#endif // ACCOUNT_H
