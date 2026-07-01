#include "Account.h"
#include <iostream>  
#include "Utils.h"

const char* getCurrencyText(Currency code)
{
    static const char* currencies[] = { "PLN",
    "EUR",
    "USD",
    "UAH",
    "JPY",
    "GBP",
    "AUD",
    "CAD", };

    if (code >= Currency::PLN && code < Currency::Limit)
    {
        return currencies[static_cast<int>(code)];
    }
    return "#ERROR";
}

void Account::SetID(int _ID)
{
    ID = _ID;
}
int Account::GetID()
{
    return ID;
}
bool Account::GiveTo(Account* other, double amount)
{
    if (amount <= 0.00)
    {
        std::cout << "[Account Transaction Error]: Unable to transfer (#INVALIDAMOUNT)\n";
        return false;
    }
    if (!other)
    {
        std::cout << "[Account Transaction Error]: Unable to transfer (#NORECIPIENT)\n";
        return false;
    }
    if (getBalance() < amount)
    {
        std::cout << "[Account Transaction Error]: Unable to transfer (#NOTENOUGHMONEY)\n";
        return false;
    }
    if (other->getCurrency() != getCurrency())
    {
        std::cout << "[Account Transaction Error]: Unable to transfer (#CURRENCYMISMATCH)\n";
        return false;
    }

    this->SubBalance(amount);
    other->AddBalance(amount);


    return true;

}

Currency Account::getCurrency() { return currency; }
double Account::getBalance() { return balance; }

std::string Account::getName() { return name; }

void Account::Dump()
{
    double balance = 0.0;
    std::cout << "Name: " << getName() << " | Currency: "
        << getCurrencyText(currency) << " | Amount: "
        << getBalance()
        << "\n";
    std::string name = "#Empty";
    Currency currency = Currency::Limit;
}
void Account::SetName(std::string newname)
{
    if (newname.empty())
    {
        std::cout << "[Account operation]: Failed to set currency [Invalid currency]\n";
        return;
    }
    name = newname;
    std::cout << "[Account operation]: Changed name to " << name << "\n";
    return;
}
void Account::SetCurrency(Currency _currency)
{
    if (_currency < Currency::PLN || _currency >= Currency::Limit)
    {
        std::cout << "[Account operation]: Failed to set currency [Invalid currency]\n";
        return;
    }
    currency = _currency;
    std::cout << "[Account operation]: Currency set to " << getCurrencyText(currency) << "\n";
}
void Account::AddBalance(double _value)
{
    oldBalance = balance;
    balance += _value;
    std::cout << "[Account operation]: Added " << getCurrencyText(getCurrency()) << _value << " to " << getName() << "'s account (" << balance << ")\n";
}
void Account::SubBalance(double _value)
{
    oldBalance = balance;
    balance -= _value;
    std::cout << "[Account operation]: Subtracted " << getCurrencyText(getCurrency()) << _value << " from " << getName() << "'s account (" << balance << ")\n";
}
void Account::SetBalance(double _value)
{
    oldBalance = balance;
    balance = _value;
    std::cout << "[Account operation]: Balance set to " << getCurrencyText(getCurrency()) << balance << "\n";
}
Account::Account() : name(name), currency(Currency::PLN), balance(0.0), ID(0)
{ 
    std::cout << "[Account]: Account created - (0x" << this << ")\n";
}
Account::Account(std::string name, Currency currency, double value, int _ID) : name(name), currency(currency), balance(value), ID(_ID)
{
    std::cout << "[Account]: Account " << _ID << " created - (0x" << this << ") - " << name << " - " << getCurrencyText(getCurrency()) << " " << getBalance() << "\n";
}
Account::Account(std::string name, int _ID) : name(name), currency(Currency::PLN), balance(0.0), ID(_ID)
{
    std::cout << "[Account]: Account "<<_ID<<" created - (0x" << this << ") - " << name << " - " << getCurrencyText(getCurrency()) << " " << getBalance() << "\n";
}

 