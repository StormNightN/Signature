//
// Created by stormnight on 9/7/19.
//

#ifndef SIGNATURE_EMPTYQUEUE_H
#define SIGNATURE_EMPTYQUEUE_H

#include <exception>

namespace Signature {

    /**
     * Exception, which throws when Queue is empty
     */
    class EmptyQueueException : public std::exception {

    public:

        /**
         * @return      Exception describe
         */
        const char* what() const noexcept override;
    };
}

#endif //SIGNATURE_EMPTYQUEUE_H
