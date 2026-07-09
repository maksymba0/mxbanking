#pragma once
#include "Account.h"
#include <iostream>
#include <functional>
#include <map>

class AccountFactory
{
public:
	

	using Creator = std::function<std::shared_ptr<Account>(const std::string&, Currency, double balance, int ID)>;
	
	static void Register(AccountType type, Creator creator);

	static std::shared_ptr<Account> Create(const AccountType& type, const std::string& name, Currency curr, double balance, int ID); 
private:
	inline static std::map<AccountType, Creator> registry_;

};

void RegisterAccountTypes();
