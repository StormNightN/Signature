#include <iostream>
#include "Helpers.h"


int main(int argc, char** argv) {
    if(argc < 2) {
        std::cerr << "Error. You should write at least processing and output file path. ";
        return -1;
    }

    const size_t defaultChankSize = 1 * 1024 * 1024;
    size_t blockSize = argc == 3 ? defaultChankSize : std::atol(argv[2]);
    std::string pathToProcessingFile(argv[1]);
    std::string pathToOutputFile(argv[2]);
    Signature::StartInfrastructure(pathToProcessingFile, pathToOutputFile, blockSize);

    return 0;
}