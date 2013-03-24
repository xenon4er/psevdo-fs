#ifndef FOLDER_H
#define FOLDER_H
#include "parent.h"
#include "file.h"
#include "link.h"
#include <vector>


class Link;
class Folder : public Parent
{
private:
    Folder();
    Folder *findFolder(Folder *root, std::string path);
public:
    Folder(std::string fname,std::string path);
    ~Folder();
    Folder* newFolder(std::string folder_name);
    File* newFile(std::string file_name);
    void rename(std::string old_name, std::string new_name);
    void renameFile(std::string old_name, std::string new_name);
    void viewFolder();
    void viewFolderInfo();
    void moveTo(Folder *root, std::string name,std::string path, char type);
    void rmFile(std::string name);
    void rmDir(std::string name);
    void setLinkFolder(std::string linkname, std::string dirname, int type);
    void setLinkFile(std::string linkname, std::string filename, int type);
    File *getFile(std::string name);
    Folder* cd(std::string name);
    size_t getSize();
    Folder *parent;
    std::vector<File *> file_list;
    std::vector<Folder *> folder_list;
    std::vector<Link *> linklist;
};

#endif // FOLDER_H
