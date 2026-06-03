#include <iostream>
#include <string>
#include "PDAItem.h"

PDAItem::PDAItem(int id, const std::string& title){
    // Constructor implementation
    setId(id);
    setTitle(title);
}

int PDAItem::getId()const {
    return id;
}

std::string PDAItem::getTitle()const {
    return title;
}

void PDAItem::setId(int id){
    if (id > 0){
        this->id = id;}
}

void PDAItem::setTitle(const std::string& title){
    if (title.length() > 0){
        this->title = title;
    }
}