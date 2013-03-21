#include "file.h"
#include <iostream>

File::File()
{
    this->name = "sd";
    this->extension = "txt";
}
File::File(std::string fname, std::string path)
{
    this->name = fname;
    this->extension = "txt";
    this->atr = new Attribute(path);
    this->size = sizeof(*this) + sizeof(*this->atr);

}

void File::viewFileInfo()
{
    if(this == NULL) return;
    std::cout << "name: " << this->name + "." + this->extension << std::endl;
    std::cout << "type: file" << std::endl;
    std::cout << "size: " << this->size << std::endl;
    std::cout << "path: " << this->atr->path << std::endl;
    std::cout << "create date: " << ctime(&this->atr->create_date);// << std::endl;
    std::cout << "edit date: " << ctime(&this->atr->edit_date) << std::endl;
}

File::~File(){
    delete this->atr;
}
