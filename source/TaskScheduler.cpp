#include "TaskScheduler.h"


TaskScheduler::TaskScheduler(bool preemptionEnabled){
    allowPreemption = preemptionEnabled;
    std::thread(&TaskScheduler::taskRunner, this).detach();
    program_start = std::chrono::steady_clock::now();
}

void TaskScheduler:: addTask(const Task& task) {
    {
        std::lock_guard<std::mutex> lock(mtx);
        tasks.push(task);
    }
    cv.notify_one();
}

void TaskScheduler::stopScheduler() {
    running = false;
    cv.notify_all();
}

