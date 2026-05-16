#ifndef TASK_H
#define TASK_H

#include <string>

class Task {
public:
    Task();
    Task(const std::string &title, const std::string &due, bool completed = false);

    std::string title;
    std::string due; // ISO date/time or date string
    bool completed;
};

#endif // TASK_H
