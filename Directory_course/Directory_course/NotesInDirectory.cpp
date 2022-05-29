#include "NotesInDirectory.h"

using namespace std;

string NotesInDirectory::GetFirstEmail() const 
{
	return e_mails.front();
}

Phone NotesInDirectory::GetPhone() const 
{
	return phone;
}

string NotesInDirectory::GetEmail() const 
{
	return email;
}

