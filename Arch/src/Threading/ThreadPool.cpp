#include "Threading/ThreadPool.hpp"


ThreadPool::ThreadPool()
    : isRunning(true), busyWorkersCount(0)
{
    auto workersCount = std::thread::hardware_concurrency();
    threads.reserve(workersCount);
    for (unsigned int i = 0; i < workersCount; i++)
        threads.emplace_back(&ThreadPool::worker, this);
}

ThreadPool::~ThreadPool()
{
    isRunning = false;
    for (auto& thread : threads)
        thread.join();
}

unsigned int ThreadPool::getWorkersCount() const
{
    return threads.size();
}

void ThreadPool::setWorkersCount(unsigned int newWorkersCount)
{
    if (getWorkersCount() == newWorkersCount)
        return;

    if (busyWorkersCount > newWorkersCount)
        busyWorkersCount = newWorkersCount;

    std::lock_guard<std::mutex> lock(taskQueueMutex);
    threads.resize(newWorkersCount);
}

void ThreadPool::addTask(task_t task)
{
    std::lock_guard<std::mutex> lock(taskQueueMutex);
    queuedTasks.push_front(std::move(task));

    taskGroupSize++;
}

void ThreadPool::killAllTasks()
{
    std::lock_guard<std::mutex> lock(taskQueueMutex);
    queuedTasks.clear();
}

void ThreadPool::worker()
{
    while (isRunning)
    {
        task_t task;
        if (getNextTask(task))
        {
            busyWorkersCount++;
            task();
            busyWorkersCount--;
            taskGroupSize--;
        }
    }
}

bool ThreadPool::getNextTask(ThreadPool::task_t &task)
{
    std::lock_guard<std::mutex> lock(taskQueueMutex);
    if (!queuedTasks.empty())
    {
        task = queuedTasks.back();
        queuedTasks.pop_back();
        return true;
    }
    return false;
}

unsigned int ThreadPool::getBusyWorkersCount() const
{
    return busyWorkersCount;
}

unsigned int ThreadPool::getFreeWorkersCount() const
{
    return getWorkersCount() - busyWorkersCount;
}

void ThreadPool::beginTaskGroup()
{
    taskGroupSize = 0;
}

void ThreadPool::endTaskGroup()
{
    while (taskGroupSize != 0);
}
