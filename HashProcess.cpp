//
// Created by stormnight on 9/4/19.
//
#include "HashProcess.h"
#include <openssl/md5.h>


Signature::HashProcess::HashProcess(Signature::WorkQueue<Signature::DataChank> &rWorkQueue) :
    m_WorkQueue(rWorkQueue) {

}

bool Signature::HashProcess::Process() {
    auto pDataChank = m_WorkQueue.Pop();
    if(pDataChank != nullptr) {
        auto pResult = std::make_unique<unsigned char[] >(MD5_DIGEST_LENGTH);
        MD5(pDataChank->GetData().get(), pDataChank->GetSize(), pResult.get());
        auto hashDataChank = DataChank(std::move(pResult), MD5_DIGEST_LENGTH, pDataChank->GetSize());
        // TODO push to result queue

        return true;
    } else {
        return false;
    }
}