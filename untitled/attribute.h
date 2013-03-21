#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <ctime>
#include <string>

class Attribute
{
private:
    Attribute();
public:
    Attribute(std::string path);
    std::string path;
    time_t create_date;
    time_t edit_date;
};

#endif // ATTRIBUTE_H
