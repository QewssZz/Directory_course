#pragma once
//#include <string>
#include <vector>
#include "Phone.h"
#include "Person.h"
#include "Institution.h"

enum class SubscriberType { individual, institution };
class Subscriber
{
public:
    Subscriber(/*vector<Phone>&, vector<string>&,*/
        SubscriberType);
    void AddPhone(Phone*);
    void AddEmail(std::string);

    void RemovePhone(const Phone&);
    void RemoveEmail(const std::string&);

    //auto FindPhone(const Phone&) const;
    //auto FindEmail(const std::string&) const;

    void ChangeMainPhone(Phone*);
    virtual void ChangeSubscriberTitle(std::string&) = 0;
private:
    SubscriberType subscriberType;
    std::vector<Phone*> phones;
    std::vector<std::string> emails;
};

class IndividualSubscriber : public Subscriber
{
public:
    IndividualSubscriber(Person*/*, vector<Phone>, vector<string>*/);
    void ChangeSubscriberTitle(std::string&) override;
private:
    Person* persSubscriber;
};

class InstitutionSubscriber : public Subscriber 
{
public:
    InstitutionSubscriber(Institution* /*, vector<Phone>, vector<string>&*/);
    void ChangeSubscriberTitle(std::string&) override;
private:
    Institution* instSubscriber;
};