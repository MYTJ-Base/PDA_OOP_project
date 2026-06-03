#include "PDAItem.h"
#include <iostream>

// Constructor
PDAItem::PDAItem(int id, const std::string& title) {
    this->id = id;
    this->title = title;
}

// Destructor
PDAItem::~PDAItem() {}

// Returns id
int PDAItem::getId()const {
    return id;
}

// Returns title
std::string PDAItem::getTitle()const {
    return title;
}

// Sets id
void PDAItem::setId(int id) {
    this->id = id;
}

// Sets title - rejects empty string
void PDAItem::setTitle(const std::string &title) {
    if (title.empty()) {
        std::cout << "Error: title cannot be empty." << std::endl;
        return;
        }
    this->title = title;
}