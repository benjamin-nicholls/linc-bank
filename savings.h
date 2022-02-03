#pragma once
#include "account.h"
#include "interestearning.h"


class savings: public account, public interestearning {

protected:
	double interestRate;
	bool isa;
		
};
