#pragma once
#include <string>


class Transaction {

protected:
	std::string m_Desc;
	std::string m_Timestamp;
	double m_Value;
	std::string ToString();

};
