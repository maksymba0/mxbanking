#include "AccountDatabase.h"
#include "Account.h"
#include "Utils.h"
#include <random>
#include <algorithm>  
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <vector>
#include <sstream>
#include <unordered_map>
#include "AccountFactory.h"
#include <chrono>
#include "PersonalAccount.h"
void AccountDatabase::LoadAccounts(const std::string& fileName)
{
     

    fs::path filePath(fileName);

    EnsureFolderExists(filePath.parent_path().string());

    std::ifstream os(filePath);

    if (!os.is_open())
    {
        std::string message = "Error: Couldn't open file for reading " + filePath.string() + "\n";
        MessageBoxA(0, message.c_str(), "Error", MB_OKCANCEL);
        return;
    }

    std::string line;
    while (std::getline(os,line))
    {
        if (line.empty()) continue;
        
        if (line.at(0) == '#') continue;
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
    fs::path filePath(fileName);
    std::ofstream os(filePath);

    EnsureFolderExists(filePath.string());



    if (!os.is_open())
    {
       std::string message = "Error: Couldn't open file for writing " + fileName + "\n";
       MessageBoxA(0, message.c_str(), "Error", MB_OKCANCEL);
       return;
    }
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::time_point_cast<std::chrono::seconds>(now);
    os << "#" << std::format("{:%Y-%m-%d %H:%M:%S}", time) << "\n";
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

void AccountDatabase::RemoveByAccountName(std::string_view _name)
{
    std::string name(_name);
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
Account* AccountDatabase::FindAccountByID(const std::unordered_map<int, std::shared_ptr<Account>>& map, int ID)
{
    auto it = map.find(ID);
    if (it != map.end())
    {
        return it->second.get();
    }
    return nullptr;

}
Account* AccountDatabase::FindAccountByID(const std::vector<std::shared_ptr<Account>>& vector, int ID)
{
    for (const auto& acc : vector) 
    {
        if (acc->GetID() == ID)
        {
            return acc.get();
        }
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

std::optional<Account*> AccountDatabase::GetRandomUserByOffset(int Offset)
{
    auto it = accounts.begin();
    std::advance(it, Offset);

    if (it != accounts.end())
    {
        return it->second.get();
    }

    return std::nullopt;
}

Account* AccountDatabase::GetAccountByName(std::string_view name, AccountType type)
{

    for (const auto& obj : accounts)
    {
        if (obj.second->getName() == name)
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
 
void EnsureFolderExists(const std::string& path)
{
    fs::path dir(path);
    if (!fs::exists(dir))
    {
        fs::create_directories(dir);
        std::cout << "Created folder for accounts "<<dir<<"\n";
    }
}

void RunBenchmark(AccountDatabase* db)
{
    const int NUM_ACCOUNTS = 12000;
    const int NUM_LOOKUPS = 1000;

    std::vector<std::shared_ptr<Account>> vAccounts;
    std::unordered_map<int, std::shared_ptr<Account>> mAccounts;


    for (int i = 0; i < NUM_ACCOUNTS; ++i)
    {
        auto acc = std::make_shared<PersonalAccount>("User" + std::to_string(i), Currency::PLN, RandomDouble(0, 100000), i);
        vAccounts.push_back(acc);
        mAccounts.emplace(i, acc);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, NUM_ACCOUNTS - 1);

    std::vector<int> ids;
    for (int i = 0; i < NUM_LOOKUPS; ++i)
    {
        ids.push_back(dist(gen));
    }

    auto start = std::chrono::high_resolution_clock::now();


    int foundCount = 0; // Vector
    for (int id : ids) {
        if (db->FindAccountByID(vAccounts,id) != nullptr) foundCount++;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto firstDuration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    start = std::chrono::high_resolution_clock::now();
    int mfoundCount = 0; // Map
    for (int id : ids) {
        if (db->FindAccountByID(mAccounts, id) != nullptr) mfoundCount++;
    }
    end = std::chrono::high_resolution_clock::now();
    auto secondDuration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Vector lookup took: " << firstDuration << " seconds\n";
    std::cout << "Map lookup took: " << secondDuration << " seconds\n";

}
