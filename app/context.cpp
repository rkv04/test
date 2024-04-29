#include "context.h"

int Context::current_user_id = 0;

Context::Context() {}

void Context::setContext(const int id_user) {
    current_user_id = id_user;
}

int Context::getContext() {
    return current_user_id;
}
