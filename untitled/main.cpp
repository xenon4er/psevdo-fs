#include <iostream>
#include "parent.h"
#include "link.h"
#include "file.h"
#include "folder.h"
#include <ctime>
#include <unistd.h>

#include <vector>

int main()
{
    //create root directory
    Folder* root = new Folder("root","/");
    ////////////////////////////////////
    File* currentFile;
    Folder* currentFolder = root;
    // sleep(5);
    std::string com = "";
    while(com.compare("exit") != 0)
    {
        std::cout << currentFolder->atr->path + currentFolder->name  << "/: ";
        std::cin >> com;

        if(com.compare("help") == 0)
        {
            std::cout << "mkdir dirname - create folder\n"
                      << "ls - view folder\n"
                      << "cd dirname or .. - tuda-cyda = )\n"
                      << "movefile filename /root/......\n"
                      << "movedir dirname /root/...... \n"
                      << "touch filename - create file \n"
                      << "renamedir foldername\n"
                      << "renamefile filename\n"
                      << "rmdir dirname\n"
                      << "rmfile filename\n"
                      << "fileinfo filename - info of file\n"
                      << "dirinfo foldername - info of folder\n"
                      << "dirlink linkname dirname type (0 or 1)"
                      << "filelink linkname filename type (0 or 1)"
                      << "exit\n";
        }


        if(com.compare("mkdir") == 0)  // новая папка
        {
            std::string name;
            //std::cout << "input name: ";
            std::cin >> name;
            currentFolder->newFolder(name);
        }

        if(com.compare("ls") == 0)  // просмотр папки
        {
            currentFolder->viewFolder();
        }

        if(com.compare("cd") == 0)  // перейти
        {
            std::string name;
            //std::cout << "input name: ";
            std::cin >> name;
            currentFolder = currentFolder->cd(name);

        }

        if(com.compare("movefile") == 0)  // переместить файл
        {
            std::string name;
            std::string path;
            std::cin >> name;
            std::cin >> path;
            currentFolder->moveTo(root, name, path, '1');
        }


        if(com.compare("movedir") == 0)  // переместить папку
        {
            std::string name;
            std::string path;
            std::cin >> name;
            std::cin >> path;
            currentFolder->moveTo(root, name, path, '2');
        }



        if(com.compare("touch") == 0)  // создать файл
        {
            std::string name;
            std::cin >> name;
            currentFolder->newFile(name);
        }

        if(com.compare("renamedir") == 0) // переименовать папку
        {
            std::string old_name;
            std::cin >> old_name;
            std::string new_name;
            std::cin >>new_name;
            currentFolder->rename(old_name,new_name);
        }

        if(com.compare("renamefile") == 0) // переименовать файл
        {
            std::string old_name;
            std::cin >> old_name;
            std::string new_name;
            std::cin >>new_name;
            currentFolder->renameFile(old_name,new_name);
        }

        if(com.compare("rmdir") == 0) // удалить папку
        {
            std::string name;
            std::cin >> name;
            currentFolder->rmDir(name);
        }

        if(com.compare("rmfile") == 0) // удалить файл
        {
            std::string name;
            std::cin >> name;
            currentFolder->rmFile(name);
        }

        if(com.compare("fileinfo") == 0) // инфо о файле
        {
            std::string name;
            std::cin >> name;
            for(int i = 0; i < currentFolder->file_list.size(); i++)
            {
                if(name.compare(currentFolder->file_list[i]->name) == 0)
                {
                    currentFolder->file_list[i]->viewFileInfo();
                }
            }
        }

        if(com.compare("dirinfo") == 0) // инфо о папке
        {
            std::string name;
            std::cin >> name;
            for(int i = 0; i < currentFolder->folder_list.size(); i++)
            {
                if(name.compare(currentFolder->folder_list[i]->name) == 0)
                {
                    currentFolder->folder_list[i]->viewFolderInfo();
                }
            }
        }

        if(com.compare("dirlink") == 0) // инфо о папке
        {
            std::string name;
            std::cin >> name;
            std::string dirname;
            std::cin >> dirname;
            int type = 0;
            std::cin >> type;
            currentFolder->setLinkFolder(name,dirname,type);
        }

        if(com.compare("filelink") == 0) // инфо о папке
        {
            std::string name;
            std::cin >> name;
            std::string filename;
            std::cin >> filename;
            int type = 0;
            std::cin >> type;
            currentFolder->setLinkFile(name,filename,type);
        }

        if(com.compare("rmlink") == 0) // инфо о папке
        {
            std::string name;
            std::cin >> name;
            for(int i = 0; i <currentFolder->linklist.size();i++)
            {
                if(name.compare(currentFolder->linklist[i]->name)==0)
                {
                    delete currentFolder->linklist[i];
                    currentFolder->linklist.erase(currentFolder->linklist.begin() + i);
                }
            }
        }

        if(com.compare("edit") == 0)
        {
            std::string name;
            std::cin >> name;
            std::string text;

            if((currentFile = currentFolder->getFile(name))!=0)
            {
                std::cin>>text;
                currentFile->edit(text);
            }else
            {
                std::cout << "bad name\n";
            }


        }

        if(com.compare("cat")==0)
        {
            std::string name;
            std::cin >> name;
            if((currentFile = currentFolder->getFile(name))!=0)
            {
                currentFile->cat();
            }
            else
            {
                std::cout << "bad name\n";
            }
        }

    }
    return 0;
}

