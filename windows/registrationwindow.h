#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include "authorizationwindow.h"

#include <QMainWindow>
#include <QValidator>

class AuthorizationWindow;

namespace Ui {
class RegistrationWindow;
}

class RegistrationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegistrationWindow(QWidget *parent = nullptr);
    ~RegistrationWindow();

signals:
    void successfulRegistration();


public slots:
    void regButtonClicked();
    void toLoginWindow();

private:
    Ui::RegistrationWindow *ui;
    AuthorizationWindow *author_window;
    QValidator *phone_validator;
    QValidator *text_validator;
};

#endif // REGISTRATIONWINDOW_H
