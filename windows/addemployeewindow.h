#ifndef ADDEMPLOYEEWINDOW_H
#define ADDEMPLOYEEWINDOW_H

#include <QDialog>

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

    QSharedPointer<User> created_employee;
};

#endif // ADDEMPLOYEEWINDOW_H
