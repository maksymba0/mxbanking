#pragma once
#include <string>
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
const char* getCurrencyText(Currency code);

extern bool DisplayErrors;

class Account
{
protected:
    double oldBalance, balance;
    std::string name;
    Currency currency;
private:

    int ID;
 

 


public:
    virtual ~Account() = default;
    virtual double getBalance() const = 0;

    
    
    void SetID(int _ID);
    int GetID() const;
    Currency getCurrency() const;
    std::string getName() const;

    //bool GiveTo(Account* other, double amount);
     

     
     
     

     
    void Dump();
     
    
    void SetName(std::string newname);
    void SetCurrency(Currency _currency);

    void AddBalance(double _value, const char* reason); 
    void SubBalance(double _value);
    void SetBalance(double _value);


    Account();
    Account(std::string name, Currency currency, double value, int _ID);
    Account(std::string name, int _ID);
    
     
    Account& operator=(Account& ptr);
protected:
    void AddBalance(double _value);

};

