#include "AccountFactory.h"
#include "Account.h"
#include "PersonalAccount.h"
#include "SavingsAccount.h"

std::shared_ptr<Account> AccountFactory::Create(const AccountType& type, const std::string& name, Currency curr, double balance, int ID)
{

	switch (type)
	{
	case AccountType::Personal:
		return std::make_shared<PersonalAccount>(name, curr, balance, ID, type);
	case AccountType::Savings:
		return std::make_shared<SavingsAccount>(name, curr, balance, ID, type);
	case AccountType::Test:
	default:
		return std::make_shared<PersonalAccount>(name, curr, balance, ID, type);
	}
}
