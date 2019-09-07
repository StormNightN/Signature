//
// Created by stormnight on 9/7/19.
//

#include "includes/EmptyQueueException.h"

const char* Signature::EmptyQueueException::what() const noexcept {
    return "Queue is empty";
}