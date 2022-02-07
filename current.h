#pragma once
#include "account.h"


class current : public account {

public:
	current();

	current(double initialDeposit);
	~current();

protected:
	double overdraft;
	bool deposit(double amount);
	bool withdraw(double amount);
	std::string toString();

};
