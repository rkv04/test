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

private slots:
    void onBackButtonClicked();
    void onAddButtonClicked();
    void onDeleteButtonClicked();
    void onFindButtonClicked();
    void onResetFiltersButtonClicked();

signals:
    void back();

private:
    Ui::EmployeeListWindow *ui;

    void initModels();
    void initUi();
    bool hasSelection();
    bool confirmDelete();
    void handleAppError(const AppError &ex);
    QMap<QString, QString> createFilter();
    QSharedPointer<EmployeeTableModel> employee_table_model;
};

#endif // EMPLOYEELISTWINDOW_H
