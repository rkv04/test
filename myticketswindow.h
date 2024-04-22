#ifndef MYTICKETSWINDOW_H
#define MYTICKETSWINDOW_H

#include <QDialog>

namespace Ui {
class MyTicketsWindow;
}

class MyTicketsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MyTicketsWindow(QWidget *parent = nullptr);
    ~MyTicketsWindow();

private:
    Ui::MyTicketsWindow *ui;
};

#endif // MYTICKETSWINDOW_H
