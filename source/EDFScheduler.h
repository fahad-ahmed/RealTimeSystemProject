
#pragma once
#ifndef EDFSCHEDULER_H
#define EDFSCHEDULER_H
#include "TaskScheduler.h"
class EDFScheduler :public TaskScheduler { // Inherit from Animal
public:
    void taskRunner()  override; // Override the speak function
    using TaskScheduler::TaskScheduler;
};
#endif 

