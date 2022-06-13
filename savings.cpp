#include "savings.h"
#include <cmath>  // Exponent.


Savings::Savings(double InitialDeposit, bool Isa) {
	if (InitialDeposit < 0) {
		throw "Initial deposit for a savings account cannot be negative.";
	}
	m_Balance = InitialDeposit;
	m_ISA = Isa;
	std::string accountType = "Savings";
	if (m_ISA) {
		if (InitialDeposit < 1000) {
			throw "Initial deposit for an ISA account must be at least £1000.";
		}
		m_InterestRate = 1.15;
		accountType = "ISA";
	}
	Transaction* t = new Transaction("Open " + accountType + " Account", m_Balance);
	m_History.push_back(t);
}	


Savings::~Savings() {
}


bool Savings::Deposit(double Amount) {
	if (Amount <= 0) { return false; }
	m_Balance += Amount;
	Transaction* t = new Transaction("Deposit", Amount);
	m_History.push_back(t);
	return true;
}


bool Savings::Withdraw(double Amount) {
	if (Amount <= 0.00) { return false; }
	if (m_Balance - Amount < 0.00) { return false; }
	m_Balance -= Amount;
	Transaction* t = new Transaction("Withdraw", Amount);
	m_History.push_back(t);
	return true;
}


double Savings::ComputeInterest(int Years) {
	int n = 12;  // Unit time (monthly = 12).
	double finalAmount = m_Balance * pow(1 + m_InterestRate / n, n * Years);
	return finalAmount;
}


std::string Savings::Truncate2dp(double Value) {
	std::string value = std::to_string(Value);
	value = value.substr(0, value.find('.')  + 3);
	return value;
}


std::string Savings::ToString() {
	std::string a = "";
	a += "Savings account | Balance: £" + Savings::Truncate2dp(m_Balance) + "\n";
	for (auto entry : m_History) {
		a += entry->ToString();
    }
	return a;   
}
