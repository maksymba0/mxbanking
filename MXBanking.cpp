#include <Windows.h>
#include <stdint.h>
#include <WinBase.h>
#include <minwinbase.h>
#include <iostream>
#include <chrono>
class App
{
private:

public: 
    const char* username;

    bool Auth();
    App();
    ~App();

};
 
App::App()
{
    std::cout << "App created\n";
}
App::~App()
{
    std::cout << "App destroyed\n";
    Sleep(5000);
}
enum class Currency : int 
{
    PLN = 0,   
    EUR = 1,
    USD = 2,
    UAH = 3,
    JPY = 4,  
    GBP = 5,   
    AUD = 6,   
    CAD = 7,
    Limit
};
const char* getCurrencyText(Currency code)
{
    static const char* currencies[] = { "PLN",
    "EUR",
    "USD",
    "UAH",
    "JPY",
    "GBP",
    "AUD",
    "CAD", };

    if (code >= Currency::PLN && code < Currency::Limit)
    {
        return currencies[static_cast<int>(code)];
    }
    return "#ERROR";
}

class Account
{
private:
    double oldBalance = 0.0;
    double balance = 0.0;
    std::string name = "#Empty";
    Currency currency = Currency::PLN;
     

public:
    
    bool GiveTo(Account* other, double amount)
    {
        if (amount <= 0.00)
        {
            std::cout << "[Account Transaction Error]: Unable to transfer (#INVALIDAMOUNT)\n";
            return false;
        }
        if (!other)
        {
            std::cout << "[Account Transaction Error]: Unable to transfer (#NORECIPIENT)\n";
            return false;
        }
        if (getBalance() < amount)
        {
            std::cout << "[Account Transaction Error]: Unable to transfer (#NOTENOUGHMONEY)\n";
            return false;
        }
        if (other->getCurrency() != getCurrency())
        {
            std::cout << "[Account Transaction Error]: Unable to transfer (#CURRENCYMISMATCH)\n";
            return false;
        }

        this->SubBalance(amount);
        other->AddBalance(amount);
         

        return true;
         
    }

    Currency getCurrency() { return currency; }
    double getBalance() { return balance; }

    std::string getName() { return name; }
    void Dump()
    {
        double balance = 0.0;
        std::cout << "Name: " << getName() << " | Currency: "
            << getCurrencyText(currency)<< " | Amount: " 
            << getBalance() 
            << "\n";
        std::string name = "#Empty";
        Currency currency = Currency::Limit;
    }
    void SetName(std::string newname)
    {
        if (newname.empty())
        {
            std::cout << "[Account operation]: Failed to set currency [Invalid currency]\n";
            return;
        }
        name = newname;
        std::cout << "[Account operation]: Changed name to " << name << "\n";
        return;
    }
    void SetCurrency(Currency _currency) 
    { 
        if (_currency < Currency::PLN || _currency >= Currency::Limit)
        {
            std::cout << "[Account operation]: Failed to set currency [Invalid currency]\n";
            return;
        }
        currency = _currency; 
        std::cout << "[Account operation]: Currency set to " << getCurrencyText(currency) << "\n";
    }
    void AddBalance(double _value)
    {
        oldBalance = balance;
        balance += _value;
        std::cout << "[Account operation]: Added " << getCurrencyText(getCurrency()) << _value<< " to " << getName() << "'s account (" << balance << ")\n";
    }
    void SubBalance(double _value)
    {
        oldBalance = balance;
        balance -= _value;
        std::cout << "[Account operation]: Subtracted " << getCurrencyText(getCurrency()) << _value << " from " << getName() << "'s account (" << balance << ")\n";
    }
    void SetBalance(double _value) 
    { 
        oldBalance = balance;
        balance = _value; 
        std::cout << "[Account operation]: Balance set to " << getCurrencyText(getCurrency()) << balance << "\n";
    }
    Account()
    {
        std::cout << "[Account]: Account created - (0x" << this << ")\n";
    }
    Account(std::string name, Currency currency, double value) : name(name), currency(currency),balance(value)
    {
        std::cout << "[Account]: Account created - (0x" << this << ") - " << name << " - " << getCurrencyText(getCurrency()) << " " << getBalance() << "\n";
    }
    Account(std::string name) : name(name), currency(Currency::PLN), balance(0.0)
    {
        std::cout << "[Account]: Account created - (0x" << this << ") - " << name << " - " << getCurrencyText(getCurrency()) << " " << getBalance() << "\n";
    }
};
 
#include <random>
double RandomDouble(double min, double max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_real_distribution<double> distrib(min, max);
    return distrib(gen);

}
float RandomFloat(float min,float max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_real_distribution<float> distrib(min, max);
    return distrib(gen);

}
int RandomInt(int min, int max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<int> distrib(min, max);
    return distrib(gen);

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
            if(logAttempts)
                std::cout << "Invalid input. Try again.\n";
            std::cin.clear();
            std::cin.ignore(1000,'\n');
            continue;
        }

        if (input == 0x948B8C) // 9735052
        {
            break; // ok
        }

        std::cout << "Error. Invalid Key\n";
        input = 0;
    }
     

    int Delay = RandomInt(0, 3);
    int sequence = 0;
    std::string dots = ".";
    std::cout << "Connecting to servers" << dots;

    while (Delay)
    {
        std::cout << dots;
        Sleep(1000); 
        Delay--;
    }
    return true;
}


class AccountDB
{
public:
    std::vector<std::unique_ptr<Account>> accounts;

    Account* Add(std::unique_ptr<Account> pAccount)
    {
        auto obj = pAccount.get();
        accounts.push_back(std::move(pAccount));
        std::cout << "[Account DB] : Increased accounts to " << accounts.size() << "\n";
        return obj;
    }
    void Remove(std::unique_ptr<Account> pAccount)
    {
         
    }

    void Dump()
    {
        std::cout << "\n----------ACCOUNTS DETAILS -----------\n";
        for (const auto& obj : accounts)
        {
            obj->Dump();
        }
        std::cout << "\n";
    }
};
int main()
{
    AccountDB accountDB;
   
     
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
     
    //Account MaxAccount("Max Cornelius", Currency::UAH, RandomDouble(0, 10000));
     
    auto MaxAccount = std::make_unique<Account>("maksymba0", Currency::PLN, RandomDouble(0, 35000));
    auto BotAccount = std::make_unique<Account>("Bot", Currency::PLN, RandomDouble(0, 500));
    auto AdminAccount = std::make_unique<Account>("Admin", Currency::PLN, RandomDouble(0, 50000));
    auto EmptyAccount = std::make_unique<Account>("Empty"); 
    

    Account* pAccount = nullptr;
    pAccount = accountDB.Add(std::move(MaxAccount));
    accountDB.Add(std::move(BotAccount));
    accountDB.Add(std::move(AdminAccount));
    accountDB.Add(std::move(EmptyAccount)); 

    pAccount->SetName("World");
    pAccount->SetBalance(39493.99);
    pAccount->Dump();

    accountDB.Dump();
    

    return 4919;
}