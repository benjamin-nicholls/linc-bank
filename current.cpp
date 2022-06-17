#include "current.h"
#include <iostream> //remove


Current::Current(double InitialDeposit) {
	if (InitialDeposit < 0.00) { throw InitialDepositBelowRequiredException(); }
	m_Balance = InitialDeposit;
	m_Overdraft = 0.00;
	Transaction* t = new Transaction("Open Current Acount", m_Balance);
	m_History.push_back(t);
	m_p_HistoryTree = new TreeNode(t);
	std::cout << "in current account constructor" << std::endl;
	std::cout << m_p_HistoryTree->m_p_Transaction->toString() << std::endl;
}


Current::~Current() {
	for (auto t : m_History) {
		delete t;
	}
}


bool Current::deposit(double &Amount, int Ref) {
	if (Amount <= 0.00) { return false; }
	double a = Amount - m_Overdraft;
	if (a > 0) {
		m_Overdraft = 0.00;
		m_Balance += a;
	} else {
		m_Overdraft = -a;
	}
	std::string desc = "Deposit";
	if (Ref != 0) { desc = "Transfer from account " + std::to_string(Ref); }
	Transaction* t = new Transaction(desc, Amount);
	m_History.push_back(t);
	BST::Insert(m_p_HistoryTree, t);
	return true;
}


bool Current::withdraw(double &Amount, int Ref) {
	if (Amount <= 0.00) { return false; }
	if (m_Balance + m_OverdraftLimit - m_Overdraft < Amount) { return false; }
	
	if (m_Balance == 0) {
		m_Overdraft += Amount;
	} else {
		m_Balance -= Amount;
		if (m_Balance < 0.00) {
			m_Overdraft = -m_Balance;
			m_Balance = 0.00;
		}
	}
	std::string desc = "Withdraw";
	if (Ref != 0) { desc = "Transfer to account " + std::to_string(Ref); }
	Transaction* t = new Transaction(desc, Amount);
	m_History.push_back(t);
	BST::Insert(m_p_HistoryTree, t);
	return true;
}


double Current::GetBalance() const {
	return m_Balance - m_Overdraft;
}


std::string Current::toString() const {
	std::string a = "Current account | Balance: £" + Truncate::Truncate2dp(this->GetBalance()) + "\n";
	for (auto entry : m_History) {
		a += entry->toString();
    }
	return a;                                                           
}
