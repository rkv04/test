#ifndef CRITICALDB_H
#define CRITICALDB_H

#include <QString>

class CriticalDB
{
public:
    CriticalDB(const QString& msg);
    inline static const QString FATAL_MSG = "Критическая ошибка! См. log.txt";
    QString what() const;
private:
    QString msg;
};

#endif // CRITICALDB_H
