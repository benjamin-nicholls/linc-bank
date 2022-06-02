#include "historyinfo.h"


HistoryInfo::HistoryInfo() {
	m_Type = "";
	m_Value = 0;
}


HistoryInfo::HistoryInfo(std::string Type, double Value) {
	m_Type = Type;
	m_Value = Value;

}


HistoryInfo::~HistoryInfo() {
}


std::string HistoryInfo::GetType() {
	return m_Type;
}


double HistoryInfo::GetValue() {
	return m_Value;
}
