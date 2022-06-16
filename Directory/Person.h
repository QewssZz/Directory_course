#pragma once
#include <string>
#include "Institution.h"

class Institution;
enum class Gender { male, female };
class Person
{
public:
    Person(const std::string&, const Gender, Institution* = NULL);
    void ChangeFullName(std::string&);
    std::string To_String() const;
    std::string GetFullName() const;
    std::string GetGender() const;
private:
    std::string fullName;
    Gender gender;
    Institution* institution;
    bool isCorrectFullName(const std::string&) const;
};

