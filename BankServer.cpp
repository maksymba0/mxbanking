#include "BankServer.h"

#include <iostream>
#include <string>
#include <thread>

std::atomic<bool> g_ExitNow(false);
 
BankServer::BankServer()
{
	std::cout << "Server connected\n";
}

int BankServer::GetOperationsNum() { return operations_.size(); }
bool BankServer::HasOperationsNow() { return GetOperationsNum() > 0; }

void BankServer::AddOperation(int arg) { operations_.push(arg); }
int BankServer::GetOperation() { return operations_.front(); }
void BankServer::DestroyLastOperation() { operations_.pop(); }

void BankServer::PrintState()
{
	auto operations = GetOperationsNum();
	std::string message = "";
	if (operations > 0)
	{
		message =  "[Server]: Currently have " + std::to_string(operations) + " operations.\n";
	}
	else
	{
		message = "[Server]: No operations currently.\n";
	}
	std::cout << message;
}

void InitServer()
{
	BankServer server;
	while (!g_ExitNow)
	{
		server.PrintState();
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	std::cout << "exit thread\n";
}