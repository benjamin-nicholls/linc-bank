#include "transaction.h"
#include "truncate.h"
#include <chrono>  // Time of transaction.


Transaction::Transaction(std::string Type, double Value) {
	auto nowRaw = std::chrono::system_clock::now();
	std::time_t nowTime = std::chrono::system_clock::to_time_t(nowRaw);
	m_Currency = "£";
	m_Type = Type;
	m_Value = Value;
	m_Time = nowTime;
}


std::string Transaction::toString() const {
	return "-- " + m_Type + ": " + m_Currency + Truncate::Truncate2dp(m_Value) + " on " + ctime(&m_Time);
}


bool Transaction::operator <(Transaction const &obj) {
    if (m_Value < obj.m_Value) { return true; }
    return false;
}
bool Transaction::operator >(Transaction const &obj) {
    if (m_Value > obj.m_Value) { return true; }
    return false;
}
bool Transaction::operator ==(Transaction const &obj) {
    if (m_Value == obj.m_Value) { return true; }
    return false;
}
bool Transaction::operator <(double const Key) {
    if (m_Value < Key) { return true; }
    return false;
}
bool Transaction::operator >(double const Key) {
    if (m_Value > Key) { return true; }
    return false;
}
bool Transaction::operator ==(double const Key) {
    if (m_Value == Key) { return true; }
    return false;
}
