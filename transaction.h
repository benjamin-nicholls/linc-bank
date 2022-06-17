#pragma once
#include <string>
#include <chrono>
#include "truncate.h"


class Transaction {
private:
	std::string m_Currency;
	std::string m_Type;
	double m_Value;
	std::time_t m_Time;

public:
	Transaction(std::string Type, double Value);
	~Transaction() {};
	std::string toString() const;
	bool operator <(Transaction const &obj);
	bool operator >(Transaction const &obj);
	bool operator ==(Transaction const &obj);
	bool operator <(double const Key);
	bool operator >(double const Key);
	bool operator ==(double const Key);
};
