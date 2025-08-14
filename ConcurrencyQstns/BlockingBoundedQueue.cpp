#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>

class BoundedBlockingQueue {
public:
    // Constructor initializes the queue with a capacity limit.
    BoundedBlockingQueue(int capacity) : capacity_(capacity), count_(0)
    {
        // No need to initialize semaphores since we will use condition_variable and mutex
    }

    // Enqueue adds an element to the queue. If the queue is full, blocks until space is available.
    void enqueue(int element)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        // Wait until there is space in the queue
        not_full_condition_.wait(lock, [this] { return count_ < capacity_; });
        queue_.push(element);
        ++count_;
        // Notify one waiting thread (if any) that an item was dequeued
        not_empty_condition_.notify_one();
    }

    // Dequeue removes and returns an element from the queue. If the queue is empty, blocks until an element is available.
    int dequeue()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        // Wait until there is an item to dequeue
        not_empty_condition_.wait(lock, [this] { return count_ > 0; });
        int value = queue_.front();
        queue_.pop();
        --count_;
        // Notify one waiting thread (if any) that space is now available
        not_full_condition_.notify_one();
        return value;
    }

    // Get the current size of the queue.
    int size() 
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return count_;
    }

private:
    std::queue<int> queue_; // The queue that holds the elements
    std::mutex mutex_; // Mutex to protect access to the queue
    std::condition_variable not_full_condition_; // Condition variable to block enqueue when queue is full
    std::condition_variable not_empty_condition_; // Condition variable to block dequeue when queue is empty
    int capacity_; // Maximum number of items in the queue
    int count_; // Current number of items in the queue
};