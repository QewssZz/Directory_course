#include "Subscriber.h"
#include <algorithm>
#include <stdexcept>
#include <vector>
//using namespace std;
Subscriber::Subscriber(SubscriberType st) : subscriberType(st) 
{}

Subscriber::Subscriber(SubscriberType st, std::vector<Phone*>& vPhone, std::vector<std::string>& vEmail) 
    : subscriberType(st), phones(vPhone), emails(vEmail)
{}

void Subscriber::AddPhone(Phone* ptrPhone)
{
    auto found = find(phones.begin(), phones.end(), ptrPhone);
    if (found != phones.end())
    {
        throw std::invalid_argument("Phone xist)");
    }
    phones.push_back(ptrPhone);
}

void Subscriber::AddEmail(std::string e_mail)
{
    auto found = find(emails.begin(), emails.end(), e_mail);
    if (found != emails.end())
    {
        throw std::invalid_argument("Email exist");
    }
    emails.push_back(e_mail);
}

/*bool Subscriber::FindByPhone(const Phone* phone)const
{
    return (find(phones.begin(), phones.end(), phone) != phones.end());
}*/

bool Subscriber::FindByPhone(const std::string& phone)const
{
    auto p = phones.begin();
    for (; p != phones.end() && !((*p)->Full() == phone); p++);
    return (p != phones.end());     
}

bool Subscriber::FindByEmail(const std::string& email)const
{
    return (find(emails.begin(), emails.end(), email) != emails.end());
}

void Subscriber::RemovePhone(const std::string& phone)
{
    auto p = phones.begin();
    for (; p != phones.end() && !((*p)->Full() == phone); p++);
    if (p == phones.end()) 
    {
        throw std::invalid_argument("Don`t exist");
    }
    delete (*p);
    phones.erase(p);
}

void Subscriber::RemoveEmail(const std::string& email)
{
    auto found = find(emails.begin(), emails.end(), email);
    if (found != emails.end())
    {
        emails.erase(found);
    }    
}

std::string Subscriber::To_String() const 
{
    std::string result = (subscriberType == SubscriberType::individual ? "Individual" : "Institution");
    result += '\n';
    for (const auto& i : phones)
    {
        result += (i->Full() + '\n');
    }
    for (const auto& i : emails) 
    {
        result += (i + '\n');
    }
    return result;
}

void Subscriber::ChangeMainPhone(Phone* phone)
{
    auto found = find(phones.begin(), phones.end(), phone);
    if (found == phones.end())
    {
        phones.insert(phones.begin(), phone);
        return;
    }
    Phone* tmp = phones.front();
    phones.front() = phone;
    *found = tmp;
}

SubscriberType Subscriber::GetSubsType() const { return subscriberType; }

IndividualSubscriber::IndividualSubscriber(Person* ptrPers) :
    Subscriber(SubscriberType::individual), persSubscriber(ptrPers) 
{}

IndividualSubscriber::IndividualSubscriber(Person* ptrPers, std::vector<Phone*>& vPhone, std::vector<std::string>& vEmail) :
    Subscriber(SubscriberType::individual, vPhone, vEmail), persSubscriber(ptrPers)
{}

void IndividualSubscriber::ChangeSubscriberTitle(std::string& newFullName)
{
    persSubscriber->ChangeFullName(newFullName);
}

std::string IndividualSubscriber::To_String() const 
{
    std::string result = Subscriber::To_String() + persSubscriber->To_String() + '\n';
    return result;
}

std::string IndividualSubscriber::GetName() 
{
    return this->persSubscriber->GetFullName();
}

InstitutionSubscriber::InstitutionSubscriber(Institution* ptrInst) :
    Subscriber(SubscriberType::institution), instSubscriber(ptrInst) 
{}

InstitutionSubscriber::InstitutionSubscriber(Institution* ptrInst, std::vector<Phone*>& vPhone, std::vector<std::string>& vEmail) :
    Subscriber(SubscriberType::institution, vPhone, vEmail), instSubscriber(ptrInst) 
{}

void InstitutionSubscriber::ChangeSubscriberTitle(std::string& newFullName)
{
    instSubscriber->ChangeTitle(newFullName);
}

std::string InstitutionSubscriber::To_String() const
{
    std::string result = Subscriber::To_String() + instSubscriber->To_String() + '\n';
    return result;
}

std::string InstitutionSubscriber::GetName()
{
    return this->instSubscriber->GetTitle();
}






