#ifndef EMPLOYEEDELETEWINDOW_H
#define EMPLOYEEDELETEWINDOW_H

#include <QDialog>

namespace Ui {
class EmployeeDeleteWindow;
}

class EmployeeDeleteWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EmployeeDeleteWindow(QWidget *parent = nullptr);
    ~EmployeeDeleteWindow();

private:
    Ui::EmployeeDeleteWindow *ui;
};

#endif // EMPLOYEEDELETEWINDOW_H
