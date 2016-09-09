//
// Created by vladislav on 13.06.16.
//

#include "threadpool.hpp"

ThreadPool::ThreadPool(size_t threads)
        : stop(false), init_size(threads), busy(0) { add_worker(threads); }

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    for(auto& pair: workers)
       pair.second.join();
}

void ThreadPool::add_worker(size_t count) {
    for(size_t i = 0; i < count; ++i) {
        std::thread thread(
                [this] {
                    std::function<void()> task;
                    for(;;) {
                        {
                            std::unique_lock<std::mutex> lock(this->queue_mutex);
                            size_t free = workers.size() - busy;
                            if (free > init_size && this->tasks.empty()) {
                                auto id = std::this_thread::get_id();
                                workers[id].detach();
                                workers.erase(id);
                                return;
                            }

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
                });
        workers[thread.get_id()] = std::move(thread);
    }
}

size_t ThreadPool::size() const {
    return workers.size();
}