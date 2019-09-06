//
// Created by stormnight on 9/6/19.
//
#include <fstream>
#include "FileWriter.h"


Signature::FileWriter::FileWriter(size_t hashCount, std::string path) :
        m_Path(std::move(path)),
        m_HashData(hashCount, nullptr),
        m_WriteMutex()
{

}

void Signature::FileWriter::ProcessHash() {
    size_t hashId = 0U;
    size_t hashCount = m_HashData.size();
    std::ofstream outputFile(m_Path);

    while (hashId < hashCount) {
        std::unique_ptr<DataChank> p_ProcessingChank(nullptr);
        do {
            std::unique_lock<std::mutex> lock(m_WriteMutex);
            std::swap(p_ProcessingChank, m_HashData[hashId]);

            if(p_ProcessingChank == nullptr) {
                // TODO signalization
            }
        } while (p_ProcessingChank == nullptr); //while waited chank is not pushed

        PrintToOutput(outputFile, p_ProcessingChank, hashId++);
    }
}

void Signature::FileWriter::PrintToOutput(std::ostream& os,
        std::unique_ptr<DataChank>& rp_ProcessingChank, size_t idx) {
    os << "Block idx: " << idx << " ";
    os << std::hex;
    for(size_t i = 0; i < rp_ProcessingChank->GetSize(); i++) {
        os << rp_ProcessingChank->GetData()[i];
    }
    os << std::dec << std::endl;
}