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

#include "mainmethods.h"

// I try to be as explicit as possible for where a method originates from (e.g. MainMethods or std).
int main() {
	std::vector <std::string> parameters;
	std::string userCommand;
	// You may also want to store a collection of opened accounts here.  
	std::vector<Account*> accounts;  // Store pointers.
	// Used for numbering accounts.
	int numberOfAccounts = 0;
	// Used to check if an account type is open.
	bool currentAccount = false;
	bool isaAccount = false;
	// Used for options where an account is not specified (e.g. withdraw/deposit).
	int activeAccount = 0;

	std::cout << "~~~ Welcome to LincBank! ~~~" << std::endl;
	MainMethods::PrintMenuOptions();
	std::cout << "Press any key to continue...";
	std::cin.ignore();
 
	while (userCommand != "exit") {
		// Clear ready for next command.  
		parameters.clear();  
		userCommand.clear();

		std::cout << std::endl << ">>> ";
		std::getline(std::cin, userCommand);
		
		char* p_cstr = new char[userCommand.length() + 1];
		strcpy(p_cstr, userCommand.c_str());
		
		char* p_token;
		p_token = strtok(p_cstr, " ");
		// If user inputs nothing, skip.
		if (p_token == nullptr) { continue; }
		while (p_token != NULL) {
			parameters.push_back(p_token);
			p_token = strtok(NULL, " ");
		}
		delete[] p_cstr;
		delete p_token;

		// Define all commands as per the brief.  
		std::string command = parameters[0];

		
		if (!command.empty()) {
			std::string command = " ";
		}

		// Catch all errors in try within main loop.
		// All exceptions go to the end of the loop, meaning no issues.
		// All exceptions are handled in the same area for ease of maintenance.
		try {
			if (command.compare("options") == 0) {
				// Display the various commands to the user.  
				MainMethods::PrintMenuOptions();

			} else if (command.compare("open") == 0) {
				// Allow a user to open an account.  
				// e.g., Account* a = new Savings(...);
				bool flagAccountCreated = false;
				double deposit = 0;
				std::string accountType = "";

				// Check deposit is valid.
				if (parameters.size() < 3) { throw NotEnoughParametersException(); }
				if (!MainMethods::IsCurrency(parameters[2])) { throw WrongTypeException("ERROR: Value was not a currency format."); }
				deposit = std::stod(parameters[2]);

				if (parameters[1] == "1") {
					// Only allowed one current account.
					if (currentAccount) { throw MaxAccountException("ERROR: Maximum number of current account(s) opened."); }
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
					// Only allowed one ISA account.
					if (isaAccount) { throw MaxAccountException("ERROR: Maximum number of ISA account(s) opened."); }
					accountType = "ISA";
					// Optional bool argument denotes this as an ISA account.
					Account* a = new Savings(deposit, true);
					accounts.push_back(a);
					// Bool could be made into an int if more than one ISA account was allowed to be opened.
					isaAccount = true;
					flagAccountCreated = true;
				} else {
					std::cout << "Account type '" << parameters[1] << "' not recognised.";
				}

				if (flagAccountCreated) {
					numberOfAccounts++;
					// Update active account. Used for withdrawing and depositing.
					activeAccount = numberOfAccounts - 1;
					std::cout << accountType << " Account number '" << accounts.size() << "' created." << std::endl;
				}

			} else if (command.compare("view") == 0) {
				// Display an account according to an index (starting from 1).  
				// Alternatively, display all accounts if no index is provided.
				if (numberOfAccounts == 0) { throw NumberOfAccountsException("ERROR: You have not opened any accounts yet."); }
				if (parameters.size() == 1) {
					std::cout << MainMethods::ViewAllAccounts(accounts) << std::endl;
				} else {
					std::cout << MainMethods::ViewSingleAccount(accounts, parameters[1], numberOfAccounts) << std::endl;
					std::string p = parameters[1];
					activeAccount = std::stoi(p) - 1;
				}

			} else if (command.compare("withdraw") == 0) {
				// Allow user to withdraw funds from an account.
				if (numberOfAccounts == 0) { throw NumberOfAccountsException("ERROR: You have not opened any accounts yet."); }
				if (parameters.size() == 1) { throw NotEnoughParametersException(); }
				// If there is at least one account, we know activeAccount will be a correct index.
				Account* a = accounts[activeAccount];

				if (!MainMethods::Withdraw(a, parameters[1])) {
					std::cout << "Could not withdraw £" << parameters[1] << " from account " << activeAccount + 1 << "." << std::endl;
				} else {
					std::cout << "Withdrawn £" << parameters[1] << " from account " << activeAccount + 1 << "." << std::endl;
					std::cout << a->toString() << std::endl;
				}

			} else if (command.compare("deposit") == 0) {
				// Allow user to deposit funds into an account.  
				if (numberOfAccounts == 0) { throw NumberOfAccountsException("ERROR: You have not opened any accounts yet."); }
				if (parameters.size() == 1) { throw NotEnoughParametersException(); }
				// If there is at least one account, we know activeAccount will be a correct index.
				Account* a = accounts[activeAccount];

				if (!MainMethods::Deposit(a, parameters[1])) {
					std::cout << "Could not deposit £" << parameters[1] << " into account " << activeAccount + 1 << "." << std::endl;
				} else {
					std::cout << "Deposited £" << parameters[1] << " into account " << activeAccount + 1 << "." << std::endl;
					std::cout << a->toString() << std::endl;
				}
	
			} else if (command.compare("transfer") == 0) {
				if (numberOfAccounts < 2) { throw NumberOfAccountsException("ERROR: You have not opened enough accounts yet."); }
				if (parameters.size() < 4) { throw NotEnoughParametersException(); }
				// Allow user to transfer funds between accounts.  
				// i.e., a withdrawal followed by a deposit!
				std::cout << MainMethods::Transfer(accounts, parameters[1], parameters[2], parameters[3], numberOfAccounts) << std::endl;

			} else if (command.compare("project") == 0) {
				// Compute compound interest t years into the future.
				if (numberOfAccounts == 0) { throw NumberOfAccountsException("ERROR: You have not opened any accounts yet."); }
				if (parameters.size() == 1) { throw NotEnoughParametersException(); }
				double interest = MainMethods::Project(accounts[activeAccount], parameters[1]);
				std::cout << "Projected balance: £" << interest << std::endl;
			
			} else if (command.compare("search") == 0) {
			//	Allow users to search their account history for a transaction.  
			//  (this is a stretch task)
				if (numberOfAccounts == 0) { throw NumberOfAccountsException("ERROR: You have not opened any accounts yet."); }
				if (parameters.size() == 1) { throw NotEnoughParametersException(); }
				std::cout << MainMethods::Search(accounts[activeAccount], parameters[1]) << std::endl;
			}

		// Accounts exceptions.
		} catch (const NumberOfAccountsException &e) {
			std::cout << e.what() << std::endl;
		} catch (const AccountNumberOutOfRangeException &e) {
			std::cout << e.what() << std::endl;
		} catch (const MaxAccountException &e) {
			std::cout << e.what() << std::endl;
		// Number exceptions.
		} catch (const WrongTypeException &e) {
			std::cout << e.what() << std::endl;
		// Parameter exceptions.
		} catch (const NotEnoughParametersException &e) {
			std::cout << e.what() << std::endl;
		// Deposit exceptions.
		} catch (const InitialDepositBelowRequiredException &e) {
			std::cout << e.what() << std::endl;
		// Transaction exceptions.
		} catch (const WithdrawFailException &e) {
			std::cout << e.what() << std::endl;
		// Other exceptions.
		} catch (const DynamicCastUnsuccessfulException &e) {
			std::cout << e.what() << std::endl;
		}
						
	}

	// Clean up. 
	for (auto a : accounts) { delete a; }
	std::cout << "Press any key to quit...";
	std::getchar();
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
