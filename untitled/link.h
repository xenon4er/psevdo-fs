
#ifndef LINK_H
#define LINK_H
//#define HARD 0
//#define SOFT 1

#include "file.h"
#include "folder.h"


class Folder;
class Link
{
private:
    Link();
public:
    Link(std::string name,int type, Folder *folder);
    Link(std::string name,int type, File *file);
    ~Link();
    std::string name;
    int type;
    Folder* link_to_folder;
    File* link_to_file;
};

#endif // LINK_H
