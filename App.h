#pragma once
#include "AccountDatabase.h"
#include "BankServer.h"
class App
{
private:

public:
    const char* username;
    
    AccountDatabase accountDB;
    
    BankServer server;

    std::chrono::steady_clock::time_point lastTransaction;

    int GenerateRandomUserID();
    void SimulateTransactions();

    bool Auth();
    bool Exit();

    void Greeting();
     

    App();
    App(const App& other) = delete;
    App& operator=(const App& other) = delete;
    ~App();

    static App* GetApp();


}; 
 