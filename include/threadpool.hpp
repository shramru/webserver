//
// Created by vladislav on 13.06.16.
//

#ifndef PROJECT_THREADPOOL_HPP
#define PROJECT_THREADPOOL_HPP

#include <queue>
#include <future>

class ThreadPool {
    std::vector< std::thread > workers;
    std::queue< std::function<void()> > tasks;

    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;

    std::atomic<size_t> busy;

    void add_worker(size_t count = 1);

public:
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args);
    size_t size() const;

    ThreadPool(size_t threads);
    ~ThreadPool();
};

#include "../src/threadpool.tcc"
#endif //PROJECT_THREADPOOL_HPP
