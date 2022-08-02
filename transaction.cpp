#define _CRT_SECURE_NO_WARNINGS
#include "transaction.h"
#include "truncate.h"
#include <chrono>  // Time of transaction.


Transaction::Transaction(std::string Type, double Value) {
	auto nowRaw = std::chrono::system_clock::now();
	std::time_t nowTime = std::chrono::system_clock::to_time_t(nowRaw);
    // Possibility to change currency if this were to be developed further .
	m_Currency = "GBP";  
	m_Type = Type;
	m_Value = Value;
	m_Time = nowTime;
}


std::string Transaction::toString() const {
	return "-- " + m_Type + ": " + m_Currency + Truncate::Truncate2dp(m_Value) + " on " + ctime(&m_Time);
}


// Operator overloading to allow transactions to be compared to one another or compared to a transaction value.
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
