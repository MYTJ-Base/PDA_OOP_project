#ifndef PDA_H
#define PDA_H

#include "PDAItem.h"
#include <vector>
#include <string>

// Central manager class — holds all items and handles all operations
// Composition: PDA "has a" collection of PDAItem pointers
class PDA {
private:
    std::vector<PDAItem*> items; // All tasks, reminders, notes stored together
    int nextId;                  // Auto-increments to give each item a unique ID

    // File paths for persistent storage
    const std::string taskFile     = "data/tasks.txt";
    const std::string reminderFile = "data/reminders.txt";
    const std::string noteFile     = "data/notes.txt";

public:
    // Constructor and destructor
    PDA();
    ~PDA(); // Must free all PDAItem* pointers to avoid memory leaks

    // Core operations
    void addItem(PDAItem* item);
    void removeItem(int id);           // Asks for confirmation before deleting
    void listItems(const std::string& type = "all"); // "all", "task", "reminder", "note"
    void search(const std::string& keyword);         // Searches title and content

    // Task-specific
    void markTaskComplete(int id);

    // Reminder-specific
    void showDueReminders(); // Checks system time and lists what is due today

    // Persistent storage
    void saveAll();  // Writes all items to their respective files
    void loadAll();  // Reads all items from files on startup

    // Utility
    int generateId(); // Returns nextId and increments it
};

#endif