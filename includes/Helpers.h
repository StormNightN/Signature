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
     *
     * @return                          processing result
     * @retval 0                        success
     * @retval -1                       unsuccess
     */
    int StartInfrastructure(const std::string& pathToProcessingFile,
                            const std::string& pathToOutputFile,
                            size_t blockSize);

    /**
     * Calculate file size in bytes
     *
     * @param fileName                  path to file
     * @return                          file size
     * @throw std::ifstream::failure    file operation error
     */
    long GetFileSize(const std::string &fileName);

    /**
     * Convert megabytes to bytes
     *
     * @param size                      size to megabytes
     * @return                          size to bytes
     */
    inline size_t ConvertMbytesToBytes(size_t size) {
        return size * 1024 * 1024;
    }

    /**
     * Print to console output
     *
     * @param message                   message
     */
    void PrintMessageToConsole(const std::string &message);

    /**
     * Print error to console output
     *
     * @param message                   message
     */
    void PrintErrorMessageToConsole(const std::string &message);
}

#endif //SIGNATURE_HELPERS_H
