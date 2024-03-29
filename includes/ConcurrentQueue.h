//
// Created by stormnight on 9/4/19.
//

#ifndef SIGNATURE_CONCURRENTQUEUE_H
#define SIGNATURE_CONCURRENTQUEUE_H

#include <cstring>
#include <atomic>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "DataChunk.h"
#include "EmptyQueueException.h"

namespace Signature {

    /**
     * Represent class, which contains data to processing
     */
    template <typename T>
    class ConcurrentQueue {

    public:
        /**
         * Default constructor
         *
         * @param maxSize       max element count in queue
         */
        explicit ConcurrentQueue(size_t maxSize);

        /**
         * Function, via which signal about stop processing will be sent
         */
        void StopProcessing();

        /**
         * Push data to queue
         *
         * @param args  args for queue element constructor
         *
         */
        template <typename... U>
        void Push(U&&... args);

        /**
         * Get data from queue
         *
         * @return unique pointer on data
         * @throw EmptyQueue exception if queue is empty
         */
        std::unique_ptr<T> Pop();

        /**
         * Destructor
         */
        virtual ~ConcurrentQueue() = default;

    private:

        /// Queue max size
        ///
        size_t m_MaxSize;

        /// Flag, indicates that no DataChank will be pushed
        ///
        bool m_StopProcessing;

        /// Queue, which contains data to processing
        ///
        std::queue<std::unique_ptr<T>> m_Queue;

        /// Mutex for queue guarding
        ///
        std::mutex m_QueueMutex;

        std::condition_variable m_PushNotification;

        std::condition_variable m_PopNotification;
    };

    template <typename T>
    Signature::ConcurrentQueue<T>::ConcurrentQueue(size_t maxSize) :
            m_MaxSize(maxSize),
            m_StopProcessing(false),
            m_Queue(),
            m_QueueMutex(),
            m_PushNotification(),
            m_PopNotification() {

    }

    template<typename T>
    void Signature::ConcurrentQueue<T>::StopProcessing() {
        std::unique_lock<std::mutex> guard(m_QueueMutex);
        m_StopProcessing = true;
        m_PushNotification.notify_all();
    }

    template <typename T>
    template <typename ...U>
    void ConcurrentQueue<T>::Push(U&&... args) {
        std::unique_lock<std::mutex> guard(m_QueueMutex);

        // waits while queue is full
        m_PopNotification.wait(guard, [this] {
            return m_Queue.size() < m_MaxSize; });

        m_Queue.push(std::make_unique<T>(std::forward<U>(args)...));
        m_PushNotification.notify_all();
    }

    template<typename T>
    std::unique_ptr<T> Signature::ConcurrentQueue<T>::Pop() {
        std::unique_lock<std::mutex> guard(m_QueueMutex);

        m_PushNotification.wait(guard, [this] {
                return !m_Queue.empty() || m_StopProcessing; });

        if(m_Queue.empty() && m_StopProcessing) {
            m_PopNotification.notify_all();
            throw EmptyQueueException();
        } else {

            auto pDataChank = std::unique_ptr<DataChunk>(std::move(m_Queue.front()));
            m_Queue.pop();
            m_PopNotification.notify_all();

            return pDataChank;
        }
    }
}

#endif //SIGNATURE_WORKQUEUE_H
