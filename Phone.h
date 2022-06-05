#pragma once
#include <string>

enum class PhoneType { home, office };
class Phone
{
public:
    Phone(const std::string&, const std::string&, PhoneType = PhoneType::home);
    virtual std::string Short() const;
    virtual std::string Full() const = 0;
protected:
    std::string countryCode;
private:
    std::string shortNo;
    PhoneType phoneType;
};

class LandlinePhone : public Phone
{
public:
    LandlinePhone(const std::string&, const std::string&, const std::string&, PhoneType = PhoneType::home);
    std::string Middle() const;
    std::string Full() const override;
private:
    std::string cityCode;
};

class MobilePhone : public Phone
{
public:
    MobilePhone(const std::string&, const std::string&, const std::string&, PhoneType = PhoneType::home);
    std::string Short() const override;
    std::string Full() const override;
private:
    std::string mobileCode;
};
