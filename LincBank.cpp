/* ------------------------------------------------------
CMP2801M: Advanced Programming
Driver program for "LincBank" Assessment Item 1
Semester A 2021

Written by James Brown (jamesbrown@lincoln.ac.uk)

During marking, we will use the exact same notation
as provided in the brief, so make sure you follow that guideline.

You should avoid removing parts of this driver program, but
add to it the necessary code to produce your implementation.

Good luck!
------------------------------------------------------ */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include "current.h"
#include "savings.h"



// to do todo blank check
// add in consts wherever possible


// Shows all menu options to the user.
void printMenuOptions() {
	std::cout << "  OPTIONS" << std::endl;
	std::cout << "\topen type initial_deposit" << "\t" << "open a current(1), savings(2) or ISA(3) account" << std::endl;
	std::cout << "\tview[index]" << "\t\t\t" << "view balance and recent transactions" << std::endl;
	std::cout << "\twithdraw sum" << "\t\t\t" << "withdraw funds from most recently viewed account" << std::endl;
	std::cout << "\tdeposit sum" << "\t\t\t" << "deposit funds into most recently viewed account" << std::endl;
	std::cout << "\ttransfer src dest sum" << "\t\t" << "transfer funds between accounts" << std::endl;
	std::cout << "\tproject years" << "\t\t\t" << "project balance forward in time" << std::endl;
	std::cout << "\texit" << "\t\t\t\t" << "close this application" << std::endl;
	std::cout << "\toptions" << "\t\t\t\t" << "view these options again" << std::endl;
}


bool isCurrency(std::string str) {
	for (auto a : str) {
		if (!isdigit(a)) {
			if (a != '.') {
				return false;
			}
		}
	}
	return true;
}


bool isInt(std::string str) {
	for (auto a : str) {
		if (!isdigit(a)) {
			return false;
		}
	}
	return true;
}


int main() {
	std::vector <std::string> parameters;
	std::string userCommand;
	// You may also want to store a collection of opened accounts here.  
	std::vector<Account*> accounts;  // Store pointers.
	int numberOfAccounts = 0;
	bool currentAccount = false;
	bool isaAccount = false;
	int activeAccount = 0;

	std::cout << "~~~ Welcome to LincBank! ~~~" << std::endl;
	printMenuOptions();
	std::cout << "Press any key to continue...";
	std::cin.ignore();
 
	int count = 0;
	while (userCommand != "exit") {
		count++;

		parameters.clear();  // Clear ready for next command.  

		std::cout << std::endl << ">>> ";

		std::getline(std::cin, userCommand);
		
		char* p_cstr = new char[userCommand.length() + 1];
		strcpy(p_cstr, userCommand.c_str());

		char* p_token;
		p_token = strtok(p_cstr, " ");

		while (p_token != NULL) {
			parameters.push_back(p_token);
			p_token = strtok(NULL, " ");
		}
		
		// Define all commands as per the brief.  
		std::string command = parameters[0];

		if (!command.empty()) {
			std::string command = " ";
		}
		try {
			if (command.compare("options") == 0) {
				// Display the various commands to the user.  
				printMenuOptions();

			} else if (command.compare("open") == 0) {
				// Allow a user to open an account.  
				// e.g., Account* a = new Savings(...);
				bool flagAccountCreated = false;
				double deposit = 0;
				std::string accountType = "";

				// Check deposit is valid.
				if (!isCurrency(parameters[2])) { throw NotCurrencyException(); }

				deposit = std::stod(parameters[2]);

				try {
					if (parameters[1] == "1") {
						if (currentAccount) { throw MaxCurrentAccountException(); }
						accountType = "Current";
						Account* a = new Current(deposit);
						accounts.push_back(a);
						currentAccount = true;
						flagAccountCreated = true;

					} else if (parameters[1] == "2") {
						accountType = "Savings";
						Account* a = new Savings(deposit);
						accounts.push_back(a);
						flagAccountCreated = true;

					} else if (parameters[1] == "3") {
						if (isaAccount) { throw MaxIsaAccountException(); }
						accountType = "ISA";
						Account* a = new Savings(deposit, true);
						accounts.push_back(a);
						flagAccountCreated = true;

					} else {
						std::cout << "Account type '" << parameters[1] << "' not recognised.";
					}
				} catch (const InitialDepositBelowISARequiredException &e) {
					std::cout << e.what() << std::endl;
				} catch (const InitialDepositBelowZeroException &e) {
					std::cout << e.what() << std::endl;
				}

				if (flagAccountCreated) {
					numberOfAccounts++;
					activeAccount = numberOfAccounts - 1;
					std::cout << accountType << " Account number '" << accounts.size() << "' created." << std::endl;
				}

			} else if (command.compare("view") == 0) {
				// Display an account according to an index (starting from 1).  
				// Alternatively, display all accounts if no index is provided.
				if (numberOfAccounts == 0) { throw NoAccountsCreatedException(); }
				if (parameters.size() == 1) {
					std::cout << viewAllAccounts(accounts) << std::endl;
				} else {
					try {
						std::cout << viewSingleAccount(accounts, parameters[1], numberOfAccounts) << std::endl;
						std::string p = parameters[1];
						activeAccount = std::stoi(p) - 1;
					} catch (const AccountNumberOutOfRangeException &e) {
						std::cout << e.what() << std::endl;
					} catch (const NotIntException &e) {
						std::cout << e.what() << std::endl;
					}
				}

			} else if (command.compare("withdraw") == 0) {
				// Allow user to withdraw funds from an account.
				if (numberOfAccounts == 0) { throw NoAccountsCreatedException(); }
				if (parameters.size() == 1) { throw NotEnoughParametersException(); }
				Account* a = accounts[activeAccount];
				try {
					if (!withdraw(a, parameters[1])) {
						std::cout << "Could not withdraw £" << parameters[1] << " from account " << activeAccount + 1 << "." << std::endl;
					} else {
						std::cout << "Withdrawn £" << parameters[1] << " from account " << activeAccount + 1 << "." << std::endl;
						std::cout << a->ToString() << std::endl;
					}
				} catch (const NotCurrencyException &e) {
					std::cout << e.what() << std::endl;
				}
				
			} else if (command.compare("deposit") == 0) {
				// Allow user to deposit funds into an account.  
				if (numberOfAccounts == 0) { throw NoAccountsCreatedException(); }
				if (parameters.size() == 1) { throw NotEnoughParametersException(); }
				Account* a = accounts[activeAccount];
				try {
					if (!deposit(a, parameters[1])) {
						std::cout << "Could not deposit £" << parameters[1] << " into account " << activeAccount + 1 << "." << std::endl;
					} else {
						std::cout << "Deposited £" << parameters[1] << " into account " << activeAccount + 1 << "." << std::endl;
						std::cout << a->ToString() << std::endl;
					}
				} catch (const NotCurrencyException &e) {
					std::cout << e.what() << std::endl;
				}
				
			} else if (command.compare("transfer") == 0) {
				if (numberOfAccounts == 0) { throw NoAccountsCreatedException(); }
				if (parameters.size() < 4) { throw NotEnoughParametersException(); }
				// Allow user to transfer funds between accounts.  
				// i.e., a withdrawal followed by a deposit!
				int indexA = 0;
				int indexB = 0;
				//todo to do blank check add in checks here for numbers
				Account* a = accounts[stod(parameters[1]) - 1];
				Account* b = accounts[stod(parameters[2]) - 1];
				double value = stod(parameters[3]);

				bool flag = a->Withdraw(value);
				if (!flag) {
					std::cout << "Could not withdraw £" << value << " from account " << indexA << "." << std::endl;
				} else {
					b->Deposit(value);
					std::cout << "Transfered £" << value << " from account " << indexA
						<< " to account " << indexB << ".\n" << std::endl;
					std::cout << a->ToString() << std::endl;
					std::cout << b->ToString() << std::endl;
				}

			} else if (command.compare("project") == 0) {
				// Compute compound interest t years into the future.
				if (numberOfAccounts == 0) { throw NoAccountsCreatedException(); }
				if (parameters.size() == 1) { throw NotEnoughParametersException(); }
				try {
					double interest = project(accounts[activeAccount], parameters[1]);
					std::cout << "Projected balance: £" << interest << std::endl;
				} catch (const NotIntException &e) {
					std::cout << e.what() << std::endl;
				} catch (const DynamicCastUnsuccessfulException &e) {
					std::cout << e.what() << std::endl;
				}


			} //else if (command.compare("search"))
			//{
			//	Allow users to search their account history for a transaction.  
			//  (this is a stretch task)
			//}
		} catch (const NoAccountsCreatedException &e) {
			std::cout << e.what() << std::endl;
		} catch (const NotEnoughParametersException &e) {
			std::cout << e.what() << std::endl;
		} catch (const NotCurrencyException &e) {
			std::cout << e.what() << std::endl;
		} catch (const MaxCurrentAccountException &e) {
			std::cout << e.what() << std::endl;
		} catch (const MaxIsaAccountException &e) {
			std::cout << e.what() << std::endl;
		}
	}
	// Don't have to delete accounts as program will terminate anyway. -- this is my comment, make sure this is true to do todo blank check
	std::cout << "Press any key to quit...";
	std::getchar();
}


static std::string viewAllAccounts (std::vector<Account*> accounts) {
	std::string str = "";
	for (auto a : accounts) {
		str += a->ToString();
	}
	return str;
}


static std::string viewSingleAccount (std::vector<Account*> &accounts, std::string &accountNumber, int &numberOfAccounts) {
	if (!isInt(accountNumber)) { throw NotIntException(); }
	int index = stoi(accountNumber);
	if (index > numberOfAccounts) { throw AccountNumberOutOfRangeException(); }
	Account* a = accounts[index - 1];
	return a->ToString();		
}


static bool withdraw (Account* a, std::string Value) {
	if (!isCurrency(Value)) { throw NotCurrencyException();	}
	double value = std::stod(Value);
	if (a->Withdraw(value)) { return true; }
	return false;
}


static bool deposit (Account* a, std::string Value) {
	if (!isCurrency(Value)) { throw NotCurrencyException();	}
	double value = std::stod(Value);
	if (a->Deposit(value)) { return true; }
	return false;
}


static double project (Account* a, std::string Years) {
	if (!isInt(Years)) { throw NotIntException(); }
	// If dynamic cast was unsuccessful, the account isn't a savings account.
	Savings* s = dynamic_cast<Savings*>(a);
	if (s == nullptr) { throw DynamicCastUnsuccessfulException(); }
	return s->ComputeInterest(std::stoi(Years));
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
