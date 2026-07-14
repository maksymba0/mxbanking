#include "SavingsAccount.h"
#include "Logger.h"
double SavingsAccount::getBalance() const
{
    return balance_;
}

void SavingsAccount::ApplyMonthlyFees()
{
    static double fee = 0.02;

    double interest = getBalance() * fee;
    AddBalance(interest);
    std::string message = "Savings interest Add " + std::string(getCurrencyText(getCurrency())) + std::to_string(interest) + " to " + std::string(getName()) + "'s savings account (Remaining:" + std::string(getCurrencyText(getCurrency())) + std::to_string(balance_) + ")\n";
    Log.InformationMsg(message);
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

 
