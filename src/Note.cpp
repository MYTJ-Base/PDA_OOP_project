#include "Note.h"
#include <iostream>
#include <sstream>
#include "PDAItem.h"

// Constructor
// Calls PDAItem parent constructor with id and title,
// then initialises content and creationDate.

Note::Note(): PDAItem(0, "Hello"), content("This is a default note"), creationDate(""){}

Note::Note(int id, const std::string& title, const std::string& content, const std::string& creationDate)
: PDAItem(id, title){
    setContent(content);
    setCreationDate(creationDate);
}

// Returns the full body text of the note.
std::string Note::getContent() const {
    return content;
}

// Returns the creation date of the note in YYYY-MM-DD format.
std::string Note::getCreationDate() const {
    return creationDate;
}

// Updates the body text. Rejects empty strings with an error message.
void Note::setContent(const std::string& content) {
    if (content.empty()) {
        std::cerr << "Error: Note content cannot be empty.\n";
        return;
    }
    this->content = content;
}

// Stores the given string as the note's creation date (YYYY-MM-DD).
void Note::setCreationDate(const std::string& date) {
    creationDate = date;
}

// Prints the note's ID, title, creation date, and content to the terminal.
void Note::display() const {
    std::cout << "------------------------------\n";
    std::cout << "[Note]ID: " << getId() << "\n";
    std::cout << "Title: " << getTitle() << "\n";
    std::cout << "Created: " << creationDate << "\n";
    std::cout << "Content: " << content << "\n";
    std::cout << "------------------------------\n";
}

// Writes one pipe-delimited line to the output file:
// ID|Title|CreationDate|Content
void Note::saveToFile(std::ofstream& file) const {
    file << getId() << "|"
         << getTitle() << "|"
         << creationDate << "|"
         << content << "\n";
}

// Reads one pipe-delimited line from the input file and
// fills all fields. getline captures content with spaces correctly.
void Note::loadFromFile(std::ifstream& file) {
    std::string line;
    if (!std::getline(file, line)) 
    return;
    std::istringstream ss(line);
    std::string idStr, titleStr, dateStr, contentStr;
    std::getline(ss, idStr,'|');
    std::getline(ss, titleStr,'|');
    std::getline(ss, dateStr,'|');
    std::getline(ss, contentStr);
    setId(std::stoi(idStr));
    setTitle(titleStr);
    creationDate = dateStr;
    content = contentStr;
}

std::string Note::getType()const{
    return "note";    
}

