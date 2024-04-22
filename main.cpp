#include "authorizationwindow.h"

#include <QApplication>
#include <QMessageBox>

#include <appdb.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AuthorizationWindow w;
    w.show();
    return a.exec();
}
