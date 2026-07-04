#pragma once
#include <vector>
#include <iostream>
#include "Account.h" 
class AccountDatabase
{
     
public:
    
    std::vector<std::shared_ptr<Account>> accounts;


    Account* Add(std::shared_ptr<Account> pAccount);
    void Remove(std::unique_ptr<Account> pAccount);

    Account* GetAccountByIndex(int Index);
    Account* GetAccountByUniqueID(int ID, AccountType type);
    Account* GetAccountByName(const char* name, AccountType type);

    void ApplyFees();

    int GenerateRandomID();

    void Dump();
    ~AccountDatabase();
};

