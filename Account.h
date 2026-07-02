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

class Account
{
private:
    int ID;
    double oldBalance;
    double balance;
    std::string name;
    Currency currency;


public:

    void SetID(int _ID);
    int GetID() const;

    bool GiveTo(Account* other, double amount);
    

    Currency getCurrency() const;
    double getBalance() const;

    std::string getName() const;
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

