#include <cstdio>
#include <cstring>  // for strcpy, strlen
#include <iostream>
#include <limits>   // for numeric_limits
#include <string>

#include "data.h"
#include "types.h"

using namespace std;

/* UTILS */

bool is_leap(int year) {
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int days_in_month(int year, int month) {
	switch (month) {
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		return 31;
	case 4: case 6: case 9: case 11:
		return 30;
	case 2:
		return is_leap(year) ? 29 : 28;
	default:
		return 0;
	}
}

/* DATA TYPES */

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

double get_input_positive_double(const char* prompt) {
	double value;
	while (true) {
		cout << prompt;
		cin >> value;
		if (cin.fail() || value <= 0.0) {
			cin.clear();              // clear error flag
			cin.ignore(10000, '\n');  // discard invalid input
			cout << "Please enter a positive number.\n";
		}
		else {
			cin.ignore(10000, '\n');  // discard remaining input
			return value;
		}
	}
}

/* CUSTOM DATA TYPES */

int get_input_existing_instructor_id(const char* prompt) {
	int id;

	while (true) {
		id = get_input_positive_int(prompt);

		if (is_instructor_exists(id)) {
			return id;
		}

		cout << "Instructor with ID " << id << " does not exist. Please try again.\n";
	}
}

int get_input_existing_client_id(const char* prompt) {
	int id;

	while (true) {
		id = get_input_positive_int(prompt);

		if (is_client_exists(id)) {
			return id;
		}

		cout << "Client with ID " << id << " does not exist. Please try again.\n";
	}
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

Date get_input_date(const char* prompt) {
	Date date;

	while (true) {
		cout << prompt << " (YYYY-MM-DD): ";

		string input;
		if (cin.peek() == '\n') cin.ignore();
		getline(cin, input);

		int year, month, day;

		if (sscanf_s(input.c_str(), "%d-%d-%d", &year, &month, &day) != 3) {
			cout << "Invalid date format. Please use YYYY-MM-DD.\n";
			continue;
		}

		if (month < 1 || month > 12) {
			cout << "Invalid month. Must be 1–12.\n";
			continue;
		}

		int max_day = days_in_month(year, month);
		if (day < 1 || day > max_day) {
			cout << "Invalid day. Month " << month
				<< " has " << max_day << " days.\n";
			continue;
		}

		date.year = year;
		date.month = (Month)month;
		date.day = day;

		return date;
	}
}

Time get_input_time(const char* prompt) {
	Time t;

	while (true) {
		cout << prompt << " (HH:MM): ";

		string input;
		if (cin.peek() == '\n') cin.ignore();
		getline(cin, input);

		int hour, minute;

		if (sscanf_s(input.c_str(), "%d:%d", &hour, &minute) != 2) {
			cout << "Invalid time format. Please use HH:MM.\n";
			continue;
		}

		if (hour < 0 || hour > 23) {
			cout << "Invalid hour (0–23).\n";
			continue;
		}

		if (minute < 0 || minute > 59) {
			cout << "Invalid minute (0–59).\n";
			continue;
		}

		t.hour = hour;
		t.minute = minute;

		return t;
	}
}

DateTime get_input_datetime(const char* prompt) {
	cout << prompt << endl;

	DateTime dt;

	dt.date = get_input_date("Enter date");
	dt.time = get_input_time("Enter time");

	return dt;
}

Client get_client() {
	Client client{};

	client.id = next_client_id();
	get_input_string("Enter name:", client.name, sizeof(client.name));
	get_input_string("Enter surname:", client.surname, sizeof(client.surname));
	client.dob = get_input_date("Enter date of birth: ");
	client.gender = get_input_gender();

	return client;
}

Instructor get_instructor() {
	Instructor ins{};

	ins.id = next_instructor_id();
	get_input_string("Enter name:", ins.name, sizeof(ins.name));
	get_input_string("Enter surname:", ins.surname, sizeof(ins.surname));
	ins.gender = get_input_gender();

	return ins;
}

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