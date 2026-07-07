#include "Account.h"
#include <iostream>  
#include "Utils.h"

#include "Logger.h"

bool DisplayErrors = true;


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

std::vector<Transaction>& Account::GetTransactions()
{
    return transactions_;
}

void Account::SetID(int _ID)
{
    ID_ = _ID;
}
int Account::GetID() const
{
    return ID_;
}
AccountType Account::GetType() const
{
    return type_;
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
    if (balance_ < amount)
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
    
    Transfer transfer;
    transfer.amount = amount;
    transfer.otherID = other->GetID();
    transfer.reason = "Transfer to";
    transactions_.push_back(transfer);
    other->AddBalance(amount,"Bank Transfer");
    
    Transfer transferA;
    transferA.amount = amount;
    transferA.otherID = GetID();
    transferA.reason = "Transfer from";
    other->transactions_.push_back(transferA);
     

    return true;

}
 

Currency Account::getCurrency() const { return currency_; }
 

std::string_view Account::getName() const { return name_; }

void Account::Dump()
{
    double balance = 0.0;
    const char* type = "Testing | ";
    
    switch (type_)
    {
    case AccountType::Personal:
        type = "Personal | ";
        break;
    case AccountType::Savings:
        type = "Savings | ";
        break;
    }

    std::cout << type << "Name: " << getName() << " | Currency: "
        << getCurrencyText(currency_) << " | Amount: "
        << balance_
        << "\n"; 
    if (!transactions_.empty())
    {
        if (transactions_.size() > 2)
            std::cout << "Transactions:\n";
        else
            std::cout << "Transaction:\n";
    
        int i = 0;
        for (const auto& obj : transactions_)
        {
            std::visit([&i](auto&& value)
                {
                    using T = std::decay_t<decltype(value)>;
                    if constexpr (std::is_same_v<T, Deposit>)
                    {
                        
                        std::cout << i << ") " << value.amount << " | " << value.reason << "\n";
                        ++i;
                    }
                    else  if constexpr (std::is_same_v<T, Transfer>)
                    {
                        std::cout << i << ") " << value.amount << " | " << value.reason << " | " << value.otherID << "\n";
                        ++i;
                    }
                    else if constexpr (std::is_same_v<T, Withdrawal>)
                    {
                        std::cout << i << ") " << value.amount << " | " << value.reason << "\n";
                        ++i;
                    }
                }, obj);
        }
    }
     
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
    std::string message = "[Account]: " + std::string(getName()) + " received " + std::string(getCurrencyText(getCurrency())) + std::to_string(_value) + " ( " + std::string(getCurrencyText(getCurrency())) + " " + std::to_string(balance_) + " ) - " + reason + "\n";
    Log.InformationMsg(message);
    //std::cout << "[Account]: " << getName() << " received " << getCurrencyText(getCurrency()) << _value << " ( " << getCurrencyText(getCurrency()) << " "<< balance << " ) - " << reason << "\n";
}
void Account::SubBalance(double _value)
{
    oldBalance_ = balance_;
    balance_ -= _value;
    std::string message = "[Account]: Subtracted " + std::string(getCurrencyText(getCurrency())) + std::to_string(_value) + " from " + std::string(getName()) + "'s account (Remaining:" + std::string(getCurrencyText(getCurrency())) + std::to_string(balance_) + ")\n";
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
Account::Account() : name_(""), currency_(Currency::PLN), balance_(0.0), ID_(0), oldBalance_(0.0), type_(AccountType::Test)
{ 
    std::cout << "[Account]: Account created - (0x" << this << ")\n";
}
Account::Account(std::string name, Currency currency, double value, int _ID) : name_(name), currency_(currency), balance_(value), ID_(_ID), type_(AccountType::Test)
{
    std::cout << "[Account]: Account " << _ID << " created - (0x" << this << ") - " << name << " - " << getCurrencyText(getCurrency()) << " " << balance_ << "\n";
}
Account::Account(std::string name, Currency currency, double value, int _ID, AccountType type) : name_(name), currency_(Currency::PLN), balance_(value), ID_(_ID), type_(type)
{
    std::cout << "[Account]: Account " << _ID << " created - (0x" << this << ") - " << name << " - " << getCurrencyText(getCurrency()) << " " << balance_ << " (type: " << static_cast<int>(type)<< "\n";
}
Account::Account(std::string name, int _ID) : name_(name), currency_(Currency::PLN), balance_(0.0), ID_(_ID), type_(AccountType::Test)
{
    std::cout << "[Account]: Account "<<_ID<<" created - (0x" << this << ") - " << name << " - " << getCurrencyText(getCurrency()) << " " << balance_ << "\n";
}

 

 