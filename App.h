#pragma once
#include "AccountDatabase.h"
class App
{
private:

public:
    const char* username;
    AccountDatabase accountDB;

    int GenerateRandomUserID();
    void SimulateTransactions();

    bool Auth();
    
    void Greeting();
     

    App();
    App(const App& other) = delete;
    App& operator=(const App& other) = delete;
    ~App();

};

 