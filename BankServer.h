#pragma once
#include <queue>
#include <atomic>
#include "Account.h"
class BankServer
{
	 
public:
	 
	BankServer();
	int GetOperationsNum();
	bool HasOperationsNow();
 

	void AddOperation(Transaction t);
	int GetOperation();
	void DestroyLastOperation();

	void PrintState();

	void ProcessOperations();

	void ProcessOperation(Transaction& arg);

	void NotifyCustomer(int ID, int RequestID, RequestStatus);

	RequestStatus ProcessTransfer(Transfer& t, ErrorCode& code);
	RequestStatus ProcessDeposit(Deposit& t, ErrorCode& code);
	RequestStatus ProcessWithdrawal(Withdrawal& t, ErrorCode& code);

private:
	void AddBalanceTo(Account* user, double amount);
	void SubBalance(Account* user, double amount);
};

extern std::queue<Transaction> g_operations;

extern std::atomic<bool> g_ExitNow;
extern std::atomic<bool> g_ServerProcessing;

void InitServer(BankServer* server);