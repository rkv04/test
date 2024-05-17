#ifndef EMPLOYEELISTWINDOW_H
#define EMPLOYEELISTWINDOW_H

#include <QMainWindow>

#include "employeetablemodel.h"
#include "apperror.h"

namespace Ui {
class EmployeeListWindow;
}

class EmployeeListWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EmployeeListWindow(QWidget *parent = nullptr);
    ~EmployeeListWindow();

    void init();
    void initModels();
    void initUi();

private slots:
    void onBackButtonClicked();
    void onAddButtonClicked();
    void onDeleteButtonClicked();

signals:
    void back();

private:
    Ui::EmployeeListWindow *ui;

    void handleAppError(const AppError &ex);
    QSharedPointer<EmployeeTableModel> employee_table_model;
};

#endif // EMPLOYEELISTWINDOW_H
