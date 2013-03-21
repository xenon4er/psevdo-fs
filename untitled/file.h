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
    void edit();
    void viewFileInfo();
    std::string extension;
};

#endif // FILE_H
