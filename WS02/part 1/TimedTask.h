//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
//Name: Max Feng
//Student ID:136141231
//Date:2024/05/24
#ifndef SENECA_TIMEDTASK_H
#define SENECA_TIMEDTASK_H
#include <iostream> 
#include <string>
#include <chrono> 
namespace seneca{
    const int MAX_TASKS = 10;
    struct Task{
        std::string taskName;
        std::string unitsOfTime;
        std::chrono::steady_clock::duration duration; 
    }; 

    class TimedTask{
        std::chrono::steady_clock::time_point startTime; 
        std::chrono::steady_clock::time_point endTime; 
    public:
        Task tasks[MAX_TASKS];
        int numRecords{0};
        TimedTask();
        void startClock();
        void stopClock();
        void addTask(const char* taskName);
        friend std::ostream& operator<<(std::ostream& os, const TimedTask& task);
    };
}

#endif