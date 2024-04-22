#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <vector>
#include <atomic>

class TaskQueue {
public:
    using Task = std::function<void()>;

    void push(Task task) {
        {
            std::unique_lock<std::mutex> lock(mutex_);
            tasks_.push(std::move(task));
        }
        condition_.notify_one();
    }

    bool try_pop(Task& task) {
        std::unique_lock<std::mutex> lock(mutex_);
        if (tasks_.empty()) {
            return false;
        }
        task = std::move(tasks_.front());
        tasks_.pop();
        return true;
    }

    void done() {
        {
            std::unique_lock<std::mutex> lock(mutex_);
            finished_ = true;
        }
        condition_.notify_all();
    }

    bool pop(Task& task) {
        std::unique_lock<std::mutex> lock(mutex_);
        while (tasks_.empty() && !finished_) {
            condition_.wait(lock);
        }
        if (tasks_.empty() && finished_) {
            return false;
        }
        task = std::move(tasks_.front());
        tasks_.pop();
        return true;
    }

private:
    std::atomic<bool> finished_{false};
    std::queue<Task> tasks_;
    std::mutex mutex_;
    std::condition_variable condition_;
};

class ThreadPool {
public:
    ThreadPool(size_t num_threads, TaskQueue& queue) : queue_(queue) {
        for (size_t i = 0; i < num_threads; ++i) {
            workers_.emplace_back([this]() {
                while (true) {
                    TaskQueue::Task task;
                    if (!queue_.pop(task)) {
                        // If queue is empty and finished flag is set, exit the loop
                        break;
                    }
                    task();
                }
            });
        }
    }

    ~ThreadPool() {
        for (auto& worker : workers_) {
            if (worker.joinable()) {
                worker.join();
            }
        }
    }

private:
    TaskQueue& queue_;
    std::vector<std::thread> workers_;
};

int main() {
    TaskQueue queue;
    const size_t num_producer_threads = 4; // You can change the number of producers
    const size_t num_consumer_threads = 4; // You can change the number of consumers

    // Create consumer threads
    ThreadPool consumers(num_consumer_threads, queue);

    // Create producer threads
    std::vector<std::thread> producers;
    for (size_t i = 0; i < num_producer_threads; ++i) {
        producers.emplace_back([&queue, i]() {
            for (int j = 0; j < 10; ++j) { // Each producer will add 10 tasks
                queue.push([i, j]() {
                    std::cout << "Producer " << i << " adding task " << j << std::endl;
                });
            }
        });
    }

    // Join producer threads
    for (auto& producer : producers) {
        if (producer.joinable()) {
            producer.join();
        }
    }

    // Signal that no more tasks will be added
    queue.done();

    // Consumer threads will be joined in the destructor of ThreadPool

    return 0;
}
