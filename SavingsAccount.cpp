#include "SavingsAccount.h"

double SavingsAccount::getBalance() const
{
	return balance + (balance*0.02);
}
