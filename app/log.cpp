#include "log.h"

#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QDir>


Log::Log() {}

void Log::write(const QString &msg) {
    QDir dir("log");
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    QFile file("./log/log.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
    QTextStream ost(&file);
    ost << Qt::endl << QDateTime::currentDateTime().toString("hh:mm:ss dd.MM.yyyy") << Qt::endl << msg << Qt::endl;
    file.close();
}
