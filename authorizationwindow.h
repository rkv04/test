#ifndef AUTHORIZATIONWINDOW_H
#define AUTHORIZATIONWINDOW_H

#include <QMainWindow>
#include <QSharedPointer>

#include "registrationwindow.h"
#include "adminmainwindow.h"
#include "employeemainwindow.h"
#include "clientmainwindow.h"

class RegistrationWindow;
class AuthorizationWindow;

namespace Ui {
class AuthorizationWindow;
}

class AuthorizationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AuthorizationWindow(QWidget *parent = nullptr);
    ~AuthorizationWindow();

private slots:
    void regButtonClicked();
    void loginButtonClicked();

private:
    Ui::AuthorizationWindow *ui;
    RegistrationWindow *reg_window;
    ClientMainWindow *client_main_window;
    EmployeeMainWindow *employee_main_window;
    AdminMainWindow *admin_main_window;
};

#endif // AUTHORIZATIONWINDOW_H
