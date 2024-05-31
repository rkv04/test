#ifndef ADDEMPLOYEEWINDOW_H
#define ADDEMPLOYEEWINDOW_H

#include <QDialog>
#include <QValidator>

#include "user.h"

namespace Ui {
class AddEmployeeWindow;
}

class AddEmployeeWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddEmployeeWindow(QWidget *parent = nullptr);
    ~AddEmployeeWindow();
    QSharedPointer<User> getCreatedEmployee();

private slots:
    void onRegistrationButtonClicked();

private:
    Ui::AddEmployeeWindow *ui;

    bool validateData();
    QSharedPointer<User> created_employee;

    QSharedPointer<QValidator> phone_validator;
};

#endif // ADDEMPLOYEEWINDOW_H
