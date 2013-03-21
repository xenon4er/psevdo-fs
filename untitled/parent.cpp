#include "parent.h"

Parent::Parent()
{
    this->name = "";
}

Parent::~Parent()
{

}

void Parent::rename(std::string new_name){
    this->name = new_name;
}
