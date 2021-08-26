#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include <thread>
#include <functional>
#include "Core/containers/vect_t.hpp"


namespace Core
{
    struct ThreadPool
    {
        vect_t<std::thread> threads;
        bool isWorking;
    };

    ThreadPool make_thread_pool(size_t size);
    void destroy(ThreadPool& TreadPool);

    void perform_task(ThreadPool& pool, std::function<void()> task);
}

#endif // THREADPOOL_HPP
