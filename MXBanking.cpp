#include <Windows.h>
#include <stdint.h>
#include <WinBase.h>
#include <minwinbase.h>
#include <iostream>
#include <chrono>

#include "Account.h"
#include "Utils.h"
 
#include "App.h"
#include "PersonalAccount.h"
#include "SavingsAccount.h"
 
#include "Logger.h"
 


 


 
int main()
{
     
    
    App app;

    if (!app.Auth())
    {
        std::cout << "Failed to log in. Exiting\n";
        Sleep(2000);
        exit(-1);
    }

    char buffer[256] = { 0 };
    DWORD buffersize = sizeof(buffer); 
    GetUserName(buffer, &buffersize);

    app.username = buffer;

    std::cout << "Welcome " << app.username << "!\n";
    std::cout << "========================================== \n";
    std::cout << "============ MXBanking System ============ \n";
 
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
     
    auto MaxAccount = std::make_shared<PersonalAccount>("maksymba0", Currency::PLN, RandomDouble(0, 4000), 1,AccountType::Personal);
    auto MaxSavingAccount = std::make_shared<SavingsAccount>("maksymba0", Currency::PLN, RandomDouble(0, 4000), MaxAccount->GetID(),AccountType::Savings);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    auto MariaAccount = std::make_shared<PersonalAccount>("Maria", Currency::PLN, RandomDouble(0, 2000), app.GenerateRandomUserID());
    auto JohnsonAccount = std::make_shared<PersonalAccount>("Johnson", Currency::PLN, RandomDouble(0, 2000), app.GenerateRandomUserID());
    auto AndreaAccount = std::make_shared<PersonalAccount>("Andrea", Currency::PLN, RandomDouble(0, 2000), app.GenerateRandomUserID());
    auto LeonAccount = std::make_shared<PersonalAccount>("Leon", Currency::PLN, RandomDouble(0, 2000), app.GenerateRandomUserID());

    Account* pAccount = nullptr;

    app.accountDB.Add(MaxAccount);
    app.accountDB.Add(MariaAccount);
    app.accountDB.Add(JohnsonAccount);
    app.accountDB.Add(AndreaAccount);
    app.accountDB.Add(LeonAccount);
    app.accountDB.Add(MaxSavingAccount);

    auto savings = app.accountDB.GetAccountByUniqueID(MaxAccount->GetID(), AccountType::Savings);
    
    auto Savings = dynamic_cast<SavingsAccount*>(savings);
    
    Log.ShowMsg = true;
    Log.ShowInformation = true;
    Log.ShowErrors = true;

     
    app.accountDB.Dump();
    //app.SimulateTransactions(); 
    app.accountDB.ApplyFees();
    app.accountDB.Dump();
     
    Log.PrintMsg("MaxAccount's balance: " + std::to_string(MaxAccount->getBalance()) + "\n Savings:" + std::to_string(MaxSavingAccount->getBalance()));
    
    
    return 4919;
}
