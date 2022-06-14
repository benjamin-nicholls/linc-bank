#pragma once
#include <string>
#include <vector>
#include "current.h"
#include "savings.h"

class MainMethods {
public:
    static void printMenuOptions();
    static bool isCurrency(std::string Str);
    static bool isInt(std::string Str);
    static std::string Truncate2dp(double Value);
    static std::string viewAllAccounts(std::vector<Account*> &Accounts);
    static std::string viewSingleAccount(std::vector<Account*> &Accounts, std::string &AccountNumber, int &NumberOfAccounts);
    static bool withdraw(Account* A, std::string Value);
    static bool deposit(Account* A, std::string Value);
    static std::string transfer(std::vector<Account*> &Accounts, std::string Source, std::string Destination, std::string Value, int &NumberOfAccounts);
    static double project(Account* A, std::string Years);
};