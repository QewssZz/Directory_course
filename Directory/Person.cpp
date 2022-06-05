#include "Person.h"
#include <stdexcept>

using namespace std;

Person::Person(const std::string& fN, const Gender gd, Institution* inst) : fullName(fN),
gender(gd), institution(inst) 
{
    if (gd != Gender::male && gd != Gender::female) 
    {
        throw invalid_argument("Other gender");
    }
}
void Person::ChangeFullName(std::string& newFullName)
{
    fullName = newFullName;
}