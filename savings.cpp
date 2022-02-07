#include "savings.h"

savings::savings(double initialDeposit = 0, bool Isa = false) {
	if (initialDeposit < 0) { 
		throw std::exception{"Initial deposit for a savings account cannot be negative."};
	}

	balance = initialDeposit;
	isa = Isa;
	std::string accountType = "Savings";
	if (isa) {
		if (initialDeposit < 1000) {
			throw std::exception{ "Initial deposit for an ISA account must be at least £1000." };
		}
		interestRate = 0.0115;
		accountType = "ISA";
	}

	historyinfo* hi = new historyinfo("Open" + accountType + "Account", balance);
	history.push_back(hi);
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

//this needs to be changed to use interestearning
void savings::assignInterest() {
	balance *= 1 + interestRate;
}


//toString
/*


	0.0085 


	double interestRate;
	bool isa;
		double computeinterest();

		double balance;
	std::vector<std::string>history;

	bool deposit();
	bool withdraw();
	bool toString();


*/