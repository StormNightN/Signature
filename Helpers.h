//
// Created by stormnight on 9/3/19.
//


#ifndef SIGNATURE_HELPERS_H
#define SIGNATURE_HELPERS_H

#include <string>

namespace Signature {

    /**
     * Calculate total system memory
     *
     * @return      total system memory in bytes
     */
    long GetTotalSystemMemory();

    /**
     * Start program infrastructure
     *
     * @param pathToProcessingFile      path to file, which will be processed
     * @param pathToOutputFile          path to output file
     * @param blockSize                 block size in bytes
     */
    void StartInfrastructure(const std::string& pathToProcessingFile,
                            const std::string& pathToOutputFile,
                            size_t blockSize);

}

#endif //SIGNATURE_HELPERS_H
