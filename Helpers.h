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

    /**
     * Calculate file size in bytes
     *
     * @param fileName                  path to file
     * @return                          file size
     * @retval -1                       file was not opened
     * @retval positive                 file size
     */
    long GetFileSize(const std::string &fileName);

}

#endif //SIGNATURE_HELPERS_H
