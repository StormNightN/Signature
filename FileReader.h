//
// Created by stormnight on 9/4/19.
//

#ifndef SIGNATURE_FILEREADER_H
#define SIGNATURE_FILEREADER_H

#include <string>


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
         * @param blockSize         block size, which will be pushed to queue
         */
        explicit FileReader(std::string path, size_t blockSize = 1);

        /**
         * Reades blocks and pushes to queue
         */
        void Read() const;
    private:

        std::string m_Path;

        size_t m_BlockSize;
    };
}

#endif //SIGNATURE_FILEREADER_H
