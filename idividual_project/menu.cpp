#include <cstdio>
#include <iostream>

#include "menu.h"

using namespace std;

void menu() {
	while (true) {
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
			cout << "Viewing All" << endl;
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