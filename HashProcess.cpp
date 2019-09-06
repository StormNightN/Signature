//
// Created by stormnight on 9/4/19.
//
#include "HashProcess.h"
#include <openssl/md5.h>
#include <iostream>


Signature::HashProcess::HashProcess(Signature::WorkQueue<Signature::DataChank> &rWorkQueue,
        FileWriter& rFileWriter) :
    m_WorkQueue(rWorkQueue),
    m_FileWriter(rFileWriter) {

}

void Signature::HashProcess::Process() {
    bool stopProcessing = false;
    while (!stopProcessing){
        auto pDataChank = m_WorkQueue.Pop();
        if(pDataChank != nullptr) {
            auto pResult = std::make_unique<unsigned char[]>(MD5_DIGEST_LENGTH);
            MD5(pDataChank->GetData().get(), pDataChank->GetSize(), pResult.get());
            m_FileWriter.PushHashChank(std::make_unique<DataChank>(
                    DataChank(std::move(pResult), MD5_DIGEST_LENGTH, pDataChank->GetId())));
        }
        stopProcessing = pDataChank == nullptr;
    }
}