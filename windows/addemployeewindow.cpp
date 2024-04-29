#include "addemployeewindow.h"
#include "ui_addemployeewindow.h"

AddEmployeeWindow::AddEmployeeWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddEmployeeWindow)
{
    ui->setupUi(this);
}

AddEmployeeWindow::~AddEmployeeWindow()
{
    delete ui;
}
