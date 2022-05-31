#pragma once
#include "NotesInDirectory.h"
#include <vector>


class Directory
{
public:
	void FindByPhone(const Phone& phone) const;
	void FindByEmail(const std::string& email) const;
	void FindByFullName(const std::string& full_name) const;
	void FineBySurname(const std::string& surname) const;
	void AddInfo(const NotesInDirectory& info);
	void RemoveInfo(std::string record);
private:
	std::vector<NotesInDirectory*> directory;
};

