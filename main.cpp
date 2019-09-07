#include <iostream>
#include <sstream>
#include "Helpers.h"

int main(int argc, char** argv) {
    if(argc < 2) {
        Signature::PrintErrorMessageToConsole("Error. You should write at least processing and output file path.");
        return -1;
    }

    const size_t defaultChankSize = 1;
    size_t blockSize = defaultChankSize;
    if (argc == 4) {
        std::istringstream is(argv[3]);
        is >> blockSize;

        if(is.fail()) { // conversion fails
            Signature::PrintErrorMessageToConsole("Can't read block size parameter. Abort.");
            return -1;
        }
    }

    Signature::StartInfrastructure(argv[1], argv[2], Signature::ConvertMbytesToBytes(blockSize));

    return 0;
}