#ifndef LINK_H
#define LINK_H

//#define HARD 0
//#define SOFT 1

#include "parent.h"

class Link
{
public:
    Link();
    int type;
    Parent link_to;
};

#endif // LINK_H
