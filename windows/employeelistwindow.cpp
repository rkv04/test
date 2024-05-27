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
    this->setWindowTitle(App::APPLICATION_NAME);
    connect(this->ui->backButton, SIGNAL(clicked(bool)), this, SLOT(onBackButtonClicked()));
    connect(this->ui->addButton, SIGNAL(clicked(bool)), this, SLOT(onAddButtonClicked()));
    connect(this->ui->deleteButton, SIGNAL(clicked(bool)), this, SLOT(onDeleteButtonClicked()));
    connect(this->ui->findButton, SIGNAL(clicked(bool)), this, SLOT(onFindButtonClicked()));
    connect(this->ui->resetFiltersButton, SIGNAL(clicked(bool)), this, SLOT(onResetFiltersButtonClicked()));
    this->employee_table_model = QSharedPointer<EmployeeTableModel>(new EmployeeTableModel());
}

EmployeeListWindow::~EmployeeListWindow()
{
    delete ui;
}

bool EmployeeListWindow::hasSelection() {
    return this->ui->tableView->selectionModel()->hasSelection();
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

bool EmployeeListWindow::confirmDelete() {
    QMessageBox confirm_box;
    confirm_box.setIcon(QMessageBox::Question);
    confirm_box.setWindowTitle(App::APPLICATION_NAME);
    confirm_box.setText("Удалить выбранное?");
    confirm_box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    return confirm_box.exec() == QMessageBox::Yes;
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
    this->ui->tableView->resizeColumnsToContents();
    QMessageBox::information(this, App::APPLICATION_NAME, "Сотрудник успешно зарегистрирован");
}

void EmployeeListWindow::onDeleteButtonClicked() {
    if (!this->hasSelection()) {
        QMessageBox::warning(this, App::APPLICATION_NAME, "Для удаления необходимо выделить нужные строки");
        return;
    }
    if (!this->confirmDelete()) {
        return;
    }
    QModelIndexList selected_indexes = this->ui->tableView->selectionModel()->selectedRows();
    std::sort(selected_indexes.begin(), selected_indexes.end(), [](const QModelIndex &l, const QModelIndex &r){return l.row() > r.row();});
    App *app = App::getInstance();
    try {
        for (auto i : selected_indexes) {
            QSharedPointer<User> employee = this->employee_table_model->getEmployeeByIndexRow(i.row());
            app->removeEmployee(employee);
            this->employee_table_model->removeEmployeeByIndexRow(i.row());
        }
    }
    catch(const AppError &ex) {
        this->handleAppError(ex);
        return;
    }
}

void EmployeeListWindow::onBackButtonClicked() {
    emit back();
    this->close();
}

void EmployeeListWindow::onFindButtonClicked() {
    QMap<QString, QString> filter = this->createFilter();
    App *app = App::getInstance();
    QVector<QSharedPointer<User>> employees;
    try {
        employees = app->getEmployeeListByFilter(filter);
    }
    catch(const AppError &ex) {
        this->handleAppError(ex);
        return;
    }
    this->employee_table_model->setEmployeeList(employees);
}

QMap<QString, QString> EmployeeListWindow::createFilter() {
    QMap<QString, QString> filter;
    filter["surname"] = this->ui->surnameEdit->text() + "%";
    filter["name"] = this->ui->nameEdit->text() + "%";
    filter["patronymic"] = this->ui->patronymicEdit->text() + "%";
    filter["phone"] = this->ui->phoneEdit->text() + "%";
    return filter;
}

void EmployeeListWindow::onResetFiltersButtonClicked() {
    this->ui->surnameEdit->clear();
    this->ui->nameEdit->clear();
    this->ui->patronymicEdit->clear();
    this->ui->phoneEdit->clear();
    App *app = App::getInstance();
    QVector<QSharedPointer<User>> employees;
    try {
        employees = app->getEmployeeList();
    }
    catch(const AppError &ex) {
        this->handleAppError(ex);
        return;
    }
    this->employee_table_model->setEmployeeList(employees);
}
