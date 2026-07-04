#pragma once
#include "Account.h"
class PersonalAccount : public Account
{
public:
	bool SendMoneyTo(int accountID, double amount);

	double getBalance() const override;
};

