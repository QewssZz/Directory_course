// RefBook.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
//#include <vector>
#include "PhoneRefBook.h"
using namespace std;

//void Menu();

int main()
{
    try
    {
        PhoneRefBook prb;
        Person* firstPers = new Person("Epifanov Oleg Endreevich", Gender::male, NULL);
                
        IndividualSubscriber* indSubscr = new IndividualSubscriber(firstPers);

        MobilePhone* homePhone = new MobilePhone("+380", "8001516", "95", PhoneType::home);
        LandlinePhone* officePhone = new LandlinePhone("+380", "7311510", "48", PhoneType::office);      

        indSubscr->AddPhone(homePhone);
        indSubscr->AddPhone(officePhone);
        
        indSubscr->AddEmail("mail_3@gmail.com");
        indSubscr->AddEmail("mail_2@ukr.net");
        
        Institution* FirstInst = new Institution("Roga & kopyta", "industry", firstPers);
        
        InstitutionSubscriber* instSubscr = new InstitutionSubscriber(FirstInst);

        MobilePhone* officeMobPhone = new MobilePhone("+380", "8709528", "67", PhoneType::office);
        LandlinePhone* officeLandPhone = new LandlinePhone("+380", "7621875", "48", PhoneType::office);

        instSubscr->AddPhone(officeMobPhone);
        instSubscr->AddPhone(officeLandPhone);

        instSubscr->AddEmail("mail_3@gmail.com");
        instSubscr->AddEmail("mail_4@ukr.net");

        prb.AddSubscriber(indSubscr);
        prb.AddSubscriber(instSubscr);
        
        prb.Menu();      
    }
    catch(invalid_argument& ia)
    {
        cout << ia.what() << endl;
    }
}
