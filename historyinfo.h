#pragma once
#include <string>


class HistoryInfo {
private:
	std::string m_Type;
	double m_Value;

public:
	HistoryInfo();
	HistoryInfo(std::string Type, double Value);
	~HistoryInfo();
	std::string GetType();
	double GetValue();

};
