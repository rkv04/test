#ifndef LOG_H
#define LOG_H

#include <QString>

class Log
{
public:
    Log();
    static void write(const QString &msg);
};

#endif // LOG_H
