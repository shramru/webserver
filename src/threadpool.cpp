//
// Created by vladislav on 13.06.16.
//
#include "threadpool.hpp"

ThreadPool::ThreadPool(size_t threads)
        : stop(false), busy(0) { add_worker(threads); }

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    for(auto& worker: workers)
        worker.join();
}

void ThreadPool::add_worker(size_t count) {
    for(size_t i = 0; i < count; ++i)
        workers.emplace_back(
                [this] {
                    for(;;) {
                        std::function<void()> task;

                        {
                            std::unique_lock<std::mutex> lock(this->queue_mutex);
                            this->condition.wait(lock,
                                                 [this]{ return this->stop || !this->tasks.empty(); });
                            if(this->stop && this->tasks.empty())
                                return;
                            task = std::move(this->tasks.front());
                            this->tasks.pop();

                        }

                        ++busy;
                        task();
                        --busy;
                    }
                }
        );
}

size_t ThreadPool::size() const {
    return workers.size();
}