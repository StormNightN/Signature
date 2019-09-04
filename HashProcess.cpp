//
// Created by stormnight on 9/4/19.
//
#include "HashProcess.h"

Signature::HashProcess::HashProcess(Signature::WorkQueue<Signature::DataChank> &rWorkQueue) :
    m_WorkQueue(rWorkQueue) {

}

bool Signature::HashProcess::Process() {
    auto pDataChank = m_WorkQueue.Pop();
    if(pDataChank != nullptr) {
        pDataChank->Hash();
        // TODO push to result queue

        return true;
    } else {
        return false;
    }
}