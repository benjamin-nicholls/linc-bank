#pragma once
#include <string>
#include <vector>
#include "current.h"
#include "savings.h"

class MainMethods {
public:
    static void PrintMenuOptions();
    static bool IsCurrency(std::string &Str);
    static bool IsInt(std::string &Str);
    static std::string Truncate2dp(double &sValue);
    static std::string ViewAllAccounts(std::vector<Account*> &Accounts);
    static std::string ViewSingleAccount(std::vector<Account*> &Accounts, std::string &AccountNumber, int &NumberOfAccounts);
    static bool Withdraw(Account* &A, std::string &Value);
    static bool Deposit(Account* &A, std::string &Value);
    static std::string Transfer(std::vector<Account*> &Accounts, std::string &Source, std::string &Destination, std::string &Value, int &NumberOfAccounts);
    static double Project(Account* &A, std::string &Years);
};