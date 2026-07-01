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
    App();
    ~App();

};

 