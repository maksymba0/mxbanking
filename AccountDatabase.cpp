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
void AccountDatabase::Remove(std::unique_ptr<Account> pAccount)
{

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
