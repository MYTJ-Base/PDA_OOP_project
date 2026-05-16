#include "Note.h"

Note::Note() : title(""), content("") {}

Note::Note(const std::string &title, const std::string &content)
    : title(title), content(content) {}
