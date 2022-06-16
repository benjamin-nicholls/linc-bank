#pragma once
#include <string>
#include <chrono>


class Transaction {
private:
	std::string m_Currency;
	std::string m_Type;
	double m_Value;
	std::time_t m_Time;
	std::string Truncate2dp(double Value) const;

public:
	Transaction(std::string Type, double Value);
	~Transaction() {};
	std::string toString() const;
};
