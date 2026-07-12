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
#include "BankServer.h"

 


 
int main()
{
     
    
    App* app = App::GetApp();
    app->Greeting();
    if (!app->Auth())
    {
        std::cout << "Failed to log in. Exiting\n";
        Sleep(2000);
        exit(-1);
    }

    char buffer[256] = { 0 };
    DWORD buffersize = sizeof(buffer); 
    GetUserName(buffer, &buffersize);

    app->username = buffer;

    std::cout << "Welcome " << app->username << "!\n";
    std::cout << "========================================== \n";
    std::cout << "============ MXBanking System ============ \n";
 
    app->accountDB.LoadAccounts("Accounts/accounts.txt");
    Log.ShowMsg = true;
    Log.ShowInformation = true;
    Log.ShowErrors = true;

    std::thread t_Server(InitServer, &app->server);
    

     
    app->accountDB.Dump();   

    EnsureFolderExists("Accounts");
    RegisterAccountTypes();
    ListRegisterAccountTypes(); 
     
    auto MaxAccount = (PersonalAccount*)app->accountDB.GetAccountByName("maksymba0", AccountType::Personal); 
    auto TestAccount = app->accountDB.GetRandomUserByOffset(1).has_value() ? app->accountDB.GetRandomUserByOffset(1).value() : app->accountDB.GetRandomUserByOffset(2).value();

    MaxAccount->SendMoneyTo(TestAccount->GetID(), 100);
    
    while (true)
    {
        if (app->Exit())
        {
            break;
        }
        app->SimulateTransactions();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    app->accountDB.SaveAccounts("Accounts/accounts.txt");
    t_Server.join();
    return 4919;
}
