#include "context.h"

QSharedPointer<User> Context::current_user = nullptr;

Context::Context() {}

void Context::setContext(const QSharedPointer<User> &user) {
    current_user = user;
}

QSharedPointer<User> Context::getContext() {
    return current_user;
}
