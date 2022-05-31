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
	Phone(std::string full, std::string middle, std::string brief, PhoneCategories PC);
	void ChangePhone(const std::string& newPhone);
private:
	PhoneCategories PC;
	std::string full, middle, brief;
};

class NotesInDirectory
{
public:
	void AddEmail(std::vector<std::string> e_mails, std::string email);
	void AddPhone(std::vector<Phone> phones, Phone phone);
	void MakeMain(Phone phone); //номер в списке
	void RemovePhone(Phone phone);
	void RemoveEmail(std::string email);
	//std::string GetEmail() const;
	//Phone GetPhone() const;
	std::string GetFirstEmail() const;
private:
	std::vector<Phone> phones;
	std::vector<std::string> e_mails;
	//std::string email;
	//Phone phone;
};

class Human : public NotesInDirectory 
{
public:
private:
	std::string Name , Surname, MiddleName, Gender;
	
};

class Organization : public NotesInDirectory 
{
public:
	//std::string GetNameOfOrg() const;
	//std::string GetActivity() const;
private:
	std::string NameOfOrg, Activity;
};