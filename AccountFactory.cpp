#include "AccountFactory.h"
#include "Account.h"
#include "PersonalAccount.h"
#include "SavingsAccount.h"

void AccountFactory::Register(AccountType type, Creator creator)
{
	registry_.emplace(type, creator);
}

void RegisterAccountTypes()
{
	AccountFactory::Register(AccountType::Personal, [](const std::string& name, Currency curr, double balance, int ID)
		{
			return std::make_shared<PersonalAccount>(name, curr, balance, ID, AccountType::Personal);
		}); 
	AccountFactory::Register(AccountType::Savings, [](const std::string& name, Currency curr, double balance, int ID)
		{
			return std::make_shared<SavingsAccount>(name, curr, balance, ID,AccountType::Savings);
		});

	std::cout << "Registered account classes\n";
}


std::shared_ptr<Account> AccountFactory::Create(const AccountType& type, const std::string& name, Currency curr, double balance, int ID)
{
	auto it = registry_.find(type);
	if (it != registry_.end())
	{
		return it->second(name, curr, balance, ID);
	}
	/*return nullptr;

	switch (type)
	{
	case AccountType::Personal:
		return std::make_shared<PersonalAccount>(name, curr, balance, ID, type);
	case AccountType::Savings:
		return std::make_shared<SavingsAccount>(name, curr, balance, ID, type);
	case AccountType::Test:
	default:
		return std::make_shared<PersonalAccount>(name, curr, balance, ID, type);
	}*/
	return std::make_shared<PersonalAccount>(name, curr, balance, ID, type);
}
