#pragma once
#include <vector>
#include <iostream>
class Account;
class AccountDatabase
{
public:
    std::vector<std::unique_ptr<Account>> accounts;

    Account* Add(std::unique_ptr<Account> pAccount);
    void Remove(std::unique_ptr<Account> pAccount);

    Account* GetAccountByIndex(int Index);
    Account* GetAccountByUniqueID(int ID);

    int GenerateRandomID();

    void Dump();
};

