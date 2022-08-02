#include "mainmethods.h"
#include <iostream>
#include <vector>

// Shows all menu options to the user.
void MainMethods::PrintMenuOptions() {
    std::cout << "  OPTIONS" << std::endl;
    std::cout << "\topen type initial_deposit" << "\t" << "open a current(1), savings(2) or ISA(3) account" << std::endl;
    std::cout << "\tview[index]" << "\t\t\t" << "view balance and recent transactions" << std::endl;
    std::cout << "\twithdraw sum" << "\t\t\t" << "withdraw funds from most recently viewed account" << std::endl;
    std::cout << "\tdeposit sum" << "\t\t\t" << "deposit funds into most recently viewed account" << std::endl;
    std::cout << "\ttransfer src dest sum" << "\t\t" << "transfer funds between accounts" << std::endl;
    std::cout << "\tproject years" << "\t\t\t" << "project balance forward in time" << std::endl;
    std::cout << "\tsearch sum" << "\t\t\t" << "search for a specific transaction value" << std::endl;
    std::cout << "\texit" << "\t\t\t\t" << "close this application" << std::endl;
    std::cout << "\toptions" << "\t\t\t\t" << "view these options again" << std::endl;
}


bool MainMethods::IsCurrency(std::string &Str) {
    // Allows one decimal point within a group of numbers.
    // Any non-number or over one decimal point returns false.
    bool decimalPoint = false;
    for (auto c : Str) {
        if (!std::isdigit(c)) {
            if (c == '.') {
                if (decimalPoint) { return false; }
                decimalPoint = true;
            } else {
                return false;
            }
        }
    }
    return true;
}


// Ensures all characters are numbers.
bool MainMethods::IsInt(std::string &Str) {
    for (auto c : Str) {
        if (!std::isdigit(c)) { return false; }
    }
    return true;
}


std::string MainMethods::ViewAllAccounts (std::vector<Account*> &Accounts) {
    std::string str = "";
    for (auto a : Accounts) { str += a->toString(); }
    return str;
}


std::string MainMethods::ViewSingleAccount (std::vector<Account*> &Accounts, std::string &AccountNumber, int &NumberOfAccounts) {
    if (!MainMethods::IsInt(AccountNumber)) { throw WrongTypeException("ERROR: Value was not an integer."); }
    int index = std::stoi(AccountNumber);
    if (index > NumberOfAccounts) { throw AccountNumberOutOfRangeException(); }
    if (index == 0) { throw AccountNumberOutOfRangeException(); }
    Account* a = Accounts[index - 1];
    return a->toString();		
}


bool MainMethods::Withdraw(Account* &A, std::string &Value) {
    if (!MainMethods::IsCurrency(Value)) { throw WrongTypeException("ERROR: Value was not a currency format.");	}
    double value = std::stod(Value);
    if (A->withdraw(value)) { return true; }
    return false;
}


bool MainMethods::Deposit(Account* &A, std::string &Value) {
    if (!MainMethods::IsCurrency(Value)) { throw WrongTypeException("ERROR: Value was not a currency format.");	}
    double value = std::stod(Value);
    if (A->deposit(value)) { return true; }
    return false;
}


std::string MainMethods::Transfer(std::vector<Account*> &Accounts, std::string &Source, std::string &Destination, std::string &Value, int &NumberOfAccounts) {
    // Guard against any possible errors, throw exception for each.
    if (!MainMethods::IsInt(Source)) { throw WrongTypeException("ERROR: Value was not an integer."); }
    if (!MainMethods::IsInt(Destination)) { throw WrongTypeException("ERROR: Value was not an integer."); }
    int source = std::stoi(Source);
    int destination = std::stoi(Destination);
    // Check account number is in range.
    if (source == 0) { throw AccountNumberOutOfRangeException(); }
    if (source > NumberOfAccounts) { throw AccountNumberOutOfRangeException(); }
    if (destination == 0) { throw AccountNumberOutOfRangeException(); }
    if (destination > NumberOfAccounts) { throw AccountNumberOutOfRangeException(); }
    // Cannot transfer to and from the same account.
    if (source == destination) { throw AccountNumberOutOfRangeException(); }
    if (!MainMethods::IsCurrency(Value)) { throw WrongTypeException("ERROR: Value was not a currency format.");	}
    Account* a = Accounts[source - 1];
    Account* b = Accounts[destination - 1];
    double value = std::stod(Value);
    if (!a->withdraw(value, destination)) { throw WithdrawFailException(); }
    b->deposit(value, source);
    return a->toString() + b->toString();
}


double MainMethods::Project(Account* &A, std::string &Years) {
    if (!MainMethods::IsInt(Years)) { throw WrongTypeException("ERROR: Value was not an integer."); }
    // If dynamic cast is unsuccessful, the account isn't a savings account.
    Savings* s = dynamic_cast<Savings*>(A);
    if (s == nullptr) { throw DynamicCastUnsuccessfulException("ERROR: Selected account is not a savings account."); }
    return s->computeInterest(std::stoi(Years));
}


std::string MainMethods::Search(Account* &A, std::string &Amount) {
    if (!MainMethods::IsCurrency(Amount)) { throw WrongTypeException("ERROR: Value was not a currency format."); }
    double amount = std::stod(Amount);
    // Recursively search binary search tree for given amount.
    TreeNode* node = BST::Search(A->m_p_HistoryTree, amount);
    if (node == nullptr) { return "No transaction found."; }
    // Prepare return string. Possibility for multiple transactions to be stored at the same node.
    std::string str = node->m_p_Transaction->toString();
    for (auto transaction : node->m_TransactionOverflow) {
        str += transaction->toString();
    }
    return str;
}
