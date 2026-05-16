#ifndef NOTE_H
#define NOTE_H

#include <string>

class Note {
public:
    Note();
    Note(const std::string &title, const std::string &content);

    std::string title;
    std::string content;
};

#endif // NOTE_H
