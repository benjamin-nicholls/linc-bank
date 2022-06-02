#pragma once
#include <vector>
#include <string>
#include "historyinfo.h"


class Account {

public:
	Account() {}
	~Account() {}

protected:
	double m_Balance;
	std::vector<HistoryInfo*> m_History;
	double m_OverdraftLimit = 0;

	virtual bool Deposit(double Amount) = 0;
	virtual bool Withdraw(double Amount) = 0;
	std::string ToString();

};
