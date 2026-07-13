#pragma once
#include <vector>
#include <iostream>
#include "Account.h" 
#include <unordered_map>
#include <optional>
#include <filesystem> 
#include <mutex>

namespace fs = std::filesystem;


class AccountDatabase
{
     
public:
     
    mutable std::mutex account_mtx_;
    //std::vector<std::shared_ptr<Account>> accounts;
    std::unordered_map<int, std::shared_ptr<Account>> accounts;

    void LoadAccounts(const std::string& fileName);
    void SaveAccounts(const std::string& fileName);


    Account* Add(std::shared_ptr<Account> pAccount);
    void Remove(std::shared_ptr<Account> pAccount);
    void Remove(int ID, AccountType type);
    void RemoveByAccountName(std::string_view name);


    Account* FindAccountByIDType(int ID, AccountType type); 
    Account* FindAccountByID(const std::vector<std::shared_ptr<Account>>& vector, int ID);
    Account* FindAccountByID(const std::unordered_map<int, std::shared_ptr<Account>>& vector, int ID);

    std::optional<Account*> GetAccountByUniqueID(int ID);
    std::optional<Account*> GetRandomUserByOffset(int Offset);

    Account* GetAccountByName(std::string_view name, AccountType type);

    void ApplyFees();

    int GenerateRandomID();

    void Dump(); 

    int GetAllAccountsBalance() const;

    Account* GetRichestAccount();

    ~AccountDatabase();
};
void EnsureFolderExists(const std::string& path);
void RunBenchmark(AccountDatabase* db);
