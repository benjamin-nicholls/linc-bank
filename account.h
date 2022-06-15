#pragma once
#include <vector>
#include <string>
#include "transaction.h"


class Account {
public:
	Account() {};
	~Account() {};
	virtual bool deposit(double Amount, int Ref = 0) = 0;
	virtual bool withdraw(double Amount, int Ref = 0) = 0;
	virtual std::string toString() const = 0;

protected:
	double m_Balance;
	std::vector<Transaction*> m_History;
	double m_OverdraftLimit = 0;
};


// Custom exceptions.

// Account exceptions.
struct NoAccountsCreatedException : public std::exception {
public:
	virtual const char* what() const throw() {
		return "ERROR: You have not opened any accounts yet.";
	}
};

struct NotEnoughAccountsException : public std::exception {
public:
	virtual const char* what() const throw() {
		return "ERROR: You have not opened enough accounts yet.";
	}
};

struct AccountNumberOutOfRangeException : public std::exception {
public:
	virtual const char* what() const throw() {
		return "ERROR: Account number specified out of range.";
	}
};

struct MaxCurrentAccountException : public std::exception {
public:
	virtual const char* what() const throw() {
		return "ERROR: You have opened the maximum number of current account(s).";
	}
};

struct MaxIsaAccountException : public std::exception {
public:
	virtual const char* what() const throw() {
		return "ERROR: You have opened the maximum number of ISA saving account(s).";
	}
};

// Number exceptions.
struct NotIntException : public std::exception {
public:
	virtual const char* what() const throw() {
		return "ERROR: Value was not an integer.";
	}
};

struct NotCurrencyException : public std::exception {
public:
	virtual const char* what() const throw() {
		return "ERROR: Value was not a currency format.";
	}
};

// Parameters exceptions.
struct NotEnoughParametersException : public std::exception {
public:
	virtual const char* what() const throw() {
		return "ERROR: You do not have enough parameters.";
	}
};

// Deposit exceptions.
struct InitialDepositBelowZeroException : public std::exception {
public:
	virtual const char* what() const throw() {
		return "ERROR: Initial deposit must be above £0.00.";
	}
};

struct InitialDepositBelowISARequiredException : public std::exception {
public:
	virtual const char* what() const throw() {
		return "ERROR: Initial deposit must be at least £1000.";
	}
};

// Transaction exceptions.
struct WithdrawFailException : public std::exception {
public:
	virtual const char* what() const throw() {
		return "ERROR: Could not withdraw from the account.";
	}
};

// Othet exceptions.
struct DynamicCastUnsuccessfulException : public std::exception {
public:
	virtual const char* what() const throw() {
		return "ERROR: Selected account is not a savings account.";
	}
};
