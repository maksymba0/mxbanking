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
#include "AccountFactory.h"
#include "Logger.h"
#include <thread>


 


 
int main()
{
     
    
    App app;
    app.Greeting();
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
 
    app.accountDB.LoadAccounts("Accounts/accounts.txt");
    std::thread t_Server();
    Log.ShowMsg = true;
    Log.ShowInformation = true;
    Log.ShowErrors = true;

     
    app.accountDB.Dump();
    //app.SimulateTransactions(); 
    app.accountDB.ApplyFees();
    app.accountDB.Dump();
       
    app.accountDB.Remove(3, AccountType::Test);

    EnsureFolderExists("Accounts");
    RegisterAccountTypes();
    ListRegisterAccountTypes();
    auto somePtr = AccountFactory::Create(AccountType::Personal, "Secret", Currency::PLN, 4444.00, 123);
    somePtr->Dump();
     

    app.accountDB.SaveAccounts("Accounts/accounts.txt");
    
     
    return 4919;
}
