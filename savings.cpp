#include "savings.h"

savings::savings() {

}

savings::~savings() {

}

bool savings::deposit(double amount) {
	if (amount <= 0) { return false; }
	balance += amount;
	historyinfo* hi = new historyinfo("Deposit", amount);
	history.push_back(hi);
	return true;
}


bool savings::withdraw(double amount) {
	if (amount <= 0) { return false; }
	if (balance - amount < 0) { return false; }

	balance -= amount;

	historyinfo* hi = new historyinfo("Withdraw", amount);
	history.push_back(hi);
	return true;
}

/*

	double interestRate;
	bool isa;
		double computeinterest();

		double balance;
	std::vector<std::string>history;

	bool deposit();
	bool withdraw();
	bool toString();


*/