#ifndef EMPLOYEEACCOUNTWINDOW_H
#define EMPLOYEEACCOUNTWINDOW_H

#include <QMainWindow>
#include <QValidator>

#include "user.h"
#include "apperror.h"

namespace Ui {
class EmployeeAccountWindow;
}

class EmployeeAccountWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EmployeeAccountWindow(QWidget *parent = nullptr);
    ~EmployeeAccountWindow();

    void init();

signals:
    void closed();

private slots:
    void onChangePasswordButtonClicked();
    void onSaveButtonClicked();
    void onCancelButtonClicked();

private:
    Ui::EmployeeAccountWindow *ui;
    bool dataIsValid();
    bool passwordIsValid();
    void handleAppError(const AppError &ex);
    QSharedPointer<QValidator> phone_validator;
    QSharedPointer<User> employee;
};

#endif // EMPLOYEEACCOUNTWINDOW_H
