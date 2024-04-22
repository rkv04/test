#ifndef USERSLISTWINDOW_H
#define USERSLISTWINDOW_H

#include <QDialog>

namespace Ui {
class UsersListWindow;
}

class UsersListWindow : public QDialog
{
    Q_OBJECT

public:
    explicit UsersListWindow(QWidget *parent = nullptr);
    ~UsersListWindow();

private:
    Ui::UsersListWindow *ui;
};

#endif // USERSLISTWINDOW_H
