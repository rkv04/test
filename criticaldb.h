#ifndef CRITICALDB_H
#define CRITICALDB_H

#include <QString>

class CriticalDB
{
public:
    CriticalDB(const QString& msg);
    QString what() const;
private:
    QString msg;
};

#endif // CRITICALDB_H
