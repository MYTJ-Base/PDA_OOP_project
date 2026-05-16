#include "Reminder.h"

Reminder::Reminder() : datetime(""), message("") {}

Reminder::Reminder(const std::string &datetime, const std::string &message)
    : datetime(datetime), message(message) {}
