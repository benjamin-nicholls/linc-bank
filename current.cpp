#include "current.h"


Current::Current(double InitialDeposit) {
	if (InitialDeposit < 0.00) {
		//throw std::exception{ "Initial deposit for a current account cannot be negative." };
		throw "Initial deposit for a current account cannot be negative.";
	}
	m_Balance = InitialDeposit;
	m_Overdraft = 0.00;
	Transaction* t = new Transaction("Open Current Acount", m_Balance);
	m_History.push_back(t);
}


Current::~Current() {
}


bool Current::Deposit(double Amount) {
	if (Amount <= 0.00) { return false; }

	double a = Amount - m_Overdraft;
	if (a > 0) {
		m_Overdraft = 0.00;
		m_Balance += a;
	} else {
		m_Overdraft = -a;
	}

	Transaction* t = new Transaction("Deposit", Amount);
	m_History.push_back(t);
	return true;

}


bool Current::Withdraw(double Amount) {
	if (Amount <= 0.00) { return false; }
	if (m_Balance + m_OverdraftLimit - m_Overdraft <= Amount) { return false; }
	
	if (m_Balance == 0) {
		m_Overdraft -= Amount;
	} else {
		m_Balance -= Amount;
		if (m_Balance < 0.00) {
			m_Overdraft = -m_Balance;
			m_Balance = 0.00;
		}
	}

	Transaction* t = new Transaction("Withdraw", Amount);
	m_History.push_back(t);
	return true;
}


double Current::GetBalance() {
	return m_Balance - m_Overdraft;
}


std::string Current::Truncate2dp(double Value) {
	std::string value = std::to_string(Value);
	value = value.substr(0, value.find('.')  + 3);
	return value;
}


std::string Current::ToString() {
	std::string a = "";

	a += "Current account | Balance: £" + Current::Truncate2dp(this->GetBalance()) + "\n";
	for (auto entry : m_History) {
		a += entry->ToString();
    }
	return a;                                                           
}

