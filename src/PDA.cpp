#include "PDA.h"
#include "Task.h"
#include "Reminder.h"
#include "Note.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

// Constructor initialization
PDA::PDA() : nextId(1) {}

// Destructor cleanup to properly free dynamic memory
PDA::~PDA()
{
    for (PDAItem* item : items) {
        delete item;
    }
    items.clear();
}

 /* @brief Generates a unique identifier and increments the internal counter.
 * @return The unique identifier as an integer (int).
 */

int PDA::generateId()
{
    return nextId++;
}

/**
 * @brief Adds a new PDA item to the internal collection.
 * @param item Pointer to the PDAItem object (Task, Reminder, or Note) to add.
 */

void PDA::addItem(PDAItem* item)
{
    if (item != nullptr) {
        items.push_back(item);
    }
}

/**
 * @brief Finds an item by its ID, asks for confirmation, then removes it.
 * @param id The unique identifier of the item to remove.
 */
void PDA::removeItem(int id)
{
    auto it = std::find_if(items.begin(), items.end(), [id](PDAItem* item) {
        return item->getId() == id;
    });

    if (it != items.end()) {
        std::cout << "Are you sure you want to delete the item titled '"
                  << (*it)->getTitle() << "'? (y/n): ";
        char confirmation;
        std::cin >> confirmation;

        if (confirmation == 'y' || confirmation == 'Y') {
            delete *it; // Free dynamic memory
            items.erase(it); // Remove from the vector
            std::cout << "Item deleted successfully.\n";
        } else {
            std::cout << "Deletion cancelled.\n";
        }
    } else {
        std::cout << "No item found with ID: " << id << "\n";
    }
}

/**
 * @brief Lists stored items while applying a filter on their type.
 * @param type The item type to display ('task', 'reminder', 'note', or 'all').
 */
void PDA::listItems(const std::string& type) const 
{
    bool found = false;
    std::cout << "\n--- Item list (" << type << ") ---\n";

    for (const PDAItem* item : items) {
        std::string itemType = item->getType(); // Supposant que getType() existe et retourne "task", "reminder" ou "note"

        if (type == "all" || itemType == type) {
            item->display(); // Call the virtual display method
            std::cout << "-----------------------\n";
            found = true;
        }
    }

    if (!found) {
        std::cout << "No items of type '" << type << "' to display.\n";
    }
}

/**
 * @brief Searches and displays items whose title contains a keyword.
 * @param keyword The keyword to search for in titles.
 */
void PDA::search(const std::string& keyword) 
{
    bool found = false;
    std::cout << "\n--- Search results for: \"" << keyword << "\" ---\n";

    for (const PDAItem* item : items) {
        // Case-insensitive search or simple substring match
        if (item->getTitle().find(keyword) != std::string::npos) {
            item->display();
            std::cout << "-----------------------\n";
            found = true;
        }
    }

    if (!found) {
        std::cout << "No items match your search.\n";
    }
}

/**
 * @brief Marks a task as completed by its ID.
 * @param id The identifier of the task to update.
 */
void PDA::markTaskComplete(int id)
{
    for (PDAItem* item : items) {
        if (item->getId() == id && item->getType() == "task") {
            // Safe dynamic cast to access the Task-specific method
            Task* task = dynamic_cast<Task*>(item);
            if (task != nullptr) {
                task->markComplete();
                std::cout << "Task ID " << id << " has been marked complete.\n";
                return;
            }
        }
    }

    std::cout << "Task not found with ID: " << id << "\n";
}

/**
 * @brief Iterates over and displays all reminders that are due.
 */
void PDA::showDueReminders() const
{
    bool found = false;
    std::cout << "\n--- Urgent / due reminders ---\n";

    for (const PDAItem* item : items) {
        if (item->getType() == "reminder") {
            const Reminder* reminder = dynamic_cast<const Reminder*>(item);
            if (reminder != nullptr && reminder->isDueNow()) {
                reminder->display();
                std::cout << "-----------------------\n";
                found = true;
            }
        }
    }

    if (!found) {
        std::cout << "No reminders are due at the moment.\n";
    }
}
void PDA::saveAll() {
    std::ofstream tFile(taskFile);
    std::ofstream rFile(reminderFile);
    std::ofstream nFile(noteFile);

    for (const PDAItem* item : items) {
        if (item->getType() == "task") item->saveToFile(tFile);
        else if (item->getType() == "reminder") item->saveToFile(rFile);
        else if (item->getType() == "note") item->saveToFile(nFile);
    }
}

void PDA::loadAll() {
    // Clear existing items
    for (PDAItem* item : items) delete item;
    items.clear();
    nextId = 1;

    // Load Tasks
    std::ifstream tFile(taskFile);
    if (tFile.is_open()) {
        while (tFile.peek() != EOF) {
            Task* task = new Task(0, "temp", "2000-01-01", "Low", false);
            task->loadFromFile(tFile);
            if (task->getId() > 0) {
                addItem(task);
                if (task->getId() >= nextId) nextId = task->getId() + 1;
            } else {
                delete task;
            }
        }
        tFile.close();
    }

    // Load Reminders
    std::ifstream rFile(reminderFile);
    if (rFile.is_open()) {
        while (rFile.peek() != EOF) {
            Reminder* reminder = new Reminder(0, "temp", "2000-01-01 00:00", "temp", false);
            reminder->loadFromFile(rFile);
            if (reminder->getId() > 0) {
                addItem(reminder);
                if (reminder->getId() >= nextId) nextId = reminder->getId() + 1;
            } else {
                delete reminder;
            }
        }
        rFile.close();
    }

    // Load Notes
    std::ifstream nFile(noteFile);
    if (nFile.is_open()) {
        while (nFile.peek() != EOF) {
            Note* note = new Note(0, "temp", "temp", "2000-01-01");
            note->loadFromFile(nFile);
            if (note->getId() > 0) {
                addItem(note);
                if (note->getId() >= nextId) nextId = note->getId() + 1;
            } else {
                delete note;
            }
        }
        nFile.close();
    }
}

void PDA::loadSampleData() {
    std::string sampleDir = "../sample_data/";
    
    // Check if ../sample_data exists, otherwise try sample_data/
    std::ifstream testFile(sampleDir + "sample_tasks.txt");
    if (!testFile.is_open()) {
        sampleDir = "sample_data/";
    } else {
        testFile.close();
    }

    // Load Tasks
    std::ifstream tFile(sampleDir + "sample_tasks.txt");
    if (tFile.is_open()) {
        std::string line;
        int count = 0;
        while (std::getline(tFile, line)) {
            if (line.empty()) continue;
            std::stringstream ss(line);
            std::string title, dueDate, completedStr;
            std::getline(ss, title, ';');
            std::getline(ss, dueDate, ';');
            std::getline(ss, completedStr, ';');
            
            bool completed = (completedStr == "true");
            addItem(new Task(generateId(), title, dueDate, "Medium", completed));
            count++;
        }
        tFile.close();
        std::cout << "  [Test] Loaded " << count << " sample tasks.\n";
    } else {
        std::cout << "  [Error] Could not find sample_tasks.txt in " << sampleDir << "\n";
    }

    // Load Reminders
    std::ifstream rFile(sampleDir + "sample_reminders.txt");
    if (rFile.is_open()) {
        std::string line;
        int count = 0;
        while (std::getline(rFile, line)) {
            if (line.empty()) continue;
            std::stringstream ss(line);
            std::string dateTime, title;
            std::getline(ss, dateTime, ';');
            std::getline(ss, title, ';');
            
            // Format check: sample has T, we want space
            if (dateTime.length() >= 11 && dateTime[10] == 'T') {
                dateTime[10] = ' ';
            }
            // If it's only YYYY-MM-DD, add default time
            if (dateTime.length() == 10) {
                dateTime += " 00:00";
            }
            
            addItem(new Reminder(generateId(), title, dateTime, "Sample reminder: " + title, false));
            count++;
        }
        rFile.close();
        std::cout << "  [Test] Loaded " << count << " sample reminders.\n";
    } else {
        std::cout << "  [Error] Could not find sample_reminders.txt in " << sampleDir << "\n";
    }
}

void PDA::setStoragePaths(const std::string& taskPath, const std::string& reminderPath, const std::string& notePath) {
    this->taskFile = taskPath;
    this->reminderFile = reminderPath;
    this->noteFile = notePath;
}

void PDA::clearItems() {
    for (PDAItem* item : items) {
        delete item;
    }
    items.clear();
    nextId = 1;
}

bool PDA::hasItems(const std::string& type) const {
    if (type == "all") return !items.empty();
    for (const auto* item : items) {
        if (item->getType() == type) return true;
    }
    return false;
}
