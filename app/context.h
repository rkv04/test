#ifndef CONTEXT_H
#define CONTEXT_H

#include <QSharedPointer>

#include "user.h"

class Context
{
public:
    Context();

    static QSharedPointer<User> getContext();
    static void setContext(const QSharedPointer<User> &user);

private:
    static QSharedPointer<User> current_user;
};

#endif // CONTEXT_H
