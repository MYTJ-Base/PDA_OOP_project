#include "Reminder.h"
#include <iostream>
#include <sstream>
#include <ctime>

using namespace std;

// Constructor
Reminder::Reminder(int id, const string& title, const string& dateTime, const string& message, bool alarm) : PDAItem(id, title){
    setDateTime(dateTime);
    setMessage(message);
    setAlarm(alarm);
}

// Returns the date and time
string Reminder::getDateTime() const {
    return dateTime;
}

// Returns the message
string Reminder::getMessage() const {
    return message;
}

// Returns true if alarm is on
bool Reminder::hasAlarm() const {
    return alarm;
}

// Sets date and time - must follow YYYY-MM-DD HH:MM format
void Reminder::setDateTime(const string& dateTime) {
    if (dateTime.length() != 16 || dateTime[4] != '-' || dateTime[7] != '-' || dateTime[10] != ' ' || dateTime[13] != ':') {
        cout << "Error: dateTime must be in YYYY-MM-DD HH:MM format." << endl;
        return;
    }
    this->dateTime = dateTime;
}

// Sets message - rejects empty strings
void Reminder::setMessage(const string& message) {
    if (message.empty()) {
        cout << "Error: message cannot be empty." << endl;
        return;
    }
    this->message = message;
}

// Sets alarm on or off
void Reminder::setAlarm(bool alarm) {
    this->alarm = alarm;
}

// Returns true if reminder is due today or overdue
bool Reminder::isDueNow() const {
    // Get today's date from system
    time_t now = time(0);
    tm* today = localtime(&now);
    // Build today's date as a string YYYY-MM-DD
    char todayStr[11];
    strftime(todayStr, sizeof(todayStr), "%Y-%m-%d", today);
    // Compare only the date part of dateTime (first 10 characters)
    string reminderDate = dateTime.substr(0, 10);
    return reminderDate <= string(todayStr);
}

// Displays reminder details in terminal
void Reminder::display() const {
    cout << "------------------------------" << endl;
    cout << "[Reminder] ID : " << getId() << endl;
    cout << "Title : " << getTitle() << endl;
    cout << "When : " << dateTime << endl;
    cout << "Message: " << message << endl;
    cout << "Alarm : " << (alarm ? "On" : "Off") << endl;
    cout << "------------------------------" << endl;
}

// Saves reminder to file in format: ID|Title|DateTime|Message|0or1
void Reminder::saveToFile(ofstream& file) const {
    file << getId() << "|"
    << getTitle() << "|"
    << dateTime << "|"
    << message << "|"
    << (alarm ? 1 : 0)
    << "\n";
}

// Reads reminder back from file
void Reminder::loadFromFile(ifstream& file) {
    string line;
    if (!getline(file, line)) return;
    istringstream ss(line);string idStr, titleStr, dateTimeStr, messageStr, alarmStr;
    getline(ss, idStr, '|');
    getline(ss, titleStr, '|');
    getline(ss, dateTimeStr, '|');
    getline(ss, messageStr, '|');
    getline(ss, alarmStr);
    setId(stoi(idStr));
    setTitle(titleStr);
    dateTime = dateTimeStr;
    message = messageStr;
    alarm = (alarmStr == "1");
}

std::string Reminder::getType()const{
    return "reminder";    
}