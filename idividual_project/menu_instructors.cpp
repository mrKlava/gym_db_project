#pragma once

#include <cstdio>
#include <cstring>
#include <iostream>
#include <limits>
#include <string>

#include "types.h"
#include "data.h"

#include "menu.h"
#include "menu_istructors.h"

using namespace std;

const string MENU_OPTIONS[] = {
	"Instructors Menu",
	"View",
	"Add New",
	"Delete",
	"Back to Main Menu"
};

const string MENU_VIEW_OPTIONS[] = {
	"View Instructors Menu",
	"View All",
	"Apply sort by ID",
	"Apply sort by Name",
	"Apply filter by Gender"
	"Search",
	"Back"
};

/* MAIN MENU */

void menu_istructors() {
	while (true) {
		print_menu_options(MENU_OPTIONS);

		int choice = get_input_positive_int("Please enter your choice: ");

		switch (choice) {
		case 1:
			menu_view_instructors();
			break;
		case 2:
		{
			menu_add_insrtuctors();
			break;
		}
		case 3:
			menu_delete_istructors();
			break;
		case 4:
			return;
		default:
			cout << "Invalid choice. Please try again." << endl;
		}
	}

	cout << endl;
}

/* VIEW UTILS */

void menu_view_instructors() {
	while (true) {
		print_menu_options(MENU_VIEW_OPTIONS);

		int choice = get_input_positive_int("Please enter your choice: ");

		switch (choice) {
		case 1:
			print_table_instructors();
			break;
		case 2:
		{

			print_table_instructors();

			break;
		}
		case 3:
		{
			print_table_instructors();

			break;
		}
		case 4:
		{
			print_table_instructors();

			break;
		}
		case 5:
		{
			print_table_instructors();

			break;
		}
		case 6:
			return;
		default:
			cout << "Invalid choice. Please try again." << endl;
		}
	}

	cout << endl;
}

/* ADD UTILS */

void menu_add_insrtuctors() {
	Instructor ins = get_instructor();
	bool is_added = add_instructor(ins);

	cout << is_added << endl;
}

/* DELETE UTILS */

void menu_delete_istructors() {
	int target_id = get_input_positive_int("Enter Instructor ID to delete: ");

	bool is_deleted = delete_instructor_by_id(target_id);
	if (!is_deleted) {
		cout << "Instructor with ID " << target_id << " not found.\n";
	}
}

/* HELPERS */


void print_table_instructors() {
	char line_sep[] = "----------------------------------------------------------------------------------------";
	char line_sep_b[] = "========================================================================================";

	cout << endl;
	cout << line_sep_b << endl;
	printf("Instructors (count = %d)\n", instructor_count);
	cout << line_sep << endl;
	printf("%-5s | %-32s | %-32s | %-6s\n", "ID", "Name", "Surname", "Gender");
	cout << line_sep << endl;

	for (int i = 0; i < instructor_count; i++)
	{
		Instructor& ins = instructors[i];

		const char* gender = (ins.gender == 1 ? "M" : (ins.gender == 2 ? "F" : "O"));

		static char buf[80];
		buf[0] = '\0';
		printf("%-5d | %-32s | %-32s | %-6s\n", ins.id, ins.name, ins.surname, gender);
	}
	cout << line_sep_b << endl;
}

Instructor get_instructor() {
	Instructor ins{};

	ins.id = next_instructor_id();
	get_input_string("Enter name:", ins.name, sizeof(ins.name));
	get_input_string("Enter surname:", ins.surname, sizeof(ins.surname));
	ins.gender = get_input_gender();

	return ins;
}



