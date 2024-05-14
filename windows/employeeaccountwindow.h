#ifndef EMPLOYEEACCOUNTWINDOW_H
#define EMPLOYEEACCOUNTWINDOW_H

#include <QMainWindow>

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

    void handleAppError(const AppError &ex);
    QSharedPointer<User> employee;
};

#endif // EMPLOYEEACCOUNTWINDOW_H
