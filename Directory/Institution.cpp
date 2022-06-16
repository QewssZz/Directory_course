#include "Institution.h"
#include "Person.h"
#include <stdexcept>
using namespace std;

Institution::Institution(const std::string& ttl, const std::string& kA, Person* lead) :
    title(ttl), kindOfActivity(kA), leader(lead) 
{
    if (ttl == "\0") { throw invalid_argument("No title of institution."); }
    if (kA == "\0") { throw invalid_argument("No activity of institution."); }
}

void Institution::ChangeTitle(const std::string& ttl)
{
    title = ttl;
}

string Institution::To_String() const 
{
    string result = "Institution: " + title + ";" + "kind of activity: " + kindOfActivity + ";";
    if (leader != NULL)
    {
        result += (" leader " + leader->To_String());
    }
    return result;
}

string Institution::GetTitle() const { return title;  }