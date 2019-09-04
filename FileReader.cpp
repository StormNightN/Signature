//
// Created by stormnight on 9/4/19.
//

#include <fstream>
#include <memory>
#include "FileReader.h"

Signature::FileReader::FileReader(std::string path, size_t blockSize) :
    m_Path(std::move(path)),
    m_BlockSize(blockSize * 1024 *1024) {

}

void Signature::FileReader::Read() const{
    std::ifstream inputFile;
    inputFile.open(m_Path, std::ios::in |std::ios::binary);

    if(inputFile.is_open()) {

        while (inputFile) {
            auto pDataBuffer = std::make_unique<unsigned char[]>(m_BlockSize);
            for(auto idx = inputFile.gcount(); idx < m_BlockSize; idx++) {
                pDataBuffer[idx] = 0U;
            }
            // TODO push to work queue
        }

    } else {
        throw std::ifstream::failure("Can't open file " + m_Path);
    }
}