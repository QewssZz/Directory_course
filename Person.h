#pragma once
#include <string>
//#include "Institution.h"

class Institution;
enum class Gender { male, female };
class Person
{
public:
    Person(const std::string&, const Gender, Institution* = NULL);
    void ChangeFullName(std::string&);
private:
    std::string fullName;
    Gender gender;
    Institution* institution;
};

