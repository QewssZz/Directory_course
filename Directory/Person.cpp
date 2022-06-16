#include "Person.h"
#include "Institution.h"
#include <stdexcept>

using namespace std;

Person::Person(const std::string& fN, const Gender gd, Institution* inst) : fullName(fN),
gender(gd), institution(inst) 
{
    if (gd != Gender::male && gd != Gender::female) 
    {
        throw invalid_argument("Other gender");
    }
    // проверка имени - хотя-бы 1 пробел, а слева и справа непробельные символы, только буквы
    auto found = fullName.find(" ");
    if (found == string::npos)
    {
        throw invalid_argument("Incorrect form of name");
    }
    
    if (isCorrectFullName(fN)) 
    {
        throw invalid_argument("Incorrect form of name");
    }
}

void Person::ChangeFullName(std::string& newFullName)
{
    fullName = newFullName;
}

string Person::GetFullName() const { return fullName; }

string Person::GetGender() const 
{
    if (gender == Gender::male) 
    {
        return "male";
    }
    return "female";
}

string Person::To_String() const 
{
    string result = "Full name: " + fullName + "; " + "gender: " + GetGender() + "; " "\n";
    return result;
}

bool Person::isCorrectFullName(const string& fullName) const 
{
    size_t posFirstNotBlank = fullName.find_first_not_of(' ');
    string tmp = fullName.substr(posFirstNotBlank);
    size_t posLastNotBlank = fullName.find_last_not_of(' ');
    tmp.erase(posLastNotBlank + 1);
   
    size_t posBlank = fullName.find(' ');
    if (posBlank != string::npos) 
    {
        return false;
    }
    
    return true;
}