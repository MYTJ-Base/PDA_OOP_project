#ifndef STORAGE_H
#define STORAGE_H

#include <string>

class Storage {
public:
    Storage(const std::string &dir);
    bool saveAll();
    bool loadAll();

private:
    std::string directory;
};

#endif // STORAGE_H
