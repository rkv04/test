#include "apperror.h"

AppError::AppError(const QString &msg, const bool fatality) {
    this->msg = msg;
    this->fatality = fatality;
}

QString AppError::what() const {
    return this->msg;
}

bool AppError::isFatal() const {
    return this->fatality;
}
