#ifndef PDAITEM_H
#define PDAITEM_H

#include <string>

// Abstract base class for all PDA items (Tasks, Reminders, Notes)
// Provides shared attributes and enforces a common interface
class PDAItem {
private:
    int id;           // Unique identifier for each item
    std::string title; // Short title or label for the item

public:
    // Constructor
    PDAItem(int id, const std::string& title);

    // Virtual destructor (required when using inheritance + pointers)
    virtual ~PDAItem();

    // Getters
    int getId() const;
    std::string getTitle() const;

    // Setters with validation (empty string must be rejected)
    void setId(int id);
    void setTitle(const std::string& title);

    // Pure virtual methods — every subclass MUST implement these
    virtual void display() const = 0;
    virtual void saveToFile(std::ofstream& file) const = 0;
    virtual void loadFromFile(std::ifstream& file) = 0;
    virtual std::string getType() const = 0;
};

#endif