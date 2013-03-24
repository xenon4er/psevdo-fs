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
    for(unsigned int i = 0; i < this->file_list.size();i++)
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

Folder *Folder::findFolder(Folder *root, std::string path)
{
    Folder *currentFolder = root;
    std::string tmp_str = path, tmp_path = "";
    bool is_found = false;
    int i = 0;
    while(i < tmp_str.size())
    {
        if(tmp_str[i] != '/')
        {
            tmp_path.push_back(tmp_str[i]);
        }
        else
        {
            for(int j= 0; j < currentFolder->folder_list.size(); j ++)
            {
                is_found = false;
                if(tmp_path.compare(currentFolder->folder_list[j]->name) == 0)
                {
                    currentFolder = currentFolder->folder_list[j];
                    is_found = true;
                    continue;
                }
            }

            tmp_path = "";
        }
        i++;
    }
    return is_found ? currentFolder : 0;
}

void Folder::moveTo(Folder *root, std::string name, std::string path, char type)
{
    //нужно организовать поиск куда переместить

    Folder *addFolder;
    if((addFolder= this->findFolder(root,path)) == 0 )
    {
        std::cout << "bad path\n";
        return;
    }

    File *file;
    Folder *folder;
    bool is_found = false;
    switch(type)
    {
    case '1':  //file
        // поиск файла и его удаление из этой папки
        for(int i = 0; i < this->file_list.size();i++)
        {
            if(name.compare(this->file_list[i]->name) == 0)
            {
                file = this->file_list[i];
                this->file_list.erase(this->file_list.begin() + i);
                is_found = true;
            }
        }
        addFolder->file_list.push_back(file);
        break;
    case '2': // folder
        // поиск папки и ее удаление из этой папки
        for(int i = 0; i < this->folder_list.size();i++)
        {
            if(name.compare(this->folder_list[i]->name) == 0)
            {
                folder = this->folder_list[i];
                this->folder_list.erase(this->folder_list.begin() + i);
                is_found = true;
                //continue;
            }
        }
        addFolder->folder_list.push_back(folder);
        break;
    default:  //other
        return;
        break;
    }

    if(!is_found)
    {
        std::cout << "not found\n";
        return;
    }
}

void Folder::rmFile(std::string name)
{
    bool is_found = false;
    for(int i = 0; i < this->file_list.size(); i++)
    {
        if(name.compare(this->file_list[i]->name)==0)
        {
            delete this->file_list[i];
            this->file_list.erase(this->file_list.begin() + i);
            is_found = true;
            continue;
        }
    }
    if(!is_found)
    {
        std::cout << "bad name\n";
    }
}

void Folder::rmDir(std::string name)
{
    bool is_found = false;
    for(int i = 0; i < this->folder_list.size(); i++)
    {
        if(name.compare(this->folder_list[i]->name)==0)
        {
            delete this->folder_list[i];
            //this->folder_list.erase(this->folder_list.begin() + i);
            is_found = true;
            continue;
        }
    }
    if(!is_found)
    {
        std::cout << "bad name\n";
    }
}
////////////////////////////////////////////////////////////////////////////////////////////
void Folder::setLinkFolder(std::string linkname, std::string dirname, int type)  ///////////
{
    for(int i = 0; i < this->folder_list.size();i++)
    {
        if(dirname.compare(this->folder_list[i]->name)==0)
        {
            Link *l = new Link(linkname,type,this->folder_list[i]);
            this->linklist.push_back(l);
        }
    }
}

void Folder::setLinkFile(std::string linkname, std::string filename, int type)
{
    for(int i = 0; i < this->file_list.size();i++)
    {
        if(filename.compare(this->file_list[i]->name)==0)
        {
            Link *l = new Link(linkname,type,this->file_list[i]);
            this->linklist.push_back(l);
        }
    }
}

File *Folder::getFile(std::string name)
{
    bool is_found = false;
    File *f;
    for(int i = 0; i < this->file_list.size();i++)
    {
        if(name.compare(this->file_list[i]->name) == 0)
        {
            is_found = true;
            f = this->file_list[i];
        }
    }
    return (is_found) ? f : 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Folder* Folder::cd(std::string name)
{
    Folder *currentFolder = this;
    bool is_found = false;
    if(name.compare("..") == 0)
    {
        currentFolder = this->parent;
        is_found = true;
    }
    else
    {
        for(int i = 0; i < this->folder_list.size(); i++)
        {
            if(name.compare(this->folder_list[i]->name) == 0)
            {
                currentFolder = this->folder_list[i];
                is_found = true;
            }
        }
    }

    if(!is_found)
    {
        std::cout << "not found\n";
    }
    return currentFolder;
}

void Folder::rename(std::string old_name, std::string new_name)
{
    Folder *f;
    bool is_found = false;
    for(int i=0;i<this->folder_list.size();i++)
    {
        if(new_name.compare(this->folder_list[i]->name) == 0)
        {
            std::cout << "bad name\n";
            return;
        }
        if(old_name.compare(this->folder_list[i]->name) == 0)
        {
            f = this->folder_list[i];
            is_found = true;
        }

    }
    if(is_found)
    {
        f->name = new_name;
    }
}


void Folder::renameFile(std::string old_name, std::string new_name)
{
    File *f;
    bool is_found = false;
    for(int i=0;i<this->folder_list.size();i++)
    {
        if(new_name.compare(this->file_list[i]->name) == 0)
        {
            std::cout << "bad name\n";
            return;
        }
        if(old_name.compare(this->file_list[i]->name) == 0)
        {
            f = this->file_list[i];
            is_found = true;
        }

    }
    if(is_found)
    {
        f->rename(name);
    }
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

    for(int i=0;i<this->linklist.size();i++)
    {
        std::cout << this->linklist[i]->name + " -- link" << std::endl;
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
    for(int i = 0; i < this->parent->folder_list.size();i++)
    {
        if(this->name.compare(this->parent->folder_list[i]->name)==0)
        {
            this->parent->folder_list.erase(this->parent->folder_list.begin()+i);
        }
    }

    for(int i = 0; i < this->file_list.size();i++)
    {
        delete this->file_list[i];
        this->file_list.erase(this->file_list.begin() + i);

    }

    for(int i = 0; i < this->linklist.size();i++)
    {
        delete this->linklist[i];
        this->linklist.erase(this->linklist.begin() + i);
    }

    for(int i = 0; i < this->folder_list.size();i++)
    {
        delete this->folder_list[i];
        this->folder_list.erase(this->folder_list.begin() + i);
    }

}



