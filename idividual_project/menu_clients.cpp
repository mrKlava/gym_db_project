#pragma once

#include <cstdio>
#include <cstring>
#include <iostream>
#include <limits>
#include <string>

#include "types.h"
#include "data.h"

#include "menu.h"
#include "menu_clients.h"

using namespace std;

const string INPUT_CHOICE_PROMPT = "Please enter your choice: ";
const string INPUT_INVALID_CHOICE_MSG = "Invalid choice. Please try again.";

const string MENU_TITLE = "Clients Menu";
const string MENU_OPTIONS[] = {
	"View",
	"Add New",
	"Delete",
	"Back to Main Menu"
};

const string MENU_VIEW_TITLE = "View Clients Menu";
const string MENU_VIEW_OPTIONS[] = {
	"View All",
	"Sort by ID",
	"Sort by Name",
	"Filter by Gender",
	"Search",
	"Back"
};

const string MENU_SORT_TITLE = "Sort Clients Menu";
const string MENU_SORT_OPTIONS[] = {
	"Ascending",
	"Descending",
	"Back"
};

const string MENU_FILTER_TITLE = "Filter by Gender Clients Menu";
const string MENU_FILTER_OPTIONS[] = {
	"Male",
	"Female",
	"Back"
};

const string MENU_SEARCH_TITLE = "Search Clients Menu";
const string MENU_SEARCH_OPTIONS[] = {
	"ID",
	"Name",
	"Back"
};

/* MAIN MENU */

void menu_clients () {
	while (true) {
		print_menu_options(MENU_TITLE, MENU_OPTIONS);

		int choice = get_input_positive_int("Please enter your choice: ");

		switch (choice) {
		case 1:
			menu_view_clients();
			break;
		case 2:
		{
			menu_add_clients();
			break;
		}
		case 3:
			menu_delete_clients();
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

void menu_view_clients() {
	while (true) {
		print_menu_options(MENU_VIEW_TITLE, MENU_VIEW_OPTIONS);

		int choice = get_input_positive_int("Please enter your choice: ");

		switch (choice) {
		case 1:
			sort_clients_by_id(true);
			print_table_clients();

			break;
		case 2:
		{
			menu_sort_id_clients();

			break;
		}
		case 3:
		{
			menu_sort_name_clients();

			break;
		}
		case 4:
		{
			menu_filter_gender_clients();

			break;
		}
		case 5:
		{
			menu_search_clients();

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

void menu_sort_id_clients() {
	while (true) {
		print_menu_options(MENU_SORT_TITLE, MENU_SORT_OPTIONS);

		int choice = get_input_positive_int("Please enter your choice: ");

		switch (choice) {
		case 1:
			sort_clients_by_id(true);

			break;
		case 2:
		{
			sort_clients_by_id(false);

			break;
		}
		case 3:
			return;
		default:
			cout << "Invalid choice. Please try again." << endl;
		}

		print_table_clients();
	}

	cout << endl;
}

void menu_sort_name_clients() {
	while (true) {
		print_menu_options(MENU_SORT_TITLE, MENU_SORT_OPTIONS);

		int choice = get_input_positive_int("Please enter your choice: ");

		switch (choice) {
		case 1:
			sort_clients_by_name(true);

			break;
		case 2:
		{
			sort_clients_by_name(false);

			break;
		}
		case 3:
			return;
		default:
			cout << "Invalid choice. Please try again." << endl;
		}

		print_table_clients();
	}

	cout << endl;
}

void menu_filter_gender_clients() {
	while (true) {
		print_menu_options(MENU_FILTER_TITLE, MENU_FILTER_OPTIONS);

		int choice = get_input_positive_int("Please enter your choice: ");

		switch (choice) {
		case 1:
			print_table_clients_by_gender(M);

			break;
		case 2:
		{
			print_table_clients_by_gender(F);

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

void menu_search_clients() {
	while (true) {
		print_menu_options(MENU_SEARCH_TITLE, MENU_SEARCH_OPTIONS);

		int choice = get_input_positive_int("Please enter your choice: ");

		switch (choice) {
		case 1:
		{
			int id = get_input_positive_int("Please enter ID: ");
			print_search_clients_by_id(id);

			break;
		}
		case 2:
		{

			print_search_clients_by_name();

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

void menu_add_clients() {
	Client client = get_client();
	bool is_added = add_client(client);

	cout << is_added << endl;
}

/* DELETE UTILS */

void menu_delete_clients() {
	int target_id = get_input_positive_int("Enter Client ID to delete: ");

	bool is_deleted = delete_client_by_id(target_id);
	if (!is_deleted) {
		cout << "Client with ID " << target_id << " not found.\n";
	}
}

/* PRINTING UTILS */

void print_table_clients() {
	char line_sep[] = "-----------------------------------------------------------------------------------------------------------";
	char line_sep_b[] = "===========================================================================================================";

	cout << endl;
	cout << line_sep_b << endl;
	printf("Clients (count = %d)\n", client_count);
	cout << line_sep << endl;
	printf("%-5s | %-15s | %-15s | %-12s | %-6s\n",
		"ID", "Name", "Surname", "DOB", "Gender");
	cout << line_sep << endl;

	for (int i = 0; i < client_count; i++)
	{
		Client& c = clients[i];

		const char* gender =
			(c.gender == M ? "Male" :
				(c.gender == F ? "Female" : "Other"));

		// Format date: YYYY-MM-DD
		char dob_str[16];
		snprintf(dob_str, sizeof(dob_str), "%04d-%02d-%02d",
			c.dob.year, (int)c.dob.month, c.dob.day);

		printf("%-5d | %-15s | %-15s | %-12s | %-6s\n",
			c.id, c.name, c.surname, dob_str, gender);
	}

	cout << line_sep_b << endl;
}

void print_table_clients_by_gender(Gender gender_filter) {
	char line_sep[] = "-----------------------------------------------------------------------------------------------------------";
	char line_sep_b[] = "===========================================================================================================";

	cout << endl;
	cout << line_sep_b << endl;

	// Count how many clients match the filter
	int count = 0;
	for (int i = 0; i < client_count; i++) {
		if (clients[i].gender == gender_filter) {
			count++;
		}
	}

	printf("Clients (count = %d, Gender = %s)\n",
		count,
		(gender_filter == M ? "Male" : "Female"));

	cout << line_sep << endl;
	printf("%-5s | %-15s | %-15s | %-12s | %-6s\n",
		"ID", "Name", "Surname", "DOB", "Gender");
	cout << line_sep << endl;

	for (int i = 0; i < client_count; i++) {
		Client& c = clients[i];
		if (c.gender != gender_filter)
			continue;

		const char* gender_str = (c.gender == M ? "Male" : "Female");

		// Format DOB
		char dob_str[16];
		snprintf(dob_str, sizeof(dob_str), "%04d-%02d-%02d",
			c.dob.year, (int)c.dob.month, c.dob.day);

		printf("%-5d | %-15s | %-15s | %-12s | %-6s\n",
			c.id, c.name, c.surname, dob_str, gender_str);
	}

	cout << line_sep_b << endl;
}

void print_search_clients_by_id(int id) {
	char line_sep[] = "-----------------------------------------------------------------------------------------------------------";
	char line_sep_b[] = "===========================================================================================================";

	cout << endl;
	cout << line_sep_b << endl;

	// Search for client with the given ID
	Client* found = nullptr;
	for (int i = 0; i < client_count; i++) {
		if (clients[i].id == id) {
			found = &clients[i];
			break;
		}
	}

	if (!found) {
		cout << "Client with ID " << id << " not found!" << endl;
		cout << line_sep_b << endl;
		return;
	}

	printf("Client Details (ID = %d)\n", id);
	cout << line_sep << endl;
	printf("%-5s | %-15s | %-15s | %-12s | %-6s\n",
		"ID", "Name", "Surname", "DOB", "Gender");
	cout << line_sep << endl;

	const char* gender_str =
		(found->gender == M ? "Male" :
			(found->gender == F ? "Female" : "Other"));

	// Format DOB
	char dob_str[16];
	snprintf(dob_str, sizeof(dob_str), "%04d-%02d-%02d",
		found->dob.year, (int)found->dob.month, found->dob.day);

	printf("%-5d | %-15s | %-15s | %-12s | %-6s\n",
		found->id, found->name, found->surname, dob_str, gender_str);

	cout << line_sep_b << endl;
}

void print_search_clients_by_name() {
	char query[64];
	cout << "Enter a name, surname, or full name to search: ";
	if (cin.peek() == '\n') cin.ignore();
	cin.getline(query, 64);

	char line_sep[] = "-----------------------------------------------------------------------------------------------------------";
	char line_sep_b[] = "===========================================================================================================";

	int match_count = 0;

	cout << endl;
	cout << line_sep_b << endl;
	printf("Search results for '%s'\n", query);
	cout << line_sep << endl;
	printf("%-5s | %-15s | %-15s | %-12s | %-6s\n",
		"ID", "Name", "Surname", "DOB", "Gender");
	cout << line_sep << endl;

	for (int i = 0; i < client_count; i++) {
		Client& c = clients[i];

		// Build full name
		char fullname[80];
		strcpy_s(fullname, c.name);
		strcat_s(fullname, " ");
		strcat_s(fullname, c.surname);

		// Check name, surname, or full name
		if (strcmp(c.name, query) == 0 ||
			strcmp(c.surname, query) == 0 ||
			strcmp(fullname, query) == 0)
		{
			const char* gender_str = (c.gender == M ? "Male" :
				(c.gender == F ? "Female" : "Other"));

			// Format DOB
			char dob_str[16];
			snprintf(dob_str, sizeof(dob_str), "%04d-%02d-%02d",
				c.dob.year, (int)c.dob.month, c.dob.day);

			printf("%-5d | %-15s | %-15s | %-12s | %-6s\n",
				c.id, c.name, c.surname, dob_str, gender_str);

			match_count++;
		}
	}

	if (match_count == 0) {
		cout << "No clients found matching '" << query << "'." << endl;
	}

	cout << line_sep_b << endl;
}

/* HELPERS */

Client get_client() {
	Client client{};

	client.id = next_client_id();
	get_input_string("Enter name:", client.name, sizeof(client.name));
	get_input_string("Enter surname:", client.surname, sizeof(client.surname));
	client.dob = get_input_date("Enter date of birth: ");
	client.gender = get_input_gender();

	return client;
}



