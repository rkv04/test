#ifndef APPERROR_H
#define APPERROR_H

#include <QString>
class AppError
{
public:
    AppError(const QString &msg, const bool isFatal);
    QString what() const;
    bool isFatal() const;
private:
    QString msg;
    bool fatality;
};

#endif // APPERROR_H
