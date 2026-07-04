#include "SavingsAccount.h"
double SavingsAccount::getBalance() const
{
	return balance_ + (balance_*0.02);
}

SavingsAccount::SavingsAccount() : Account()
{

}
SavingsAccount::SavingsAccount(std::string name, Currency currency, double value, int _ID) : Account(name, currency, value, _ID)
{

}
SavingsAccount::SavingsAccount(std::string name, Currency currency, double value, int _ID, AccountType _type) : Account(name, currency, value, _ID, _type)
{

}
SavingsAccount::SavingsAccount(std::string name, int _ID) : Account(name, _ID)
{

}