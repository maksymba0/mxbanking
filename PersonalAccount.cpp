#include "PersonalAccount.h"
#include "AccountDatabase.h"
bool PersonalAccount::SendMoneyTo(int accountID, double amount)
{
    return false;
}

double PersonalAccount::getBalance() const
{
    return balance_ - .5;
}

 
PersonalAccount::PersonalAccount() : Account()
{

}
PersonalAccount::PersonalAccount(std::string name, Currency currency, double value, int _ID) : Account(name,  currency,  value,  _ID)
{

}
PersonalAccount::PersonalAccount(std::string name, Currency currency, double value, int _ID, AccountType _type) : Account(name, currency, value, _ID, _type)
{
}
PersonalAccount::PersonalAccount(std::string name, int _ID) : Account(name, _ID)
{

}

 

