#include "savings.h"
#include <cmath> // exponent


savings::savings(double InitialDeposit = 0, bool Isa = false) {
	if (InitialDeposit < 0) {
		throw std::exception{"Initial deposit for a savings account cannot be negative."};
	}

	balance = InitialDeposit;
	isa = Isa;
	std::string accountType = "Savings";
	if (isa) {
		if (InitialDeposit < 1000) {
			throw std::exception{ "Initial deposit for an ISA account must be at least £1000." };
		}
		interestRate = 1.15;
		accountType = "ISA";
	}

	historyinfo* hi = new historyinfo("Open" + accountType + "Account", balance);
	history.push_back(hi);
}

savings::~savings() {

}

bool savings::deposit(double Amount) {
	if (Amount <= 0) { return false; }
	balance += Amount;
	historyinfo* hi = new historyinfo("Deposit", Amount);
	history.push_back(hi);
	return true;
}


bool savings::withdraw(double Amount) {
	if (Amount <= 0) { return false; }
	if (balance - Amount < 0) { return false; }

	balance -= Amount;

	historyinfo* hi = new historyinfo("Withdraw", Amount);
	history.push_back(hi);
	return true;
}


double savings::computeInterest(double InitialBalance, int Years) {
	// Compound interest equation.
	// A = P(1+(r/n))^nt
	// A = final amount, P = intial balance, r = interest rate decimal, t = time period, n = applied per unit time (monthly).
	return InitialBalance * pow(1 + interestRate / 12, 12 * Years);
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