//
// Created by stormnight on 9/4/19.
//

#ifndef SIGNATURE_WORKQUEUE_H
#define SIGNATURE_WORKQUEUE_H

#include <cstring>
#include <atomic>
#include <queue>
#include <mutex>
#include "DataChank.h"

namespace Signature {

    class WorkQueue {

    public:
        explicit WorkQueue(size_t maxSize);

        void StopProcessing();

        template <typename... T>
        bool Push(T&&... args);

        std::unique_ptr<DataChank> Pop();
    private:

        /// Queue max size
        ///
        size_t m_MaxSize;

        /// Flag, indicates that no DataChank will be pushed
        ///
        std::atomic<bool> m_StopProcessing;

        /// Queue, which contains data to processing
        ///
        std::queue<std::unique_ptr<DataChank>> m_Queue;

        std::mutex m_QueueMutex;
    };

    template <typename... T>
    bool WorkQueue::Push(T&&... args) {
        std::lock_guard<std::mutex> guard(m_QueueMutex);

        if(m_Queue.size() < m_MaxSize) {
            m_Queue.push(std::make_unique<DataChank>(std::forward<T>(args)...));

            return true;

        } else {
            return false;
        }
    }
}

#endif //SIGNATURE_WORKQUEUE_H
