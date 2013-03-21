#ifndef FOLDER_H
#define FOLDER_H
#include "parent.h"
#include "file.h"
#include <vector>

class Folder : public Parent
{
private:
    Folder();
public:
    Folder(std::string fname,std::string path);
    ~Folder();
    Folder* newFolder(std::string folder_name);
    File* newFile(std::string file_name);
    void viewFolder();
    void viewFolderInfo();
    size_t getSize();
    Folder *parent;
    std::vector<File *> file_list;
    std::vector<Folder *> folder_list;
};

#endif // FOLDER_H
