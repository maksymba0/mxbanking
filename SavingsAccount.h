#pragma once
#include "Account.h"
class SavingsAccount : public Account
{
public:
	double rate;
	double getBalance() const override;
};

