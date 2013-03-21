#include <iostream>
#include "parent.h"
#include "link.h"
#include "file.h"
#include "folder.h"
#include <typeinfo>
#include <ctime>
#include <unistd.h>

int main()
{
    //create root directory
    Folder* root = new Folder("root","/");
    ////////////////////////////////////
   // sleep(5);
    root->rename("root2");
    root->viewFolderInfo();

    return 0;
}

