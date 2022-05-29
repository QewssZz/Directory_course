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
	std::string GetFirstEmail() const;
private:
	std::vector<Phone> phones;
	std::vector<std::string> e_mails;
};

