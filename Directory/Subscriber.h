#pragma once
//#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include "Phone.h"
#include "Person.h"
#include "Institution.h"

enum class SubscriberType { individual, institution };
class Subscriber
{
public:
    Subscriber(SubscriberType);
    Subscriber(SubscriberType, std::vector<Phone*>&, std::vector<std::string>&);

    void AddPhone(Phone*);
    void AddEmail(std::string);

    void RemovePhone(const Phone&);
    void RemoveEmail(const std::string&);

    bool FindByPhone(const Phone*)const;
    bool FindByPhone(const Phone&)const;
    bool FindByEmail(const std::string&)const;

    void ChangeMainPhone(Phone*);
    virtual void ChangeSubscriberTitle(std::string&) = 0;

    virtual std::string To_String() const;

    SubscriberType GetSubsType() const;
    virtual std::string GetName() = 0;
private:
    SubscriberType subscriberType;
    std::vector<Phone*> phones;
    std::vector<std::string> emails;
};

class IndividualSubscriber : public Subscriber
{
public:
    IndividualSubscriber(Person*);
    IndividualSubscriber(Person*, std::vector<Phone*>&, std::vector<std::string>&);
    void ChangeSubscriberTitle(std::string&) override;
    std::string To_String() const override;
    std::string GetName() override;
private:
    Person* persSubscriber;
};

class InstitutionSubscriber : public Subscriber 
{
public:
    InstitutionSubscriber(Institution* );
    InstitutionSubscriber(Institution*, std::vector<Phone*>&, std::vector<std::string>&);
    void ChangeSubscriberTitle(std::string&) override;
    std::string To_String() const override;
    std::string GetName() override;
private:
    Institution* instSubscriber;
};