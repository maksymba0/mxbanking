#include "Account.h"
#include <iostream>  
#include "Utils.h"

#include "Logger.h"

bool DisplayErrors = true;
std::mutex mtx;


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
     
    return true;

}

void Account::OnReceivedResponse(int RequestID, RequestStatus status)
{
    // find the transaction and notify whether it was success/error/pending
    for (auto& obj : transactions_)
    {
        std::visit([RequestID, status](auto&& arg)
            {
                using t = std::decay_t<decltype(arg)>;
                
                if constexpr (std::is_same_v<t, Deposit>)
                {
                    if (arg.requestID == RequestID)
                    {
                        if (status == RequestStatus::Pending)
                        {
                            std::cout << "[Account]: DEPOSIT - Payment ID " << RequestID << ". Amount: "<< arg.amount << "Status: Pending\n";
                        }else if (status == RequestStatus::Error)
                        {
                            std::cout << "[Account]: DEPOSIT - Payment ID " << RequestID << ". Amount: " << arg.amount << "Status: Error\n";
                        } if (status == RequestStatus::Success)
                        {
                            std::cout << "[Account]: DEPOSIT - Payment ID " << RequestID << ". Amount: " << arg.amount << "Status: Success\n";
                        }
                        else
                        {
                            std::cout << "Unknown RequestStatus:" << status << "\n";
                        }
                    }
                }
                else if constexpr (std::is_same_v<t, Withdrawal>)
                {
                    if (arg.requestID == RequestID)
                    {
                        if (status == RequestStatus::Pending)
                        {
                            std::cout << "[Account]: Withdrawal - Payment ID " << RequestID << ". Amount: " << arg.amount << "Status: Pending\n";
                        }
                        else if (status == RequestStatus::Error)
                        {
                            std::cout << "[Account]: Withdrawal - Payment ID " << RequestID << ". Amount: " << arg.amount << "Status: Error\n";
                        } if (status == RequestStatus::Success)
                        {
                            std::cout << "[Account]: Withdrawal - Payment ID " << RequestID << ". Amount: " << arg.amount << "Status: Success\n";
                        }
                        else
                        {
                            std::cout << "Unknown RequestStatus:" << status << "\n";
                        }
                    }
                }
                else if constexpr (std::is_same_v<t, Transfer>)
                {
                    if (arg.requestID == RequestID)
                    {
                        if (status == RequestStatus::Pending)
                        {
                            std::cout << "[Account]: Transfer - Payment ID " << RequestID << ". Amount: " << arg.amount << "Status: Pending\n";
                        }
                        else if (status == RequestStatus::Error)
                        {
                            std::cout << "[Account]: Transfer - Payment ID " << RequestID << ". Amount: " << arg.amount << "Status: Error\n";
                        } if (status == RequestStatus::Success)
                        {
                            std::cout << "[Account]: Transfer - Payment ID " << RequestID << ". Amount: " << arg.amount << "Status: Success\n";
                        }
                        else
                        {
                            std::cout << "Unknown RequestStatus:" << status << "\n";
                        }
                    }
                }

            }, obj);
    }
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
                        std::cout << i << ") " << value.amount << " | " << value.reason << " | " << value.targetID << "\n";
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

Account::Account(const Account& other) :
    name_(other.name_), 
    balance_(other.balance_),
    currency_(other.currency_),
    transactions_(other.transactions_)
{
    std::cout << "[Account] Copied account\n";
}

Account::Account(Account&& other) :
    name_(std::move(other.name_)), 
    balance_(other.balance_), 
    currency_(other.currency_), 
    transactions_(std::move(other.transactions_))
{
    other.balance_ = 0;
    std::cout << "[Account] Moved account\n";
}

 

 