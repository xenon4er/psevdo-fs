#include "link.h"

Link::Link(std::string name, int type, Folder *folder)
{
    this->name = name;
    this->type = type;
    this->link_to_folder = folder;
}

Link::Link(std::string name, int type, File *file)
{
    this->name = name;
    this->type = type;
    this->link_to_file = file;
}

Link::~Link()
{
    if(this->type == 1)
    {
        delete this->link_to_file;
        delete this->link_to_folder;
    }
}

