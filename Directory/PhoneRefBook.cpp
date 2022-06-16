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

vector<Subscriber*> PhoneRefBook::FindByPhone(const Phone& phone) const
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

void PhoneRefBook::RemovePhone(Subscriber* ptrSubs, const Phone* phone)
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

	ptrSubs->RemovePhone(*phone);
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
	int c1, c2, c3, c4, c5, c6, c7;
	string name, name_lead, new_name, email, phone, gender, institution, kindofactivity;
	string countryCode, shortNumber, mobileCode, cityCode;
	//string countryCode_1, shortNumber_1, mobileCode_1, cityCode_1;
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
								throw invalid_argument("Incorrect form of name");
							}
							cout << endl;
							vector<Subscriber*> found = FindByEmail(email);
							cout << "1. Add phone " << endl;
							cout << "2. Add email " << endl;
							cout << ">>>>";
							cin >> c3;
							cout << endl;
							switch (c3)
							{
							case 1: 
								{
									cout << "1. Landline phone " << endl;
									cout << "2. Mobile phone " << endl;
									cout << ">>>>";
									cin >> c4;
									cout <<  endl;
									switch (c4) 
									{
									case 1:
										{
											cout << "1. Home phone " << endl;
											cout << "2. Office phone " << endl;
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
													LandlinePhone* homePhone = new LandlinePhone (countryCode, shortNumber, cityCode, PhoneType::home);
													for (Subscriber* sub : found) 
													{
														sub->AddPhone(homePhone);
													}
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
													LandlinePhone* officePhone = new LandlinePhone (countryCode, shortNumber, cityCode, PhoneType::office);
													for (Subscriber* sub : found)
													{
														sub->AddPhone(officePhone);
													}
												break;
												}
											}//switch
											break;
										}
									case 2: 
										{
											cout << "1. Home phone " << endl;
											cout << "2. Office phone " << endl;
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
													cin >> mobileCode;
													cout << endl;
													MobilePhone* homePhone = new MobilePhone(countryCode, shortNumber, mobileCode, PhoneType::home);
													for (Subscriber* sub : found) 
													{
														sub->AddPhone(homePhone);
													}
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
													cin >> mobileCode;
													cout << endl;
													MobilePhone* officePhone = new MobilePhone(countryCode, shortNumber, mobileCode, PhoneType::office); 
													for (Subscriber* sub : found) 
													{
														sub->AddPhone(officePhone);
													}
													break;
												}
											}//switch
										break;
										}
									}//switch
								break;
								}
								break;
							case 2: 
								{
									cout << "Enter new email: " << endl;
									cout << ">>>>";
									cin >> email;
									auto found1 = email.find("@");
									if (found1 == std::string::npos)
									{
										throw std::invalid_argument("Incorrect form of email");
									}
									cout << endl;
									for (Subscriber* sub : found) 
									{
										sub->AddEmail(email);
									}
									break;
								}
							}//switch
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
							cout << "Select phone type: " << endl;
							cout << "1. Landline phone " << endl;
							cout << "2. Mobile phone " << endl;
							cout << ">>>>";
							cin >> c3;
							cout << endl;
							switch (c3) 
							{
							case 1:
								{
									cout << "1. Home phone " << endl;
									cout << "2. Office phone " << endl;
									cout << ">>>>";
									cin >> c4;
									cout << endl;
									switch (c4) 
									{
									case 1:
										{
											cout << "Enter city code: " << endl;
											cout << ">>>>";
											cin >> cityCode;
											cout << endl;
											LandlinePhone llphone(countryCode, shortNumber, cityCode, PhoneType::home);
											vector<Subscriber*> found = FindByPhone(llphone);
											cout << "1. Add phone " << endl;
											cout << "2. Add email " << endl;
											cout << ">>>>";
											cin >> c5;
											cout << endl;
											switch (c5) 
											{
											case 1: 
												{
													cout << "1. Landline phone " << endl;
													cout << "2. Mobile phone " << endl;
													cout << ">>>>";
													cin >> c6;
													cout << endl;
													switch (c6) 
													{
													case 1:
														{
															cout << "1. Home phone " << endl;
															cout << "2. Office phone " << endl;
															cout << ">>>>";
															cin >> c7;
															cout << endl;
															switch (c7) 
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
																	cout << "Enter city code:" << endl;
																	cout << ">>>>";
																	cin >> cityCode;
																	cout << endl;
																	LandlinePhone* homePhone = new LandlinePhone(countryCode, shortNumber, cityCode, PhoneType::home);
																	for (Subscriber* sub : found) 
																	{
																		sub->AddPhone(homePhone);
																	}
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
																	cout << "Enter city code:" << endl;
																	cout << ">>>>";
																	cin >> cityCode;
																	cout << endl;
																	LandlinePhone* homePhone = new LandlinePhone(countryCode, shortNumber, cityCode, PhoneType::office);
																	for (Subscriber* sub : found)
																	{
																		sub->AddPhone(homePhone);
																	}
																	break;
																}
															}//switch
														break;
														}
													case 2: 
														{
															cout << "1. Home phone " << endl;
															cout << "2. Office phone " << endl;
															cout << ">>>>";
															cin >> c7;
															cout << endl;
															switch (c7) 
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
																	cout << "Enter mobile code:" << endl;
																	cout << ">>>>";
																	cin >> mobileCode;
																	cout << endl;
																	MobilePhone homePhone(countryCode, shortNumber, mobileCode, PhoneType::home);
																	for (Subscriber* sub : found) 
																	{
																		sub->AddPhone(&homePhone);
																	}
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
																	cout << "Enter mobile code:" << endl;
																	cout << ">>>>";
																	cin >> mobileCode;
																	cout << endl;
																	MobilePhone officePhone(countryCode, shortNumber, mobileCode, PhoneType::office);
																	for (Subscriber* sub : found)
																	{
																		sub->AddPhone(&officePhone);
																	}
																	break;
																}
															}//switch(done)
														break;
														}
													}//switch(done)
												break;
												}
											case 2: 
												{
													cout << "Enter new email: " << endl;
													cout << ">>>>";
													cin >> email;
													auto found1 = email.find("@");
													if (found1 == std::string::npos)
													{
														throw std::invalid_argument("Incorrect form of email");
													}
													cout << endl;
													for (Subscriber* sub : found) 
													{
														sub->AddEmail(email);
													}
													break;
												}
											}//switch
										break;
										}
									case 2: 
										{
											cout << "Enter city code: " << endl;
											cout << ">>>>";
											cin >> cityCode;
											cout << endl;
											LandlinePhone llphone(countryCode, shortNumber, cityCode, PhoneType::office);
											vector<Subscriber*> found = FindByPhone(llphone);
											cout << "1. Add phone " << endl;
											cout << "2. Add email " << endl;
											cout << ">>>>";
											cin >> c5;
											cout << endl;
											switch (c5) 
											{
											case 1: 
												{
													cout << "1. Landline phone " << endl;
													cout << "2. Mobile phone " << endl;
													cout << ">>>>";
													cin >> c6;
													cout << endl;
													switch (c6) 
													{
													case 1: 
														{
															cout << "1. Home phone " << endl;
															cout << "2. Office phone " << endl;
															cout << ">>>>";
															cin >> c7;
															cout << endl;
															switch (c7) 
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
																	cout << "Enter city code:" << endl;
																	cout << ">>>>";
																	cin >> cityCode;
																	cout << endl;
																	LandlinePhone homePhone(countryCode, shortNumber, cityCode, PhoneType::home);
																	for (Subscriber* sub : found)
																	{
																		sub->AddPhone(&homePhone);
																	}
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
																	cout << "Enter city code:" << endl;
																	cout << ">>>>";
																	cin >> cityCode;
																	cout << endl;
																	LandlinePhone homePhone(countryCode, shortNumber, cityCode, PhoneType::office);
																	for (Subscriber* sub : found)
																	{
																		sub->AddPhone(&homePhone);
																	}
																	break;
																}
															}//switch
														}
													case 2: 
														{
															cout << "1. Home phone " << endl;
															cout << "2. Office phone " << endl;
															cout << ">>>>";
															cin >> c7;
															cout << endl;
															switch (c7) 
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
																	cout << "Enter mobile code: " << endl;
																	cout << ">>>>";
																	cin >> mobileCode;
																	cout << endl;
																	MobilePhone homePhone(countryCode, shortNumber, mobileCode, PhoneType::home);
																	for (Subscriber* sub : found) 
																	{
																		sub->AddPhone(&homePhone);
																	}
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
																	cout << "Enter mobile code: " << endl;
																	cout << ">>>>";
																	cin >> mobileCode;
																	cout << endl;
																	MobilePhone homePhone(countryCode, shortNumber, mobileCode, PhoneType::office);
																	for (Subscriber* sub : found)
																	{
																		sub->AddPhone(&homePhone);
																	}
																	break;
																}
															}//switch
														break;
														}
													}//switch
												break;
												}
											}//switch
										}
									}//switch
								break;
								}
							case 2: 
								{
									cout << "1. Home phone" << endl;
									cout << "2. Office phone " << endl;
									cout << ">>>>";
									cin >> c4;
									cout << endl;
									switch (c4) 
									{
									case 1: 
										{
											cout << "Enter mobile code: " << endl;
											cout << ">>>>";
											cin >> mobileCode;
											cout << endl;
											MobilePhone mphone(countryCode, shortNumber, mobileCode, PhoneType::home);
											vector<Subscriber*> found = FindByPhone(mphone);
											cout << "1. Add phone " << endl;
											cout << "2. Add email " << endl;
											cout << ">>>>";
											cin >> c5;
											cout << endl;
											switch (c5) 
											{
											case 1: 
												{
													cout << "1. Landline phone " << endl;
													cout << "2. Mobile phone " << endl;
													cout << ">>>>";
													cin >> c6;
													cout << endl;
													switch (c6) 
													{
													case 1: 
														{
															cout << "1. Home phone " << endl;
															cout << "2. Office phone " << endl;
															cout << ">>>>";
															cin >> c7;
															cout << endl;
															switch (c7) 
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
																	for (Subscriber* sub : found) 
																	{
																		sub->AddPhone(homePhone);
																	}
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
																	LandlinePhone* homePhone = new LandlinePhone(countryCode, shortNumber, cityCode, PhoneType::office);
																	for (Subscriber* sub : found)
																	{
																		sub->AddPhone(homePhone);
																	}
																	break;
																}
															}//switch
														break;
														}
													case 2: 
														{
															cout << "1. Home phone" << endl;
															cout << "2. Office phone " << endl;
															cout << ">>>>";
															cin >> c7;
															cout << endl;
															switch (c7) 
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
																	cout << "Enter mobile code: " << endl;
																	cout << ">>>>";
																	cin >> mobileCode;
																	cout << endl;
																	MobilePhone* homePhone = new MobilePhone(countryCode, shortNumber, mobileCode, PhoneType::home);
																	for (Subscriber* sub : found) 
																	{
																		sub->AddPhone(homePhone);
																	}
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
																	cout << "Enter mobile code: " << endl;
																	cout << ">>>>";
																	cin >> mobileCode;
																	cout << endl;
																	MobilePhone* officePhone = new MobilePhone(countryCode, shortNumber, mobileCode, PhoneType::office);
																	for (Subscriber* sub : found)
																	{
																		sub->AddPhone(officePhone);
																	}
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
													for (Subscriber* sub : found) 
													{
														sub->AddEmail(email);
													}
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
							cout << "Enter full name: " << endl;
							cout << ">>>>";
							cin >> ws; getline(cin, name);
							cout << endl;
							vector<Subscriber*> found = FindIndividual(name);
							cout << "1. Add phone " << endl;
							cout << "2. Add email " << endl;
							cout << ">>>>";
							cin >> c3;
							cout << endl;
							switch (c3) 
							{
							case 1: 
								{
									cout << "1. Landline phone " << endl;
									cout << "2. Mobile phone " << endl;
									cout << ">>>>";
									cin >> c4;
									cout << endl;
									switch (c4) 
									{
									case 1: 
										{
											cout << "1. Home phone " << endl;
											cout << "2. Office phone " << endl;
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
													cout << "Enter city code" << endl;
													cout << ">>>>";
													cin >> cityCode;
													cout << endl;
													LandlinePhone* homePhone = new LandlinePhone(countryCode, shortNumber, cityCode, PhoneType::home);
													for (Subscriber* sub : found) 
													{
														sub->AddPhone(homePhone);
													}
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
													cout << "Enter city code" << endl;
													cout << ">>>>";
													cin >> cityCode;
													cout << endl;
													LandlinePhone* officePhone = new LandlinePhone(countryCode, shortNumber, cityCode, PhoneType::office);
													for (Subscriber* sub : found)
													{
														sub->AddPhone(officePhone);
													}
													break;
												}
											}//switch
										break;
										}
									case 2: 
										{
											cout << "1. Home phone " << endl;
											cout << "2. Office phone " << endl;
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
													cout << "Enter mobile code" << endl;
													cout << ">>>>";
													cin >> mobileCode;
													cout << endl;
													MobilePhone* homePhone = new MobilePhone(countryCode, shortNumber, mobileCode, PhoneType::home);
													for (Subscriber* sub : found)
													{
														sub->AddPhone(homePhone);
													}
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
													cout << "Enter mobile code" << endl;
													cout << ">>>>";
													cin >> mobileCode;
													cout << endl;
													MobilePhone* officePhone = new MobilePhone(countryCode, shortNumber, mobileCode, PhoneType::office);
													for (Subscriber* sub : found)
													{
														sub->AddPhone(officePhone);
													}
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
								auto found1 = email.find("@");
								if (found1 == std::string::npos)
								{
									throw std::invalid_argument("Incorrect form of email");
								}
								cout << endl;
								for (Subscriber* sub : found)
								{
									sub->AddEmail(email);
								}
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
							if (found1 == std::string::npos)
							{
								throw std::invalid_argument("Incorrect form of email");
							}
							cout << endl;
							vector<Subscriber*> found = FindByEmail(email);
							cout << "1. Remove phone " << endl;
							cout << "2. Remove email " << endl;
							cout << ">>>>";
							cin >> c3;
							cout << endl;
							switch (c3) 
							{
							case 1: 
								{
									cout << "1. Landline phone " << endl;
									cout << "2. Mobile phone " << endl;
									cout << ">>>>";
									cin >> c4;
									cout << endl;
									switch (c4) 
									{
									case 1: 
										{
											cout << "1. Home phone " << endl;
											cout << "2. Office phone " << endl;
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
													LandlinePhone homePhone(countryCode, shortNumber, cityCode, PhoneType::home);
													for (Subscriber* sub : found) 
													{
														sub->RemovePhone(homePhone);
													}
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
													LandlinePhone officePhone(countryCode, shortNumber, cityCode, PhoneType::office);
													for (Subscriber* sub : found)
													{
														sub->RemovePhone(officePhone);
													}
													break;
												}
											}//switch
										break;
										}
									case 2: 
										{
											cout << "1. Home phone " << endl;
											cout << "2. Office phone " << endl;
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
													cout << "Enter mobile code: " << endl;
													cout << ">>>>";
													cin >> mobileCode;
													cout << endl;
													MobilePhone homePhone(countryCode, shortNumber, mobileCode, PhoneType::home);
													for (Subscriber* sub : found) 
													{
														sub->RemovePhone(homePhone);
													}
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
													cout << "Enter mobile code: " << endl;
													cout << ">>>>";
													cin >> mobileCode;
													cout << endl;
													MobilePhone officePhone(countryCode, shortNumber, mobileCode, PhoneType::office);
													for (Subscriber* sub : found)
													{
														sub->RemovePhone(officePhone);
													}
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
									cout << "Enter email to remove: " << endl;
									cout << ">>>>";
									cin >> email;
									auto found1 = email.find("@");
									if (found1 == std::string::npos)
									{
										throw std::invalid_argument("Incorrect form of email");
									}
									for (Subscriber* sub : found) 
									{
										sub->RemoveEmail(email);
									}
									break;
								}
							}//switch
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
							cout << "Select phone type: " << endl;
							cout << "1. Landline phone " << endl;
							cout << "2. Mobile phone " << endl;
							cout << ">>>>";
							cin >> c3;
							switch (c3) 
							{
							case 1: 
								{
									cout << "1. Home phone " << endl;
									cout << "2. Office phone " << endl;
									cout << ">>>>";
									cin >> c4;
									cout << endl;
									switch (c4) 
									{
									case 1: 
										{
											cout << "Enter city code: " << endl;
											cout << ">>>>";
											cin >> cityCode;
											cout << endl;
											LandlinePhone llphone(countryCode, shortNumber, cityCode, PhoneType::home);
											vector<Subscriber*> found = FindByPhone(llphone);
											cout << "1. Remove phone " << endl;
											cout << "2. Remove email " << endl;
											cout << ">>>>";
											cin >> c5;
											cout << endl;
											switch (c5) 
											{
											case 1: 
												{
													cout << "1. Landline phone " << endl;
													cout << "2. Mobile code " << endl;
													cout << ">>>>";
													cin >> c6;
													cout << endl;
													switch (c6) 
													{
													case 1: 
														{
															cout << "1. Home phone " << endl;
															cout << "2. Office phone " << endl;
															cout << ">>>>";
															cin >> c7;
															cout << endl;
															switch (c7) 
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
																	LandlinePhone homePhone(countryCode, shortNumber, cityCode, PhoneType::home);
																	for (Subscriber* sub : found) 
																	{
																		sub->RemovePhone(homePhone);
																	}
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
																	LandlinePhone officePhone(countryCode, shortNumber, cityCode, PhoneType::office);
																	for (Subscriber* sub : found)
																	{
																		sub->RemovePhone(officePhone);
																	}
																	break;
																}
															}//switch
														}
													case 2: 
														{
															cout << "1. Home phone" << endl;
															cout << "2. Office phone " << endl;
															cout << ">>>>";
															cin >> c7;
															switch (c7) 
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
																	cout << "Enter mobile code: " << endl;
																	cout << ">>>>";
																	cin >> mobileCode;
																	cout << endl;
																	MobilePhone homePhone(countryCode, shortNumber, mobileCode, PhoneType::home);
																	for (Subscriber* sub : found) 
																	{
																		sub->RemovePhone(homePhone);
																	}
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
																	cout << "Enter mobile code: " << endl;
																	cout << ">>>>";
																	cin >> mobileCode;
																	cout << endl;
																	MobilePhone officePhone(countryCode, shortNumber, mobileCode, PhoneType::office);
																	for (Subscriber* sub : found)
																	{
																		sub->RemovePhone(officePhone);
																	}
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
													cout << "Enter email to remove: " << endl;
													cout << ">>>>";
													cin >> email;
													auto found1 = email.find("@");
													if (found1 == string::npos)
													{
														throw invalid_argument("Incorrect form of name");
													}
													cout << endl;
													for (Subscriber* sub : found) 
													{
														sub->RemoveEmail(email);
													}
													break;
												}
											}//switch
										break;
										}
									case 2:
										{
											cout << "Enter city code: " << endl;
											cout << ">>>>";
											cin >> cityCode;
											cout << endl;
											LandlinePhone llphone(countryCode, shortNumber, cityCode, PhoneType::office);
											vector<Subscriber*> found = FindByPhone(llphone);
											cout << "1. Remove phone " << endl;
											cout << "2. Remove email " << endl;
											cout << ">>>>";
											cin >> c5;
											cout << endl;
											switch (c5) 
											{
											case 1: 
												{
													cout << "1. Landline phone " << endl;
													cout << "2. Mobile code " << endl;
													cout << ">>>>";
													cin >> c6;
													cout << endl;
													switch (c6)
													{
													case 1:
														{
															cout << "1. Home phone " << endl;
															cout << "2. Office phone " << endl;
															cout << ">>>>";
															cin >> c7;
															cout << endl;
															switch (c7) 
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
																	LandlinePhone homePhone(countryCode, shortNumber, cityCode, PhoneType::home);
																	for (Subscriber* sub : found)
																	{
																		sub->RemovePhone(homePhone);
																	}
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
																	LandlinePhone officePhone(countryCode, shortNumber, cityCode, PhoneType::office);
																	for (Subscriber* sub : found)
																	{
																		sub->RemovePhone(officePhone);
																	}
																	break;
																}
															}//switch
														break;
														}
													case 2: 
														{
															cout << "1. Home phone " << endl;
															cout << "2. Office phone " << endl;
															cout << ">>>>";
															cin >> c7;
															cout << endl;
															switch (c7) 
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
																	MobilePhone homePhone(countryCode, shortNumber, cityCode, PhoneType::home);
																	for (Subscriber* sub : found) 
																	{
																		sub->RemovePhone(homePhone);
																	}
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
																	MobilePhone officePhone(countryCode, shortNumber, cityCode, PhoneType::office);
																	for (Subscriber* sub : found)
																	{
																		sub->RemovePhone(officePhone);
																	}
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
													cout << "Enter email to remove: " << endl;
													cout << ">>>>";
													cin >> email;
													cout << endl;
													for (Subscriber* sub : found) 
													{
														sub->RemoveEmail(email);
													}
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
									cout << "1. Home phone " << endl;
									cout << "2. Office phone " << endl;
									cout << ">>>>";
									cin >> c4;
									cout << endl;
									switch (c4) 
									{
										cout << "Enter mobile code: " << endl;
										cout << ">>>>";
										cin >> mobileCode;
										cout << endl;
										MobilePhone mphone(countryCode, shortNumber, mobileCode, PhoneType::home);
										vector<Subscriber*> found = FindByPhone(mphone);
										cout << "1. Remove phone " << endl;
										cout << "2. Remove email " << endl;
										cout << ">>>>";
										cin >> c5;
										cout << endl;
										switch (c5) 
										{
										case 1: 
											{
												cout << "1. Landline phone " << endl;
												cout << "2. Mobile phone " << endl;
												cout << ">>>>";
												cin >> c6;
												cout << endl;
												switch (c6) 
												{
												case 1: 
													{
														cout << "1. Home phone " << endl;
														cout << "2. Office phone " << endl;
														cout << ">>>>";
														cin >> c7;
														cout << endl;
														switch (c7) 
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
																LandlinePhone homePhone(countryCode, shortNumber, cityCode, PhoneType::home);
																for (Subscriber* sub : found)
																{
																	sub->RemovePhone(homePhone);
																}
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
																LandlinePhone officePhone(countryCode, shortNumber, cityCode, PhoneType::office);
																for (Subscriber* sub : found)
																{
																	sub->RemovePhone(officePhone);
																}
																break;
															}
														}//switch
													break;
													}
												case 2: 
													{
														cout << "1. Home phone " << endl;
														cout << "2. Office phone " << endl;
														cout << ">>>>";
														cin >> c7;
														cout << endl;
														switch (c7) 
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
																MobilePhone homePhone(countryCode, shortNumber, cityCode, PhoneType::home);
																for (Subscriber* sub : found)
																{
																	sub->RemovePhone(homePhone);
																}
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
																MobilePhone officePhone(countryCode, shortNumber, cityCode, PhoneType::office);
																for (Subscriber* sub : found)
																{
																	sub->RemovePhone(officePhone);
																}
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
												cout << "Enter email to remove: " << endl;
												cout << ">>>>";
												cin >> email;
												auto found1 = email.find("@");
												if (found1 == string::npos)
												{
													throw invalid_argument("Incorrect form of name");
												}
												cout << endl;
												for (Subscriber* sub : found)
												{
													sub->RemoveEmail(email);
												}
												break;
											}
										}
										break;
									}//switch
								break;
								}
							}//switch
						break;
						}
					case 3: 
						{
							cout << "Enter full name: " << endl;
							cout << ">>>>";
							cin >> ws; getline(cin, name);
							cout << endl;
							vector<Subscriber*> found = FindIndividual(name);
							cout << "1. Remove phone " << endl;
							cout << "2. Remove email " << endl;
							cout << ">>>>";
							cin >> c3;
							switch (c3)
							{
							case 1:
								{
									cout << "1. Landline phone " << endl;
									cout << "2. Mobile phone " << endl;
									cout << ">>>>";
									cin >> c4;
									cout << endl;
									switch (c4) 
									{
									case 1: 
										{
											cout << "1. Home phone " << endl;
											cout << "2. Office phone " << endl;
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
													LandlinePhone homePhone(countryCode, shortNumber, cityCode, PhoneType::home);
													for (Subscriber* sub : found)
													{
														sub->RemovePhone(homePhone);
													}
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
													LandlinePhone officePhone(countryCode, shortNumber, cityCode, PhoneType::office);
													for (Subscriber* sub : found)
													{
														sub->RemovePhone(officePhone);
													}
													break;
												}
											}//switch
										break;
										}
									case 2: 
										{
											cout << "1. Home phone " << endl;
											cout << "2. Office phone " << endl;
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
													cout << "Enter mobile code: " << endl;
													cout << ">>>>";
													cin >> mobileCode;
													MobilePhone homePhone(countryCode, shortNumber, mobileCode, PhoneType::home);
													for (Subscriber* sub : found) 
													{
														sub->RemovePhone(homePhone);
													}
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
													cout << "Enter mobile code: " << endl;
													cout << ">>>>";
													cin >> mobileCode;
													MobilePhone officePhone(countryCode, shortNumber, mobileCode, PhoneType::office);
													for (Subscriber* sub : found)
													{
														sub->RemovePhone(officePhone);
													}
													break;
												}
											}
										}
									}//switch
								break;
								}
							case 2:
								{
									cout << "Enter email to remove: " << endl;
									cout << ">>>>";
									cin >> email;
									auto found1 = email.find("@");
									if (found1 == string::npos)
									{
										throw invalid_argument("Incorrect form of name");
									}
									cout << endl;
									for (Subscriber* sub : found) 
									{
										sub->RemoveEmail(email);
									}
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
								throw invalid_argument("Incorrect form of name");
							}
							cout << endl;
							vector<Subscriber*> found = FindByEmail(email);
							for (int i = 0; i < found.size(); i++)
							{
								cout << found[i]->To_String() << endl;
							}
							break;
						}
					case 2: 
						{
							cout << "1. Landline phone " << endl;
							cout << "2. Mobile phone " << endl;
							cout << ">>>>";
							cin >> c3;
							cout << endl;
							switch (c3) 
							{
							case 1: 
								{
									cout << "1. Home phone " << endl;
									cout << "2. Office phone " << endl;
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
											cout << "Enter city code: " << endl;
											cout << ">>>>";
											cin >> cityCode;
											cout << endl;
											LandlinePhone homePhone(countryCode, shortNumber, cityCode, PhoneType::home);
											vector<Subscriber*> found = FindByPhone(homePhone);
											for (int i = 0; i < found.size(); i++)
											{
												cout << found[i]->To_String() << endl;
											}
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
											LandlinePhone officePhone(countryCode, shortNumber, cityCode, PhoneType::office);
											vector<Subscriber*> found = FindByPhone(officePhone);
											for (int i = 0; i < found.size(); i++)
											{
												cout << found[i]->To_String() << endl;
											}
											break;
										}
									}//switch
								break;
								}
							case 2: 
								{
									cout << "1. Home phone " << endl;
									cout << "2. Office phone " << endl;
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
											cout << "Enter mobile code: " << endl;
											cout << ">>>>";
											cin >> mobileCode;
											cout << endl;
											MobilePhone homePhone(countryCode, shortNumber, mobileCode, PhoneType::home);
											vector<Subscriber*> found = FindByPhone(homePhone);
											for (int i = 0; i < found.size(); i++)
											{
												cout << found[i]->To_String() << endl;
											}
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
											cout << "Enter mobile code: " << endl;
											cout << ">>>>";
											cin >> mobileCode;
											cout << endl;
											MobilePhone officePhone(countryCode, shortNumber, mobileCode, PhoneType::office);
											vector<Subscriber*> found = FindByPhone(officePhone);
											for (int i = 0; i < found.size(); i++)
											{
												cout << found[i]->To_String() << endl;
											}
											break;
										}
									}//switch
									break;
								}
							}//switch
						}
					case 3: 
						{
							cout << "Enter name or full name: " << endl;
							cout << ">>>>";
							cin >> ws; getline(cin, name);
							cout << endl;
							vector<Subscriber*> found = FindIndividual(name);
							for (int i = 0; i < found.size(); i++)
							{
								cout << found[i]->To_String() << endl;
							}
							break;
						}
					}//switch
					break;
				}
				case 4: 
				{
					cout << "Enter name: " << endl;
					cout << ">>>>";
					cin >> ws; getline(cin, name); 
					cout << endl;
					cout << "1. Individual subscriber " << endl;
					cout << "2. Institution subscriber " << endl;
					cout << ">>>>";
					cin >> c2;
					cout << endl;
					switch (c2) 
					{
					case 1: 
						{
							cout << "1. Male " << endl;
							cout << "2. Female " << endl;
							cout << ">>>>";
							cin >> c3;
							cout << endl;
							switch (c3) 
							{
							case 1: 
								{
									cout << "1. Subscriber has institution " << endl;
									cout << "2. Subscriber has not institution " << endl;
									cout << ">>>>";
									cin >> c4;
									cout << endl;
									switch (c4) 
									{
									case 1: 
										{
											cout << "1. With leader " << endl;
											cout << "2. Without leader " << endl;
											cout << ">>>>";
											cin >> c5;
											cout << endl;
											switch (c5) 
											{
											case 1: 
												{
													cout << "Enter name of leader: " << endl;
													cout << ">>>>";
													cin >> ws; getline(cin, name_lead);
													cout << endl;
													cout << "1. Male " << endl;
													cout << "2. Female " << endl;
													cout << ">>>>";
													cin >> c5;
													cout << endl;
													switch (c5)
													{
													case 1:
														{
															cout << "Enter title of institution: " << endl;
															cout << ">>>>";
															cin >> institution;
															cout << endl;
															cout << "Entet kind of activity: " << endl;
															cout << ">>>>";
															cin >> kindofactivity;
															cout << endl;
															Person* lead = new Person(name_lead, Gender::male, NULL);
															Institution* inst = new Institution(institution, kindofactivity, lead);
															Person*  pers = new Person (name, Gender::male, inst);
															IndividualSubscriber indSub(pers);
															AddSubscriber(&indSub);
															cout << "Subscriber added " << endl;
															cout << endl;
															break;
														}
													case 2:
														{
															cout << "Enter title of institution: " << endl;
															cout << ">>>>";
															cin >> institution;
															cout << endl;
															cout << "Entet king of activity: " << endl;
															cout << ">>>>";
															cin >> kindofactivity;
															cout << endl;
															Person* lead = new Person(name_lead, Gender::female, NULL);
															Institution* inst = new Institution(institution, kindofactivity, lead);
															Person* pers = new Person(name, Gender::male, inst);
															IndividualSubscriber indSub(pers);
															AddSubscriber(&indSub);
															cout << "Subscriber added " << endl;
															cout << endl;
															break;
														}
													}//switch
												break;
												}
											case 2: 
												{
													cout << "Enter title of institution: " << endl;
													cout << ">>>>";
													cin >> institution;
													cout << endl;
													cout << "Entet king of activity: " << endl;
													cout << ">>>>";
													cin >> kindofactivity;
													cout << endl;
													Institution* inst = new Institution(institution, kindofactivity, NULL);
													Person* pers = new Person(name, Gender::male, inst);
													IndividualSubscriber IndSub(pers);
													AddSubscriber(&IndSub);
													cout << "Subscriber added " << endl;
													cout << endl;
													break;
												}
											}//switch
										break;
										}
									case 2: 
										{
											Person* pers = new Person(name, Gender::male, NULL);
											IndividualSubscriber indPers(pers);
											AddSubscriber(&indPers);
											cout << "Subscriber added " << endl;
											cout << endl;
											break;
										}
									}//switch
								break;
								}
							case 2: 
								{
									cout << "1. Subscriber has institution " << endl;
									cout << "2. Subscriber has not institution " << endl;
									cout << ">>>>";
									cin >> c4;
									cout << endl;
									switch (c4) 
									{
									case 1: 
										{
											cout << "1. With leader " << endl;
											cout << "2. Without leader " << endl;
											cout << ">>>>";
											cin >> c5;
											cout << endl;
											switch (c5) 
											{
											case 1: 
												{
													cout << "Enter name of leader: " << endl;
													cout << ">>>>";
													cin >> ws; getline(cin, name_lead);
													cout << endl;
													cout << "1. Male " << endl;
													cout << "2. Female " << endl;
													cout << ">>>>";
													cin >> c5;
													cout << endl;
													switch (c5)
													{
													case 1:
														{
															cout << "Enter title of institution: " << endl;
															cout << ">>>>";
															cin >> institution;
															cout << endl;
															cout << "Entet king of activity: " << endl;
															cout << ">>>>";
															cin >> kindofactivity;
															cout << endl;
															Person* lead = new Person(name_lead, Gender::male, NULL);
															Institution* inst = new Institution(institution, kindofactivity, lead);
															Person* pers = new Person(name, Gender::female, inst);
															IndividualSubscriber indPers(pers);
															AddSubscriber(&indPers);
															cout << "Subscriber added " << endl;
															cout << endl;
															break;
														}
													case 2:
														{
															cout << "Enter title of institution: " << endl;
															cout << ">>>>";
															cin >> institution;
															cout << endl;
															cout << "Entet king of activity: " << endl;
															cout << ">>>>";
															cin >> kindofactivity;
															cout << endl;
															Person* lead = new Person(name_lead, Gender::female, NULL);
															Institution* inst = new Institution(institution, kindofactivity, lead);
															Person* pers = new Person(name, Gender::female, inst);
															IndividualSubscriber indPers(pers);
															AddSubscriber(&indPers);
															cout << "Subscriber added " << endl;
															cout << endl;
															break;
														}
													}//switch
													break;
												}
											case 2: 
												{
													cout << "Enter title of institution: " << endl;
													cout << ">>>>";
													cin >> institution;
													cout << endl;
													cout << "Entet king of activity: " << endl;
													cout << ">>>>";
													cin >> kindofactivity;
													cout << endl;
													Institution* inst = new Institution(institution, kindofactivity, NULL);
													Person* pers = new Person(name, Gender::female, inst);
													IndividualSubscriber IndSub(pers);
													AddSubscriber(&IndSub);
													cout << "Subscriber added " << endl;
													cout << endl;
													break;
												}
											}//switch
										}
									case 2: 
										{
											Person* pers = new Person(name, Gender::female, NULL);
											IndividualSubscriber indPers(pers);
											AddSubscriber(&indPers);
											cout << "Subscriber added " << endl;
											break;
										}
									}//switch
								}
							}//switch
						break;
						}
					case 2: 
						{
							cout << "1. With leader " << endl;
							cout << "2. Without leader " << endl;
							cout << ">>>>";
							cin >> c3;
							cout << endl;
							switch (c3) 
							{
							case 1: 
								{
									cout << "Enter name of leader: " << endl;
									cout << ">>>>";
									cin >> ws; getline(cin, name_lead);
									cout << endl;
									cout << "1. Male " << endl;
									cout << "2. Female " << endl;
									cout << ">>>>";
									cin >> c4;
									cout << endl;
									switch (c4) 
									{
									case 1: 
										{
											cout << "Enter title of institution: " << endl;
											cout << ">>>>";
											cin >> institution;
											cout << endl;
											cout << "Enter kind of activity: " << endl;
											cout << ">>>>";
											cin >> kindofactivity;
											cout << endl;
											Person* lead = new Person(name_lead, Gender::male, NULL);
											Institution* inst = new Institution(institution, kindofactivity, lead);
											InstitutionSubscriber instSub(inst);
											AddSubscriber(&instSub);
											cout << "Subscriber added " << endl;
											cout << endl;
											break;
										}
									case 2: 
										{
											cout << "Enter title of institution: " << endl;
											cout << ">>>>";
											cin >> institution;
											cout << endl;
											cout << "Enter kind of activity: " << endl;
											cout << ">>>>" << endl;
											cin >> kindofactivity;
											cout << endl;
											Person* lead = new Person(name_lead, Gender::female, NULL);
											Institution* inst = new Institution(institution, kindofactivity, lead);
											InstitutionSubscriber instSub(inst);
											AddSubscriber(&instSub);
											cout << "Subscriber added " << endl;
											cout << endl;
											break;
										}
									}//switch
								break;
								}
							case 2: 
								{
									cout << "Enter title of institution: " << endl;
									cout << ">>>>";
									cin >> institution;
									cout << endl;
									cout << "Enter kind of activity: " << endl;
									cout << ">>>>" << endl;
									cin >> kindofactivity;
									cout << endl;
									Institution* inst = new Institution(institution, kindofactivity, NULL);
									InstitutionSubscriber instSub(inst);
									AddSubscriber(&instSub);
									cout << "Subscriber added " << endl;
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
							for (Subscriber* sub : found) 
							{
								RemoveSubscriber(sub);
							}
							cout << "Subscriber removed " << endl;
							cout << endl;
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
							cout << "1. Landline phone " << endl;
							cout << "2. Mobile phone " << endl;
							cout << ">>>>";
							cin >> c3;
							switch (c3) 
							{
							case 1: 
								{
									cout << "1. Home phone " << endl;
									cout << "2. Office phone " << endl;
									cout << ">>>>";
									cin >> c4;
									cout << endl;
									switch (c4) 
									{
									case 1: 
										{
											cout << "Enter city code: " << endl;
											cout << ">>>>";
											cin >> cityCode;
											cout << endl;
											LandlinePhone homePhone(countryCode, shortNumber, cityCode, PhoneType::home);
											vector<Subscriber*> found = FindByPhone(homePhone);
											for (Subscriber* sub : found)
											{
												RemoveSubscriber(sub);
											}
											cout << "Subscriber removed " << endl;
											cout << endl;
											break;
										}
									case 2: 
										{
											cout << "Enter city code: " << endl;
											cout << ">>>>";
											cin >> cityCode;
											cout << endl;
											LandlinePhone officePhone(countryCode, shortNumber, cityCode, PhoneType::office);
											vector<Subscriber*> found = FindByPhone(officePhone);
											for (Subscriber* sub : found)
											{
												RemoveSubscriber(sub);
											}
											cout << "Subscriber removed " << endl;
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
									cout << ">>>>";
									cin >> c4;
									cout << endl;
									switch (c4) 
									{
									case 1:
										{
											cout << "Enter city code: " << endl;
											cout << ">>>>";
											cin >> cityCode;
											cout << endl;
											MobilePhone homePhone(countryCode, shortNumber, cityCode, PhoneType::home);
											vector<Subscriber*> found = FindByPhone(homePhone);
											for (Subscriber* sub : found)
											{
												RemoveSubscriber(sub);
											}
											cout << "Subscriber removed " << endl;
											cout << endl;
											break;
										}
									case 2:
										{
											cout << "Enter city code: " << endl;
											cout << ">>>>";
											cin >> cityCode;
											cout << endl;
											MobilePhone officePhone(countryCode, shortNumber, cityCode, PhoneType::office);
											vector<Subscriber*> found = FindByPhone(officePhone);
											for (Subscriber* sub : found)
											{
												RemoveSubscriber(sub);
											}
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
					case 3: 
						{
							cout << "Enter name or full name: " << endl;
							cout << ">>>>";
							cin >> ws; getline(cin, name);
							cout << endl;
							vector<Subscriber*> found = FindIndividual(name);
							for (Subscriber* sub : found)
							{
								RemoveSubscriber(sub);
							}
							cout << "Subscriber removed " << endl;
							cout << endl;
					break;
						}
					}//switch
				break;
				}
				case 6: 
				{
					cout << "Full list of subscribers: " << endl;
					cout << endl;
					Print();
					break;
				}
				case 7: 
				{
					cout << "1. Find subscriber by email " << endl;
					cout << "2. Find subscriber by phone " << endl;
					cout << "3. Find subscriber by name " << endl;
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
								throw invalid_argument("Incorrect form of name");
							}
							cout << endl;
							vector<Subscriber*> found = FindByEmail(email);
							cout << "1. Change name of subscriber " << endl;
							cout << "2. Change main phone " << endl;
							cout << ">>>>";
							cin >> c3;
							cout << endl;
							switch (c3) 
							{
							case 1: 
								{
									cout << "Enter new name: " << endl;
									cin >> ws; getline(cin,new_name);
									cout << endl;
									for (Subscriber* sub : found) 
									{
										sub->ChangeSubscriberTitle(new_name);
									}
									cout << "Name changed " << endl;
									cout << endl;
									break;
								}
							case 2: 
								{
									cout << "Enter country dode: " << endl;
									cout << ">>>>";
									cin >> countryCode;
									cout << endl;
									cout << "Enter short number: " << endl;
									cout << ">>>>";
									cin >> shortNumber;
									cout << endl;
									cout << "1. Landline phone " << endl;
									cout << "2. Mobile phone " << endl;
									cout << ">>>>";
									cin >> c4;
									cout << endl;
									switch (c4) 
									{
									case 1: 
										{
											cout << "1. Home phone " << endl;
											cout << "2. Office phone " << endl;
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
													for (Subscriber* sub : found) 
													{
														sub->ChangeMainPhone(homePhone);
													}
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
													for (Subscriber* sub : found)
													{
														sub->ChangeMainPhone(officePhone);
													}
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
													for (Subscriber* sub : found)
													{
														sub->ChangeMainPhone(homePhone);
													}
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
													for (Subscriber* sub : found)
													{
														sub->ChangeMainPhone(officePhone);
													}
													cout << "Main phone changed " << endl;
													cout << endl;
													break;
												}
											}//switch
										}
									}//switch
								break;
								}
							}//switch
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
							cout << "1. Landline phone " << endl;
							cout << "2. Mobile phone " << endl;
							cout << ">>>>";
							cin >> c3;
							cout << endl;
							switch (c3) 
							{
							case 1: 
								{
									cout << "1. Home phone " << endl;
									cout << "2. Office phone " << endl;
									cout << ">>>>";
									cin >> c4;
									cout << endl;
									switch (c4) 
									{
									case 1: 
										{
											cout << "Enter city code:" << endl;
											cout << ">>>>";
											cin >> cityCode;
											cout << endl;
											LandlinePhone llphone(countryCode, shortNumber, cityCode, PhoneType::home);
											vector<Subscriber*> found = FindByPhone(llphone);
											cout << "1. Change name of subscriber " << endl;
											cout << "2. Change main phone " << endl;
											cout << ">>>>";
											cin >> c5;
											cout << endl;
											switch (c5)
											{
											case 1: 
												{
													cout << "Enter new name: " << endl;
													cin >> ws; getline(cin, new_name);
													cout << endl;
													for (Subscriber* sub : found)
													{
														sub->ChangeSubscriberTitle(new_name);
													}
													cout << "Name changed " << endl;
													cout << endl;
													break;
												}
											case 2: 
												{
													cout << "Enter country code: " << endl;
													cout << ">>>>";
													cin >> countryCode;
													cout << endl;
													cout << "Enter short number " << endl;
													cout << ">>>>";
													cin >> shortNumber;
													cout << endl;
													cout << "1. Landline phone " << endl;
													cout << "2. Mobile phone " << endl;
													cout << ">>>>";
													cin >> c6;
													cout << endl;
													switch (c6) 
													{
													case 1: 
														{
															cout << "1. Home phone " << endl;
															cout << "2. Office phone " << endl;
															cout << ">>>>";
															cin >> c7;
															cout << endl;
															switch (c7) 
															{
															case 1: 
																{
																	cout << "Enter city code: " << endl;
																	cout << ">>>>";
																	cin >> cityCode;
																	cout << endl;
																	LandlinePhone* homePhone = new LandlinePhone(countryCode, shortNumber, cityCode, PhoneType::home);
																	for (Subscriber* sub : found) 
																	{
																		sub->ChangeMainPhone(homePhone);
																	}
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
																	for (Subscriber* sub : found)
																	{
																		sub->ChangeMainPhone(officePhone);
																	}
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
															cout << ">>>>";
															cin >> c7;
															cout << endl;
															switch (c7)
															{
															case 1: 
																{
																	cout << "Enter mobile code: " << endl;
																	cout << ">>>>";
																	cin >> mobileCode;
																	cout << endl;
																	MobilePhone* homePhone = new MobilePhone(countryCode, shortNumber, mobileCode, PhoneType::home);
																	for (Subscriber* sub : found)
																	{
																		sub->ChangeMainPhone(homePhone);
																	}
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
																	for (Subscriber* sub : found)
																	{
																		sub->ChangeMainPhone(officePhone);
																	}
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
											}//switch
										break;
										}
									case 2: 
										{
											cout << "Enter city code: " << endl;
											cout << ">>>>";
											cin >> cityCode;
											cout << endl;
											LandlinePhone llphone(countryCode, shortNumber, cityCode, PhoneType::office);
											vector<Subscriber*> found = FindByPhone(llphone);
											cout << "1. Change name of subsciber " << endl;
											cout << "2. Change main phone " << endl;
											cout << ">>>>";
											cin >> c5;
											cout << endl;
											switch (c5) 
											{
											case 1: 
												{
													cout << "Enter new name: " << endl;
													cin >> ws; getline(cin, new_name);
													cout << endl;
													for (Subscriber* sub : found)
													{
														sub->ChangeSubscriberTitle(new_name);
													}
													cout << "Name changed " << endl;
													cout << endl;
													break;
												}
											case 2: 
												{
													cout << "Enter country code: " << endl;
													cout << ">>>>";
													cin >> countryCode;
													cout << endl;
													cout << "Enter short number " << endl;
													cout << ">>>>";
													cin >> shortNumber;
													cout << endl;
													cout << "1. Landline phone " << endl;
													cout << "2. Mobile phone " << endl;
													cout << ">>>>";
													cin >> c6;
													cout << endl;
													switch (c6) 
													{
													case 1: 
														{
															cout << "1. Home phone " << endl;
															cout << "2. Office phone " << endl;
															cout << ">>>>";
															cin >> c7;
															cout << endl;
															switch (c7) 
															{
															case 1: 
																{
																	cout << "Enter city code: " << endl;
																	cout << ">>>>";
																	cin >> cityCode;
																	cout << endl;
																	LandlinePhone* homePhone = new LandlinePhone(countryCode, shortNumber, cityCode, PhoneType::home);
																	for (Subscriber* sub : found)
																	{
																		sub->ChangeMainPhone(homePhone);
																	}
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
																	for (Subscriber* sub : found)
																	{
																		sub->ChangeMainPhone(officePhone);
																	}
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
															cout << ">>>>";
															cin >> c7;
															cout << endl;
															switch (c7) 
															{
															case 1: 
																{
																	cout << "Enter mobile code: " << endl;
																	cout << ">>>>";
																	cin >> mobileCode;
																	cout << endl;
																	MobilePhone* homePhone = new MobilePhone(countryCode, shortNumber, mobileCode, PhoneType::home); 
																	for (Subscriber* sub : found) 
																	{
																		sub->ChangeMainPhone(homePhone);
																	}
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
																	for (Subscriber* sub : found)
																	{
																		sub->ChangeMainPhone(officePhone);
																	}
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
											}//switch
										break;
										}
									}//switch
								break;
								}
							case 2: 
								{
									cout << "1. Home phone " << endl;
									cout << "2. Office phone " << endl;
									cout << ">>>>";
									cin >> c4;
									cout << endl;
									switch (c4)
									{
									case 1: 
										{
											cout << "Enter mobile code: " << endl;
											cout << ">>>>";
											cin >> mobileCode;
											cout << endl;
											MobilePhone mphone(countryCode, shortNumber, mobileCode, PhoneType::home);
											vector<Subscriber*> found = FindByPhone(mphone);
											cout << "1. Change name of subsciber " << endl;
											cout << "2. Change main phone " << endl;
											cout << ">>>>";
											cin >> c5;
											cout << endl;
											switch (c5) 
											{
											case 1: 
												{
													cout << "Enter new name: " << endl;
													cin >> ws; getline(cin, new_name);
													cout << endl;
													for (Subscriber* sub : found)
													{
														sub->ChangeSubscriberTitle(new_name);
													}
													cout << "Name changed " << endl;
													cout << endl;
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
													cout << "1. Landline phone " << endl;
													cout << "2. Mobile phone " << endl;
													cout << ">>>>";
													cin >> c6;
													cout << endl;
													switch (c6) 
													{
													case 1: 
														{
															cout << "1. Home phone " << endl;
															cout << "2. Office phone " << endl;
															cout << ">>>>";
															cin >> c7;
															cout << endl;
															switch (c7) 
															{
															case 1: 
																{
																	cout << "Enter city code: " << endl;
																	cout << ">>>>";
																	cin >> cityCode;
																	cout << endl;
																	LandlinePhone* homePhone = new LandlinePhone(countryCode, shortNumber, cityCode, PhoneType::home);
																	for (Subscriber* sub : found) 
																	{
																		sub->ChangeMainPhone(homePhone);
																	}
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
																	for (Subscriber* sub : found)
																	{
																		sub->ChangeMainPhone(officePhone);
																	}
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
															cout << ">>>>";
															cin >> c7;
															cout << endl;
															switch (c7) 
															{
															case 1: 
																{
																	cout << "Enter mobile code: " << endl;
																	cout << ">>>>";
																	cin >> mobileCode;
																	cout << endl;
																	MobilePhone* homePhone = new MobilePhone(countryCode, shortNumber, mobileCode, PhoneType::home);
																	for (Subscriber* sub : found) 
																	{
																		sub->ChangeMainPhone(homePhone);
																	}
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
																	for (Subscriber* sub : found)
																	{
																		sub->ChangeMainPhone(officePhone);
																	}
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
											}//switch
										break;
										}
									case 2: 
										{
											cout << "Enter mobile code: " << endl;
											cout << ">>>>";
											cin >> mobileCode;
											cout << endl;
											MobilePhone mphone(countryCode, shortNumber, mobileCode, PhoneType::office);
											vector<Subscriber*> found = FindByPhone(mphone);
											cout << "1. Change name of subsciber " << endl;
											cout << "2. Change main phone " << endl;
											cout << ">>>>";
											cin >> c5;
											cout << endl;
											switch (c5) 
											{
											case 1: 
												{
													cout << "Enter new name: " << endl;
													cin >> ws; getline(cin, new_name);
													cout << endl;
													for (Subscriber* sub : found)
													{
														sub->ChangeSubscriberTitle(new_name);
													}
													cout << "Name changed " << endl;
													cout << endl;
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
													cout << "1. Landline phone " << endl;
													cout << "2. Mobile phone " << endl;
													cout << ">>>>";
													cin >> c6;
													cout << endl;
													switch (c6) 
													{
													case 1: 
														{
															cout << "1. Home phone " << endl;
															cout << "2. Office phone " << endl;
															cout << ">>>>";
															cin >> c7;
															cout << endl;
															switch (c7) 
															{
															case 1: 
																{
																	cout << "Enter city code: " << endl;
																	cout << ">>>>";
																	cin >> cityCode;
																	cout << endl;
																	LandlinePhone* homePhone = new LandlinePhone(countryCode, shortNumber,cityCode, PhoneType::home);
																	for (Subscriber* sub : found) 
																	{
																		sub->ChangeMainPhone(homePhone);
																	}
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
																	for (Subscriber* sub : found)
																	{
																		sub->ChangeMainPhone(officePhone);
																	}
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
															cout << ">>>>";
															cin >> c7;
															cout << endl;
															switch (c7)
															{
															case 1:
																{
																	cout << "Enter city code: " << endl;
																	cout << ">>>>";
																	cin >> cityCode;
																	cout << endl;
																	MobilePhone* homePhone = new MobilePhone(countryCode, shortNumber, cityCode, PhoneType::home);
																	for (Subscriber* sub : found)
																	{
																		sub->ChangeMainPhone(homePhone);
																	}
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
																	MobilePhone* officePhone = new MobilePhone(countryCode, shortNumber, cityCode, PhoneType::office);
																	for (Subscriber* sub : found)
																	{
																		sub->ChangeMainPhone(officePhone);
																	}
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
							cout << "Enter full name: " << endl;
							cout << ">>>>";
							cin >> ws; getline(cin, name);
							cout << endl;
							cout << "1. Change name of subscriber " << endl;
							cout << "2. Change main phone " << endl;
							cout << ">>>>";
							cin >> c3;
							cout << endl;
							switch (c3) 
							{
							case 1: 
								{
									cout << "Enter new name: " << endl;
									cin >> ws; getline(cin, new_name);
									cout << endl;
									for (Subscriber* sub : found)
									{
										sub->ChangeSubscriberTitle(new_name);
									}
									cout << "Name changed " << endl;
									cout << endl;
									break;
								}
							case 2: 
								{
									cout << "Enter country dode: " << endl;
									cout << ">>>>";
									cin >> countryCode;
									cout << endl;
									cout << "Enter short number: " << endl;
									cout << ">>>>";
									cin >> shortNumber;
									cout << endl;
									cout << "1. Landline phone " << endl;
									cout << "2. Mobile phone " << endl;
									cout << ">>>>";
									cin >> c4;
									cout << endl;
									switch (c4) 
									{
									case 1: 
										{
											cout << "1. Home phone " << endl;
											cout << "2. Office phone " << endl;
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
													for (Subscriber* sub : found) 
													{
														sub->ChangeMainPhone(homePhone);
													}
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
													for (Subscriber* sub : found)
													{
														sub->ChangeMainPhone(officePhone);
													}
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
													MobilePhone* homePhone = new MobilePhone(countryCode, shortNumber, cityCode, PhoneType::home);
													for (Subscriber* sub : found)
													{
														sub->ChangeMainPhone(homePhone);
													}
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
													MobilePhone* officePhone = new MobilePhone(countryCode, shortNumber, cityCode, PhoneType::office);
													for (Subscriber* sub : found)
													{
														sub->ChangeMainPhone(officePhone);
													}
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
							}//switch
						break;
						}
					}//switch
				break;				
				}
				
			}//switch
		}
		catch (invalid_argument& ia)
		{
			cout << ia.what() << endl;
		}
	} while (c1 != 0);
	
	
	
}


