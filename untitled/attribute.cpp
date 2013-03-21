#include "attribute.h"

Attribute::Attribute()
{
    //this->test = "ololo";
}

Attribute::Attribute(std::string path)
{
    this->path = path;
    this->create_date = time(0);
    this->edit_date = time(0);
}

