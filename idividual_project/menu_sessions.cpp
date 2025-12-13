#pragma once

#include <cstdio>
#include <cstring>
#include <iostream>
#include <limits>
#include <string>

#include "types.h"
#include "data.h"

#include "menu.h"
#include "menu_sessions.h"

const string MENU_TITLE = "Training Session Menu";
const string MENU_OPTIONS[] = {
	"View",
	"Add New",
	"Delete",
	"Back to Main Menu"
};

const string MENU_VIEW_TITLE = "View Training Session Menu";
const string MENU_VIEW_OPTIONS[] = {
	"View All",
	"Sort by ID",
	"Sort by Client ID",
	"Sort by Instructor ID",
	"Sort by Price",
	"Sort by Date",
	"Filter",
	"Search",
	"Back"
};

const string MENU_SORT_TITLE = "Sort Training Sessions Menu";
const string MENU_SORT_OPTIONS[] = {
	"Ascending",
	"Descending",
	"Back"
};

const string MENU_FILTER_TITLE = "Filter Training Sessions Menu";
const string MENU_FILTER_OPTIONS[] = {
	"Client",
	"Instructor",
	"Back"
};

const string MENU_SEARCH_TITLE = "Search Training Sessions Menu";
const string MENU_SEARCH_OPTIONS[] = {
	"ID",
	"Back"
};

/* MAIN MENU */

void menu_sessions() {
	while (true) {
		print_menu_options(MENU_TITLE, MENU_OPTIONS);

		int choice = get_input_positive_int("Please enter your choice: ");

		switch (choice) {
		case 1: {
			menu_view_sessions();

			break;
		}
		case 2: {
			menu_add_session();

			break;
		}
		case 3: {
			menu_delete_sessions();

			break;
		}
		case 4:
			return;
		default:
			cout << "Invalid choice. Please try again." << endl;
		}
	}
}

/* MENU UTILS */

void menu_view_sessions() {
	while (true) {
		print_menu_options(MENU_VIEW_TITLE, MENU_VIEW_OPTIONS);

		int choice = get_input_positive_int("Please enter your choice: ");

		switch (choice) {
		case 1:
			//sort_session_by_id(true);
			print_table_sessions();

			break;
		case 2:
		{
			menu_sort_id_sessions();

			break;
		}
		case 3:
		{
			menu_sort_client_sessions();

			break;
		}
		case 4:
		{
			menu_sort_instructor_sessions();

			break;
		}
		case 5:
		{
			menu_sort_price_sessions();

			break;
		}
		case 6:
		{
			menu_sort_date_sessions();

			break;
		}
		case 7:
		{
			menu_filter_sessions();

			break;
		}
		case 8:
		{
			menu_search_sessions();

			break;
		}
		case 9:
			return;
		default:
			cout << "Invalid choice. Please try again." << endl;
		}
	}

	cout << endl;
}

void menu_sort_id_sessions() {
	while (true) {
		print_menu_options(MENU_SORT_TITLE, MENU_SORT_OPTIONS);

		int choice = get_input_positive_int("Please enter your choice: ");

		switch (choice) {
		case 1:
			sort_sessions_by_id(true);

			break;
		case 2:
		{
			sort_sessions_by_id(false);

			break;
		}
		case 3:
			return;
		default:
			cout << "Invalid choice. Please try again." << endl;
		}

		print_table_sessions();
	}

	cout << endl;
}

void menu_sort_client_sessions() {
	while (true) {
		print_menu_options(MENU_SORT_TITLE, MENU_SORT_OPTIONS);

		int choice = get_input_positive_int("Please enter your choice: ");

		switch (choice) {
		case 1:
			sort_sessions_by_client_id(true);

			break;
		case 2:
		{
			sort_sessions_by_client_id(false);

			break;
		}
		case 3:
			return;
		default:
			cout << "Invalid choice. Please try again." << endl;
		}

		print_table_sessions();
	}

	cout << endl;
}

void menu_sort_instructor_sessions() {
	while (true) {
		print_menu_options(MENU_SORT_TITLE, MENU_SORT_OPTIONS);

		int choice = get_input_positive_int("Please enter your choice: ");

		switch (choice) {
		case 1:
			sort_sessions_by_instructor_id(true);

			break;
		case 2:
		{
			sort_sessions_by_instructor_id(false);

			break;
		}
		case 3:
			return;
		default:
			cout << "Invalid choice. Please try again." << endl;
		}

		print_table_sessions();
	}

	cout << endl;
}

void menu_sort_price_sessions() {
	while (true) {
		print_menu_options(MENU_SORT_TITLE, MENU_SORT_OPTIONS);

		int choice = get_input_positive_int("Please enter your choice: ");

		switch (choice) {
		case 1:
			sort_sessions_by_price(true);

			break;
		case 2:
		{
			sort_sessions_by_price(false);

			break;
		}
		case 3:
			return;
		default:
			cout << "Invalid choice. Please try again." << endl;
		}

		print_table_sessions();
	}

	cout << endl;
}

void menu_sort_date_sessions() {
	while (true) {
		print_menu_options(MENU_SORT_TITLE, MENU_SORT_OPTIONS);

		int choice = get_input_positive_int("Please enter your choice: ");

		switch (choice) {
		case 1:
			sort_sessions_by_start_datetime(true);

			break;
		case 2:
		{
			sort_sessions_by_start_datetime(false);

			break;
		}
		case 3:
			return;
		default:
			cout << "Invalid choice. Please try again." << endl;
		}

		print_table_sessions();
	}

	cout << endl;
}

void menu_filter_sessions() {
	while (true) {
		print_menu_options(MENU_FILTER_TITLE, MENU_FILTER_OPTIONS);

		int choice = get_input_positive_int("Please enter your choice: ");

		switch (choice) {
		case 1: {
			int client_id = get_input_positive_int("Enter Client ID to filter: ");

			print_table_sessions_by_client(client_id);

			break;
		}
		case 2:
		{
			int instructor_id = get_input_positive_int("Enter Instructor ID to filter: ");

			print_table_sessions_by_instructor(instructor_id);

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

void menu_search_sessions() {
	while (true) {
		print_menu_options(MENU_SEARCH_TITLE, MENU_SEARCH_OPTIONS);

		int choice = get_input_positive_int("Please enter your choice: ");

		switch (choice) {
		case 1:
		{
			int id = get_input_positive_int("Please enter ID: ");
			print_search_session_by_id(id);

			break;
		}
		case 2:
			return;
		default:
			cout << "Invalid choice. Please try again." << endl;
		}
	}

	cout << endl;
}

/* ADD UTILS */

void menu_add_session() {
	TrainingSession session = get_session();
	bool is_added = add_session(session);

	cout << is_added << endl;
}

/* DELETE UTILS */

void menu_delete_sessions() {
	int target_id = get_input_positive_int("Enter Session ID to delete: ");

	bool is_deleted = delete_session_by_id(target_id);
	if (!is_deleted) {
		cout << "Session with ID " << target_id << " not found.\n";
	}
}

/* PRINTING UTILS */

void print_table_sessions() {
	char line_sep[] = "-----------------------------------------------------------------------------------------------------------";
	char line_sep_b[] = "===========================================================================================================";

	cout << endl;
	cout << line_sep_b << endl;

	printf("Training Sessions (count = %d)\n", session_count);
	cout << line_sep << endl;

	printf("%-5s | %-12s | %-12s | %-8s | %-20s | %-20s\n",
		"ID", "Instructor", "Client", "Price", "Start", "End");

	cout << line_sep << endl;

	for (int i = 0; i < session_count; i++)
	{
		TrainingSession& session = sessions[i];

		// Format start datetime
		char start_str[32];
		snprintf(start_str, sizeof(start_str), "%04d-%02d-%02d %02d:%02d",
			session.start.date.year,
			(int)session.start.date.month,
			session.start.date.day,
			session.start.time.hour,
			session.start.time.minute
		);

		// Format end datetime
		char end_str[32];
		snprintf(end_str, sizeof(end_str), "%04d-%02d-%02d %02d:%02d",
			session.end.date.year,
			(int)session.end.date.month,
			session.end.date.day,
			session.end.time.hour,
			session.end.time.minute
		);

		printf("%-5d | %-12d | %-12d | %-8.2f | %-20s | %-20s\n",
			session.id, session.instructor_id, session.client_id, session.price, start_str, end_str);
	}

	cout << line_sep_b << endl;
}

void print_table_sessions_by_client(int client_filter) {
	char line_sep[] = "-----------------------------------------------------------------------------------------------------------";
	char line_sep_b[] = "===========================================================================================================";

	cout << endl;
	cout << line_sep_b << endl;

	// Count how many clients match the filter
	int count = 0;
	for (int i = 0; i < session_count; i++) {
		if (sessions[i].client_id == client_filter) {
			count++;
		}
	}

	printf("Training Sessions (count = %d, Client with ID = %d)\n",
		count,
		client_filter);
	cout << line_sep << endl;

	printf("%-5s | %-12s | %-12s | %-8s | %-20s | %-20s\n",
		"ID", "Instructor", "Client", "Price", "Start", "End");

	cout << line_sep << endl;

	for (int i = 0; i < session_count; i++)
	{
		TrainingSession& session = sessions[i];
		if (session.client_id != client_filter)
			continue;

		// Format start datetime
		char start_str[32];
		snprintf(start_str, sizeof(start_str), "%04d-%02d-%02d %02d:%02d",
			session.start.date.year,
			(int)session.start.date.month,
			session.start.date.day,
			session.start.time.hour,
			session.start.time.minute
		);

		// Format end datetime
		char end_str[32];
		snprintf(end_str, sizeof(end_str), "%04d-%02d-%02d %02d:%02d",
			session.end.date.year,
			(int)session.end.date.month,
			session.end.date.day,
			session.end.time.hour,
			session.end.time.minute
		);

		printf("%-5d | %-12d | %-12d | %-8.2f | %-20s | %-20s\n",
			session.id, session.instructor_id, session.client_id, session.price, start_str, end_str);
	}

	cout << line_sep_b << endl;
}

void print_table_sessions_by_instructor(int instructor_filter) {
	char line_sep[] = "-----------------------------------------------------------------------------------------------------------";
	char line_sep_b[] = "===========================================================================================================";

	cout << endl;
	cout << line_sep_b << endl;

	// Count how many clients match the filter
	int count = 0;
	for (int i = 0; i < session_count; i++) {
		if (sessions[i].instructor_id == instructor_filter) {
			count++;
		}
	}

	printf("Training Sessions (count = %d, Instructor with ID = %d)\n",
		count,
		instructor_filter);
	cout << line_sep << endl;

	printf("%-5s | %-12s | %-12s | %-8s | %-20s | %-20s\n",
		"ID", "Instructor", "Client", "Price", "Start", "End");

	cout << line_sep << endl;

	for (int i = 0; i < session_count; i++)
	{
		TrainingSession& session = sessions[i];
		if (session.instructor_id != instructor_filter)
			continue;

		// Format start datetime
		char start_str[32];
		snprintf(start_str, sizeof(start_str), "%04d-%02d-%02d %02d:%02d",
			session.start.date.year,
			(int)session.start.date.month,
			session.start.date.day,
			session.start.time.hour,
			session.start.time.minute
		);

		// Format end datetime
		char end_str[32];
		snprintf(end_str, sizeof(end_str), "%04d-%02d-%02d %02d:%02d",
			session.end.date.year,
			(int)session.end.date.month,
			session.end.date.day,
			session.end.time.hour,
			session.end.time.minute
		);

		printf("%-5d | %-12d | %-12d | %-8.2f | %-20s | %-20s\n",
			session.id, session.instructor_id, session.client_id, session.price, start_str, end_str);
	}

	cout << line_sep_b << endl;
}

void print_search_session_by_id(int id) {
	char line_sep[] = "-----------------------------------------------------------------------------------------------------------";
	char line_sep_b[] = "===========================================================================================================";
	cout << endl;
	cout << line_sep_b << endl;
	// Search for session with the given ID
	TrainingSession* found = nullptr;
	for (int i = 0; i < session_count; i++) {
		if (sessions[i].id == id) {
			found = &sessions[i];
			break;
		}
	}

	if (!found) {
		cout << "Session with ID " << id << " not found!" << endl;
		cout << line_sep_b << endl;
		return;
	}

	printf("Training Session Details (ID = %d)\n", id);
	cout << line_sep << endl;
	printf("%-5s | %-12s | %-12s | %-8s | %-20s | %-20s\n",
		"ID", "Instructor", "Client", "Price", "Start", "End");
	cout << line_sep << endl;
	// Format start datetime
	char start_str[32];
	snprintf(start_str, sizeof(start_str), "%04d-%02d-%02d %02d:%02d",
		found->start.date.year,
		(int)found->start.date.month,
		found->start.date.day,
		found->start.time.hour,
		found->start.time.minute
	);
	// Format end datetime
	char end_str[32];
	snprintf(end_str, sizeof(end_str), "%04d-%02d-%02d %02d:%02d",
		found->end.date.year,
		(int)found->end.date.month,
		found->end.date.day,
		found->end.time.hour,
		found->end.time.minute
	);
	printf("%-5d | %-12d | %-12d | %-8.2f | %-20s | %-20s\n",
		found->id, found->instructor_id, found->client_id, found->price, start_str, end_str);
	cout << line_sep_b << endl;
}

/* HELPERS */

TrainingSession get_session() {
	TrainingSession session{};

	// assign next available ID
	session.id = next_session_id();

	// get existing instructor and client
	session.instructor_id = get_input_existing_instructor_id("Enter Instructor ID: ");
	session.client_id = get_input_existing_client_id("Enter Client ID: ");

	// get price
	session.price = get_input_positive_double("Enter Price: ");

	// get start and end datetime
	session.start = get_input_datetime("Enter Start DateTime: ");
	// validate end datetime is after start datetime
	while (true) {
		session.end = get_input_datetime("Enter End DateTime:");

		if (is_end_after_start(session.start, session.end)) {
			break;
		}

		cout << "Error: End of the Training Session must be AFTER Start (Date time)" << endl;
	}

	return session;
}