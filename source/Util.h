#include <iostream>
#include <unistd.h>
#include <limits.h>
#include <string>
#include "ConfigReader.h"

std::string getExecutablePath() {
    char path[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", path, PATH_MAX);
    return (count > 0) ? std::string(path, count) : std::string();
}

std::string getExecutableDir() {
    std::string fullPath = getExecutablePath();
    size_t lastSlashPos = fullPath.find_last_of('/');
    return (lastSlashPos != std::string::npos) ? fullPath.substr(0, lastSlashPos) : "";
}

Task ConstructTask(TaskType type, std::function<void()> func)
{
    Task task;
    task.schedulerType = ConfigReader::getInstance().isEdfEnabled() ? edf : priorityDriven;
    task.scheduledTime = std::chrono::steady_clock::now();
    switch (type)
    {
    case periodic:
        task.action = func;
        task.type = periodic;
        task.name = "Periodic";
        task.priority = (TaskPriority) ConfigReader::getInstance().periodicPriority();
        task.executionTime = std::chrono::milliseconds(ConfigReader::getInstance().periodicExectionTime());
        task.deadline = task.scheduledTime + std::chrono::milliseconds(ConfigReader::getInstance().periodicDeadline());
        
        break;
    case aperiodic:
        task.action = func;
        task.type = aperiodic;
        task.name = "aperiodic";
        task.priority = (TaskPriority) ConfigReader::getInstance().aperiodicPriority();
        task.executionTime = std::chrono::milliseconds(ConfigReader::getInstance().aperiodicExectionTime());
        task.deadline = task.scheduledTime + std::chrono::milliseconds(ConfigReader::getInstance().aperiodicDeadline());
        break;
    case sporadic:
        task.action = func;
        task.type = sporadic;
        task.name = "Sporadic";
        task.priority = (TaskPriority)ConfigReader::getInstance().sporadicPriority();
        task.executionTime = std::chrono::milliseconds(ConfigReader::getInstance().sporadicExectionTime());
        task.deadline = task.scheduledTime + std::chrono::milliseconds(ConfigReader::getInstance().sporadicDeadline());
        break;
    default:
        break;
    }

    return task;
   
   
}


#pragma once
