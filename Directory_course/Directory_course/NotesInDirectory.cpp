#include "NotesInDirectory.h"
#include <algorithm>

using namespace std;

string NotesInDirectory::GetFirstEmail() const 
{
	return e_mails.front();
}

/*Phone NotesInDirectory::GetPhone() const
{
	return phone;
}*/

/*string NotesInDirectory::GetEmail() const
{
	return email;
}*/

void NotesInDirectory::RemoveEmail(string email)
{
	auto found = find(e_mails.begin(), e_mails.end(), email);
	if (found != e_mails.end()) 
	{
		e_mails.erase(found);
	}
}
