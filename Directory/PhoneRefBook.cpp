#include "PhoneRefBook.h"
#include "Person.h"
#include "Subscriber.h"
#include "Institution.h"
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

void PhoneRefBook::AddSubscriber(Subscriber* ptrSubs)
{
	if (find(subscribers.begin(), subscribers.end(), ptrSubs) != subscribers.end())
	{
		throw invalid_argument("Person already in directory");
	}
	subscribers.push_back(ptrSubs);
}

void PhoneRefBook::RemoveSubscriber(Subscriber* ptrSubs)
{
	auto found = find(subscribers.begin(), subscribers.end(), ptrSubs);
	if (found == subscribers.end())
	{
		throw invalid_argument("Person not in directory");
	}
	delete ptrSubs;
	subscribers.erase(found);
}

vector<Subscriber*> PhoneRefBook::FindByPhone(const std::string& phone) const
{
	std::vector<Subscriber*> result;
	for (Subscriber* i : subscribers) 
	{
		if (i->FindByPhone(phone)) 
		{
			result.push_back(i);
		}
	}
	return result;
}

vector<Subscriber*> PhoneRefBook::FindByEmail(const string& email) const
{
	std::vector<Subscriber*> result;
	for (Subscriber* i : subscribers) 
	{
		if (i->FindByEmail(email)) 
		{
			result.push_back(i);
		}
	}
	return result;
}

std::vector<Subscriber*> PhoneRefBook::FindIndividual(const std::string& fname, bool completeMatch) const 
{
	std::vector<Subscriber*> result;
	if (completeMatch)
	{
		for (Subscriber* i : subscribers)
		{
			if (i->GetSubsType() == SubscriberType::individual)
			{
				if (i->GetName() == fname)
				{
					result.push_back(i);
				}
			}
		}
	}
	else 
	{
		for (Subscriber* i : subscribers)
		{
			if (i->GetSubsType() == SubscriberType::individual)
			{
				std::string currName = i->GetName();
				if (currName.substr(0, fname.length()) == fname)
				{	
					result.push_back(i);
				}
			}
		}
	}
	return result;
}

void PhoneRefBook::AddPhone(Subscriber* ptrSubs, Phone* ph)
{
	//проверка на существования абонента ptrSubs
	if (find(subscribers.begin(), subscribers.end(), ptrSubs) == subscribers.end())//абонент в справочнике
	{
		throw invalid_argument("Person not in directory");
	}
	ptrSubs->AddPhone(ph);
}

void PhoneRefBook::AddEmail(Subscriber* ptrSubs, std::string& email)
{
	//проверка на существования абонента ptrSubs
	if (find(subscribers.begin(), subscribers.end(), ptrSubs) == subscribers.end())//абонент в справочнике
	{
		throw invalid_argument("Person not in directory");
	}
	ptrSubs->AddEmail(email);
}	

void PhoneRefBook::RemovePhone(Subscriber* ptrSubs, const std::string& phone)
{
	//проверка на существования абонента ptrSubs
	if (find(subscribers.begin(), subscribers.end(), ptrSubs) == subscribers.end())//абонент в справочнике
	{
		throw invalid_argument("Person not in directory");
	}
	if(!ptrSubs->FindByPhone(phone))
	{
		throw invalid_argument("Phone not found");
	}
	ptrSubs->RemovePhone(phone);
}
void PhoneRefBook::RemoveEmail(Subscriber* ptrSubs, const std::string& email)
{
	//проверка на существования абонента ptrSubs
	if (find(subscribers.begin(), subscribers.end(), ptrSubs) == subscribers.end())//абонент в справочнике
	{
		throw invalid_argument("Person not in directory");
	}
	ptrSubs->RemoveEmail(email);
}

void PhoneRefBook::ChangeSubscriberTitle(Subscriber* ptrSubs, std::string& title)
{
	if (find(subscribers.begin(), subscribers.end(), ptrSubs) == subscribers.end())
	{
		throw invalid_argument("Person doesn`t exist");
	}
	ptrSubs->ChangeSubscriberTitle(title);
}
void PhoneRefBook::ChangeMainPhone(Subscriber* ptrSubs, Phone& phone)
{
	ptrSubs->ChangeMainPhone(&phone);
}

void PhoneRefBook::Print() const 
{
	/*for (const Subscriber* i : subscribers)
	{
		cout << i->To_String() << endl;
	}*/
	for (int i = 0, k = 1; i < subscribers.size(); i++, k++) 
	{
		cout << k << ")" << subscribers[i]->To_String() << endl;
	}
}

void PhoneRefBook::Menu() 
{
	int c1, c2, c3, c4, c5, c6, c7, id;
	string name, name_lead, new_name, email, gender, institution, kindofactivity;
	string phone;
	string countryCode, shortNumber, mobileCode, cityCode;
	vector<Subscriber*> found;
	do
	{
		cout << "1. Add info about subscriber" << endl;
		cout << "2. Remove info about subscriber" << endl;
		cout << "3. Find subscriber" << endl;
		cout << "4. Add subscriber" << endl; 
		cout << "5. Remove subscriber" << endl;
		cout << "6. Show full list of subscribers" << endl;
		cout << "7. Change info about subscriber" << endl;
		cout << "0. Exit" << endl;
		cout << ">>>>";
		cin >> c1;
		cout << "======================================" << endl;

		try
		{
			switch (c1)
			{
			case 1:
				{
					cout << "1. Find subscriber by email " << endl;
					cout << "2. Find subscriber by phone " << endl;
					cout << "3. Find subscriber by name " << endl;
					cout << "0. Exit " << endl;
					cout << ">>>>";
					cin >> c2;
					cout << endl;
					switch (c2)
					{
					case 1:
						{
							cout << "Enter email: " << endl;
							cout << ">>>>";
							cin >> email;
							auto found1 = email.find("@");
							if (found1 == string::npos)
							{
								throw invalid_argument("Incorrect form of email");
							}
							cout << endl;
							int k = 1;
							vector<Subscriber*> found = FindByEmail(email);
							for (Subscriber* sub : found)
							{
								cout << k << ") " << sub->To_String() << endl;
								k++;
							}
							if (found.size() == 0) 
							{
								throw invalid_argument("Not found");
							}
							cout << "Select subscriber to add info: " << endl;
							cout << ">>>>";
							cin >> id;
							cout << endl;
							if (id > found.size() || id < 0)
							{
								throw invalid_argument("Incorrect id of subscriber");
							}
							cout << "1. Add phone " << endl;
							cout << "2. Add email " << endl;
							cout << "0. Exit " << endl;
							cout << ">>>>";
							cin >> c3;
							cout << endl;
							switch (c3) 
							{
							case 1: 
								{
									cout << "1. Landline phone " << endl;
									cout << "2. Mobile phone " << endl;
									cout << "0. Exit " << endl;
									cout << ">>>>";
									cin >> c4;
									cout << endl;
									switch (c4) 
									{
									case 1: 
										{
											cout << "1. Home phone " << endl;
											cout << "2. Office phone " << endl;
											cout << "0. Exit " << endl;
											cout << ">>>>";
											cin >> c5;
											cout << endl;
											switch (c5) 
											{
											case 1: 
												{
													cout << "Enter country code: " << endl;
													cout << ">>>>";
													cin >> countryCode;
													cout << endl;
													cout << "Enter short number: " << endl;
													cout << ">>>>";
													cin >> shortNumber;
													cout << endl;
													cout << "Enter city code: " << endl;
													cout << ">>>>";
													cin >> cityCode;
													cout << endl;
													LandlinePhone* homePhone = new LandlinePhone(countryCode, shortNumber, cityCode, PhoneType::home);
													found[id - 1]->AddPhone(homePhone);
													cout << "Phone added to " << found[id - 1]->GetName() << " " << endl;
													break;
												}
											case 2: 
												{
													cout << "Enter country code: " << endl;
													cout << ">>>>";
													cin >> countryCode;
													cout << endl;
													cout << "Enter short number: " << endl;
													cout << ">>>>";
													cin >> shortNumber;
													cout << endl;
													cout << "Enter city code: " << endl;
													cout << ">>>>";
													cin >> cityCode;
													cout << endl;
													LandlinePhone* officePhone = new LandlinePhone(countryCode, shortNumber, cityCode, PhoneType::office);
													found[id - 1]->AddPhone(officePhone);
													cout << "Phone added to " << found[id - 1]->GetName() << " " << endl;
													break;
												}
											}//switch
											break;
										}
									case 2: 
										{
											cout << "1. Home phone " << endl;
											cout << "2. Office phone " << endl;
											cout << "0. Exit " << endl;
											cout << ">>>>";
											cin >> c5;
											cout << endl;
											switch (c5) 
											{
											case 1: 
												{
													cout << "Enter country code: " << endl;
													cout << ">>>>";
													cin >> countryCode;
													cout << endl;
													cout << "Enter short number: " << endl;
													cout << ">>>>";
													cin >> shortNumber;
													cout << endl;
													cout << "Enter city code: " << endl;
													cout << ">>>>";
													cin >> cityCode;
													cout << endl;
													MobilePhone* homePhone = new MobilePhone(countryCode, shortNumber, cityCode, PhoneType::home);
													found[id - 1]->AddPhone(homePhone);
													cout << "Phone added to " << found[id - 1]->GetName() << " " << endl;
													break;
												}
											case 2: 
												{
													cout << "Enter country code: " << endl;
													cout << ">>>>";
													cin >> countryCode;
													cout << endl;
													cout << "Enter short number: " << endl;
													cout << ">>>>";
													cin >> shortNumber;
													cout << endl;
													cout << "Enter city code: " << endl;
													cout << ">>>>";
													cin >> cityCode;
													cout << endl;
													MobilePhone* officePhone = new MobilePhone(countryCode, shortNumber, cityCode, PhoneType::office);
													found[id - 1]->AddPhone(officePhone);
													cout << "Phone added to " << found[id - 1]->GetName() << " " << endl;
													break;
												}
											}//switch
											break;
										}
									}//switch
									break;
								} 
							case 2: 
								{
									cout << "Enter new email: " << endl;
									cout << ">>>>";
									cin >> email;
									cout << endl;
									auto found1 = email.find("@");
									if (found1 == std::string::npos)
									{
										throw std::invalid_argument("Incorrect form of email");
									}
									found[id - 1]->AddEmail(email);
									cout << "Email added to " << found[id - 1]->GetName()<< " " << endl;
									break;
								}
							}//switch
						break;
						}
					case 2:
						{
							cout << "Enter phone to find: " << endl;
							cout << ">>>>";
							cin >> phone;
							auto found1 = phone.find("+");
							if (found1 == std::string::npos)
							{
								throw std::invalid_argument("Incorrect form of phone");
							}
							cout << endl;
							vector<Subscriber*> found = FindByPhone(phone);
							int k = 1;
							for (Subscriber* sub : found)
							{
								cout << k << ") " << sub->To_String() << endl;
								k++;
							}
							if (found.size() == 0)
							{
								throw invalid_argument("Not found");
							}
							cout << "Select subscriber to add info: " << endl;
							cout << ">>>>";
							cin >> id;
							cout << endl;
							if (id > found.size() || id < 0)
							{
								throw invalid_argument("Incorrect id of subscriber");
							}
							cout << "1. Add phone " << endl;
							cout << "2. Add email " << endl;
							cout << "0. Exit " << endl;
							cout << ">>>>";
							cin >> c3;
							cout << endl;
							switch (c3)
							{
							case 1: 
								{
									cout << "1. Landline phone " << endl;
									cout << "2. Mobile phone " << endl;
									cout << "0. Exit " << endl;
									cout << ">>>>";
									cin >> c4;
									cout << endl;
									switch (c4)
									{
									case 1: 
										{
											cout << "1. Home phone " << endl;
											cout << "2. Office phone " << endl;
											cout << "0. Exit " << endl;
											cout << ">>>>";
											cin >> c5;
											cout << endl;
											switch (c5) 
											{
											case 1: 
												{
													cout << "Enter country code: " << endl;
													cout << ">>>>";
													cin >> countryCode;
													cout << endl;
													cout << "Enter short number: " << endl;
													cout << ">>>>";
													cin >> shortNumber;
													cout << endl;
													cout << "Enter city code: " << endl;
													cout << ">>>>";
													cin >> cityCode;
													cout << endl;
													LandlinePhone* homePhone = new LandlinePhone(countryCode, shortNumber, cityCode, PhoneType::home);
													found[id - 1]->AddPhone(homePhone);
													cout << "Phone added to " << found[id - 1]->GetName() << " " << endl;
													break;
												}
											case 2: 
												{
													cout << "Enter country code: " << endl;
													cout << ">>>>";
													cin >> countryCode;
													cout << endl;
													cout << "Enter short number: " << endl;
													cout << ">>>>";
													cin >> shortNumber;
													cout << endl;
													cout << "Enter city code: " << endl;
													cout << ">>>>";
													cin >> cityCode;
													cout << endl;
													LandlinePhone* officePhone = new LandlinePhone(countryCode, shortNumber, cityCode, PhoneType::office);
													found[id - 1]->AddPhone(officePhone);
													cout << "Phone added to " << found[id - 1]->GetName() << " " << endl;
													break;
												}
											}//switch
											break;
										}
									case 2: 
										{
											cout << "1. Home phone " << endl;
											cout << "2. Office phone " << endl;
											cout << "0. Exit " << endl;
											cout << ">>>>";
											cin >> c5;
											cout << endl;
											switch (c5) 
											{
											case 1: 
												{
													cout << "Enter country code: " << endl;
													cout << ">>>>";
													cin >> countryCode;
													cout << endl;
													cout << "Enter short number: " << endl;
													cout << ">>>>";
													cin >> shortNumber;
													cout << endl;
													cout << "Enter city code: " << endl;
													cout << ">>>>";
													cin >> cityCode;
													cout << endl;
													MobilePhone* homePhone = new MobilePhone(countryCode, shortNumber, cityCode, PhoneType::home);
													found[id - 1]->AddPhone(homePhone);
													cout << "Phone added to " << found[id - 1]->GetName() << " " << endl;
													break;
												}
											case 2: 
												{
													cout << "Enter country code: " << endl;
													cout << ">>>>";
													cin >> countryCode;
													cout << endl;
													cout << "Enter short number: " << endl;
													cout << ">>>>";
													cin >> shortNumber;
													cout << endl;
													cout << "Enter city code: " << endl;
													cout << ">>>>";
													cin >> cityCode;
													cout << endl;
													MobilePhone* officePhone = new MobilePhone(countryCode, shortNumber, cityCode, PhoneType::office);
													found[id - 1]->AddPhone(officePhone);
													cout << "Phone added to " << found[id - 1]->GetName() << " " << endl;
													break;
												}
											}//switch
											break;
										}
									}//switch
									break;
								}
							case 2: 
								{
									cout << "Enter new email: " << endl;
									cout << ">>>>";
									cin >> email;
									cout << endl;
									auto found1 = email.find("@");
									if (found1 == std::string::npos)
									{
										throw std::invalid_argument("Incorrect form of email");
									}
									found[id - 1]->AddEmail(email);
									cout << "Email added to " << found[id - 1]->GetName() << " " << endl;
									break;
								}
							}//switch
							break;
						}
					case 3:
						{
							cout << "1. Find by full name " << endl;
							cout << "2. Find by first part of full name " << endl;
							cout << "0. Exit " << endl;
							cout << ">>>>";
							cin >> c3;
							cout << endl;
							switch (c3)
							{
							case 1: 
								{
									cout << "Enter full name: " << endl;
									cin >> ws; getline(cin, name);
									cout << endl;
									vector<Subscriber*> found = FindIndividual(name, true);
									int k = 1;
									for (Subscriber* sub : found)
									{
										cout << k << ") " << sub->To_String() << endl;
										k++;
									}
									if (found.size() == 0)
									{
										throw invalid_argument("Not found");
									}
									cout << "Select subscriber to add info: " << endl;
									cout << ">>>>";
									cin >> id;
									cout << endl;
									if (id > found.size() || id < 0)
									{
										throw invalid_argument("Incorrect id of subscriber");
									}
									cout << "1. Add phone " << endl;
									cout << "2. Add email " << endl;
									cout << "0. Exit " << endl;
									cout << ">>>>";
									cin >> c4;
									cout << endl;
									switch (c4) 
									{
									case 1: 
										{
											cout << "1. Landline phone " << endl;
											cout << "2. Mobile phone " << endl;
											cout << "0. Exit " << endl;
											cout << ">>>>";
											cin >> c5;
											cout << endl;
											switch (c5) 
											{
											case 1:
												{
													cout << "1. Home phone " << endl;
													cout << "2. Office phone " << endl;
													cout << "0. Exit " << endl;
													cout << ">>>>";
													cin >> c6;
													cout << endl;
													switch (c6) 
													{
													case 1: 
														{
															cout << "Enter country code: " << endl;
															cout << ">>>>";
															cin >> countryCode;
															cout << endl;
															cout << "Enter short number: " << endl;
															cout << ">>>>";
															cin >> shortNumber;
															cout << endl;
															cout << "Enter city code: " << endl;
															cout << ">>>>";
															cin >> cityCode;
															cout << endl;
															LandlinePhone* homePhone = new LandlinePhone(countryCode, shortNumber, cityCode, PhoneType::home);
															found[id - 1]->AddPhone(homePhone);
															cout << "Phone added to " << found[id - 1]->GetName() << " " << endl;
															break;
														}
													case 2: 
														{
															cout << "Enter country code: " << endl;
															cout << ">>>>";
															cin >> countryCode;
															cout << endl;
															cout << "Enter short number: " << endl;
															cout << ">>>>";
															cin >> shortNumber;
															cout << endl;
															cout << "Enter city code: " << endl;
															cout << ">>>>";
															cin >> cityCode;
															cout << endl;
															LandlinePhone* officePhone = new LandlinePhone(countryCode, shortNumber, cityCode, PhoneType::office);
															found[id - 1]->AddPhone(officePhone);
															cout << "Phone added to " << found[id - 1]->GetName() << " " << endl;
															break;
														}
													}//switch
													break;
												}
											case 2: 
												{
													cout << "1. Home phone " << endl;
													cout << "2. Office phone " << endl;
													cout << "0. Exit " << endl;
													cout << ">>>>";
													cin >> c6;
													cout << endl;
													switch (c6) 
													{
													case 1: 
														{
															cout << "Enter country code: " << endl;
															cout << ">>>>";
															cin >> countryCode;
															cout << endl;
															cout << "Enter short number: " << endl;
															cout << ">>>>";
															cin >> shortNumber;
															cout << endl;
															cout << "Enter city code: " << endl;
															cout << ">>>>";
															cin >> cityCode;
															cout << endl;
															MobilePhone* homePhone = new MobilePhone(countryCode, shortNumber, cityCode, PhoneType::home);
															found[id - 1]->AddPhone(homePhone);
															cout << "Phone added to " << found[id - 1]->GetName() << " " << endl;
															break;
														}
													case 2: 
														{
															cout << "Enter country code: " << endl;
															cout << ">>>>";
															cin >> countryCode;
															cout << endl;
															cout << "Enter short number: " << endl;
															cout << ">>>>";
															cin >> shortNumber;
															cout << endl;
															cout << "Enter city code: " << endl;
															cout << ">>>>";
															cin >> cityCode;
															cout << endl;
															MobilePhone* officePhone = new MobilePhone(countryCode, shortNumber, cityCode, PhoneType::office);
															found[id - 1]->AddPhone(officePhone);
															cout << "Phone added to " << found[id - 1]->GetName() << " " << endl;
															break;
														}
													}//switch
													break;
												}
											}//switch
											break;
										}
									case 2: 
										{
											cout << "Enter new email: " << endl;
											cout << ">>>>";
											cin >> email;
											cout << endl;
											auto found1 = email.find("@");
											if (found1 == std::string::npos)
											{
												throw std::invalid_argument("Incorrect form of email");
											}
											found[id - 1]->AddEmail(email);
											cout << "Email added to " << found[id - 1]->GetName() << " " << endl;
											break;
										}
									}//switch
									break;
								}
							case 2: 
								{
									cout << "Enter first part of full name: " << endl;
									cin >> ws; getline(cin, name);
									cout << endl;
									vector<Subscriber*> found = FindIndividual(name, false);
									int k = 1;
									for (Subscriber* sub : found)
									{
										cout << k << ") " << sub->To_String() << endl;
										k++;
									}
									if (found.size() == 0)
									{
										throw invalid_argument("Not found");
									}
									cout << "Select subscriber to add info: " << endl;
									cout << ">>>>";
									cin >> id;
									cout << endl;
									if (id > found.size() || id < 0)
									{
										throw invalid_argument("Incorrect id of subscriber");
									}
									cout << "1. Add phone " << endl;
									cout << "2. Add email " << endl;
									cout << "0. Exit " << endl;
									cout << ">>>>";
									cin >> c4;
									cout << endl;
									switch (c4) 
									{
									case 1: 
										{
											cout << "1. Landline phone " << endl;
											cout << "2. Mobile phone " << endl;
											cout << "0. Exit " << endl;
											cout << ">>>>";
											cin >> c5;
											cout << endl;
											switch (c5) 
											{
											case 1: 
												{
													cout << "1. Home phone " << endl;
													cout << "2. Office phone " << endl;
													cout << "0. Exit " << endl;
													cout << ">>>>";
													cin >> c6;
													cout << endl;
													switch (c6) 
													{
													case 1: 
														{
															cout << "Enter country code: " << endl;
															cout << ">>>>";
															cin >> countryCode;
															cout << endl;
															cout << "Enter short number: " << endl;
															cout << ">>>>";
															cin >> shortNumber;
															cout << endl;
															cout << "Enter city code: " << endl;
															cout << ">>>>";
															cin >> cityCode;
															cout << endl;
															LandlinePhone* homePhone = new LandlinePhone(countryCode, shortNumber, cityCode, PhoneType::home);
															found[id - 1]->AddPhone(homePhone);
															cout << "Phone added to " << found[id - 1]->GetName() << " " << endl;
															break;
														}
													case 2: 
														{
															cout << "Enter country code: " << endl;
															cout << ">>>>";
															cin >> countryCode;
															cout << endl;
															cout << "Enter short number: " << endl;
															cout << ">>>>";
															cin >> shortNumber;
															cout << endl;
															cout << "Enter city code: " << endl;
															cout << ">>>>";
															cin >> cityCode;
															cout << endl;
															LandlinePhone* officePhone = new LandlinePhone(countryCode, shortNumber, cityCode, PhoneType::office);
															found[id - 1]->AddPhone(officePhone);
															cout << "Phone added to " << found[id - 1]->GetName() << " " << endl;
															break;
														}
													}//switch
													break;
												}
											case 2: 
												{
													cout << "1. Home phone " << endl;
													cout << "2. Office phone " << endl;
													cout << "0. Exit " << endl;
													cout << ">>>>";
													cin >> c6;
													cout << endl;
													switch (c6) 
													{
													case 1: 
														{
															cout << "Enter country code: " << endl;
															cout << ">>>>";
															cin >> countryCode;
															cout << endl;
															cout << "Enter short number: " << endl;
															cout << ">>>>";
															cin >> shortNumber;
															cout << endl;
															cout << "Enter city code: " << endl;
															cout << ">>>>";
															cin >> cityCode;
															cout << endl;
															MobilePhone* homePhone = new MobilePhone(countryCode, shortNumber, cityCode, PhoneType::home);
															found[id - 1]->AddPhone(homePhone);
															cout << "Phone added to " << found[id - 1]->GetName() << " " << endl;
															break;
														}
													case 2: 
														{
															cout << "Enter country code: " << endl;
															cout << ">>>>";
															cin >> countryCode;
															cout << endl;
															cout << "Enter short number: " << endl;
															cout << ">>>>";
															cin >> shortNumber;
															cout << endl;
															cout << "Enter city code: " << endl;
															cout << ">>>>";
															cin >> cityCode;
															cout << endl;
															MobilePhone* officePhone = new MobilePhone(countryCode, shortNumber, cityCode, PhoneType::office);
															found[id - 1]->AddPhone(officePhone);
															cout << "Phone added to " << found[id - 1]->GetName() << " " << endl;
															break;
														}
													}//switch
													break;
												}
											}//switch
											break;
										}
									case 2: 
										{
											cout << "Enter new email: " << endl;
											cout << ">>>>";
											cin >> email;
											cout << endl;
											auto found1 = email.find("@");
											if (found1 == std::string::npos)
											{
												throw std::invalid_argument("Incorrect form of email");
											}
											found[id - 1]->AddEmail(email);
											cout << "Email added to " << found[id - 1]->GetName() << " " << endl;
											break;
										}
									}//switch
									break;
								}
							}//switch
							break;
						}
					}//switch
					break;
				}
			case 2: 
				{
					cout << "1. Find subscriber by email " << endl;
					cout << "2. Find subscriber by phone " << endl;
					cout << "3. Find subscriber by name " << endl;
					cout << "0. Exit " << endl;
					cout << ">>>>";
					cin >> c2;
					cout << endl;
					switch (c2) 
					{
					case 1: 
						{
							cout << "Enter email: " << endl;
							cout << ">>>>";
							cin >> email;
							auto found1 = email.find("@");
							if (found1 == string::npos)
							{
								throw invalid_argument("Incorrect form of email");
							}
							cout << endl;
							int k = 1;
							vector<Subscriber*> found = FindByEmail(email);
							for (Subscriber* sub : found)
							{
								cout << k << ") " << sub->To_String() << endl;
								k++;
							}
							if (found.size() == 0)
							{
								throw invalid_argument("Not found");
							}
							cout << "Select subscriber to add info: " << endl;
							cout << ">>>>";
							cin >> id;
							if (id > found.size() || id < 0)
							{
								throw invalid_argument("Incorrect id of subscriber");
							}
							cout << "1. Remove phone " << endl;
							cout << "2. Remove email " << endl;
							cout << "0. Exit " << endl;
							cout << ">>>>";
							cin >> c3;
							cout << endl;
							switch (c3) 
							{
							case 1: 
								{
									cout << "Enter phone to remove: " << endl;
									cout << ">>>>";
									cin >> phone;
									auto found1 = phone.find("+");
									if (found1 == std::string::npos)
									{
										throw std::invalid_argument("Incorrect form of phone");
									}
									cout << endl;
									found[id - 1]->RemovePhone(phone);
									cout << "Phone removed from " << found[id - 1]->GetName() << " " << endl;
									cout << endl;
									break;
								}
							case 2: 
								{
									cout << "Enter email to remove: " << endl;
									cout << ">>>>";
									cin >> email;
									auto found1 = email.find("@");
									if (found1 == std::string::npos)
									{
										throw std::invalid_argument("Incorrect form of email");
									}
									cout << endl;
									found[id - 1]->RemoveEmail(email);
									cout << "Phone removed from " << found[id - 1]->GetName() << " " << endl;
									cout << endl;
									break;
								}
							}//switch
							break;
						}
					case 2: 
						{
							cout << "Enter phone to find: " << endl;
							cout << ">>>>";
							cin >> phone;
							auto found1 = phone.find("+");
							if (found1 == std::string::npos)
							{
								throw std::invalid_argument("Incorrect form of phone");
							}
							cout << endl;
							vector<Subscriber*> found = FindByPhone(phone);
							int k = 1;
							for (Subscriber* sub : found)
							{
								cout << k << ") " << sub->To_String() << endl;
								k++;
							}
							if (found.size() == 0)
							{
								throw invalid_argument("Not found");
							}
							cout << "Select subscriber to add info: " << endl;
							cout << ">>>>";
							cin >> id;
							if (id > found.size() || id < 0)
							{
								throw invalid_argument("Incorrect id of subscriber");
							}
							cout << "1. Remove phone " << endl;
							cout << "2. Remove email " << endl;
							cout << "0. Exit " << endl;
							cout << ">>>>";
							cin >> c3;
							cout << endl;
							switch (c3) 
							{
							case 1: 
								{
									cout << "Enter phone to remove: " << endl;
									cout << ">>>>";
									cin >> phone;
									auto found1 = phone.find("+");
									if (found1 == std::string::npos)
									{
										throw std::invalid_argument("Incorrect form of phone");
									}
									cout << endl;
									found[id - 1]->RemovePhone(phone);
									cout << "Phone removed from " << found[id - 1]->GetName() << " " << endl;
									cout << endl;
									break;
								}
							case 2: 
								{
									cout << "Enter email to remove: " << endl;
									cout << ">>>>";
									cin >> email;
									auto found1 = email.find("@");
									if (found1 == std::string::npos)
									{
										throw std::invalid_argument("Incorrect form of email");
									}
									cout << endl;
									found[id - 1]->RemoveEmail(email);
									cout << "Email removed from " << found[id - 1]->GetName() << " " << endl;
									cout << endl;
									break;
								}
							}//switch
							break;
						}
					case 3: 
						{
							cout << "1. Find by full name " << endl;
							cout << "2. Find by first part of full name " << endl;
							cout << "0. Exit " << endl;
							cout << ">>>>";
							cin >> c3;
							cout << endl;
							switch (c3) 
							{
							case 1: 
								{
									cout << "Enter full name: " << endl;
									cin >> ws; getline(cin, name);
									cout << endl;
									vector<Subscriber*> found = FindIndividual(name, true);
									int k = 1;
									for (Subscriber* sub : found)
									{
										cout << k << ") " << sub->To_String() << endl;
										k++;
									}
									if (found.size() == 0)
									{
										throw invalid_argument("Not found");
									}
									cout << "Select subscriber to add info: " << endl;
									cout << ">>>>";
									cin >> id;
									if (id > found.size() || id < 0)
									{
										throw invalid_argument("Incorrect id of subscriber");
									}
									cout << "1. Remove phone " << endl;
									cout << "2. Remove email " << endl;
									cout << "0. Exit " << endl;
									cout << ">>>>";
									cin >> c4;
									cout << endl;
									switch (c4) 
									{
									case 1: 
										{
											cout << "Enter phone to remove: " << endl;
											cout << ">>>>";
											cin >> phone;
											auto found1 = phone.find("+");
											if (found1 == std::string::npos)
											{
												throw std::invalid_argument("Incorrect form of phone");
											}
											cout << endl;
											found[id - 1]->RemovePhone(phone);
											cout << "Phone removed from " << found[id - 1]->GetName() << " " << endl;
											cout << endl;
											break;
										}
									case 2: 
										{
											cout << "Enter email to remove: " << endl;
											cout << ">>>>";
											cin >> email;
											auto found1 = email.find("@");
											if (found1 == std::string::npos)
											{
												throw std::invalid_argument("Incorrect form of email");
											}
											cout << endl;
											found[id - 1]->RemoveEmail(email);
											cout << "Email removed from " << found[id - 1]->GetName() << " " << endl;
											cout << endl;
											break;
										}
									}//switch
									break;
								}
							case 2: 
								{
									cout << "Enter first part of full name: " << endl;
									cin >> ws; getline(cin, name);
									cout << endl;
									vector<Subscriber*> found = FindIndividual(name, false);
									int k = 1;
									for (Subscriber* sub : found)
									{
										cout << k << ") " << sub->To_String() << endl;
										k++;
									}
									if (found.size() == 0)
									{
										throw invalid_argument("Not found");
									}
									cout << "Select subscriber to add info: " << endl;
									cout << ">>>>";
									cin >> id;
									if (id > found.size() || id < 0)
									{
										throw invalid_argument("Incorrect id of subscriber");
									}
									cout << "1. Remove phone " << endl;
									cout << "2. Remove email " << endl;
									cout << "0. Exit " << endl;
									cout << ">>>>";
									cin >> c4;
									cout << endl;
									switch (c4) 
									{
									case 1: 
										{
											cout << "Enter phone to remove: " << endl;
											cout << ">>>>";
											cin >> phone;
											auto found1 = phone.find("+");
											if (found1 == std::string::npos)
											{
												throw std::invalid_argument("Incorrect form of phone");
											}
											cout << endl;
											found[id - 1]->RemovePhone(phone);
											cout << "Phone removed from " << found[id - 1]->GetName() << " " << endl;
											cout << endl;
											break;
										}
									case 2: 
										{
											cout << "Enter email to remove: " << endl;
											cout << ">>>>";
											cin >> email;
											auto found1 = email.find("@");
											if (found1 == std::string::npos)
											{
												throw std::invalid_argument("Incorrect form of email");
											}
											cout << endl;
											found[id - 1]->RemoveEmail(email);
											cout << "Email removed from " << found[id - 1]->GetName() << " " << endl;
											cout << endl;
											break;
										}
									}//switch
									break;
								}
							}//switch
							break;
						}
					}//switch
					break;
				}
			case 3: 
				{
					cout << "1. Find subscriber by email " << endl;
					cout << "2. Find subscriber by phone " << endl;
					cout << "3. Find subscriber by name " << endl;
					cout << "0. Exit " << endl;
					cout << ">>>>";
					cin >> c2;
					cout << endl;
					switch (c2) 
					{
					case 1: 
						{
							cout << "Enter email: " << endl;
							cout << ">>>>";
							cin >> email;
							auto found1 = email.find("@");
							if (found1 == string::npos)
							{
								throw invalid_argument("Incorrect form of email");
							}
							cout << endl;
							vector<Subscriber*> found = FindByEmail(email);
							if (found.size() == 0)
							{
								throw invalid_argument("Not found");
							}
							for (int i = 0, k = 1; i < found.size(); i++, k++)
							{
								cout << k << ")" << found[i]->To_String() << endl;
							}
							break;
						}
					case 2:
						{
							cout << "Enter phone to find: " << endl;
							cout << ">>>>";
							cin >> phone;
							auto found1 = phone.find("+");
							if (found1 == std::string::npos)
							{
								throw std::invalid_argument("Incorrect form of phone");
							}
							cout << endl;
							vector<Subscriber*> found = FindByPhone(phone);
							if (found.size() == 0)
							{
								throw invalid_argument("Not found");
							}
							for (int i = 0, k = 1; i < found.size(); i++, k++)
							{
								cout << k << ")" << found[i]->To_String() << endl;
							}
							break;
						}
					case 3: 
						{
							cout << "1. Find by full name " << endl;
							cout << "2. Find by first part of full name " << endl;
							cout << "0. Exit " << endl;
							cout << ">>>>";
							cin >> c3;
							cout << endl;
							switch (c3) 
							{
							case 1: 
								{
									cout << "Enter full name: " << endl;
									cin >> ws; getline(cin, name);
									cout << endl;
									vector<Subscriber*> found = FindIndividual(name, true);
									if (found.size() == 0)
									{
										throw invalid_argument("Not found");
									}
									for (int i = 0, k = 1; i < found.size(); i++, k++)
									{
										cout << k << ")" << found[i]->To_String() << endl;
									}
									break;
								}
							case 2: 
								{
									cout << "Enter full name: " << endl;
									cin >> ws; getline(cin, name);
									cout << endl;
									vector<Subscriber*> found = FindIndividual(name, false);
									if (found.size() == 0)
									{
										throw invalid_argument("Not found");
									}
									for (int i = 0, k = 1; i < found.size(); i++, k++)
									{
										cout << k << ")" << found[i]->To_String() << endl;
									}
									break;
								}
							}
							break;
						}
					}//switch
					break;
				}
			case 4: 
				{
					cout << "Enter name of new subscriber: " << endl;
					cin >> ws; getline(cin, name);
					cout << endl;
					cout << "1. Individual subscriber " << endl;
					cout << "2. Institution subscriber " << endl;
					cout << "0. Exit " << endl;
					cout << ">>>>";
					cin >> c2;
					cout << endl;
					switch (c2) 
					{
					case 1: 
						{
							cout << "1. Male " << endl;
							cout << "2. Female " << endl;
							cout << "0. Exit " << endl;
							cout << ">>>>";
							cin >> c3;
							cout << endl;
							switch (c3) 
							{
							case 1: 
								{
									cout << "1. With institution " << endl;
									cout << "2. Without institution " << endl;
									cout << "0. Exit " << endl;
									cout << ">>>>";
									cin >> c4;
									cout << endl;
									switch (c4) 
									{
									case 1: 
										{
											cout << "Enter name of institution: " << endl;
											cout << ">>>>";
											cin >> ws; getline(cin, institution);
											cout << endl;
											cout << "Enter kind of activity of institution: " << endl;
											cout << ">>>>";
											cin >> ws; getline(cin, kindofactivity);
											cout << endl;
											cout << "1. With leader " << endl;
											cout << "2. Without leader " << endl;
											cout << "0. Exit " << endl;
											cout << ">>>>";
											cin >> c5;
											cout << endl;
											switch (c5) 
											{
											case 1: 
												{
													cout << "1. Male(leader) " << endl;
													cout << "2. Female(leader) " << endl;
													cout << "0. Exit " << endl;
													cout << ">>>>";
													cin >> c6;
													cout << endl;
													switch (c6) 
													{
													case 1: 
														{
															cout << "Enter name of leader: " << endl;
															cin >> ws; getline(cin, name_lead);
															cout << endl;
															Person* lead = new Person(name_lead, Gender::male, NULL);
															Institution* inst = new Institution(institution, kindofactivity, lead);
															Person* pers = new Person(name, Gender::male, inst);
															IndividualSubscriber* indSub = new IndividualSubscriber(pers);
															AddSubscriber(indSub);
															cout << "Indvidual subscriber added " << endl;
															cout << endl;
															break;
														}
													case 2: 
														{
															cout << "Enter name of leader: " << endl;
															cin >> ws; getline(cin, name_lead);
															cout << endl;
															Person* lead = new Person(name_lead, Gender::female, NULL);
															Institution* inst = new Institution(institution, kindofactivity, lead);
															Person* pers = new Person(name, Gender::male, inst);
															IndividualSubscriber* indSub = new IndividualSubscriber(pers);
															AddSubscriber(indSub);
															cout << "Indvidual subscriber added " << endl;
															cout << endl;
															break;
														}
													}//switch
													break;
												}
											case 2: 
												{
													Institution* inst = new Institution(institution, kindofactivity, NULL);
													Person* pers = new Person(name, Gender::male, NULL);
													IndividualSubscriber* indSub = new IndividualSubscriber(pers);
													AddSubscriber(indSub);
													cout << "Indvidual subscriber added " << endl;
													cout << endl;
													break;
												}
											}//switch
											break;
										}
									case 2: 
										{
											Person* pers = new Person(name, Gender::male, NULL);
											IndividualSubscriber* indSub = new IndividualSubscriber(pers);
											AddSubscriber(indSub);
											cout << "Individual subscriber added " << endl;
											cout << endl;
											break;
										}
									}
									break;
								}
							case 2: 
								{
									cout << "1. With institution " << endl;
									cout << "2. Without institution " << endl;
									cout << "0. Exit " << endl;
									cout << ">>>>";
									cin >> c4;
									cout << endl;
									switch (c4) 
									{
									case 1: 
										{
											cout << "Enter name of institution: " << endl;
											cout << ">>>>";
											cin >> ws; getline(cin, institution);
											cout << endl;
											cout << "Enter kind of activity of institution: " << endl;
											cout << ">>>>";
											cin >> ws; getline(cin, kindofactivity);
											cout << endl;
											cout << "1. With leader " << endl;
											cout << "2. Without leader " << endl;
											cout << "0. Exit " << endl;
											cout << ">>>>";
											cin >> c5;
											cout << endl;
											switch (c5) 
											{
											case 1: 
												{
													cout << "1. Male(leader) " << endl;
													cout << "2. Female(leader) " << endl;
													cout << "0. Exit " << endl;
													cout << ">>>>";
													cin >> c6;
													cout << endl;
													switch (c6) 
													{
													case 1: 
														{
															cout << "Enter name of leader: " << endl;
															cin >> ws; getline(cin, name_lead);
															cout << endl;
															Person* lead = new Person(name_lead, Gender::male, NULL);
															Institution* inst = new Institution(institution, kindofactivity, lead);
															Person* pers = new Person(name, Gender::female, inst);
															IndividualSubscriber* indSub = new IndividualSubscriber(pers);
															AddSubscriber(indSub);
															cout << "Indvidual subscriber added " << endl;
															cout << endl;
															break;
														}
													case 2: 
														{
															cout << "Enter name of leader: " << endl;
															cin >> ws; getline(cin, name_lead);
															cout << endl;
															Person* lead = new Person(name_lead, Gender::female, NULL);
															Institution* inst = new Institution(institution, kindofactivity, lead);
															Person* pers = new Person(name, Gender::female, inst);
															IndividualSubscriber* indSub = new IndividualSubscriber(pers);
															AddSubscriber(indSub);
															cout << "Indvidual subscriber added " << endl;
															cout << endl;
															break;
														}
													}//switch
													break;
												}
											case 2: 
												{
													Institution* inst = new Institution(institution, kindofactivity, NULL);
													Person* pers = new Person(name, Gender::female, NULL);
													IndividualSubscriber* indSub = new IndividualSubscriber(pers);
													AddSubscriber(indSub);
													cout << "Indvidual subscriber added " << endl;
													cout << endl;
													break;
												}
											}//switch
											break;
										}
									case 2: 
										{
											Person* pers = new Person(name, Gender::male, NULL);
											IndividualSubscriber* indSub = new IndividualSubscriber(pers);
											AddSubscriber(indSub);
											cout << "Individual subscriber added " << endl;
											cout << endl;
											break;
										}
									}//switch
									break;
								}
							}//switch
							break;
						}
					case 2: 
						{
							cout << "Enter name of institution: " << endl;
							cout << ">>>>";
							cin >> ws; getline(cin, institution);
							cout << endl;
							cout << "Enter kind of actitvity of institution: " << endl;
							cout << ">>>>";
							cin >> ws; getline(cin, kindofactivity);
							cout << endl;
							cout << "1. With leader " << endl;
							cout << "2. Without leader " << endl;
							cout << "0. Exit " << endl;
							cout << ">>>>";
							cin >> c3;
							cout << endl;
							switch (c3) 
							{
							case 1: 
								{
									cout << "1. Male " << endl;
									cout << "2. Female " << endl;
									cout << "0. Exit " << endl;
									cout << ">>>>";
									cin >> c4;
									cout << endl;
									switch (c4) 
									{
									case 1: 
										{
											cout << "Enter name of leader: " << endl;
											cout << ">>>>";
											cin >> ws; getline(cin, name_lead);
											cout << endl;
											Person* lead = new Person(name_lead, Gender::male, NULL);
											Institution* inst = new Institution(institution, kindofactivity, lead);
											InstitutionSubscriber* instSub = new InstitutionSubscriber(inst);
											AddSubscriber(instSub);
											cout << "Institution subscriber added " << endl;
											cout << endl;
											break;
										}
									case 2: 
										{
											cout << "Enter name of leader: " << endl;
											cout << ">>>>";
											cin >> ws; getline(cin, name_lead);
											cout << endl;
											Person* lead = new Person(name_lead, Gender::female, NULL);
											Institution* inst = new Institution(institution, kindofactivity, lead);
											InstitutionSubscriber* instSub = new InstitutionSubscriber(inst);
											AddSubscriber(instSub);
											cout << "Institution subscriber added " << endl;
											cout << endl;
											break;
										}
									}//switch
									break;
								}
							case 2: 
								{
									Institution* inst = new Institution(institution, kindofactivity, NULL);
									InstitutionSubscriber* instSub = new InstitutionSubscriber(inst);
									AddSubscriber(instSub);
									cout << "Institution subscriber added " << endl;
									cout << endl;
									break;
								}
							}//switch
							break;
						}
					}//switch
					break;
				}
			case 5: 
				{
					cout << "1. Find subscriber by email " << endl;
					cout << "2. Find subscriber by phone " << endl;
					cout << "3. Find subscriber by name " << endl;
					cout << "0. Exit " << endl;
					cout << ">>>>";
					cin >> c2;
					cout << endl;
					switch (c2) 
					{
					case 1: 
						{
							cout << "Enter email: " << endl;
							cout << ">>>>";
							cin >> email;
							auto found1 = email.find("@");
							if (found1 == string::npos)
							{
								throw invalid_argument("Incorrect form of email");
							}
							cout << endl;
							int k = 1;
							vector<Subscriber*> found = FindByEmail(email);
							for (Subscriber* sub : found)
							{
								cout << k << ") " << sub->To_String() << endl;
								k++;
							}
							if (found.size() == 0)
							{
								throw invalid_argument("Not found");
							}
							cout << "Select subscriber to add info: " << endl;
							cout << ">>>>";
							cin >> id;
							cout << endl;
							if (id > found.size() || id < 0)
							{
								throw invalid_argument("Incorrect id of subscriber");
							}
							RemoveSubscriber(found[id - 1]);
							cout << "Subscriber removed " << endl;
							cout << endl;
							break;
						}
					case 2: 
						{
							cout << "Enter phone to find: " << endl;
							cout << ">>>>";
							cin >> phone;
							auto found1 = phone.find("+");
							if (found1 == std::string::npos)
							{
								throw std::invalid_argument("Incorrect form of phone");
							}
							cout << endl;
							vector<Subscriber*> found = FindByPhone(phone);
							int k = 1;
							for (Subscriber* sub : found)
							{
								cout << k << ") " << sub->To_String() << endl;
								k++;
							}
							if (found.size() == 0)
							{
								throw invalid_argument("Not found");
							}
							cout << "Select subscriber to add info: " << endl;
							cout << ">>>>";
							cin >> id;
							cout << endl;
							if (id > found.size() || id < 0)
							{
								throw invalid_argument("Incorrect id of subscriber");
							}
							RemoveSubscriber(found[id - 1]);
							cout << "Subscriber removed " << endl;
							cout << endl;
							break;

						}
					case 3: 
						{
							cout << "1. Find by full name " << endl;
							cout << "2. Find by first part of full name " << endl;
							cout << "0. Exit " << endl;
							cout << ">>>>";
							cin >> c3;
							cout << endl;
							switch (c3) 
							{
							case 1: 
								{
									cout << "Enter full name(individual subscriber): " << endl;
									cin >> ws; getline(cin, name);
									cout << endl;
									vector<Subscriber*> found = FindIndividual(name, true);
									int k = 1;
									for (Subscriber* sub : found)
									{
										cout << k << ") " << sub->To_String() << endl;
										k++;
									}
									if (found.size() == 0)
									{
										throw invalid_argument("Not found");
									}
									cout << "Select subscriber to add info: " << endl;
									cout << ">>>>";
									cin >> id;
									cout << endl;
									if (id > found.size() || id < 0)
									{
										throw invalid_argument("Incorrect id of subscriber");
									}
									RemoveSubscriber(found[id - 1]);
									cout << "Subscriber removed " << endl;
									cout << endl;
									break;
								}
							case 2: 
								{
									cout << "Enter full name(individual subscriber): " << endl;
									cin >> ws; getline(cin, name);
									cout << endl;
									vector<Subscriber*> found = FindIndividual(name, false);
									int k = 1;
									for (Subscriber* sub : found)
									{
										cout << k << ") " << sub->To_String() << endl;
										k++;
									}
									if (found.size() == 0)
									{
										throw invalid_argument("Not found");
									}
									cout << "Select subscriber to add info: " << endl;
									cout << ">>>>";
									cin >> id;
									cout << endl;
									if (id > found.size() || id < 0)
									{
										throw invalid_argument("Incorrect id of subscriber");
									}
									RemoveSubscriber(found[id - 1]);
									cout << "Subscriber removed " << endl;
									cout << endl;
									break;
								}
							}//switch
							break;
						}
					}//switch
					break;
				}
			case 6: 
				{
				cout << "Full list of subscribers: " << endl;
				Print();
				break;
			}
			case 7: 
				{
					cout << "1. Find subscriber by email " << endl;
					cout << "2. Find subscriber by phone " << endl;
					cout << "3. Find subscriber by name " << endl;
					cout << "0. Exit " << endl;
					cout << ">>>>";
					cin >> c2;
					cout << endl;
					switch (c2) 
					{
					case 1: 
						{
							cout << "Enter email: " << endl;
							cout << ">>>>";
							cin >> email;
							auto found1 = email.find("@");
							if (found1 == string::npos)
							{
								throw invalid_argument("Incorrect form of email");
							}
							cout << endl;
							int k = 1;
							vector<Subscriber*> found = FindByEmail(email);
							for (Subscriber* sub : found)
							{
								cout << k << ") " << sub->To_String() << endl;
								k++;
							}
							if (found.size() == 0)
							{
								throw invalid_argument("Not found");
							}
							cout << "Select subscriber to add info: " << endl;
							cout << ">>>>";
							cin >> id;
							cout << endl;
							if (id > found.size() || id < 0)
							{
								throw invalid_argument("Incorrect id of subscriber");
							}
							cout << "1. Change main phone " << endl;
							cout << "2. Change subscriber name or title of institution " << endl;
							cout << "0. Exit " << endl;
							cout << ">>>>";
							cin >> c3;
							cout << endl;
							switch (c3) 
							{
							case 1: 
								{
									cout << "Enter country code: " << endl;
									cout << ">>>>";
									cin >> countryCode;
									cout << endl;
									cout << "Enter short number: " << endl;
									cout << ">>>>";
									cin >> shortNumber;
									cout << endl;
									cout << "1. Landline phone " << endl;
									cout << "2. Mobile phone " << endl;
									cout << "0. Exit " << endl;
									cout << ">>>>";
									cin >> c4;
									cout << endl;
									switch (c4) 
									{
									case 1: 
										{
											cout << "1. Home phone " << endl;
											cout << "2. Office phone " << endl;
											cout << "0. Exit " << endl;
											cout << ">>>>";
											cin >> c5;
											cout << endl;
											switch (c5) 
											{
											case 1: 
												{
													cout << "Enter city code: " << endl;
													cout << ">>>>";
													cin >> cityCode;
													cout << endl;
													LandlinePhone* homePhone = new LandlinePhone(countryCode, shortNumber, cityCode, PhoneType::home);
													found[id - 1]->ChangeMainPhone(homePhone);
													cout << "Main phone changed " << endl;
													cout << endl;
													break;
												}
											case 2: 
												{
													cout << "Enter city code: " << endl;
													cout << ">>>>";
													cin >> cityCode;
													cout << endl;
													LandlinePhone* officePhone = new LandlinePhone(countryCode, shortNumber, cityCode, PhoneType::office);
													found[id - 1]->ChangeMainPhone(officePhone);
													cout << "Main phone changed " << endl;
													cout << endl;
													break;
												}
											}//switch
											break;
										}
									case 2: 
										{
											cout << "1. Home phone " << endl;
											cout << "2. Office phone " << endl;
											cout << "0. Exit " << endl;
											cout << ">>>>";
											cin >> c5;
											cout << endl;
											switch (c5) 
											{
											case 1: 
												{
													cout << "Enter mobile code: " << endl;
													cout << ">>>>";
													cin >> mobileCode;
													cout << endl;
													MobilePhone* homePhone = new MobilePhone(countryCode, shortNumber, mobileCode, PhoneType::home);
													found[id - 1]->ChangeMainPhone(homePhone);
													cout << "Main phone changed " << endl;
													cout << endl;
													break;
												}
											case 2: 
												{
													cout << "Enter mobile code: " << endl;
													cout << ">>>>";
													cin >> mobileCode;
													cout << endl;
													MobilePhone* officePhone = new MobilePhone(countryCode, shortNumber, mobileCode, PhoneType::office);
													found[id - 1]->ChangeMainPhone(officePhone);
													cout << "Main phone changed " << endl;
													cout << endl;
													break;
												}
											}//switch
											break;
										}
									}//switch
									break;
								}
							case 2: 
								{
									cout << "Enter new name or new title: " << endl;
									cin >> ws; getline(cin, name);
									cout << endl;
									ChangeSubscriberTitle(found[id - 1], name);
									cout << "Name or title changed " << endl;
									break;
								}
							}//switch
							break;
						}
					case 2: 
						{
							cout << "Enter phone to find: " << endl;
							cout << ">>>>";
							cin >> phone;
							auto found1 = phone.find("+");
							if (found1 == std::string::npos)
							{
								throw std::invalid_argument("Incorrect form of phone");
							}
							cout << endl;
							vector<Subscriber*> found = FindByPhone(phone);
							int k = 1;
							for (Subscriber* sub : found)
							{
								cout << k << ") " << sub->To_String() << endl;
								k++;
							}
							if (found.size() == 0)
							{
								throw invalid_argument("Not found");
							}
							cout << "Select subscriber to add info: " << endl;
							cout << ">>>>";
							cin >> id;
							cout << endl;
							if (id > found.size() || id < 0)
							{
								throw invalid_argument("Incorrect id of subscriber");
							}
							cout << "1. Change main phone " << endl;
							cout << "2. Change name of subscriber or title of institution " << endl;
							cout << "0. Exit " << endl;
							cout << ">>>>";
							cin >> c3;
							cout << endl;
							switch (c3) 
							{
							case 1: 
								{
									cout << "Enter country code: " << endl;
									cout << ">>>>";
									cin >> countryCode;
									cout << endl;
									cout << "Enter short number: " << endl;
									cout << ">>>>";
									cin >> shortNumber;
									cout << endl;
									cout << "1. Landline phone " << endl;
									cout << "2. Mobile phone " << endl;
									cout << "0. Exit " << endl;
									cout << ">>>>";
									cin >> c4;
									cout << endl;
									switch (c4) 
									{
									case 1: 
										{
											cout << "1. Home phone " << endl;
											cout << "2. Office phone " << endl;
											cout << "0. Exit " << endl;
											cout << ">>>>";
											cin >> c5;
											cout << endl;
											switch (c5) 
											{
											case 1: 
												{
													cout << "Enter city code: " << endl;
													cout << ">>>>";
													cin >> cityCode;
													cout << endl;
													LandlinePhone* homePhone = new LandlinePhone(countryCode, shortNumber, cityCode, PhoneType::home);
													found[id - 1]->ChangeMainPhone(homePhone);
													cout << "Main phone changed " << endl;
													cout << endl;
													break;
												}
											case 2: 
												{
													cout << "Enter city code: " << endl;
													cout << ">>>>";
													cin >> cityCode;
													cout << endl;
													LandlinePhone* officePhone = new LandlinePhone(countryCode, shortNumber, cityCode, PhoneType::office);
													found[id - 1]->ChangeMainPhone(officePhone);
													cout << "Main phone changed " << endl;
													cout << endl;
													break;
												}
											}//switch
											break;
										}
									case 2: 
										{
											cout << "1. Home phone " << endl;
											cout << "2. Office phone " << endl;
											cout << "0. Exit " << endl;
											cout << ">>>>";
											cin >> c5;
											cout << endl;
											switch (c5) 
											{
											case 1: 
												{
													cout << "Enter mobile code: " << endl;
													cout << ">>>>";
													cin >> mobileCode;
													cout << endl;
													MobilePhone* homePhone = new MobilePhone(countryCode, shortNumber, mobileCode, PhoneType::home);
													found[id - 1]->ChangeMainPhone(homePhone);
													cout << "Main phone changed " << endl;
													cout << endl;
													break;
												}
											case 2: 
												{
													cout << "Enter mobile code: " << endl;
													cout << ">>>>";
													cin >> mobileCode;
													cout << endl;
													MobilePhone* officePhone = new MobilePhone(countryCode, shortNumber, mobileCode, PhoneType::office);
													found[id - 1]->ChangeMainPhone(officePhone);
													cout << "Main phone changed " << endl;
													cout << endl;
													break;
												}
											}//switch
											break;
										}
									}//switch
									break;
								}
							case 2: 
								{
									cout << "Enter new name or new title: " << endl;
									cin >> ws; getline(cin, name);
									cout << endl;
									ChangeSubscriberTitle(found[id - 1], name);
									cout << "Name or title changed " << endl;
									break;
								}
							}//switch
							break;
						}
					case 3: 
						{
							cout << "1. Find by full name " << endl;
							cout << "2. Find by first part of full name " << endl;
							cout << "0. Exit " << endl;
							cout << ">>>>";
							cin >> c3;
							cout << endl;
							switch (c3) 
							{
							case 1: 
								{
									cout << "Enter full name: " << endl;
									cin >> ws; getline(cin, name);
									cout << endl;
									vector<Subscriber*> found = FindIndividual(name, true);
									int k = 1;
									for (Subscriber* sub : found)
									{
										cout << k << ") " << sub->To_String() << endl;
										k++;
									}
									if (found.size() == 0)
									{
										throw invalid_argument("Not found");
									}
									cout << "Select subscriber to add info: " << endl;
									cout << ">>>>";
									cin >> id;
									cout << endl;
									if (id > found.size() || id < 0)
									{
										throw invalid_argument("Incorrect id of subscriber");
									}
									cout << "1. Change main phone " << endl;
									cout << "2. Change name of subscriber or title of institution " << endl;
									cout << "0. Exit " << endl;
									cout << ">>>>";
									cin >> c4;
									cout << endl;
									switch (c4) 
									{
									case 1: 
										{
											cout << "Enter country code: " << endl;
											cout << ">>>>";
											cin >> countryCode;
											cout << endl;
											cout << "Enter short number: " << endl;
											cout << ">>>>";
											cin >> shortNumber;
											cout << endl;
											cout << "1. Landline phone " << endl;
											cout << "2. Mobile phone " << endl;
											cout << "0. Exit " << endl;
											cout << ">>>>";
											cin >> c5;
											cout << endl;
											switch (c5) 
											{
											case 1: 
												{
													cout << "1. Home phone " << endl;
													cout << "2. Office phone " << endl;
													cout << "0. Exit " << endl;
													cout << ">>>>";
													cin >> c6;
													cout << endl;
													switch (c6) 
													{
													case 1: 
														{
															cout << "Enter city code: " << endl;
															cout << ">>>>";
															cin >> cityCode;
															cout << endl;
															LandlinePhone* homePhone = new LandlinePhone(countryCode, shortNumber, cityCode, PhoneType::home);
															found[id - 1]->ChangeMainPhone(homePhone);
															cout << "Main phone changed " << endl;
															cout << endl;
															break;
														}
													case 2: 
														{
															cout << "Enter city code: " << endl;
															cout << ">>>>";
															cin >> cityCode;
															cout << endl;
															LandlinePhone* officePhone = new LandlinePhone(countryCode, shortNumber, cityCode, PhoneType::office);
															found[id - 1]->ChangeMainPhone(officePhone);
															cout << "Main phone changed " << endl;
															cout << endl;
															break;
														}
													}//switch
													break;
												}
											case 2: 
												{
													cout << "1. Home phone " << endl;
													cout << "2. Office phone " << endl;
													cout << "0. Exit " << endl;
													cout << ">>>>";
													cin >> c6;
													cout << endl;
													switch (c6)
													{
													case 1:
														{
															cout << "Enter mobile code: " << endl;
															cout << ">>>>";
															cin >> mobileCode;
															cout << endl;
															MobilePhone* homePhone = new MobilePhone(countryCode, shortNumber, mobileCode, PhoneType::home);
															found[id - 1]->ChangeMainPhone(homePhone);
															cout << "Main phone changed " << endl;
															cout << endl;
															break;
														}
													case 2:
														{
															cout << "Enter mobile code: " << endl;
															cout << ">>>>";
															cin >> mobileCode;
															cout << endl;
															MobilePhone* officePhone = new MobilePhone(countryCode, shortNumber, mobileCode, PhoneType::office);
															found[id - 1]->ChangeMainPhone(officePhone);
															cout << "Main phone changed " << endl;
															cout << endl;
															break;
														}
													}//switch
													break;
												}
											}//switch
											break;
										}
									case 2: 
										{
											cout << "Enter new name or new title: " << endl;
											cin >> ws; getline(cin, name);
											cout << endl;
											ChangeSubscriberTitle(found[id - 1], name);
											cout << "Name or title changed " << endl;
											cout << endl;
											break;
										}
									}//switch
									break;
								}
							case 2: 
								{
									cout << "Enter first part of full name: " << endl;
									cin >> ws; getline(cin, name);
									cout << endl;
									vector<Subscriber*> found = FindIndividual(name, false);
									int k = 1;
									for (Subscriber* sub : found)
									{
										cout << k << ") " << sub->To_String() << endl;
										k++;
									}
									if (found.size() == 0)
									{
										throw invalid_argument("Not found");
									}
									cout << "Select subscriber to add info: " << endl;
									cout << ">>>>";
									cin >> id;
									cout << endl;
									if (id > found.size() || id < 0)
									{
										throw invalid_argument("Incorrect id of subscriber");
									}
									cout << "1. Change main phone " << endl;
									cout << "2. Change name of subscriber or title of institution " << endl;
									cout << "0. Exit " << endl;
									cout << ">>>>";
									cin >> c4;
									cout << endl;
									switch (c4) 
									{
									case 1: 
										{
											cout << "Enter country code: " << endl;
											cout << ">>>>";
											cin >> countryCode;
											cout << endl;
											cout << "Enter short number: " << endl;
											cout << ">>>>";
											cin >> shortNumber;
											cout << endl;
											cout << "1. Landline phone " << endl;
											cout << "2. Mobile phone " << endl;
											cout << "0. Exit " << endl;
											cout << ">>>>";
											cin >> c5;
											cout << endl;
											switch (c5) 
											{
											case 1: 
												{
													cout << "1. Home phone " << endl;
													cout << "2. Office phone " << endl;
													cout << "0. Exit " << endl;
													cout << ">>>>";
													cin >> c6;
													cout << endl;
													switch (c6) 
													{
													case 1: 
														{
															cout << "Enter city code: " << endl;
															cout << ">>>>";
															cin >> cityCode;
															cout << endl;
															LandlinePhone* homePhone = new LandlinePhone(countryCode, shortNumber, cityCode, PhoneType::home);
															found[id - 1]->ChangeMainPhone(homePhone);
															cout << "Main phone changed " << endl;
															cout << endl;
															break;
														}
													case 2: 
														{
															cout << "Enter city code: " << endl;
															cout << ">>>>";
															cin >> cityCode;
															cout << endl;
															LandlinePhone* officePhone = new LandlinePhone(countryCode, shortNumber, cityCode, PhoneType::office);
															found[id - 1]->ChangeMainPhone(officePhone);
															cout << "Main phone changed " << endl;
															cout << endl;
															break;
														}
													}//switch
													break;
												}
											case 2: 
												{
													cout << "1. Home phone " << endl;
													cout << "2. Office phone " << endl;
													cout << "0. Exit " << endl;
													cout << ">>>>";
													cin >> c6;
													cout << endl;
													switch (c6) 
													{
													case 1: 
														{
															cout << "Enter mobile code: " << endl;
															cout << ">>>>";
															cin >> mobileCode;
															cout << endl;
															MobilePhone* homePhone = new MobilePhone(countryCode, shortNumber, cityCode, PhoneType::home);
															found[id - 1]->ChangeMainPhone(homePhone);
															cout << "Main phone changed " << endl;
															cout << endl;
															break;
														}
													case 2: 
														{
															cout << "Enter mobile code: " << endl;
															cout << ">>>>";
															cin >> mobileCode;
															cout << endl;
															MobilePhone* officePhone = new MobilePhone(countryCode, shortNumber, cityCode, PhoneType::office);
															found[id - 1]->ChangeMainPhone(officePhone);
															cout << "Main phone changed " << endl;
															cout << endl;
															break;
														}
													}//switch
													break;
												}
											}//switch
											break;
										}
									case 2: 
										{
											cout << "Enter new name or new title: " << endl;
											cin >> ws; getline(cin, name);
											cout << endl;
											ChangeSubscriberTitle(found[id - 1], name);
											cout << "Name or title changed " << endl;
											cout << endl;
											break;
										}
									}//switch
									break;
								}
							}//switch
							break;
						}
					}//switch
					break;
				}
			break;		
			}//switch
		}
		catch (invalid_argument& ia)
		{
			cout << ia.what() << endl;
		}
	} while (c1 != 0);
	
	
	
}


