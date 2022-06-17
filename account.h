#pragma once
#include <vector>
#include <string>
#include "exceptions.h"
#include "transaction.h"
#include "bst.h"
#include "truncate.h"


class Account {
public:
	virtual ~Account() {};
	virtual bool deposit(double &Amount, int Ref = 0) = 0;
	virtual bool withdraw(double &Amount, int Ref = 0) = 0;
	virtual std::string toString() const = 0;
	TreeNode* m_p_HistoryTree;

protected:
	double m_Balance;
	std::vector<Transaction*> m_History;
	double m_OverdraftLimit = 0;
};
