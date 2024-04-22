#ifndef ADDEMPLOYEEWINDOW_H
#define ADDEMPLOYEEWINDOW_H

#include <QDialog>

namespace Ui {
class AddEmployeeWindow;
}

class AddEmployeeWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddEmployeeWindow(QWidget *parent = nullptr);
    ~AddEmployeeWindow();

private:
    Ui::AddEmployeeWindow *ui;
};

#endif // ADDEMPLOYEEWINDOW_H
