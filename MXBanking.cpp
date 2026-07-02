#include <Windows.h>
#include <stdint.h>
#include <WinBase.h>
#include <minwinbase.h>
#include <iostream>
#include <chrono>

#include "Account.h"
#include "Utils.h"
 
#include "App.h"

 
 
 


 


 
int main()
{
     
    
    App app;

    if (!app.Auth())
    {
        std::cout << "Failed to log in. Exiting\n";
        Sleep(2000);
        exit(-1);
    }

    Sleep(100);

    char buffer[256] = { 0 };
    DWORD buffersize = sizeof(buffer); 
    GetUserName(buffer, &buffersize);

    app.username = buffer;

    std::cout << "Welcome " << app.username << "!\n";
    std::cout << "========================================== \n";
    std::cout << "============ MXBanking System ============ \n";
 
    auto MaxAccount = std::make_shared<Account>("maksymba0", Currency::PLN, RandomDouble(0, 4000), app.GenerateRandomUserID());
    auto MariaAccount = std::make_shared<Account>("Maria", Currency::PLN, RandomDouble(0, 2000), app.GenerateRandomUserID());
    auto JohnsonAccount = std::make_shared<Account>("Johnson", Currency::PLN, RandomDouble(0, 2000), app.GenerateRandomUserID());
    auto AndreaAccount = std::make_shared<Account>("Andrea", Currency::PLN, RandomDouble(0, 2000), app.GenerateRandomUserID());
    auto LeonAccount = std::make_shared<Account>("Leon", Currency::PLN, RandomDouble(0, 2000), app.GenerateRandomUserID());

    Account* pAccount = nullptr;

    app.accountDB.Add(MaxAccount);
    app.accountDB.Add(MariaAccount);
    app.accountDB.Add(JohnsonAccount);
    app.accountDB.Add(AndreaAccount);
    app.accountDB.Add(LeonAccount);
      
    app.accountDB.Dump();

    app.SimulateTransactions();
    

    return 4919;
}
