#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include "authorizationwindow.h"
#include "apperror.h"

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

    void init();

signals:
    void successfulRegistration();
    void back();

public slots:
    void regButtonClicked();
    void toLoginWindow();

private:

    bool validateData();
    void handleAppError(const AppError &ex);

    Ui::RegistrationWindow *ui;
    QSharedPointer<QValidator> phone_validator;
    QSharedPointer<QValidator> text_validator;
};

#endif // REGISTRATIONWINDOW_H
