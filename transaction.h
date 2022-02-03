#pragma once
#include <string>


class transaction {

protected:
	std::string desc;
	std::string timestamp;
	double value;
	std::string toString();

};
