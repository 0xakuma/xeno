#pragma once;

#include <cstddef>
#include <vector>

class File
{
public:
    File(const char *filename);
    ~File();

    void open();
    void close();
    std::vector<char> read(size_t size);
    bool isOpen() const;

private:
    std::ifstream file;
    size_t fileSize;
    bool openFlag;
};