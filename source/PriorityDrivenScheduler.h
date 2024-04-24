#pragma once
#ifndef PRIORITYDRIVENSCHEDULER_H
#define PRIORITYDRIVENSCHEDULER_H
#include "TaskScheduler.h"

class PriorityDrivenScheduler : public TaskScheduler { // Inherit from Animal
public:
    void taskRunner()  override; // Override the speak function
    using TaskScheduler::TaskScheduler;
};
#endif // PRIORITYDRIVENSCHEDULER_H

