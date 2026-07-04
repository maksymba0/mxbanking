#include "AccountDatabase.h"
#include "Account.h"
#include "Utils.h"
Account* AccountDatabase::Add(std::shared_ptr<Account> pAccount)
{
    auto obj = pAccount.get();
    accounts.push_back(std::move(pAccount));
    std::cout << "[Account DB] : Increased accounts to " << accounts.size() << "\n";
    return obj;
}
void AccountDatabase::Remove(std::shared_ptr<Account> pAccount)
{
    
}
#include "Logger.h"
void AccountDatabase::Remove(int ID, AccountType type)
{
    auto it = std::remove_if(accounts.begin(), accounts.end(), 
        [ID, type](std::shared_ptr<Account>& object) 
        {
            return ID == object->GetID() && type == object->GetType();
        }); 

    accounts.erase(it, accounts.end());

    Log.InformationMsg("Removed account " + std::to_string(ID) + " from database.\n");

}

void AccountDatabase::RemoveByAccountName(std::string& name)
{
    auto it = std::erase_if(accounts, [&name](const std::shared_ptr<Account>& object)
        {
            return object->getName() == name;
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
    auto it = std::find_if(accounts.begin(), accounts.end(), [ID, type](const std::shared_ptr<Account>& acc) 
        {
            return acc->GetType() == type && acc->GetID() == ID;
        });
    if (it != accounts.end())
    {
        return it->get();
    }
    return nullptr;
}

Account* AccountDatabase::GetAccountByIndex(int Index)
{
    if (accounts.empty() || Index >= accounts.size() || Index < 0)
    {
        return nullptr;
    }
    return accounts[Index].get();
}

Account* AccountDatabase::GetAccountByUniqueID(int ID, AccountType type = AccountType::Test)
{
    for (const auto& obj : accounts)
    {
        if (obj->GetID() == ID && type == obj->GetType())
        {
            return obj.get();
        }
    }
    return nullptr;
}

Account* AccountDatabase::GetAccountByName(const char* name, AccountType type)
{
    for (const auto& obj : accounts)
    {
        if (!strcmp(obj->getName().c_str(), name))
        {
            return obj.get();
        }
    }
    return nullptr;
}

void AccountDatabase::ApplyFees()
{
    for (const auto& obj : accounts)
    {
        auto type = obj->GetType();
        if (type == AccountType::Personal || type == AccountType::Savings)
        {
            obj->ApplyMonthlyFees();
        }
    }
}

int AccountDatabase::GenerateRandomID()
{
    int ID = 0;
   
    do
    {
        ID = RandomInt(0, 10000);
    } while (GetAccountByUniqueID(ID,AccountType::Personal));

    return ID;

}

void AccountDatabase::Dump()
{
    std::cout << "\n----------ACCOUNTS DETAILS -----------\n";
    for (const auto& obj : accounts)
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
