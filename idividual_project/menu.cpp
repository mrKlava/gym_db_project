#include <cstdio>
#include <cstring>
#include <iostream>

#include "menu.h"
#include "data.h"
#include "types.h"

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

void print_table_instructors() {;
	printf("\n========================================================================================\n");
	printf("Instructors (count = %d)\n", instructor_count);
	printf("----------------------------------------------------------------------------------------\n");
	printf("%-5s | %-32s | %-32s | %-6s\n", "ID", "Name", "Surname", "Gender");
	printf("----------------------------------------------------------------------------------------\n");
	for (int i = 0; i < instructor_count; i++)
	{
		Instructor& ins = instructors[i];

		const char* gender = (ins.gender == 1 ? "M" : (ins.gender == 2? "F" : "O"));
		
		static char buf[80];
		buf[0] = '\0';
		printf("%-5d | %-32s | %-32s | %-6s\n", ins.id, ins.name, ins.surname, gender);
	}
	printf("========================================================================================\n\n");
}