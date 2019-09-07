//
// Created by stormnight on 9/6/19.
//
#include <fstream>
#include <iomanip>
#include "FileWriter.h"
#include "Helpers.h"


Signature::FileWriter::FileWriter(size_t hashCount, std::string path) :
        m_Path(std::move(path)),
        m_HashData(hashCount),
        m_WriteMutex()
{

}

void Signature::FileWriter::ProcessHash() {
    size_t hashId = 0U;
    size_t hashCount = m_HashData.size();
    std::ofstream outputFile(m_Path, std::ios::out | std::ios::trunc);

    if(outputFile.is_open()) {
        while (hashId < hashCount) {
            std::unique_ptr<DataChank> p_ProcessingChank(nullptr);
            std::unique_lock<std::mutex> lock(m_WriteMutex);

            m_Push.wait(lock, [this, &hashId]() { return m_HashData[hashId] != nullptr; });

            std::swap(p_ProcessingChank, m_HashData[hashId]);

            if(!PrintToOutput(outputFile, p_ProcessingChank, hashId++)) {
                PrintErrorMessageToConsole("Can't write to output file. Stop processing");
                std::abort();
            }
            PrintMessageToConsole(std::to_string((hashId * 100) / hashCount));
        }
    } else {
        PrintErrorMessageToConsole("Can't open output file " + m_Path + ". Stop processing.");
        std::abort();
    }
}

void Signature::FileWriter::PushHashChank(std::unique_ptr<Signature::DataChank> pDataChank) {
    std::unique_lock<std::mutex> lock(m_WriteMutex);

    m_HashData[pDataChank->GetId()].swap(pDataChank);
    m_Push.notify_one();
}

bool Signature::FileWriter::PrintToOutput(std::ostream& os,
        std::unique_ptr<DataChank>& rp_ProcessingChank, size_t idx) {
    bool isGoodState = (os << "Block idx: " << idx << " Hash value: " << std::hex << std::setfill('0')).good();
    for(size_t i = 0; (i < rp_ProcessingChank->GetSize()) && (isGoodState); i++) {
        isGoodState = (os << std::setw(2) << static_cast<int>(rp_ProcessingChank->GetData()[i]) << ' ').good();
    }

    return isGoodState && (os << std::dec << std::endl).good();
}