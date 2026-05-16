#include "Task.h"

Task::Task() : title(""), due(""), completed(false) {}

Task::Task(const std::string &title, const std::string &due, bool completed)
    : title(title), due(due), completed(completed) {}
