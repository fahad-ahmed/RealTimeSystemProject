#include "EDFScheduler.h"

void EDFScheduler::taskRunner() {


  while (running) 
  {
        Task task;

        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [&] { return !tasks.empty() || !running; });

            if (!running && tasks.empty()) break;

            task = tasks.top();
            tasks.pop();
        }

        auto now = std::chrono::steady_clock::now();
        if (now < task.scheduledTime) {
            // Wait until the scheduled time if it's not reached yet
            std::this_thread::sleep_until(task.scheduledTime);
        }
        


        // Check if the current time plus execution time exceeds the deadline
        bool deadlineMissed = (std::chrono::steady_clock::now() + task.executionTime) > task.deadline;
        if (deadlineMissed) {
            std::cout << "Task " << task.name << " missed its deadline and will not execute." << std::endl;
            continue; // Skip execution if the deadline is missed
        }

        auto deadline = task.deadline;
        auto deadline_elapsed = deadline - program_start;
        auto deadline_seconds = std::chrono::duration_cast<std::chrono::seconds>(deadline_elapsed).count();
        auto deadline_minutes = std::chrono::duration_cast<std::chrono::minutes>(deadline_elapsed).count();
        auto deadline_hours = std::chrono::duration_cast<std::chrono::hours>(deadline_elapsed).count();



        std::cout << "Current Task type:"<<task.name<< ", Task Deadline : "
            << deadline_hours << "h: "
            << deadline_minutes % 60 << "m: "
            << deadline_seconds % 60 << "s" << std::endl;

        if (task.type == sporadic || task.type == aperiodic)
        {
            task.action(); // Execute the task
        }
        else
        {
            //periodic task (file reading) will executed until execution time is reached.
            auto start = std::chrono::system_clock::now();
            while ((std::chrono::system_clock::now() - start) < task.executionTime)
            {
                task.action();

                if (allowPreemption && !tasks.empty() && tasks.top().deadline < task.deadline) {
                    // earliest deadline task will be preempted
                    std::cout << "------------------------------------------->\n\nPeriodic Task Preempted\n\n-------------------------------------------" << std::endl;

                    break; // Break out of execution loop for periodic single task
                }

            }
        }

        std::cout << "Task " << task.name << " completed." << std::endl;
    }
}
