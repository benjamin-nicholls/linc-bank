#pragma once
#include <vector>
#include <string>
#include "transaction.h"


class Account {

public:
	Account() {}
	~Account() {}
	virtual std::string ToString() = 0;

protected:
	double m_Balance;
	std::vector<Transaction*> m_History;
	double m_OverdraftLimit = 0;
	virtual bool Deposit(double Amount) = 0;
	virtual bool Withdraw(double Amount) = 0;

};
