#pragma once
#include <vector>
//#include <string>
#include "Subscriber.h"
#include "Phone.h"

class PhoneRefBook
{
public:
    void Menu();

    void AddSubscriber(Subscriber*);
    void RemoveSubscriber(Subscriber*);

    /*std::vector<Subscriber*> FindByPhone(const Phone&) const;
    std::vector<Subscriber*> FindByEmail(const std::string&) const;
    std::vector<Subscriber*> FindIndividual(const std::string&, bool completeMatch = true) const;*/

    void AddPhone(Subscriber*, Phone&);
    void AddEmail(Subscriber*, std::string&);

    void RemovePhone(Subscriber*, const Phone&);
    void RemoveEmail(Subscriber*, const std::string&);

    void ChangeSubscriberTitle(Subscriber*, std::string&);
    void ChangeMainPhone(Subscriber*, Phone&);
private:
    std::vector<Subscriber*> subscribers;
};

