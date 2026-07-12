#pragma once
#include <string>
#include <vector>
#include <variant>
 
enum RequestStatus
{
    Pending = 0,
    Success,
    Error
};

enum ErrorCode
{
    None,
    InvalidDetails,
    InternalError,
    InvalidAmount,
    NeedToVerify,

    
};
struct Withdrawal
{
    int requestID;
    
    int sourceID;
    double amount;
    std::string reason;
};
struct Deposit
{
    int requestID;
    
    int sourceID;
    double amount;
    std::string reason;
};
struct Transfer
{
    int requestID;

    int sourceID;
    int targetID;
    double amount;
    std::string reason;
};
using Transaction = std::variant<Withdrawal, Deposit, Transfer>;

enum class Currency : int
{
    PLN = 0,
    EUR = 1,
    USD = 2,
    UAH = 3,
    JPY = 4,
    GBP = 5,
    AUD = 6,
    CAD = 7,
    Limit
};
enum class AccountType : int
{
    Test = 0,
    Personal = 1,
    Savings,
    ALL,
};
const char* getCurrencyText(Currency code);

extern bool DisplayErrors;

class Account
{
protected:
    double oldBalance_, balance_;
    std::string name_;
    Currency currency_;
private:

    int ID_;
    AccountType type_;

    std::vector<Transaction> transactions_;
 


public:
    virtual ~Account() = default;
    virtual double getBalance() const = 0;
    virtual void ApplyMonthlyFees() = 0;

    
    
    std::vector<Transaction>& GetTransactions();
    void SetID(int _ID);
    int GetID() const;
    AccountType GetType() const;
    Currency getCurrency() const;
    std::string_view getName() const;
    
    bool GiveTo(Account* other, double amount);
     

     
    void OnReceivedResponse(int RequestID, RequestStatus status);

     

     
    void Dump();
     
    
    void SetName(std::string newname);
    void SetCurrency(Currency _currency);

    void AddBalance(double _value, const char* reason); 
    void SubBalance(double _value);
    void SubBalance(double _value, std::string reason);
    void SetBalance(double _value);


    Account();
    Account(std::string name, Currency currency, double value, int _ID);
    Account(std::string name, Currency currency, double value, int _ID, AccountType type);
    Account(std::string name, int _ID);
     
protected:
    void AddBalance(double _value);

};

