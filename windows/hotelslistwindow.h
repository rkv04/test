#ifndef HOTELSLISTWINDOW_H
#define HOTELSLISTWINDOW_H

#include <QMainWindow>

namespace Ui {
class HotelsListWindow;
}

class HotelsListWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit HotelsListWindow(QWidget *parent = nullptr);
    ~HotelsListWindow();

private:
    Ui::HotelsListWindow *ui;
};

#endif // HOTELSLISTWINDOW_H
