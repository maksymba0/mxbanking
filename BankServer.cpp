#include "BankServer.h"

#include <iostream>
#include <string>
#include <thread>
#include <Windows.h>
#include "Account.h"
#include "App.h"
std::atomic<bool> g_ExitNow(false);
std::atomic<bool> g_ServerProcessing(false);
std::queue<Transaction> g_operations;
 
BankServer::BankServer()
{
	std::cout << "Server connected\n";
}
 
int BankServer::GetOperationsNum() 
{ 
	return g_operations.size();
}
bool BankServer::HasOperationsNow() 
{
	return GetOperationsNum() > 0; 
}

void BankServer::AddOperation(Transaction t) 
{
	g_operations.push(t);
	std::cout << "[Server]: Received operation request\n";
}
int BankServer::GetOperation() { 
	return 0; 
}
void BankServer::DestroyLastOperation() { 
	return; 
}

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

void BankServer::ProcessOperations()
{
	if (!HasOperationsNow())
	{
		return;
	}
	while (!g_operations.empty())
	{
		auto transaction = g_operations.front();
		ProcessOperation(transaction);
		g_operations.pop();
	}
}

void BankServer::ProcessOperation(Transaction& arg_)
{
	std::visit([this](auto&& arg) 
		{
			ErrorCode ec = ErrorCode::InternalError;
			using T = std::decay_t<decltype(arg)>;
			if constexpr (std::is_same_v<T, Transfer>)
			{
				ProcessTransfer(arg, ec);
			}
			else if constexpr (std::is_same_v<T, Deposit>)
			{
				ProcessDeposit(arg,ec);
			}
			else if constexpr (std::is_same_v<T, Withdrawal>)
			{
				ProcessWithdrawal(arg,ec);
			}
			 
			if (ec == ErrorCode::None)
			{
				NotifyCustomer(arg.sourceID, arg.requestID, RequestStatus::Success);
			}
			else if (ec == ErrorCode::NeedToVerify)
			{
				NotifyCustomer(arg.sourceID, arg.requestID, RequestStatus::Pending);
			}

		}, arg_);
}

void BankServer::NotifyCustomer(int ID, int RequestID, RequestStatus status)
{
	auto customer = App::GetApp()->accountDB.GetAccountByUniqueID(ID).has_value() ? App::GetApp()->accountDB.GetAccountByUniqueID(ID).value() : nullptr;

	if (!customer)
	{
		std::cout << "Unable to notify customer (ID:" << ID << ")\n";
		return;
	}

	customer->OnReceivedResponse(RequestID, status);
}

RequestStatus BankServer::ProcessTransfer(Transfer& t, ErrorCode& code)
{
	auto sender = App::GetApp()->accountDB.GetAccountByUniqueID(t.sourceID).has_value() ? App::GetApp()->accountDB.GetAccountByUniqueID(t.sourceID).value(): nullptr;
	auto recipient = App::GetApp()->accountDB.GetAccountByUniqueID(t.targetID).has_value() ? App::GetApp()->accountDB.GetAccountByUniqueID(t.targetID).value() : nullptr;
	
	if (!sender || !recipient)
	{
		code = ErrorCode::InvalidDetails;
		return RequestStatus::Error;
	}
	if (t.amount > sender->getBalance() || t.amount <= 0.0)
	{

		code = ErrorCode::InvalidAmount;
		return RequestStatus::Error;
	}
	if (t.amount > 10000)
	{
		code = ErrorCode::NeedToVerify;
		return RequestStatus::Pending;
	}
	code = ErrorCode::None;
	AddBalanceTo(recipient, t.amount);
	SubBalance(sender, t.amount);

	return RequestStatus::Success;
}
void BankServer::AddBalanceTo(Account* user, double amount)
{
	user->SetBalance(user->getBalance() + amount);
}
void BankServer::SubBalance(Account* user, double amount)
{
	user->SetBalance(user->getBalance() - amount);
}

RequestStatus BankServer::ProcessDeposit(Deposit& t, ErrorCode& code)
{
	auto sender = App::GetApp()->accountDB.GetAccountByUniqueID(t.sourceID).has_value() ? App::GetApp()->accountDB.GetAccountByUniqueID(t.sourceID).value() : nullptr; 

	if (!sender)
	{
		code = ErrorCode::InvalidDetails;
		return RequestStatus::Error;
	}
	if (t.amount > sender->getBalance() || t.amount <= 0.0)
	{

		code = ErrorCode::InvalidAmount;
		return RequestStatus::Error;
	}

	AddBalanceTo(sender, t.amount);

	return RequestStatus::Success;
}

RequestStatus BankServer::ProcessWithdrawal(Withdrawal& t, ErrorCode& code)
{
	auto sender = App::GetApp()->accountDB.GetAccountByUniqueID(t.sourceID).has_value() ? App::GetApp()->accountDB.GetAccountByUniqueID(t.sourceID).value() : nullptr; 

	if (!sender)
	{
		code = ErrorCode::InvalidDetails;
		return RequestStatus::Error;
	}
	if (t.amount > sender->getBalance() || t.amount <= 0.0)
	{

		code = ErrorCode::InvalidAmount;
		return RequestStatus::Error;
	}

	SubBalance(sender, t.amount);

	return RequestStatus::Success;
}



void InitServer(BankServer* server)
{
	 
	while (!g_ExitNow)
	{
		server->PrintState();
		server->ProcessOperations();
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}
	std::cout << "exit thread\n";
	 
}