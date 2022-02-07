#pragma once
#include "account.h"
#include "interestearning.h"


class savings: public account, public interestearning {

public:
	//savings();
	savings(double initialDeposit, bool Isa);
	~savings();

protected:
	double interestRate = 0.0085;
	bool isa;
	bool deposit(double amount);
	bool withdraw(double amount);
	void assignInterest();
	
};
