#ifndef CLIENT_SERVER_BERKELEY_SOCKETS_COMMON_THREADSAFEQUE_H
#define CLIENT_SERVER_BERKELEY_SOCKETS_COMMON_THREADSAFEQUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

namespace s21 {
    template <typename T>
    class ThreadSafeQ  {
        using lock_guard = std::lock_guard<std::mutex>;
    public:
        ThreadSafeQ() = default;
        ThreadSafeQ(const ThreadSafeQ&) = delete;
        ThreadSafeQ(ThreadSafeQ&&)  noexcept = default;
        ThreadSafeQ& operator=(const ThreadSafeQ&) = delete;
        ThreadSafeQ& operator=(ThreadSafeQ&&)  noexcept = default;
        ~ThreadSafeQ() { Clear(); }
        /// returns the first element in the queue
        const T& Front() const noexcept {
            lock_guard lock(q_mutex_);
            return message_que_.front();
        }

        /// returns the first element in the queue removing it from the queue
        T PopFront() {
            lock_guard lock(q_mutex_);
            auto t = std::move(message_que_.front());
            message_que_.pop_front();
            return t;
        }

        /// adds an element to the back of the queue
        template <typename... Args>
        void EmplaceBack(Args&&... args) {
            {
                lock_guard lock(q_mutex_);
                message_que_.emplace_back(std::forward<Args>(args)...);
            }
            cv_.notify_one();
        }
        /// remove target value
        void Erase(T& value) {
            lock_guard lock(q_mutex_);
            message_que_.erase(
                    std::remove(message_que_.begin(), message_que_.end(), value),
                    message_que_.end());
        }

        bool Empty() const {
            lock_guard lock(q_mutex_);
            return message_que_.empty();
        }

        void Clear() {
            lock_guard lock(q_mutex_);
            message_que_.clear();
        }

        void Wait() {
            std::unique_lock<std::mutex> ul(cv_lock_);
            cv_.wait(ul, [this](){ return !Empty(); });
        }

    private:
        std::deque<T> message_que_;
        mutable std::mutex q_mutex_;
        std::condition_variable cv_;
        std::mutex cv_lock_;
    };
}  // namespace s21

#endif  // CLIENT_SERVER_BERKELEY_SOCKETS_COMMON_THREADSAFEQUE_H