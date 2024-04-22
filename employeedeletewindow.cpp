#include "employeedeletewindow.h"
#include "ui_employeedeletewindow.h"

EmployeeDeleteWindow::EmployeeDeleteWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EmployeeDeleteWindow)
{
    ui->setupUi(this);
}

EmployeeDeleteWindow::~EmployeeDeleteWindow()
{
    delete ui;
}
