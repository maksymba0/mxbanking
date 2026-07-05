#include "AccountDatabase.h"
#include "Account.h"
#include "Utils.h"
#include <algorithm>  
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <sstream>
#include "AccountFactory.h"
void AccountDatabase::LoadAccounts(const std::string& fileName)
{
    std::ifstream os(fileName);

    if (!os.is_open())
    {
        std::string message = "Error: Couldn't open file for reading " + fileName + "\n";
        MessageBoxA(0, message.c_str(), "Error", MB_OKCANCEL);
        return;
    }

    std::string line;
    while (std::getline(os,line))
    {
        if (line.empty()) continue;
        
        std::stringstream ss(line);

        //1|maksymba0|630.879|0|1
        std::string id, name, balance, currency, type;

        std::getline(ss, id, '|');
        std::getline(ss, name, '|');
        std::getline(ss, balance, '|');
        std::getline(ss, currency, '|');
        std::getline(ss, type, '|');

        int ID = std::stoi(id);
        double BALANCE = std::stod(balance);
        Currency CURRENCY = static_cast<Currency>(std::stoi(currency));
        AccountType TYPE = static_cast<AccountType>(std::stoi(type));

        AccountFactory af;

        auto account = af.Create(TYPE, name, CURRENCY, BALANCE, ID);
        
        accounts.emplace(ID,account);

    }

    std::cout << "Loaded " << accounts.size() << " accounts from " << fileName << "\n";
}
//double oldBalance_, 
// double balance_;
//std::string name_;
//Currency currency_;
//int ID_;
//AccountType type_;

// ID | NAME | OLD BALANCE | BALANCE | CURRENCY | TYPE

void AccountDatabase::SaveAccounts(const std::string& fileName)
{
    std::ofstream os(fileName);

    if (!os.is_open())
    {
       std::string message = "Error: Couldn't open file for writing " + fileName + "\n";
       MessageBoxA(0, message.c_str(), "Error", MB_OKCANCEL);
       return;
    }

    for (const auto& pair : accounts)
    {
        const auto& obj = pair.second;

        os << obj->GetID() << "|" <<
            obj->getName() << "|" <<
            obj->getBalance() << "|" <<
            static_cast<int>(obj->getCurrency()) << "|" <<
            static_cast<int>(obj->GetType()) << "\n";

    }
    std::cout << "Saved " << accounts.size() << " accounts to " << fileName << "\n";

}
Account* AccountDatabase::Add(std::shared_ptr<Account> pAccount)
{
    accounts.emplace(pAccount->GetID(),pAccount);
    //accounts.push_back(std::move(pAccount));
    std::cout << "[Account DB] : Increased accounts to " << accounts.size() << "\n";
    return pAccount.get();
}
void AccountDatabase::Remove(std::shared_ptr<Account> pAccount)
{
    
}
#include "Logger.h"
void AccountDatabase::Remove(int ID, AccountType type)
{
    auto it = accounts.erase(ID);

    if(it > 0)
        Log.InformationMsg("Removed account " + std::to_string(ID) + " from database.\n");
    else
        Log.InformationMsg("Cannot remove account " + std::to_string(ID) + " from database. Not found\n");
    
    return;
}

void AccountDatabase::RemoveByAccountName(std::string& name)
{
    auto it = std::erase_if(accounts, 
        [&name](const std::pair< const int, std::shared_ptr<Account>>& object)
        {
            return object.second->getName() == name;
        });
     
    std::string message;

    if (it > 0)
        message = "Removed account " + name + " from database.\n";
    else
        message = "Cannot delete " + name + " from database. Not found\n";

    Log.InformationMsg(message);

}

Account* AccountDatabase::FindAccountByIDType(int ID, AccountType type)
{
    auto it = std::find_if(accounts.begin(), accounts.end(), [ID, type](const std::pair<const int,std::shared_ptr<Account>>& acc) 
        {
            return acc.second->GetType() == type && acc.second->GetID() == ID;
        });
    if (it != accounts.end())
    {
        return it->second.get();
    }
    return nullptr;
} 

std::optional<Account*> AccountDatabase::GetAccountByUniqueID(int ID)
{
    auto it = accounts.find(ID);

    if (it != accounts.end())
    {
        return it->second.get();
    }
    
    return std::nullopt;
}

Account* AccountDatabase::GetAccountByName(const char* name, AccountType type)
{
    for (const auto& obj : accounts)
    {
        if (!strcmp(obj.second->getName().c_str(), name))
        {
            return obj.second.get();
        }
    }
    return nullptr;
}

void AccountDatabase::ApplyFees()
{
    for (const auto& obj : accounts)
    {
        auto type = obj.second->GetType();
        if (type == AccountType::Personal || type == AccountType::Savings)
        {
            obj.second->ApplyMonthlyFees();
        }
    }
}

int AccountDatabase::GenerateRandomID()
{
    int ID = 0;
   
    do
    {
        ID = RandomInt(0, 10000);
    } while (GetAccountByUniqueID(ID).has_value());

    return ID;

}

void AccountDatabase::Dump()
{
     
    std::vector<std::shared_ptr<Account>> sorted;
    sorted.reserve(accounts.size());

    for (auto& obj : accounts)
    {
        sorted.push_back(obj.second);
    }

    std::sort(sorted.begin(), sorted.end(), 
        [](const std::shared_ptr<Account>&a, const std::shared_ptr<Account>&b) 
        {
            return a->getBalance() > b->getBalance();
        });

    std::cout << "\n----------ACCOUNTS DETAILS -----------\n";
    for (const auto& obj : sorted)
    {
        obj->Dump();
    }
    std::cout << "\n";
}

AccountDatabase::~AccountDatabase()
{
    std::cout << "\n----------CLOSING DB -----------\n";
    this->accounts.clear();
}
