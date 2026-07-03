#include "App.h"
#include <iostream>
#include <Windows.h> 
#include "Account.h"  

#include "Utils.h"
App::App()
{
    std::cout << "App created\n";
}
App::~App()
{
    std::cout << "App destroyed\n";
    Sleep(5000);
}

 
int App::GenerateRandomUserID()
{
    return this->accountDB.GenerateRandomID();
}
void App::SimulateTransactions()
{
    while (true)
    {
        int DelayTime = RandomInt(900, 5000);

        if (GetAsyncKeyState(VK_F1))
        {
            break;
        } 
        int Action = RandomInt(0, 5);
        int MAX_USERS = accountDB.accounts.size();

        switch (Action)
        {
            case 1:
            {
                int subjectIndex = RandomInt(0, MAX_USERS);

                Account* Subject = this->accountDB.GetAccountByIndex(subjectIndex);

                if (Subject)
                {
                    double amount = RandomDouble(0, static_cast<double>(Subject->getBalance() / 2));
                    
                    Subject->AddBalance(amount,"ATM Deposit");
                }
                break;
            }
            case 0: 
            default:
            {
                int subjectIndex = RandomInt(0, MAX_USERS);
                int targetIndex = RandomInt(0, MAX_USERS);
                while (targetIndex == subjectIndex)
                {
                    targetIndex = RandomInt(0, MAX_USERS); // Ensure these not the same customers
                }

                Account* Subject = this->accountDB.GetAccountByIndex(subjectIndex);
                Account* Target = this->accountDB.GetAccountByIndex(targetIndex);

                if (Subject)
                {
                    double amount = RandomDouble(0, static_cast<double>(Subject->getBalance() / 2));

                    Subject->GiveTo(Target, amount);
                }
                break;
            }
        }
        Sleep(DelayTime);
    }
}

bool App::Auth()
{
    int logAttempts = 3;
    while (true)
    {
        long long input{ 0 };
        if (logAttempts == 0)
        {
            return false;
        }

        std::cout << "Please enter your employee key\n";

        if (!(std::cin >> input))
        {
            logAttempts--;
            if (logAttempts)
                std::cout << "Invalid input. Try again.\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }
         
        if (input == 4444) // 9735052 
        {
            break; // ok
        }

        std::cout << "Error. Invalid Key\n";
        input = 0;
    }


    int Delay = RandomInt(0, 2);
    int sequence = 0;
    std::string dots = ".";
    std::cout << "Connecting to servers" << dots;

    while (Delay)
    {
        std::cout << dots;
        Sleep(600);
        Delay--;
    }
    return true;
}
#include <chrono>
#include <format>

 
