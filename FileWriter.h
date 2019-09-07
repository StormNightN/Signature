//
// Created by stormnight on 9/5/19.
//

#ifndef SIGNATURE_FILEWRITER_H
#define SIGNATURE_FILEWRITER_H

#include <vector>
#include <memory>
#include <mutex>
#include <condition_variable>
#include "DataChank.h"
#include "WorkQueue.h"

namespace Signature {

    /**
     * Represent object, which write block hashes to output file
     */
    class FileWriter {
    public:
        /**
         * Default constructor
         *
         * @param hashCount     count waited hashes
         * @param path          path to output file
         */
        FileWriter(size_t hashCount, std::string path);

        /**
         * Thread function, which waits and prints hashes to output
         */
        void ProcessHash();

        void PushHashChank(std::unique_ptr<DataChank> pDataChank);

    private:

        /**
         * Print hash to output
         * @param os                        output stream
         * @param rp_ProcessingChank        reference on unique pointer which points on hash chank
         * @param idx                       hash block id
         */
        void PrintToOutput(std::ostream& os, std::unique_ptr<DataChank>& rp_ProcessingChank, size_t idx);

        /// Path to output file
        ///
        std::string m_Path;

        /// Collection, which contains unique pointers on hash data chanks
        ///
        std::vector<std::unique_ptr<DataChank>> m_HashData;

        /// Mutex for m_HashData guarding
        ///
        std::mutex m_WriteMutex;

        /// Push signal
        ///
        std::condition_variable m_Push;
    };
}

#endif //SIGNATURE_FILEWRITER_H
