#pragma once
#include <vector>
#include <string>
#include "historyinfo.h"


class account {

public:
	virtual ~account() {}

protected:
	double balance;
	std::vector<historyinfo *>history;
	double overdraftLimit = 500.00;

	virtual bool deposit() = 0;
	virtual bool withdraw() = 0;
	bool toString();

};
