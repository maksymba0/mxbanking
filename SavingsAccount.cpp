#include "SavingsAccount.h"

double SavingsAccount::getBalance() const
{
	return balance_ + (balance_*0.02);
}
