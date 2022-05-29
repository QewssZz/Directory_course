#pragma once
#include <vector>
#include <string>

enum class PhoneCategories 
{
	mobile, home, office
};

class Phone 
{
public:
private:
	PhoneCategories PC;
};

class NotesInDirectory
{
public:
	void AddEmail(std::vector<std::string> e_mails, std::string email);
	void Add(std::vector<Phone> phones, Phone phone);
	std::string GetEmail() const;
	Phone GetPhone() const;
	std::string GetFirstEmail() const;
private:
	std::vector<Phone> phones;
	std::vector<std::string> e_mails;
	std::string email;
	Phone phone;
};

class Human : public NotesInDirectory 
{
public:
private:
	std::string FullName, Gender;
	
};

class Organization : public NotesInDirectory 
{
public:
	std::string GetNameOfOrg() const;
	std::string GetActivity() const;
private:
	std::string NameOfOrg, Activity;
};