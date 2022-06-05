// RefBook.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
//#include <vector>
#include "PhoneRefBook.h"
using namespace std;

int main()
{
    try
    {
        PhoneRefBook prb;

        Person firstPers("Епифанов Олег Андреевич", Gender::male, NULL);

        IndividualSubscriber indSubscr(&firstPers);

        MobilePhone homePhone("380", "8001516", "95", PhoneType::home);
        LandlinePhone officePhone("380", "7311510", "48", PhoneType::office);

        indSubscr.AddPhone(&homePhone);
        indSubscr.AddPhone(&officePhone);

        indSubscr.AddEmail("mail_1@gmail.com");
        indSubscr.AddEmail("mail_2@ukr.net");

        Institution FirstInst("Рога и копыта", "производство", &firstPers);

        InstitutionSubscriber instSubscr(&FirstInst);

        MobilePhone officeMobPhone("380", "8709528", "67", PhoneType::office);
        LandlinePhone officeLandPhone("380", "7621875", "48", PhoneType::office);

        instSubscr.AddPhone(&officeMobPhone);
        instSubscr.AddPhone(&officeLandPhone);

        indSubscr.AddEmail("mail_3@gmail.com");
        indSubscr.AddEmail("mail_4@ukr.net");

        prb.AddSubscriber(&indSubscr);
        prb.AddSubscriber(&instSubscr);
    }
    catch(invalid_argument& ia)
    {
        cout << ia.what() << endl;
    }
}
