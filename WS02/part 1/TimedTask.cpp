//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
//Name: Max Feng
//Student ID:136141231
//Date:2024/05/24
#include "TimedTask.h"
#include <iostream>
#include <iomanip>

using namespace std;

namespace seneca {

    TimedTask::TimedTask(){};

    void TimedTask::startClock(){
        startTime = chrono::steady_clock::now();
    }

    void TimedTask::stopClock(){
        endTime = chrono::steady_clock::now();
    }

    void TimedTask::addTask(const char* taskName){
        if(numRecords < MAX_TASKS){
            tasks[numRecords].taskName = taskName;
            tasks[numRecords].unitsOfTime = "nanoseconds";
            tasks[numRecords].duration = endTime - startTime;
            ++numRecords;
        }
    }

    ostream& operator<<(ostream& os, const TimedTask& task) {
        os << "--------------------------" << endl;
        os << "Execution Times:" << endl;
        os << "--------------------------" << endl;
        for (int i = 0; i < task.numRecords; i++){
            os << setw(21) << std::left << task.tasks[i].taskName << " " 
            << setw(13) << std::right << std::chrono::duration_cast<std::chrono::nanoseconds>(task.tasks[i].duration).count() << " " 
            << task.tasks[i].unitsOfTime << endl;
        }
        os << "--------------------------" << endl;
        return os;
    }
}