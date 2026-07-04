#include "AccountFactory.h"
#include "Account.h"
#include "PersonalAccount.h"
#include "SavingsAccount.h"
std::unique_ptr<Account> AccountFactory::Create(const AccountType& type, const std::string& name, Currency curr, double balance)
{
	switch (type)
	{
	case AccountType::Personal:
		return std::make_unique<PersonalAccount>(name, curr, balance, 0, type);
	case AccountType::Savings:
		return std::make_unique<SavingsAccount>(name, curr, balance, 0, type);
	case AccountType::Test:
	default:
		return std::make_unique<Account>(name, curr, balance, 0, type);
	}
}
