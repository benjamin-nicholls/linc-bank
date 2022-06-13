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


Transaction::~Transaction() {
}


std::string Transaction::ToString() {
	return "-- " + m_Type + ": " + m_Currency + Transaction::Truncate2dp(m_Value) + " on " + ctime(&m_Time);
}


std::string Transaction::Truncate2dp(double Value) {
	std::string value = std::to_string(Value);
	value = value.substr(0, value.find('.')  + 3);
	return value;
}