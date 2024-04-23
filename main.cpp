#include "authorizationwindow.h"
#include "db.h"
#include "app.h"
#include "criticaldb.h"

#include <QApplication>
#include <QMessageBox>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    try {
        DB::init();
        // App::init();
    }
    catch(const CriticalDB &ex) {
        QMessageBox::critical(nullptr, "Tour operator", ex.what());
        exit(-1);
    }

    AuthorizationWindow w;
    w.show();
    return a.exec();
}
