#include "savings.h"
#include <cmath>  // Exponent.


Savings::Savings(double InitialDeposit, bool Isa) {
	if (InitialDeposit < 0) {
		//throw std::exception{"Initial deposit for a savings account cannot be negative."};
		throw "Initial deposit for a savings account cannot be negative.";
	}

	m_Balance = InitialDeposit;
	m_ISA = Isa;
	std::string accountType = "Savings";
	if (m_ISA) {
		if (InitialDeposit < 1000) {
			//throw std::exception& e("Initial deposit for an ISA account must be at least �1000.");
			throw "Initial deposit for an ISA account must be at least £1000.";
		}
		m_InterestRate = 1.15;
		accountType = "ISA";
	}

	HistoryInfo* hi = new HistoryInfo("Open" + accountType + "Account", m_Balance);
	m_History.push_back(hi);
	delete hi;
}	

Savings::~Savings() {

}

bool Savings::Deposit(double Amount) {
	if (Amount <= 0) { return false; }
	m_Balance += Amount;
	HistoryInfo* hi = new HistoryInfo("Deposit", Amount);
	m_History.push_back(hi);
	delete hi;
	return true;
}


bool Savings::Withdraw(double Amount) {
	if (Amount <= 0) { return false; }
	if (m_Balance - Amount < 0) { return false; }

	m_Balance -= Amount;

	HistoryInfo* hi = new HistoryInfo("Withdraw", Amount);
	m_History.push_back(hi);
	delete hi;
	return true;
}


double Savings::ComputeInterest(double InitialBalance, int Years) {
	// Compound interest equation.
	// A = P(1+(r/n))^nt
	// A = final amount, P = intial balance, r = interest rate decimal, t = time period, n = applied per unit time (monthly).
	return InitialBalance * pow(1 + m_InterestRate / 12, 12 * Years);
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