#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include <mutex>
#include <deque>
#include <list>
#include <vector>
#include <thread>
#include <functional>
#include <atomic>


class ThreadPool
{
public:
    using task_t = std::function<void()>;

    ThreadPool();
    ~ThreadPool();

    [[nodiscard]] unsigned int getWorkersCount() const;
    void setWorkersCount(unsigned int newWorkersCount);

    [[nodiscard]] unsigned int getBusyWorkersCount() const;
    [[nodiscard]] unsigned int getFreeWorkersCount() const;

    void addTask(task_t task);
    void killAllTasks();

    void beginTaskGroup();
    void endTaskGroup();

private:
    void worker();

    bool getNextTask(task_t& task);

    std::atomic<bool> isRunning;
    std::vector<std::thread> threads;
    std::atomic<unsigned int> busyWorkersCount;

    std::mutex taskQueueMutex;
    std::deque<task_t> queuedTasks;

    std::atomic<int> taskGroupSize;
};

#endif // THREADPOOL_HPP
