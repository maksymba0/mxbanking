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
 
    app.accountDB.LoadAccounts("accounts.txt");
    
    Log.ShowMsg = true;
    Log.ShowInformation = true;
    Log.ShowErrors = true;

     
    app.accountDB.Dump();
    //app.SimulateTransactions(); 
    app.accountDB.ApplyFees();
    app.accountDB.Dump();
       
    app.accountDB.Remove(3, AccountType::Test);
    std::string toDelete[3] = { "Johnson", "Maria", "Andrea"};
    app.accountDB.RemoveByAccountName(toDelete[0]);
    app.accountDB.RemoveByAccountName(toDelete[1]); 
    app.accountDB.RemoveByAccountName(toDelete[2]);
    app.accountDB.Dump();
    
    auto maxAccount = app.accountDB.GetAccountByUniqueID(1).value();
    auto someAccount = app.accountDB.GetAccountByUniqueID(6).value();
    maxAccount->GiveTo(someAccount, 400);

    maxAccount->Dump();
    someAccount->Dump();



    app.accountDB.SaveAccounts("accounts.txt");
    
     
    return 4919;
}
