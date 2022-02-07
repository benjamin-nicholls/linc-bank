#pragma once
#include "account.h"
#include "interestearning.h"


class savings: public account, public interestearning {

public:
	savings();
	~savings();

protected:
	double interestRate = 0.85;
	bool isa;
	bool deposit(double amount);
	bool withdraw(double amount);
	
};
