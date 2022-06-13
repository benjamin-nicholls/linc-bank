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


// Both for setprecision.
#include <iomanip>
#include <limits>

// to do
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

int main() {
	std::vector <std::string> parameters;
	std::string userCommand;
	// You may also want to store a collection of opened accounts here.  
	std::vector<Account*> accounts;  // Store pointers.
	int numberOfAccounts = 0;

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

		if (command.compare("options") == 0) {
			// Display the various commands to the user.  
			printMenuOptions();
		} else if (command.compare("open") == 0) {
			

			// Allow a user to open an account.  
			// e.g., Account* a = new Savings(...);
			bool flag = false;
			double deposit = stod(parameters[2]);
			std::string accountType = "";

			if (parameters[1] == "1") {
				// do check here
				accountType = "Current";
				Account* a = new Current(deposit);
				accounts.push_back(a);
				flag = true;
			} else if (parameters[1] == "2") {
				accountType = "Savings";
				Account* a = new Savings(deposit, false);
				accounts.push_back(a);
				flag = true;
			} else if (parameters[1] == "3") {
				accountType = "ISA";
				Account* a = new Savings(deposit, true);
				accounts.push_back(a);
				flag = true;
			} else {

				std::cout << "Account type '" << parameters[1] << "' not recognised.";
			}
			if (flag) {
				numberOfAccounts++;
				std::cout << accountType << " Account number '" << accounts.size() << "' created." << std::endl;
			}
		} else if (command.compare("view") == 0) {
			// Display an account according to an index (starting from 1).  
			// Alternatively, display all accounts if no index is provided.
			if (parameters.size() == 1) {
				for (auto a : accounts) {
					std::cout << a->ToString() << std::endl;
				}
			} else {
				try {
					int index = stod(parameters[1]);
					Account* a = accounts[index-1];
					std::cout << a->ToString() << std::endl;
				} catch (const std::out_of_range& e) {
					std::cout << "ERROR: Is your index valid?" << std::endl;
				}
			}
			

		} else if (command.compare("withdraw") == 0) {
			// Allow user to withdraw funds from an account.  
		} else if (command.compare("deposit") == 0) {
			// Allow user to deposit funds into an account.  
		} else if (command.compare("transfer") == 0) {
			// Allow user to transfer funds between accounts.  
			// i.e., a withdrawal followed by a deposit!
		} else if (command.compare("project") == 0) {
			// Compute compound interest t years into the future.  
		}
		//else if (command.compare("search"))
		//{
		//	Allow users to search their account history for a transaction.  
		//  (this is a stretch task)
		//}
	}
	// Don't have to delete accounts as program will terminate anyway.
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
