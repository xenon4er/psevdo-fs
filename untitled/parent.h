#ifndef PARENT_H
#define PARENT_H
#include <string>
#include "attribute.h"


class Parent
{
public:
    Parent();

    //virtual void rename() = 0;
    std::string name;
    Attribute *atr;
    //Folder parent;
};

#endif // PARENT_H
