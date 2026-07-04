#include "PersonalAccount.h"
#include "AccountDatabase.h"
#include "Logger.h"
bool PersonalAccount::SendMoneyTo(int accountID, double amount)
{
    return false;
}

double PersonalAccount::getBalance() const
{
    return balance_;
}

void PersonalAccount::ApplyMonthlyFees()
{
    static double fee = 35.99;
    SubBalance(fee);
    std::string message = "Mountly fees Subtract " + std::string(getCurrencyText(getCurrency())) + std::to_string(fee) + " from " + getName() + "'s account (Remaining:" + std::string(getCurrencyText(getCurrency())) + std::to_string(balance_) + ")\n";
    Log.InformationMsg(message);
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

 

