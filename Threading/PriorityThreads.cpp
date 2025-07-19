/*
TOPIC : Implementing priority-based threading in C++

Notes on thread priority :
-------------------------
1. Understanding Thread Priority Fundamentals
Thread priority determines the scheduling order and CPU time allocation for threads.
The system schedules threads with higher priority to run before lower priority threads,
and only when higher priority threads are unavailable does the system 
execute lower priority threads


Notes on Priority Management with Thread Pools :
-----------------------------------------------
1. Priority Inversion and Safety
Be aware of priority inversion, which occurs when a low-priority thread prevents a higher-priority thread from running. This happens when a low-priority thread holds a mutex that a high-priority thread needs. Some systems provide priority inheritance protocols to mitigate this issue.

2. Performance Impact
Setting thread priorities doesn't guarantee improved performance in all scenarios. If your application is the only one running or system load is low, priority differences may have minimal impact. However, in high-load environments with multiple competing processes, proper priority management becomes crucial.

This approach allows you to conditionally execute code blocks in different priority threads based on variable values, providing fine-grained control over task scheduling and system resource utilization.
*/

#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <vector>

class PriorityThreadPool {
public:
    enum TaskPriority {
        LOW = 0,
        NORMAL = 1,
        HIGH = 2
    };

    struct Task {
        std::function<void()> function;
        TaskPriority priority;
        
        bool operator<(const Task& other) const {
            return priority < other.priority; // Higher priority first
        }
    };

    PriorityThreadPool(size_t numThreads) {
        for (size_t i = 0; i < numThreads; ++i) {
            workers.emplace_back([this] {
                while (true) {
                    Task task;
                    {
                        std::unique_lock<std::mutex> lock(queueMutex);
                        condition.wait(lock, [this] { return !tasks.empty() || stop; });
                        
                        if (stop && tasks.empty()) return;
                        
                        task = tasks.top();
                        tasks.pop();
                    }
                    task.function();
                }
            });
        }
    }

    void enqueue(std::function<void()> function, TaskPriority priority) {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            tasks.emplace(Task{function, priority});
        }
        condition.notify_one();
    }

    ~PriorityThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            stop = true;
        }
        condition.notify_all();
        for (std::thread& worker : workers) {
            worker.join();
        }
    }

private:
    std::vector<std::thread> workers;
    std::priority_queue<Task> tasks;
    std::mutex queueMutex;
    std::condition_variable condition;
    bool stop = false;
};

int main()
{
    PriorityThreadPool pool(4);
    std::string variable = "xyz";

    // Add tasks based on variable value
    if (variable == "xyz") {
        pool.enqueue([]() {
            std::cout << "High priority task executing" << std::endl;
            // High priority work
        }, PriorityThreadPool::HIGH);
    } else {
        pool.enqueue([]() {
            std::cout << "Low priority task executing" << std::endl;
            // Low priority work
        }, PriorityThreadPool::LOW);
    }

    // Add more tasks as needed
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return 0;
}
