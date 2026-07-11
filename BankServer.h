#pragma once
#include <queue>
#include <atomic>
class BankServer
{
	std::queue<int> operations_;
public:
	 
	BankServer();
	int GetOperationsNum();
	bool HasOperationsNow();

	void AddOperation(int arg);
	int GetOperation();
	void DestroyLastOperation();

	void PrintState();
};

extern std::atomic<bool> g_ExitNow;
void InitServer();