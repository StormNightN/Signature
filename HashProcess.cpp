//
// Created by stormnight on 9/4/19.
//
#include "includes/HashProcess.h"
#include "includes/Helpers.h"
#include <openssl/md5.h>
#include <iostream>


Signature::HashProcess::HashProcess(Signature::ConcurrentQueue<Signature::DataChunk> &rWorkQueue,
        FileWriter& rFileWriter) :
    m_WorkQueue(rWorkQueue),
    m_FileWriter(rFileWriter) {

}

void Signature::HashProcess::Process() {
    bool stopProcessing = false;

    while (!stopProcessing) {
        try {
            auto pDataChank = m_WorkQueue.Pop();

            try {
                auto pResult = std::make_unique<unsigned char[]>(MD5_DIGEST_LENGTH);
                MD5(pDataChank->GetData().get(), pDataChank->GetSize(), pResult.get());
                m_FileWriter.PushHashChank(std::make_unique<DataChunk>(
                        DataChunk(std::move(pResult), MD5_DIGEST_LENGTH, pDataChank->GetId())));
            } catch (std::bad_alloc &ex) {
                PrintErrorMessageToConsole("Memory allocation error. Stop processing.");
                std::abort();
            }
        } catch (EmptyQueueException& ex) {
            stopProcessing = true;
        }
    }
}