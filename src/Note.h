#ifndef NOTE_H
#define NOTE_H

#include "PDAItem.h"
#include <string>
#include <fstream>

// Represents a text note with a body and an automatic creation date
class Note : public PDAItem {
private:
    std::string content;      // The full body text of the note
    std::string creationDate; // Format: YYYY-MM-DD, set automatically on creation

public:
    // Constructor
    Note(int id,
         const std::string& title,
         const std::string& content,
         const std::string& creationDate);

    // Getters
    std::string getContent() const;
    std::string getCreationDate() const;

    // Setters with validation
    // content must not be empty
    void setContent(const std::string& content);
    void setCreationDate(const std::string& date);

    // Inherited interface — must implement all three
    void display() const override;
    void saveToFile(std::ofstream& file) const override;
    void loadFromFile(std::ifstream& file) override;
};

#endif // NOTE_H