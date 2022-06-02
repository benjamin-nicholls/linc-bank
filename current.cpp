#include "current.h"


Current::Current() {
	m_Balance = 0;
	m_Overdraft = 0;
	HistoryInfo* hi = new HistoryInfo("Open Current Account", m_Balance);
	m_History.push_back(hi);
	//delete hi; //will this delete the data or just the pointer?
}


Current::Current(double InitialDeposit) {
	if (InitialDeposit < 0) {
		//throw std::exception{ "Initial deposit for a current account cannot be negative." };
		throw "Initial deposit for a current account cannot be negative.";
	}
	m_Balance = InitialDeposit;
	m_Overdraft = 0;
	HistoryInfo* hi = new HistoryInfo("Open Current Account", m_Balance);
	m_History.push_back(hi);
}


Current::~Current() {
}


bool Current::Deposit(double Amount) {
	if (Amount <= 0) { return false; }

	double a = Amount - m_Overdraft;
	if (a > 0) {
		m_Overdraft = 0;
		m_Balance += a;
	} else {
		m_Overdraft = -a;
	}

	HistoryInfo* hi = new HistoryInfo("Deposit", Amount);
	m_History.push_back(hi);
	return true;

}


bool Current::Withdraw(double Amount) {
	if (Amount <= 0) { return false; }
	if (m_Balance + m_OverdraftLimit - m_Overdraft <= Amount) { return false; }

	m_Balance -= Amount;
	if (m_Balance < 0) {
		m_Overdraft = -m_Balance;
		m_Balance = 0;
	}

	HistoryInfo* hi = new HistoryInfo("Withdraw", Amount);
	m_History.push_back(hi);
	return true;
}


std::string Current::ToString() {
	return "";
}
