#include "current.h"


Current::Current(double InitialDeposit) {
	if (InitialDeposit < 0.00) { throw InitialDepositBelowRequiredException(); }
	// Set the balance and overdraft values.
	m_Balance = InitialDeposit;
	m_Overdraft = 0.00;
	// Create a transaction object and pointer to that object (t).
	Transaction* t = new Transaction("Open Current Account", m_Balance);
	// Store the pointer twice, once in a vector for chronological operations
	// and once in a binary tree for value searching.
	m_History.push_back(t);
	m_p_HistoryTree = new TreeNode(t);
}


Current::~Current() {
	if (m_p_HistoryTree != nullptr) { delete m_p_HistoryTree; }
	// Same transaction objects stored in binary tree as m_History vector.
	// Only have to clear the vector.
	m_History.clear();
}


bool Current::deposit(double &Amount, int Ref) {
	if (Amount <= 0.00) { return false; }
	double a = Amount - m_Overdraft;
	// Calculate new balance and overdraft.
	if (a > 0) {
		m_Overdraft = 0.00;
		m_Balance += a;
	} else {
		m_Overdraft = -a;
	}
	std::string desc = "Deposit";
	// Show the deposit was a transfer if applicable.
	if (Ref != 0) { desc = "Transfer from account " + std::to_string(Ref); }
	// Create transaction object.
	Transaction* t = new Transaction(desc, Amount);
	// Store transaction object pointer twice.
	m_History.push_back(t);
	m_p_HistoryTree = BST::Insert(m_p_HistoryTree, t);
	return true;
}


bool Current::withdraw(double &Amount, int Ref) {
	// Guarding.
	if (Amount <= 0.00) { return false; }
	// Ensure withdraw amount is a legal operation.
	if (m_Balance + m_OverdraftLimit - m_Overdraft < Amount) { return false; }
	// Caluclate new balance and overdraft, if applicable.
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
	// Show transaction as a transfer, if applicable.
	if (Ref != 0) { desc = "Transfer to account " + std::to_string(Ref); }
	// Create transaction.
	Transaction* t = new Transaction(desc, Amount);
	// Store transaction pointer twice.
	m_History.push_back(t);
	m_p_HistoryTree = BST::Insert(m_p_HistoryTree, t);
	return true;
}


double Current::getBalance() const {
	return m_Balance - m_Overdraft;
}


std::string Current::toString() const {
	std::string a = "Current account | Balance: £" + Truncate::Truncate2dp(this->getBalance()) + "\n";
	for (auto entry : m_History) { a += entry->toString(); }
	return a;                                                           
}
