//
// Created by stormnight on 9/4/19.
//

#ifndef SIGNATURE_HASHPROCESS_H
#define SIGNATURE_HASHPROCESS_H

#include "WorkQueue.h"

namespace Signature {

    /**
     * Represent Hash process action
     */
    class HashProcess {

    public:

        /**
         * Default constructor
         *
         * @param rWorkQueue reference to work queue
         */
        explicit HashProcess(WorkQueue<DataChank>& rWorkQueue);

        /**
         * Calculate hash for next element from work queue and
         * push it to result queue
         *
         * @return processing result
         * @retval true new chank was processed
         * @retval false work queue is empty
         */
        bool Process();

        /**
         * Destructor
         */
        virtual ~HashProcess() = default;

    private:

        /// Reference to work queue
        ///
        WorkQueue<DataChank>& m_WorkQueue;
    };
}

#endif //SIGNATURE_HASHPROCESS_H
