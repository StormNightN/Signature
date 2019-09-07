//
// Created by stormnight on 9/4/19.
//

#ifndef SIGNATURE_HASHPROCESS_H
#define SIGNATURE_HASHPROCESS_H

#include "WorkQueue.h"
#include "FileWriter.h"

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
         * @param rFileWriter reference to file writer
         */
        HashProcess(WorkQueue<DataChank>& rWorkQueue, FileWriter& rFileWriter);

        /**
         * Calculate hash for next element from work queue and
         * push it to result queue
         *
         * @return processing result
         * @retval true new chank was processed
         * @retval false work queue is empty
         */
        void Process();

        /**
         * Destructor
         */
        virtual ~HashProcess() = default;

    private:

        /// Reference to work queue
        ///
        WorkQueue<DataChank>& m_WorkQueue;

        /// Reference to hash consumer
        ///
        FileWriter& m_FileWriter;
    };
}

#endif //SIGNATURE_HASHPROCESS_H
