#include <cstdio>
#include <cstring>  // for strcpy, strlen
#include <iostream>
#include <limits>   // for numeric_limits
#include <string>

#include "data.h"
#include "types.h"

#include "menu.h"
#include "menu_istructors.h"

using namespace std;

const string MENU_OPTIONS[] = {
	"Menu Options",
	"Instructors",
	"Clients",
	"Training Sessions",
	"Exit"
};

void menu() {
	while (true) {
		print_menu_options(MENU_OPTIONS);

		int choice = get_input_positive_int("Please enter your choice: ");

		switch (choice) {
		case 1:
			menu_istructors();
			break;
		case 2:
			menu_clients();
			break;
		case 3:
			menu_trainig_sessions();
			break;
		case 4:
			cout << "Exiting the program." << endl;
			return;
		default:
			cout << "Invalid choice. Please try again." << endl;
		}
	}
}

/* MENU UTILS */

void menu_clients() {
	while (true) {
		cout << endl;
		cout << "=============================" << endl;
		cout << "Client Menu:" << endl;
		cout << "-----------------------------" << endl;
		cout << "1. View All" << endl;
		cout << "2. Add New" << endl;
		cout << "3. Delete" << endl;
		cout << "4. Back to Main Menu" << endl;
		cout << "=============================" << endl;
		cout << "Please enter your choice: ";

		int choice;
		cin >> choice;

		switch (choice) {
		case 1:
			cout << "Viewing Instructors" << endl;
			break;
		case 2:
			cout << "Adding Instructor" << endl;
			break;

		case 3:
			cout << "Deleting Instructor" << endl;
			break;
		case 4:
			return;
		default:
			cout << "Invalid choice. Please try again." << endl;
		}
	}
}

void menu_trainig_sessions() {
	while (true) {
		cout << endl;
		cout << "=============================" << endl;
		cout << "Client Menu:" << endl;
		cout << "-----------------------------" << endl;
		cout << "1. View All" << endl;
		cout << "2. Add New" << endl;
		cout << "3. Delete" << endl;
		cout << "4. Back to Main Menu" << endl;
		cout << "=============================" << endl;
		cout << "Please enter your choice: ";

		int choice;
		cin >> choice;

		switch (choice) {
		case 1:
			cout << "Viewing Training Sessions" << endl;
			break;
		case 2:
			cout << "Adding Training Session" << endl;
			break;

		case 3:
			cout << "Deleting Training Session" << endl;
			break;
		case 4:
			return;
		default:
			cout << "Invalid choice. Please try again." << endl;
		}
	}
}


/* INPUT UTILS */

void get_input_string(const char* prompt, char* destination, int length) {
	string input;

	while (true) {
		cout << prompt << " ";

		// flush any leftover characters in the buffer
		if (cin.peek() == '\n') cin.ignore();  // ignore single leftover newline

		getline(cin, input);

		if ((int)input.length() >= length) {
			cout << "Input too long. Maximum allowed length is "
				<< (length - 1) << " characters.\n";
		}
		else if (input.empty()) {
			cout << "Input cannot be empty. Please try again.\n";
		}
		else {
			break;
		}
	}

	strncpy_s(destination, length, input.c_str(), _TRUNCATE);
}

Gender get_input_gender() {
	int choice;

	while (true) {
		cout << "Enter gender: 1. Male, 2. Female: ";
		cin >> choice;

		// check for invalid input (non-number)
		if (cin.fail()) {
			cin.clear();             // clear error flag
			cin.ignore(1000, '\n');  // discard invalid input
			cout << "Invalid input. Please enter a number: 1. Male, 2. Female" << endl;
			continue;
		}

		if (choice == 1 || choice == 2) {
			if (choice == 1) {
				return M;
			}
			else {
				return F;
			}
		}
		else {
			cout << "Invalid choice. Please enter number: 1. Male, 2. Female\n";
		}
	}
}

int get_input_positive_int(const char* prompt) {
	int value;
	while (true) {
		cout << prompt;
		cin >> value;

		if (cin.fail() || value <= 0) {
			cin.clear();              // clear error flag
			cin.ignore(10000, '\n');  // discard invalid input
			cout << "Please enter a positive integer.\n";
		}
		else {
			cin.ignore(10000, '\n');  // discard remaining input
			return value;
		}
	}
}