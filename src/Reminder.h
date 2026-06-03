#ifndef REMINDER_H
#define REMINDER_H

#include "PDAItem.h"
#include <string>
#include <fstream>

// Represents a reminder with a scheduled date/time and optional alarm flag
class Reminder : public PDAItem {
private:
    std::string dateTime; // Format: YYYY-MM-DD HH:MM
    std::string message;  // The reminder message shown to the user
    bool alarm;           // true = alert user if reminder is due today

public:
    // Constructor
    Reminder(int id,
             const std::string& title,
             const std::string& dateTime,
             const std::string& message,
             bool alarm = false);

    // Getters
    std::string getDateTime() const;
    std::string getMessage() const;
    bool hasAlarm() const;

    // Setters with validation
    // dateTime must match YYYY-MM-DD HH:MM format
    // message must not be empty
    void setDateTime(const std::string& dateTime);
    void setMessage(const std::string& message);
    void setAlarm(bool alarm);

    // Check if this reminder is due today or overdue
    // Compares dateTime against current system time
    bool isDueNow() const;

    // Inherited interface — must implement all three
    void display() const override;
    void saveToFile(std::ofstream& file) const override;
    void loadFromFile(std::ifstream& file) override;
};

#endif // REMINDER_H