//
// Created by victor on 17/05/2023.
//

#include "Errors.h"

const char *RepositoryError::what() const noexcept {
        return message.c_str();
}

const char *ValidatorError::what() const noexcept {
    return message.c_str();
}
