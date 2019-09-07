//
// Created by stormnight on 9/6/19.
//
#include <fstream>
#include <iomanip>
#include "includes/FileWriter.h"
#include "includes/Helpers.h"


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

    size_t completedPercents = 0;
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

            size_t newCompletedPercents = (hashId * 100) / hashCount;
            if(completedPercents != newCompletedPercents) {
                PrintMessageFromStartCurrentLine(CreateProgressBar(newCompletedPercents));
                completedPercents = newCompletedPercents;
            }
        }
    } else {
        PrintErrorMessageToConsole("Can't open output file " + m_Path + ". Stop processing.");
        std::abort();
    }

    PrintMessageToConsole("\nProcessing was completed.");
}

void Signature::FileWriter::PushHashChank(std::unique_ptr<Signature::DataChank> pDataChank) {
    std::unique_lock<std::mutex> lock(m_WriteMutex);

    m_HashData[pDataChank->GetId()].swap(pDataChank);
    m_Push.notify_one();
}

bool Signature::FileWriter::PrintToOutput(std::ostream& os,
        std::unique_ptr<DataChank>& rp_ProcessingChank, size_t idx) const {
    bool isGoodState = (os << "Block idx: " << idx << " Hash value: " << std::hex << std::setfill('0')).good();
    for(size_t i = 0; (i < rp_ProcessingChank->GetSize()) && (isGoodState); i++) {
        isGoodState = (os << std::setw(2) << static_cast<int>(rp_ProcessingChank->GetData()[i]) << ' ').good();
    }

    return isGoodState && (os << std::dec << std::endl).good();
}

std::string Signature::FileWriter::CreateProgressBar(size_t progress) const {
    std::string result;
    for(size_t i = 0U; i <= progress; i++) {
        result.append("_");
    }
    for(size_t i = progress + 1; i < 100; i++) {
        result.append(".");
    }

    return result;
}