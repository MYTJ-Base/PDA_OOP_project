#ifndef REMINDER_H
#define REMINDER_H

#include <string>

class Reminder {
public:
    Reminder();
    Reminder(const std::string &datetime, const std::string &message);

    std::string datetime; // ISO date/time
    std::string message;
};

#endif // REMINDER_H
