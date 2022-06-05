#include "Subscriber.h"
#include <algorithm>

Subscriber::Subscriber(SubscriberType st) : subscriberType(st) 
{
    
}
void Subscriber::AddPhone(Phone* ptrPhone)
{
    phones.push_back(ptrPhone);
}
void Subscriber::AddEmail(std::string e_mail)
{
    emails.push_back(e_mail);
}
void Subscriber::RemovePhone(const Phone& phone)
{
    /*auto found = find(phones.begin(), phones.end(), phone);
    if (found != phones.end()) 
    {
        phones.erase(found);
    }*/
}
void Subscriber::RemoveEmail(const std::string& email)
{
    /*auto found = find(emails.begin(), emails.end(), email);
    if(found != email.end())
    {
        emails.erase(found);
    }*/
}

//auto FindPhone(const Phone&) const;
//auto FindEmail(const std::string&) const;

void Subscriber::ChangeMainPhone(Phone* phone)
{
    phones.insert(phones.begin(), phone);
}

IndividualSubscriber::IndividualSubscriber(Person* ptrPers) :
    Subscriber(SubscriberType::individual), persSubscriber(ptrPers) 
{
    
}
void IndividualSubscriber::ChangeSubscriberTitle(std::string& newFullName)
{
    persSubscriber->ChangeFullName(newFullName);
}

InstitutionSubscriber::InstitutionSubscriber(Institution* ptrInst) :
    Subscriber(SubscriberType::institution), instSubscriber(ptrInst) 
{

}
void InstitutionSubscriber::ChangeSubscriberTitle(std::string& newFullName)
{
    instSubscriber->ChangeTitle(newFullName);
}


