#include "savings.h"
#include <cmath>  // Exponent.



Savings::Savings(double InitialDeposit, bool Isa) {
	if (InitialDeposit < 0) { throw InitialDepositBelowRequiredException(); }
	m_Balance = InitialDeposit;
	m_ISA = Isa;
	m_InterestRate = 0.85;
	std::string accountType = "Savings";
	if (m_ISA) {
		if (InitialDeposit < m_IsaRequiredDeposit) {
			throw InitialDepositBelowRequiredException("ERROR: Initial deposit must be at least £" + Truncate::Truncate2dp(m_IsaRequiredDeposit) + ".");
		}
		m_InterestRate = 1.15;
		accountType = "ISA";
	}
	Transaction* t = new Transaction("Open " + accountType + " Account", m_Balance);
	m_History.push_back(t);
	m_p_HistoryTree = new TreeNode(t);
}	


Savings::~Savings() {
	if (m_p_HistoryTree != nullptr) { delete m_p_HistoryTree; }
	// Same transaction objects stored in binary tree as m_History vector.
	// Only have to clear the vector.
	m_History.clear();
}


bool Savings::deposit(double &Amount, int Ref) {
	if (Amount <= 0) { return false; }
	m_Balance += Amount;
	std::string desc = "Deposit";
	if (Ref != 0) { desc = "Transfer from account " + std::to_string(Ref); }
	Transaction* t = new Transaction(desc, Amount);
	m_History.push_back(t);
	m_p_HistoryTree = BST::Insert(m_p_HistoryTree, t);
	return true;
}


bool Savings::withdraw(double &Amount, int Ref) {
	if (Amount <= 0.00) { return false; }
	if (m_Balance - Amount < 0.00) { return false; }
	m_Balance -= Amount;
	std::string desc = "Withdraw";
	if (Ref != 0) { desc = "Transfer to account " + std::to_string(Ref); }
	Transaction* t = new Transaction(desc, Amount);
	m_History.push_back(t);
	m_p_HistoryTree = BST::Insert(m_p_HistoryTree, t);
	return true;
}


double Savings::computeInterest(int Years) const {
	int n = 12;  // Unit time (monthly = 12).
	return m_Balance * pow(1 + m_InterestRate / 100 / n, n * Years);
}


std::string Savings::toString() const {
	std::string str = "Savings";
	if (m_ISA) { str = "ISA"; }
	str += " account | Balance: £" + Truncate::Truncate2dp(m_Balance) + "\n";
	for (auto entry : m_History) { str += entry->toString(); }
	return str;   
}
