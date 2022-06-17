#pragma once
#include <string>


class Truncate {
public:
	static std::string Truncate2dp(double Value) {
		std::string value = std::to_string(Value);
		return value.substr(0, value.find('.')  + 3);
	}
};
