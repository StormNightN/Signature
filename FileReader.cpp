//
// Created by stormnight on 9/4/19.
//

#include <fstream>
#include <memory>
#include "FileReader.h"

Signature::FileReader::FileReader(std::string path, WorkQueue<DataChank>& rWorkQueue, size_t blockSize) :
    m_Path(std::move(path)),
    m_BlockSize(blockSize * 1024 *1024),
    m_WorkQueue(rWorkQueue) {

}

void Signature::FileReader::Read() const{
    std::ifstream inputFile;
    inputFile.open(m_Path, std::ios::in |std::ios::binary);

    if(inputFile.is_open()) {

        size_t blockIdx = 0U;
        while (inputFile) {
            auto pDataBuffer = std::make_unique<unsigned char[]>(m_BlockSize);
            for(auto idx = static_cast<size_t >(inputFile.gcount()); idx < m_BlockSize; idx++) {
                pDataBuffer[idx] = 0U;
            }

            m_WorkQueue.Push(std::move(pDataBuffer), m_BlockSize, blockIdx++);
        }

        // Send stop signal to work queue
        m_WorkQueue.StopProcessing();

        if(!inputFile.eof()) {    // unsuccess reading
            throw std::ifstream::failure("Error during file processing " + m_Path);
        }

    } else {
        throw std::ifstream::failure("Can't open file " + m_Path);
    }
}