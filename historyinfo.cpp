#include "historyinfo.h"


historyinfo::historyinfo() {
	type = "";
	value = NULL;
}


historyinfo::historyinfo(std::string Type, double Value) {
	type = Type;
	value = Value;

}


historyinfo::~historyinfo() {
}


std::string historyinfo::getType() {
	return type;
}


double historyinfo::getValue() {
	return value;
}
