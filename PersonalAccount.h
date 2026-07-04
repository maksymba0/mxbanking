#pragma once
#include "Account.h"
class PersonalAccount : public Account
{
public:
	bool SendMoneyTo(int accountID, double amount);

	double getBalance() const override;
	void ApplyMonthlyFees() override;

	PersonalAccount();
	PersonalAccount(std::string name, Currency currency, double value, int _ID);
	PersonalAccount(std::string name, Currency currency, double value, int _ID, AccountType _type);
	PersonalAccount(std::string name, int _ID); 
};

