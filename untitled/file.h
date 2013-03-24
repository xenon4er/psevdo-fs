#ifndef FILE_H
#define FILE_H
#include "parent.h"
#include <string>


class File:public Parent
{
private:
    File();
public:
    File(std::string fname,std::string path);
    ~File();
    size_t size;
    void rename(std::string new_name);
    void edit(std::string text);
    void viewFileInfo();
    void cat();
    std::string text;
    std::string extension;
};

#endif // FILE_H
