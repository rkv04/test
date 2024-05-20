#ifndef AUTHORIZATIONWINDOW_H
#define AUTHORIZATIONWINDOW_H

#include <QMainWindow>
#include <QSharedPointer>
#include <QRegularExpressionValidator>

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
    void clearAndShow();

private:
    Ui::AuthorizationWindow *ui;

    bool validateData();

    QSharedPointer<RegistrationWindow> registration_window;
    QSharedPointer<ClientMainWindow> client_main_window;
    QSharedPointer<EmployeeMainWindow> employee_main_window;
    QSharedPointer<AdminMainWindow> admin_main_window;

    QSharedPointer<QValidator> phone_validator;
};

#endif // AUTHORIZATIONWINDOW_H
