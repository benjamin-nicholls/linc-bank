#pragma once
#include <string>


class historyinfo {

private:
	std::string type;
	double value;

public:
	historyinfo();
	historyinfo(std::string type, double value);
	std::string getType();
	double getValue();

};
