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

    /**
     * Represent class, which contains data to processing
     */
    template <typename T>
    class WorkQueue {

    public:
        /**
         * Default constructor
         *
         * @param maxSize       max element count in queue
         */
        explicit WorkQueue(size_t maxSize);

        /**
         * Function, via which signal about stop processing will be sent
         */
        void StopProcessing();

        /**
         * Push data to queue
         *
         * @param args  args for queue element constructor
         *
         * @return push result
         * @retval true success
         * @retval false queue is full
         */
        template <typename... U>
        bool Push(U&&... args);

        /**
         * Get data from queue
         *
         * @return unique pointer on data
         * @retval nullptr queue is empty, data otherwise
         */
        std::unique_ptr<T> Pop();

        /**
         * Destructor
         */
        virtual ~WorkQueue() = default;

    private:

        /// Queue max size
        ///
        size_t m_MaxSize;

        /// Flag, indicates that no DataChank will be pushed
        ///
        std::atomic<bool> m_StopProcessing;

        /// Queue, which contains data to processing
        ///
        std::queue<std::unique_ptr<T>> m_Queue;

        /// Mutex for queue guarding
        ///
        std::mutex m_QueueMutex;
    };

    template <typename T>
    Signature::WorkQueue<T>::WorkQueue(size_t maxSize) :
            m_MaxSize(maxSize),
            m_StopProcessing(false),
            m_Queue(),
            m_QueueMutex() {

    }

    template<typename T>
    void Signature::WorkQueue<T>::StopProcessing() {
        m_StopProcessing.store(true);
    }

    template <typename T>
    template <typename ...U>
    bool WorkQueue<T>::Push(U&&... args) {
        std::lock_guard<std::mutex> guard(m_QueueMutex);

        if(m_Queue.size() < m_MaxSize) {
            m_Queue.push(std::make_unique<T>(std::forward<U>(args)...));
            // TODO signalization

            return true;

        } else {
            return false;
        }
    }

    template<typename T>
    std::unique_ptr<T> Signature::WorkQueue<T>::Pop() {
        std::lock_guard<std::mutex> guard(m_QueueMutex);

        if(!m_Queue.empty()) {
            auto pDataChank = std::unique_ptr<DataChank>(std::move(m_Queue.front()));
            m_Queue.pop();
            // TODO signalization

            return pDataChank;
        } else {
            return std::unique_ptr<DataChank>(nullptr);
        }
    }
}

#endif //SIGNATURE_WORKQUEUE_H
