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

public:
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args);

    ThreadPool(size_t);
    ~ThreadPool();
};

#include "threadpool.tcc"
#endif //PROJECT_THREADPOOL_HPP
