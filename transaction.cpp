#include "transaction.h"
#include <cmath>


Transaction::Transaction(std::string Type, double Value) {
	auto nowRaw = std::chrono::system_clock::now();
	std::time_t nowTime = std::chrono::system_clock::to_time_t(nowRaw);
	m_Currency = "£";
	m_Type = Type;
	m_Value = Value;
	m_Time = nowTime;
}


std::string Transaction::toString() const {
	return "-- " + m_Type + ": " + m_Currency + Transaction::Truncate2dp(m_Value) + " on " + ctime(&m_Time);
}


std::string Transaction::Truncate2dp(double Value) const {
	std::string value = std::to_string(Value);
	return value.substr(0, value.find('.')  + 3);
}
