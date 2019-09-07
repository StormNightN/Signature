//
// Created by stormnight on 9/4/19.
//

#ifndef SIGNATURE_FILEREADER_H
#define SIGNATURE_FILEREADER_H

#include <string>
#include "WorkQueue.h"

namespace Signature {

    /**
     * Represent object, which will read file and push DataChunks to WorkQueue
     */
    class FileReader {

    public:

        /**
         * Default constructor
         *
         * @param path              path to file
         * @param rWorkQueue        reference to work queue
         * @param blockSize         block size, which will be pushed to queue
         */
        FileReader(std::string path, WorkQueue<DataChank>& rWorkQueue, size_t blockSize);

        /**
         * Reades blocks and pushes to queue
         */
        void Read() const;

        /**
         * Destructor
         */
        virtual ~FileReader() = default;

    private:

        /// Path to processed file
        ///
        std::string m_Path;

        /// Block size for processing
        ///
        size_t m_BlockSize;

        /// Reference to queue, which will contains tasks for processing
        ///
        WorkQueue<DataChank>& m_WorkQueue;
    };
}

#endif //SIGNATURE_FILEREADER_H
