#pragma once
#include "Account.h"
#include <iostream>
class AccountFactory
{
public:
	
	static std::unique_ptr<Account> Create(const AccountType& type, const std::string& name, Currency curr, double balance);


};

