#ifndef PARENT_H
#define PARENT_H
#include <string>
#include "attribute.h"


class Parent
{
public:
    Parent();
    ~Parent();
    void rename(std::string new_name);
    void moveTo();
    std::string name;
    Attribute *atr;
    //Folder parent;
};

#endif // PARENT_H
