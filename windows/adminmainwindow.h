#ifndef ADMINMAINWINDOW_H
#define ADMINMAINWINDOW_H

#include <QMainWindow>

#include "employeelistwindow.h"
#include "userslistwindow.h"

namespace Ui {
class AdminMainWindow;
}

class AdminMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminMainWindow(QWidget *parent = nullptr);
    ~AdminMainWindow();

signals:
    void logout();

private slots:
    void onEmployeeButtonClicked();
    void onUsersButtonClicked();
    void onLogoutButtonClicked();

private:
    Ui::AdminMainWindow *ui;

    QSharedPointer<EmployeeListWindow> employee_list_window;
    QSharedPointer<UsersListWindow> user_list_window;
};

#endif // ADMINMAINWINDOW_H
