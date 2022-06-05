#pragma once
#include <string>
//#include "Person.h"

class Person;
class Institution
{
public:
    Institution(const std::string&, const std::string&, Person* = NULL);
    void ChangeTitle(const std::string&);
private:
    std::string title;
    std::string kindOfActivity;
    Person* leader;
};



