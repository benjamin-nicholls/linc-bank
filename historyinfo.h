#pragma once
#include <string>
#include <chrono>

class HistoryInfo {
private:
	std::string m_Currency;
	std::string m_Type;
	double m_Value;
	std::time_t m_Time;
	std::string Truncate2dp(double Value);

public:
	HistoryInfo(std::string Type, double Value);
	~HistoryInfo();
	std::string ToString();


};
