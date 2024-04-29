#include "criticaldb.h"

CriticalDB::CriticalDB(const QString& msg) {
    this->msg = msg;
}

QString CriticalDB::what() const {
    return this->msg;
}
