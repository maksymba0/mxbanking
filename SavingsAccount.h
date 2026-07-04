#pragma once
#include "Account.h"
class SavingsAccount : public Account
{
public:
	double rate;
	double getBalance() const override;

	SavingsAccount();
	SavingsAccount(std::string name, Currency currency, double value, int _ID);
	SavingsAccount(std::string name, Currency currency, double value, int _ID, AccountType _type);
	SavingsAccount(std::string name, int _ID);

};

