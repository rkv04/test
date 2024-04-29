#include "authorizationwindow.h"
#include "db.h"
#include "app.h"
#include "criticaldb.h"
#include "log.h"

#include <QApplication>
#include <QMessageBox>


int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    try {
        App *app = App::getInstance();
        app->init();
    }
    catch(const CriticalDB &ex) {
        QMessageBox::critical(nullptr, App::APPLICATION_NAME, CriticalDB::FATAL_MSG);
        Log::write(ex.what());
        exit(-1);
    }

    AuthorizationWindow w;
    w.show();
    return a.exec();

}
