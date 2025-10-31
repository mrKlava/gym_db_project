#include <cstdio>
#include <cstring>  // for strcpy, strlen
#include <iostream>
#include <limits>   // for numeric_limits

#include "menu.h"
#include "data.h"
#include "types.h"
#include <string>

using namespace std;

void menu() {
	while (true) {
		cout << endl;
		cout << "=============================" << endl;
		cout << "Menu Options:" << endl;
		cout << "-----------------------------" << endl;
		cout << "1. Instructors" << endl;
		cout << "2. Clients" << endl;
		cout << "3. Training Sessions" << endl;
		cout << "4. Exit" << endl;
		cout << "=============================" << endl;
		cout << "Please enter your choice: ";

		int choice;
		cin >> choice;

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

void menu_istructors() {
	while (true) {
		cout << endl;
		cout << "=============================" << endl;
		cout << "Instructors Menu:" << endl;
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
			print_table_instructors();
			break;
		case 2:
		{
			Instructor ins = get_instructor();
			bool is_added = add_instructor(ins);

			cout << is_added << endl;

			break;
		}
		case 3:
			delete_instructor();
			break;
		case 4:
			return;
		default:
			cout << "Invalid choice. Please try again." << endl;
		}
	}

	cout << endl;
}

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

/* PRINT UTILS */

void print_table_instructors() {
	;
	printf("\n========================================================================================\n");
	printf("Instructors (count = %d)\n", instructor_count);
	printf("----------------------------------------------------------------------------------------\n");
	printf("%-5s | %-32s | %-32s | %-6s\n", "ID", "Name", "Surname", "Gender");
	printf("----------------------------------------------------------------------------------------\n");
	for (int i = 0; i < instructor_count; i++)
	{
		Instructor& ins = instructors[i];

		const char* gender = (ins.gender == 1 ? "M" : (ins.gender == 2 ? "F" : "O"));

		static char buf[80];
		buf[0] = '\0';
		printf("%-5d | %-32s | %-32s | %-6s\n", ins.id, ins.name, ins.surname, gender);
	}
	printf("========================================================================================\n\n");
}

/* GET UTILS */

Instructor& get_instructor() {
	Instructor ins{};

	ins.id = next_instructor_id();
	get_input_string("Enter name:", ins.name, sizeof(ins.name));
	get_input_string("Enter surname:", ins.surname, sizeof(ins.surname));
	ins.gender = get_input_gender();

	return ins;
}

/* DELETE UTILS */

void delete_instructor() {
	int target_id = get_input_positive_int("Enter Instructor ID to delete: ");

	bool is_deleted = delete_instructor_by_id(target_id);
	if (!is_deleted) {
		cout << "Instructor with ID " << target_id << " not found.\n";
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