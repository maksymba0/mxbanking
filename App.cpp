#include "App.h"
#include <iostream>
#include <Windows.h> 
#include "Account.h"   
#include "Utils.h"

std::string g_TestValue = "some";
App::App()
{
    std::cout << "App created\n";
    this->lastTransaction = {};
}
App::~App()
{
    std::cout << "App destroyed\n";
    Sleep(5000);
}

App* App::GetApp()
{
    // This static instance is initialized the very first time GetApp() is called.
         // C++11 guarantees this initialization is 100% thread-safe!
    static App instance;
    return &instance;
}

 
int App::GenerateRandomUserID()
{
    return this->accountDB.GenerateRandomID();
}
void App::SimulateTransactions()
{
    auto Now = std::chrono::steady_clock::now();
    if (lastTransaction == std::chrono::steady_clock::time_point{})
    {
        lastTransaction = Now;
    }
    if (lastTransaction + std::chrono::seconds(5) >= Now) // not passed 5 seconds since last transaction
    {
        return;
    }
    else
    {
        lastTransaction = Now;
    }
    auto now = std::chrono::steady_clock::now();
    int DelayTime = RandomInt(900, 5000);

    if (GetAsyncKeyState(VK_F1))
    {
        return;
    }
    int Action = RandomInt(0, 5);
    int MAX_USERS = accountDB.accounts.size();

    switch (Action)
    {
        case 1:
        {
            int subjectIndex = RandomInt(0, MAX_USERS);

            auto SubjectK = this->accountDB.GetRandomUserByOffset(subjectIndex);

            Account* Subject = SubjectK.has_value() ? SubjectK.value() : nullptr; //this->accountDB.GetAccountByUniqueID(subjectIndex).value();

            if (Subject)
            {
                double amount = RandomDouble(0, static_cast<double>(Subject->getBalance() / 2));

                Subject->AddBalance(amount, "ATM Deposit");
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


            auto SubjectK = this->accountDB.GetRandomUserByOffset(subjectIndex);
            auto TargetK = this->accountDB.GetRandomUserByOffset(targetIndex);

            Account* Subject = nullptr; //this->accountDB.GetAccountByUniqueID(subjectIndex).value();
            Account* Target = nullptr;//this->accountDB.GetAccountByUniqueID(targetIndex).value();

            if (SubjectK.has_value())
            {
                Subject = SubjectK.value();
            }
            if (TargetK.has_value())
            {
                Target = TargetK.value();
            }


            if (Subject)
            {
                double amount = RandomDouble(0, static_cast<double>(Subject->getBalance() / 2));

                Subject->GiveTo(Target, amount);
            }
            break;
        }
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
bool App::Exit()
{
    if (GetAsyncKeyState(VK_F1) & 1)
    {
        g_ExitNow = true;
        return true;
    }
    return false;
}
#include <thread>
void App::Greeting()
{
    std::string text = "The Matrix has you...";
    auto len = std::strlen(text.c_str());
    std::cout << "Length:" << len << "\n";

    for (int i = 0; i < len; ++i)
    {
        auto delay = RandomInt(40, 100);
        std::cout << text[i];
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
    std::cout << "\n";
    system("cls");


}
#include <chrono>
#include <format>

 