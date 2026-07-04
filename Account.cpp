#include "Account.h"
#include <iostream>  
#include "Utils.h"

#include "Logger.h"

bool DisplayErrors = false;


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
    ID_ = _ID;
}
int Account::GetID() const
{
    return ID_;
}
bool Account::GiveTo(Account* other, double amount)
{
    if (amount <= 0.00)
    {

         
        //std::cout << "[Account Transaction Error]: Unable to transfer (#INVALIDAMOUNT)\n";

        if(DisplayErrors)
            Log.ErrorMsg("Unable to transfer (#INVALIDAMOUNT)\n", "[Account Transaction Error]");
        return false;
    }
    if (!other)
    {

         
        //std::cout << "[Account Transaction Error]: Unable to transfer (#NORECIPIENT)\n";

        if (DisplayErrors)
            Log.ErrorMsg("Unable to transfer (#NORECIPIENT)\n", "[Account Transaction Error]");

        return false;
    }
    if (getBalance() < amount)
    {

         
        //std::cout << "[Account Transaction Error]: Unable to transfer (#NOTENOUGHMONEY)\n";
        if (DisplayErrors)
            Log.ErrorMsg("Unable to transfer (#NOTENOUGHMONEY)\n", "[Account Transaction Error]");

        return false;
    }
    if (other->getCurrency() != getCurrency())
    {

         
        //std::cout << "[Account Transaction Error]: Unable to transfer (#CURRENCYMISMATCH)\n";

        if (DisplayErrors)
            Log.ErrorMsg("Unable to transfer (#CURRENCYMISMATCH)\n", "[Account Transaction Error]");
        return false;
    }

    this->SubBalance(amount);
    other->AddBalance(amount,"Bank Transfer");


    return true;

}
 

Currency Account::getCurrency() const { return currency_; }
 

std::string Account::getName() const { return name_; }

void Account::Dump()
{
    double balance = 0.0;
    std::cout << "Name: " << getName() << " | Currency: "
        << getCurrencyText(currency_) << " | Amount: "
        << getBalance()
        << "\n";
    std::string name = "#Empty";
    Currency currency = Currency::Limit;
}
void Account::SetName(std::string newname)
{
    if (newname.empty())
    {
        std::cout << "[Account]: Failed to set currency [Invalid currency]\n";
        return;
    }
    name_ = newname;
    std::cout << "[Account]: Changed name to " << name_ << "\n";
    return;
}
void Account::SetCurrency(Currency _currency)
{
    if (_currency < Currency::PLN || _currency >= Currency::Limit)
    {
        std::cout << "[Account]: Failed to set currency [Invalid currency]\n";
        return;
    }
    currency_ = _currency;
    std::cout << "[Account]: Currency set to " << getCurrencyText(currency_) << "\n";
}
void Account::AddBalance(double _value)
{
    oldBalance_ = balance_;
    balance_ += _value;
}
void Account::AddBalance(double _value, const char* reason)
{
    static const char* reasonUnk = "#InvalidReason";
    if (!reason)
    {
        reason = reasonUnk;
    }
    AddBalance(_value);
    std::cout << getTime();
    std::string message = "[Account]: " + getName() + " received " + std::string(getCurrencyText(getCurrency())) + std::to_string(_value) + " ( " + std::string(getCurrencyText(getCurrency())) + " " + std::to_string(balance_) + " ) - " + reason + "\n";
    Log.InformationMsg(message);
    //std::cout << "[Account]: " << getName() << " received " << getCurrencyText(getCurrency()) << _value << " ( " << getCurrencyText(getCurrency()) << " "<< balance << " ) - " << reason << "\n";
}
void Account::SubBalance(double _value)
{
    oldBalance_ = balance_;
    balance_ -= _value;
    std::string message = "[Account]: Subtracted " + std::string(getCurrencyText(getCurrency())) + std::to_string(_value) + " from " + getName() + "'s account (Remaining:" + std::string(getCurrencyText(getCurrency())) + std::to_string(balance) + ")\n";
    Log.InformationMsg(message);
    //std::cout << "[Account]: Subtracted " << getCurrencyText(getCurrency()) << _value << " from " << getName() << "'s account (Remaining:" << getCurrencyText(getCurrency()) << balance << ")\n";
}
void Account::SetBalance(double _value)
{
    oldBalance_ = balance_;
    balance_ = _value;
    std::string message = "[Account]: Balance set to " + std::string(getCurrencyText(getCurrency())) + std::to_string(balance_) + "\n";
    Log.InformationMsg(message);
    //std::cout << "[Account]: Balance set to " << getCurrencyText(getCurrency()) << balance << "\n";
}
Account::Account() : name_(""), currency_(Currency::PLN), balance_(0.0), ID_(0), oldBalance_(0.0)
{ 
    std::cout << "[Account]: Account created - (0x" << this << ")\n";
}
Account::Account(std::string name, Currency currency, double value, int _ID) : name_(name), currency_(currency), balance_(value), ID_(_ID)
{
    std::cout << "[Account]: Account " << _ID << " created - (0x" << this << ") - " << name << " - " << getCurrencyText(getCurrency()) << " " << getBalance() << "\n";
}
Account::Account(std::string name, int _ID) : name_(name), currency_(Currency::PLN), balance_(0.0), ID_(_ID)
{
    std::cout << "[Account]: Account "<<_ID<<" created - (0x" << this << ") - " << name << " - " << getCurrencyText(getCurrency()) << " " << getBalance() << "\n";
}

Account& Account::operator=(Account& ptr)
{
    if (this == &ptr)
    {
        return *this;
    }
    
    SetBalance(ptr.getBalance());
    SetCurrency(ptr.getCurrency());
    SetID(ptr.GetID());
    SetName(ptr.getName());
 
    return *this;
}

 