#pragma once
#include "account.h"


class Current : public Account {

public:
	Current();
	Current(double InitialDeposit);
	~Current();

protected:
	double m_OverdraftLimit = 500.00;
	double m_Overdraft;
	bool Deposit(double Amount);
	bool Withdraw(double Amount);
	std::string ToString();

};
