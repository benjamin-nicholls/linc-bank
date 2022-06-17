#pragma once
#include <string>


// Custom exceptions.

// Account exceptions.
struct NumberOfAccountsException : public std::exception {
public:
	NumberOfAccountsException() {}
	NumberOfAccountsException(const std::string &Message) { m_WhatMessage = Message; }
	virtual const char* what() const throw() { return m_WhatMessage.c_str(); }
private:
	std::string m_WhatMessage = "ERROR: Incorrect number of accounts.";
};


struct AccountNumberOutOfRangeException : public std::exception {
public:
	AccountNumberOutOfRangeException() {}
	AccountNumberOutOfRangeException(const std::string &Message) {m_WhatMessage = Message; }
	virtual const char* what() const throw() { return m_WhatMessage.c_str(); }
private:
	std::string m_WhatMessage = "ERROR: Account number specified out of range.";
};


struct MaxAccountException : public std::exception {
public:
	MaxAccountException() {}
	MaxAccountException(const std::string &Message) { m_WhatMessage = Message; }
	virtual const char* what() const throw() { return m_WhatMessage.c_str(); }
private:
	std::string m_WhatMessage = "ERROR: Maximum number of account(s) opened.";
};


// Number exceptions.
struct WrongTypeException : public std::exception {
public:
	WrongTypeException() {}
	WrongTypeException(const std::string &Message) { m_WhatMessage = Message; }
	virtual const char* what() const throw() { return m_WhatMessage.c_str(); }
private:
	std::string m_WhatMessage = "ERROR: Value was not the correct type/format.";
};


// Parameters exceptions.
struct NotEnoughParametersException : public std::exception {
public:
	NotEnoughParametersException() {}
	NotEnoughParametersException(const std::string &Message) { m_WhatMessage = Message; }
	virtual const char* what() const throw() { return m_WhatMessage.c_str(); }
private:
	std::string m_WhatMessage = "ERROR: You do not have enough parameters.";
};


// Deposit exceptions.
struct InitialDepositBelowRequiredException : public std::exception {
public:
	InitialDepositBelowRequiredException() {}
	InitialDepositBelowRequiredException(const std::string &Message) { m_WhatMessage = Message; }
	virtual const char* what() const throw() { return m_WhatMessage.c_str(); }
private:
	std::string m_WhatMessage = "ERROR: Initial deposit below required amount.";
};


// Transaction exceptions.
struct WithdrawFailException : public std::exception {
public:
	WithdrawFailException() {}
	WithdrawFailException(const std::string &Message) { m_WhatMessage = Message; }
	virtual const char* what() const throw() { return m_WhatMessage.c_str(); }
private:
	std::string m_WhatMessage = "ERROR: Could not withdraw from the account.";
};


// Other exceptions.
struct DynamicCastUnsuccessfulException : public std::exception {
public:
	DynamicCastUnsuccessfulException() {}
	DynamicCastUnsuccessfulException(const std::string &Message) { m_WhatMessage = Message; }
	virtual const char* what() const throw() { return m_WhatMessage.c_str(); }
private:
	std::string m_WhatMessage = "ERROR: Dynamic cast unsuccessful. Check types.";
};
