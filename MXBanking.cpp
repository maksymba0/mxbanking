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

 

int someCounter = 0;

 
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

    app->accountDB.Dump();

    std::thread t_Server(InitServer, &app->server);
    

     
     

    EnsureFolderExists("Accounts");
    RegisterAccountTypes();
    ListRegisterAccountTypes(); 
     
    auto MaxAccount = (PersonalAccount*)app->accountDB.GetAccountByName("maksymba0", AccountType::Personal); 
    auto TestAccount = app->accountDB.GetRandomUserByOffset(1).has_value() ? app->accountDB.GetRandomUserByOffset(1).value() : app->accountDB.GetRandomUserByOffset(2).value();

    MaxAccount->SendMoneyTo(TestAccount->GetID(), 100);
    
    auto maxAcc = App::GetApp()->accountDB.GetAccountByName("maksymba0",AccountType::Personal); 


    std::vector<PersonalAccount> accounts;

    //std::vector<Transaction> maxTransactions (maxAcc->GetTransactions());

    PersonalAccount ac("Neo", 1);
    accounts.push_back(ac);

    ac.SetBalance(10000);

    PersonalAccount ae("Morph", 2);
    ae.SetBalance(1000);

    std::cout << "before move - balance is " << ae.getBalance() << "\n";
    accounts.push_back(std::move(ae));

    std::cout << "after move - balance is " << ae.getBalance() << "\n";

     

    app->accountDB.Dump();
    app->accountDB.GiveAllAccountsBonusPerc(100);
    app->accountDB.Dump();
    while (true)
    { 
        if (app->Exit())
        {
            break;
        }
        app->SimulateTransactions();
        std::cout << "Bank networth increased to " << app->accountDB.GetAllAccountsBalance() << "\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    app->accountDB.SaveAccounts("Accounts/accounts.txt");
    t_Server.join();
    return 4919;
}
