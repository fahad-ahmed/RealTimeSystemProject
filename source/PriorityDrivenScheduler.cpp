
#include "PriorityDrivenScheduler.h"

void PriorityDrivenScheduler::taskRunner() {
    while (running) {
        Task task;

        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [&] { return !tasks.empty() || !running; });

            if (!running && tasks.empty()) break;

            task = tasks.top();
            tasks.pop();
        }

        if (task.type == periodic)
            std::cout << "------------------------------------------->Periodic Task Started" << std::endl;

        auto start = std::chrono::system_clock::now();
        bool isDeadlineMissed = true;
        while ((std::chrono::system_clock::now() - start) < task.executionTime) {
            // Simulate execution in chunks to allow checking for preemption
            //This sleep is give for preemption and for viewable printing in console output
            std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Execution chunk

            isDeadlineMissed = false;
            task.action();

            if (task.type != periodic)
            {
                //for sporadic and aperiodic , there will no preemption. So end the loop
                //std::cout << "------------------------------->Task Completed ----->" << task.name << std::endl;
                break;

            }


            if (allowPreemption && !tasks.empty() && tasks.top().priority > task.priority) {
                // Higher-priority task detected, preempt current task
                std::cout << "------------------------------------------->\n\nPeriodic Task Preempted\n\n-------------------------------------------" << std::endl;
                {
                    std::unique_lock<std::mutex> lock(mtx);
                    tasks.push(task); // Put the current task back in the queue
                }
                break; // Break out of execution loop
            }
        }

        if ((std::chrono::system_clock::now() - start) >= task.executionTime) {
            // Task completed
            if (task.type == periodic)
                std::cout << "------------------------------------------->\n\nPeriodic Task Completed\n\n-------------------------------------------" << std::endl;
        }

        if (isDeadlineMissed)
        {

            std::cout << "\n=================" << task.name << "Task" << "======> Missed Deadline <=========" << std::endl;

        }
    }
}
