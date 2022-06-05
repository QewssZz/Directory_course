#include "Institution.h"
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
