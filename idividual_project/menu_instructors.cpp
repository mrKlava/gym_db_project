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
	"View",
	"Add New",
	"Delete",
	"Back to Main Menu"
};

const string MENU_VIEW_OPTIONS[] = {
	"View All",
	"Sort by ID",
	"Sort by Name",
	"Filter by Gender",
	"Search",
	"Back"
};

const string MENU_SORT_OPTIONS[] = {
	"Ascending",
	"Descending",
	"Back"
};

const string MENU_FILTER_OPTIONS[] = {
	"Male",
	"Female",
	"Back"
};

const string MENU_SEARCH_OPTIONS[] = {
	"ID",
	"Name",
	"Back"
};

/* MAIN MENU */

void menu_istructors() {
	while (true) {
		print_menu_options("Instructors Menu", MENU_OPTIONS);

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

/* MENU UTILS */

void menu_view_instructors() {
	while (true) {
		print_menu_options("View Instructors Menu", MENU_VIEW_OPTIONS);

		int choice = get_input_positive_int("Please enter your choice: ");

		switch (choice) {
		case 1:
			sort_instructors_by_id(true);
			print_table_instructors();

			break;
		case 2:
		{
			menu_sort_id_instructors();

			break;
		}
		case 3:
		{
			menu_sort_name_instructors();

			break;
		}
		case 4:
		{
			menu_filter_gender_instructors();

			break;
		}
		case 5:
		{
			menu_search_instructors();

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

void menu_sort_id_instructors() {
	while (true) {
		print_menu_options("Sort by ID Instructors Menu", MENU_SORT_OPTIONS);

		int choice = get_input_positive_int("Please enter your choice: ");

		switch (choice) {
		case 1:
			sort_instructors_by_id(true);

			break;
		case 2:
		{
			sort_instructors_by_id(false);

			break;
		}
		case 3:
			return;
		default:
			cout << "Invalid choice. Please try again." << endl;
		}

		print_table_instructors();
	}

	cout << endl;
}

void menu_sort_name_instructors() {
	while (true) {
		print_menu_options("Sort by Name Instructors Menu", MENU_SORT_OPTIONS);

		int choice = get_input_positive_int("Please enter your choice: ");

		switch (choice) {
		case 1:
			sort_instructors_by_name(true);

			break;
		case 2:
		{
			sort_instructors_by_name(false);

			break;
		}
		case 3:
			return;
		default:
			cout << "Invalid choice. Please try again." << endl;
		}

		print_table_instructors();
	}

	cout << endl;
}

void menu_filter_gender_instructors() {
	while (true) {
		print_menu_options("Filter by Gender Instructors Menu", MENU_FILTER_OPTIONS);

		int choice = get_input_positive_int("Please enter your choice: ");

		switch (choice) {
		case 1:
			print_table_instructors_by_gender(M);

			break;
		case 2:
		{
			print_table_instructors_by_gender(F);

			break;
		}
		case 3:
			return;
		default:
			cout << "Invalid choice. Please try again." << endl;
		}
	}

	cout << endl;
}

void menu_search_instructors() {
	while (true) {
		print_menu_options("Search Instructors Menu", MENU_SEARCH_OPTIONS);

		int choice = get_input_positive_int("Please enter your choice: ");

		switch (choice) {
		case 1:
		{
			int id = get_input_positive_int("Please enter ID: ");
			print_search_instructors_by_id(id);

			break;
		}
		case 2:
		{

			print_search_instructors_by_name();

			break;
		}
		case 3:
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

/* PRINTING UTILS */

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

		const char* gender = (ins.gender == 1 ? "Male" : (ins.gender == 2 ? "Female" : "Other"));

		static char buf[80];
		buf[0] = '\0';
		printf("%-5d | %-32s | %-32s | %-6s\n", ins.id, ins.name, ins.surname, gender);
	}
	cout << line_sep_b << endl;
}

void print_table_instructors_by_gender(Gender gender_filter) {
	char line_sep[] = "----------------------------------------------------------------------------------------";
	char line_sep_b[] = "========================================================================================";

	cout << endl;
	cout << line_sep_b << endl;

	// count how many instructors match the filter
	int count = 0;
	for (int i = 0; i < instructor_count; i++) {
		if (instructors[i].gender == gender_filter) {
			count++;
		}
	}

	printf("Instructors (count = %d, Gender = %s)\n", count, (gender_filter == 1 ? "Male" : "Female"));
	cout << line_sep << endl;
	printf("%-5s | %-32s | %-32s | %-6s\n", "ID", "Name", "Surname", "Gender");
	cout << line_sep << endl;

	for (int i = 0; i < instructor_count; i++) {
		Instructor& ins = instructors[i];
		if (ins.gender != gender_filter)
			continue;

		const char* gender_str = (ins.gender == 1 ? "Male" : "Female");
		printf("%-5d | %-32s | %-32s | %-6s\n", ins.id, ins.name, ins.surname, gender_str);
	}

	cout << line_sep_b << endl;
}

void print_search_instructors_by_id(int id) {
	char line_sep[] = "----------------------------------------------------------------------------------------";
	char line_sep_b[] = "========================================================================================";

	cout << endl;
	cout << line_sep_b << endl;

	// Search for instructor with the given ID
	Instructor* found = nullptr;
	for (int i = 0; i < instructor_count; i++) {
		if (instructors[i].id == id) {
			found = &instructors[i];
			break;
		}
	}

	if (!found) {
		cout << "Instructor with ID " << id << " not found!" << endl;
		cout << line_sep_b << endl;
		return;
	}

	printf("Instructor Details (ID = %d)\n", id);
	cout << line_sep << endl;
	printf("%-5s | %-32s | %-32s | %-6s\n", "ID", "Name", "Surname", "Gender");
	cout << line_sep << endl;

	const char* gender_str = (found->gender == 1 ? "Male" : (found->gender == 2 ? "Female" : "Other"));
	printf("%-5d | %-32s | %-32s | %-6s\n", found->id, found->name, found->surname, gender_str);

	cout << line_sep_b << endl;
}

void print_search_instructors_by_name() {
	char query[64];
	cout << "Enter a name, surname, or full name to search: ";
	if (cin.peek() == '\n') cin.ignore();
	cin.getline(query, 64);

	char line_sep[] = "----------------------------------------------------------------------------------------";
	char line_sep_b[] = "========================================================================================";

	int match_count = 0;

	cout << endl;
	cout << line_sep_b << endl;
	printf("Search results for '%s'\n", query);
	cout << line_sep << endl;
	printf("%-5s | %-32s | %-32s | %-6s\n", "ID", "Name", "Surname", "Gender");
	cout << line_sep << endl;

	for (int i = 0; i < instructor_count; i++) {
		Instructor& ins = instructors[i];

		// Build full name
		char fullname[80];
		strcpy_s(fullname, ins.name);
		strcat_s(fullname, " ");
		strcat_s(fullname, ins.surname);

		// Check all possibilities (case-sensitive)
		if (strcmp(ins.name, query) == 0 ||
			strcmp(ins.surname, query) == 0 ||
			strcmp(fullname, query) == 0) {

			const char* gender_str = (ins.gender == 1 ? "Male" : (ins.gender == 2 ? "Female" : "Other"));
			printf("%-5d | %-32s | %-32s | %-6s\n", ins.id, ins.name, ins.surname, gender_str);
			match_count++;
		}
	}

	if (match_count == 0) {
		cout << "No instructors found matching '" << query << "'." << endl;
	}

	cout << line_sep_b << endl;
}

/* HELPERS */

Instructor get_instructor() {
	Instructor ins{};

	ins.id = next_instructor_id();
	get_input_string("Enter name:", ins.name, sizeof(ins.name));
	get_input_string("Enter surname:", ins.surname, sizeof(ins.surname));
	ins.gender = get_input_gender();

	return ins;
}



