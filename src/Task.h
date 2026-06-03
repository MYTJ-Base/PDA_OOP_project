#ifndef TASK_H
#define TASK_H

#include "PDAItem.h"
#include <string>
#include <fstream>

// Represents a task with a due date, priority level, and completion status
class Task : public PDAItem {
private:
    std::string dueDate;   // Format: YYYY-MM-DD
    std::string priority;  // Values: "High", "Medium", "Low"
    bool completed;        // false = pending, true = done

public:
    // Constructor
    Task(int id,
         const std::string& title,
         const std::string& dueDate,
         const std::string& priority,
         bool completed = false);

    // Getters
    std::string getDueDate() const;
    std::string getPriority() const;
    bool isCompleted() const;

    // Setters with validation
    // dueDate must match YYYY-MM-DD format
    // priority must be "High", "Medium", or "Low"
    void setDueDate(const std::string& dueDate);
    void setPriority(const std::string& priority);
    void setCompleted(bool status);

    // Mark this task as done
    void markComplete();

    // Inherited interface — must implement all three
    void display() const override;
    void saveToFile(std::ofstream& file) const override;
    void loadFromFile(std::ifstream& file) override;
};

#endif // TASK_H