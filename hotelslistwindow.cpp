#include "hotelslistwindow.h"
#include "ui_hotelslistwindow.h"

HotelsListWindow::HotelsListWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HotelsListWindow)
{
    ui->setupUi(this);
}

HotelsListWindow::~HotelsListWindow()
{
    delete ui;
}
