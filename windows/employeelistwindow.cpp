#include "employeelistwindow.h"
#include "ui_employeelistwindow.h"

#include <QMessageBox>

#include "app.h"
#include "apperror.h"
#include "addemployeewindow.h"

EmployeeListWindow::EmployeeListWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EmployeeListWindow)
{
    ui->setupUi(this);
    connect(this->ui->backButton, SIGNAL(clicked(bool)), this, SLOT(onBackButtonClicked()));
    connect(this->ui->addButton, SIGNAL(clicked(bool)), this, SLOT(onAddButtonClicked()));
    this->employee_table_model = QSharedPointer<EmployeeTableModel>(new EmployeeTableModel());
}

EmployeeListWindow::~EmployeeListWindow()
{
    delete ui;
}

void EmployeeListWindow::handleAppError(const AppError &ex) {
    if (ex.isFatal()) {
        QMessageBox::critical(this, App::APPLICATION_NAME, ex.what());
        exit(-1);
    }
    QMessageBox::warning(this, App::APPLICATION_NAME, ex.what());
}

void EmployeeListWindow::init() {
    this->initModels();
    this->initUi();
}

void EmployeeListWindow::initModels() {
    QVector<QSharedPointer<User>> employees;
    App *app = App::getInstance();
    try {
        employees = app->getEmployeeList();
    }
    catch(const AppError &ex) {
        this->handleAppError(ex);
        return;
    }
    this->employee_table_model->setEmployeeList(employees);
}

void EmployeeListWindow::initUi() {
    this->ui->tableView->setModel(this->employee_table_model.get());
    this->ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->ui->tableView->resizeColumnsToContents();
    this->ui->tableView->verticalHeader()->stretchLastSection();
}

void EmployeeListWindow::onAddButtonClicked() {
    AddEmployeeWindow add_employee_window;
    add_employee_window.setModal(true);
    if (add_employee_window.exec() != QDialog::Accepted) {
        return;
    }
    auto employee = add_employee_window.getCreatedEmployee();
    App *app = App::getInstance();
    try {
        employee->id = app->createEmployee(employee);
    }
    catch(const AppError &ex) {
        this->handleAppError(ex);
        return;
    }
    this->employee_table_model->addEmployee(employee);
    QMessageBox::information(this, App::APPLICATION_NAME, "Сотрудник успешно зарегистрирован");
}

void EmployeeListWindow::onDeleteButtonClicked() {

}

void EmployeeListWindow::onBackButtonClicked() {
    emit back();
    this->close();
}
