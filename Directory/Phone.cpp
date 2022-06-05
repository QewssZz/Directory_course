#include "Phone.h"
#include <stdexcept>

using namespace std;

Phone::Phone(const std::string& cC, const std::string& no, PhoneType pT) :
    countryCode(cC), shortNo(no), phoneType(pT)
{
    if (countryCode == "\0") { throw invalid_argument("No country code in number."); }
    if (shortNo == "\0") { throw invalid_argument("Number doesn`t exist."); }
    if (int(PhoneType::home) > 1 && int(PhoneType::office) > 1) 
    {
        throw invalid_argument("Non-existent type of number.");
    }
}
std::string Phone::Short() const
{
    return shortNo;
}

LandlinePhone::LandlinePhone(const std::string& cC, const std::string& no, const std::string& ciC, PhoneType pt) :
    Phone(cC, no, pt), cityCode(ciC)
{
    if (cityCode == "\0") { throw invalid_argument("Not full phone number."); }
}
std::string LandlinePhone::Middle() const
{
    return cityCode + Short();
}
std::string LandlinePhone::Full() const
{
    return countryCode + Middle();
}

MobilePhone::MobilePhone(const std::string& cC, const std::string& no, const std::string& mC, PhoneType pT) :
    Phone(cC, no, pT), mobileCode(mC)
{
    if (mobileCode == "\0") { throw invalid_argument("Not full phone number."); }
}
std::string MobilePhone::Short() const
{
    return mobileCode + Phone::Short();
}
std::string MobilePhone::Full() const
{
    return countryCode + Short();
}
