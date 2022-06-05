#include "PhoneRefBook.h"
#include <iostream>
using namespace std;

void PhoneRefBook::AddSubscriber(Subscriber* ptrSubs)
{
	subscribers.push_back(ptrSubs);
}
void PhoneRefBook::RemoveSubscriber(Subscriber* ptrSubs)
{
	auto found = find(subscribers.begin(), subscribers.end(), ptrSubs);
	if (found != subscribers.end())
	{
		subscribers.erase(found);
	}
}
/*vector<Subscriber*> PhoneRefBook::FindByPhone(const Phone&) const
{
	
}
vector<Subscriber*> PhoneRefBook::FindByEmail(const string&) const
{
}
vector<Subscriber*> PhoneRefBook::FindIndividual(const string&, bool completeMatch = true) const 
{
}*/

void PhoneRefBook::AddPhone(Subscriber* ptrSubs, Phone& ph)
{
	
}
void PhoneRefBook::AddEmail(Subscriber* ptrSubs, std::string& email)
{
	
}

void PhoneRefBook::RemovePhone(Subscriber* ptrSubs, const Phone& phone)
{
	
}
void PhoneRefBook::RemoveEmail(Subscriber* ptrSubs, const std::string& email)
{
	
}

void PhoneRefBook::ChangeSubscriberTitle(Subscriber* ptrSubs, std::string& title)
{
	
}
void PhoneRefBook::ChangeMainPhone(Subscriber* ptrSubs, Phone& phone)
{
	
}

void PhoneRefBook::Menu() 
{
	cout << "1. Add info about subscriber" << endl;
	cout << "2. Remove info about subscriber" << endl;
	cout << "3. Find subscriber" << endl;
	cout << "4. Add subscriber" << endl;
	cout << "5. ..." << endl;
	cout << "0. Exit" << endl;
}
