#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <chrono>
#include <atomic>
#include <thread>

enum TaskPriority { low = 0, medium = 1, high = 2 };
enum TasksShedulerType { priorityDriven = 0, edf =1 };
enum TaskType {periodic = 0, aperiodic = 1, sporadic = 2 };

struct Task {
    std::function<void()> action;
    TaskType type;
    TaskPriority priority;
    TasksShedulerType schedulerType;
    std::string name;
    std::chrono::steady_clock::time_point scheduledTime;
    std::chrono::milliseconds executionTime;
    std::chrono::steady_clock::time_point deadline;
    

    bool operator<(const Task& rhs) const {

        if(schedulerType == edf)
            return deadline < rhs.deadline;
        
        return priority < rhs.priority;
    }
};

class TaskScheduler {
protected:
    std::priority_queue<Task> tasks;
    std::mutex mtx;
    std::condition_variable cv;
    std::atomic<bool> running{ true };
    bool allowPreemption;
    virtual void taskRunner() = 0; //pure virtual function
    std::chrono::steady_clock::time_point program_start;

public:
    TaskScheduler(bool preemptionEnabled = false);

    void addTask(const Task& task);

    void stopScheduler();
};

