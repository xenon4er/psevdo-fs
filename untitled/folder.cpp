#include "folder.h"
#include <iostream>
#include <ctime>
Folder::Folder(std::string fname,std::string path)
{
    this->name = fname;
    this->atr = new Attribute(path);
}

File* Folder::newFile(std::string file_name)
{
    if(this == NULL) return 0;
    for(int i = 0; i < this->file_list.size();i++)
    {
        if(file_name.compare(this->file_list[i]->name) == 0)
        {
            std::cout << "bad name\n";
            return 0;
        }
    }
    File *f = new File(file_name,this->atr->path);
    this->file_list.push_back(f);
    this->atr->edit_date = time(0);
    return f;
}

Folder* Folder::newFolder(std::string folder_name)
{
    if(this == NULL) return 0;
    for(int i = 0; i < this->folder_list.size();i++)
    {
        if(folder_name.compare(this->folder_list[i]->name) == 0)
        {
            std::cout << "bad name\n";
            return 0;
        }
    }

    Folder* f = new Folder(folder_name,this->atr->path + this->name + "/");
    f->parent = this;
    this->folder_list.push_back(f);
    this->atr->edit_date = time(0);
    return f;
}

void Folder::viewFolder()
{
    if(this == NULL) return;
    for(int i=0;i<this->folder_list.size();i++)
    {
        std::cout << this->folder_list[i]->name << std::endl;

    }
    for(int i=0;i<this->file_list.size();i++)
    {
        std::cout << this->file_list[i]->name + "." + this->file_list[i]->extension << std::endl;
    }
}

void Folder::viewFolderInfo()
{
    if(this == NULL) return;
    std::cout << "name: " << this->name << std::endl;
    std::cout << "type: folder" << std::endl;
    std::cout << "size: " << this->getSize()<< std::endl;
    std::cout << "path: " << this->atr->path << std::endl;
    std::cout << "create date: " << ctime(&this->atr->create_date);// << std::endl;
    std::cout << "edit date: " << ctime(&this->atr->edit_date) << std::endl;
}

size_t Folder::getSize()
{
    if(this == NULL) return 0;
    size_t size = 0;
    for(int i = 0; i < this->file_list.size();i++)
    {
        size += this->file_list[i]->size;
    }
    for(int i = 0; i < this->folder_list.size();i++)
    {
        size += this->folder_list[i]->getSize();
    }
    return size;

}

Folder::~Folder()
{
    delete this->atr;
    for(int i = 0; i < this->file_list.size();i++)
    {
        delete this->file_list[i];
    }
    for(int i = 0; i < this->folder_list.size();i++)
    {
        delete this->folder_list[i];
    }

}
