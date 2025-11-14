#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring> // for strcmp

#include "constants.h"
#include "types.h"
#include "data.h"

using namespace std;

/* Instructors */
Instructor instructors[MAX_RECORDS];
int instructor_count = 0;
int instructor_last_id = 0;

/* Clients */
Client clients[MAX_RECORDS];
int client_count = 0;
int client_last_id = 0;

/* Sessions */
// TODO: implement training sessions data storage


bool load_data() {
	load_ids();
	load_instructors();
	load_clients();

	return true;
}

/* LOAD UTILS */

bool load_ids() {
	ifstream f(FILE_CONFIG);
	if (!f.is_open()) {
		cerr << "Error: Could not open file " << FILE_CONFIG << endl;
		return false;
	}
	string line;

	while (getline(f, line)) {
		if (line.empty()) continue;
		// extract ids 

		int delimiter = line.find('=');
		string key = line.substr(0, delimiter);
		string value = line.substr(delimiter + 1);

		if (key == "instructor_id") {
			instructor_last_id = atoi(value.c_str());
		}
		if (key == "client_id") {
			client_last_id = atoi(value.c_str());
		}
	}
	f.close();
	return true;
}

bool load_instructors() {
	ifstream f(FILE_INSTRUCTORS);

	if (!f.is_open()) {
		cerr << "Error: Could not open file " << FILE_INSTRUCTORS << endl;
		return false;
	}

	string line;

	instructor_count = 0;

	while (getline(f, line)) {
		if (line.empty()) continue;

		stringstream ss(line);

		string token;

		Instructor ins{};

		// handle id 
		if (!getline(ss, token, ',')) continue;
		ins.id = atoi(token.c_str());

		// handle name
		if (!getline(ss, token, ',')) continue;
		strncpy_s(ins.name, token.c_str(), sizeof(ins.name) - 1);

		// handle surname
		if (!getline(ss, token, ',')) continue;
		strncpy_s(ins.surname, token.c_str(), sizeof(ins.surname) - 1);

		// handle gender
		if (!getline(ss, token, ',')) continue;
		if (token == "1") {
			ins.gender = M;
		}
		else if (token == "2") {
			ins.gender = F;
		}

		instructors[instructor_count] = ins;

		instructor_count++;
	}

	cout << "Loaded " << instructor_count << " instructors from " << FILE_INSTRUCTORS << endl;

	f.close();

	return true;
}

bool load_clients() {
	ifstream f(FILE_CLIENTS);

	if (!f.is_open()) {
		cerr << "Error: Could not open file " << FILE_CLIENTS << endl;
		return false;
	}

	string line;

	client_count = 0;

	while (getline(f, line)) {
		if (line.empty()) continue;

		stringstream ss(line);

		string token;

		Client client{};

		// handle id 
		if (!getline(ss, token, ',')) continue;
		client.id = atoi(token.c_str());

		// handle name
		if (!getline(ss, token, ',')) continue;
		strncpy_s(client.name, token.c_str(), sizeof(client.name) - 1);

		// handle surname
		if (!getline(ss, token, ',')) continue;
		strncpy_s(client.surname, token.c_str(), sizeof(client.surname) - 1);

		// ---- DOB (YYYY-MM-DD) ----
		if (!getline(ss, token, ',')) continue;
		// Format: 1985-06-15
		int year, month, day;
		if (sscanf_s(token.c_str(), "%d-%d-%d", &year, &month, &day) == 3) {
			client.dob.year = year;
			client.dob.month = (Month)month;
			client.dob.day = day;
		}
		else {
			cerr << "Warning: Invalid date format for client ID " << client.id << endl;
			continue;
		}

		// handle gender
		if (!getline(ss, token, ',')) continue;
		if (token == "1") {
			client.gender = M;
		}
		else if (token == "2") {
			client.gender = F;
		}

		clients[client_count] = client;

		client_count++;
	}

	cout << "Loaded " << client_count << " Clients from " << FILE_CLIENTS << endl;

	f.close();

	return true;
}

/* ADD UTILS */

bool add_instructor(const Instructor& ins) {
	if (instructor_count >= MAX_RECORDS) {
		cerr << "Error: Maximum number of instructors reached." << endl;
		return false;
	}

	// Append to file
	ofstream file(FILE_INSTRUCTORS, ios::app); // append mode
	if (!file.is_open()) {
		cerr << "Error: Could not open file " << FILE_INSTRUCTORS << " for writing." << endl;
		return false;
	}

	// Write record in CSV format
	file << ins.id << ","
		<< ins.name << ","
		<< ins.surname << ","
		<< ins.gender << "\n";

	file.close();

	instructors[instructor_count] = ins;
	instructor_count++;
	return true;
}

bool add_client(const Client& client) {
	if (client_count >= MAX_RECORDS) {
		cerr << "Error: Maximum number of clients reached." << endl;
		return false;
	}

	// Append to file
	ofstream file(FILE_CLIENTS, ios::app); // append mode
	if (!file.is_open()) {
		cerr << "Error: Could not open file " << FILE_CLIENTS << " for writing." << endl;
		return false;
	}

	// Write record in CSV format
	file << client.id << ","
		<< client.name << ","
		<< client.surname << ","
		<< client.dob.year << "-" << client.dob.month << "-" << client.dob.day << ","
		<< client.gender << "\n";

	file.close();

	clients[client_count] = client;
	client_count++;
	return true;
}

/* UPDATE UTILS */

int next_instructor_id() {
	int new_id = ++instructor_last_id;

	ifstream infile(FILE_CONFIG);
	if (!infile.is_open()) {
		cerr << "Error: Cannot open config file for reading: " << FILE_CONFIG << endl;
		return new_id;
	}

	string line;
	string new_content;
	bool found = false;


	while (getline(infile, line)) {
		size_t pos = line.find('=');
		if (pos != string::npos) {
			string key = line.substr(0, pos);
			if (key == "instructor_id") {
				new_content += "instructor_id=" + to_string(new_id) + "\n";

				found = true;
			}
			else {
				new_content += line + "\n";
			}
		}
		else {
			new_content += line + "\n";
		}
	}
	infile.close();

	ofstream outfile(FILE_CONFIG, ios::trunc);
	if (!outfile.is_open()) {
		cerr << "Error: Cannot open config file for writing: " << FILE_CONFIG << endl;
		return new_id;
	}

	outfile << new_content;
	outfile.close();

	return new_id;
}

int next_client_id() {
	int new_id = ++client_last_id;

	ifstream infile(FILE_CONFIG);
	if (!infile.is_open()) {
		cerr << "Error: Cannot open config file for reading: " << FILE_CONFIG << endl;
		return new_id;
	}

	string line;
	string new_content;
	bool found = false;


	while (getline(infile, line)) {
		size_t pos = line.find('=');
		if (pos != string::npos) {
			string key = line.substr(0, pos);
			if (key == "client_id") {
				new_content += "client_id=" + to_string(new_id) + "\n";

				found = true;
			}
			else {
				new_content += line + "\n";
			}
		}
		else {
			new_content += line + "\n";
		}
	}
	infile.close();

	ofstream outfile(FILE_CONFIG, ios::trunc);
	if (!outfile.is_open()) {
		cerr << "Error: Cannot open config file for writing: " << FILE_CONFIG << endl;
		return new_id;
	}

	outfile << new_content;
	outfile.close();

	return new_id;
}

/* DELETE UTILS */

bool delete_instructor_by_id(int target_id) {
	bool deleted = false;

	ifstream in(FILE_INSTRUCTORS);
	ofstream temp(FILE_TEMP);
	if (!in.is_open() || !temp.is_open()) {
		cerr << "Error: cannot open file(s)." << endl;
		return deleted;
	}

	string line;

	while (getline(in, line)) {
		if (line.empty()) continue;

		size_t pos = line.find(',');
		if (pos == string::npos) {
			temp << line << "\n"; // keep malformed line
			continue;
		}

		int id = stoi(line.substr(0, pos));
		if (id != target_id) {
			temp << line << "\n"; // keep everything except target
		}
		else {
			deleted = true;
		}
	}

	in.close();
	temp.close();

	// replace original file
	remove(FILE_INSTRUCTORS);
	rename(FILE_TEMP, FILE_INSTRUCTORS);

	// clear or remove temp file (to ensure no leftovers)
	remove(FILE_TEMP);

	if (deleted)
		cout << "Instructor with ID " << target_id << " deleted successfully.\n";
	else
		cout << "Instructor with ID " << target_id << " not found.\n";

	// reload data
	load_instructors();

	return deleted;
}

bool delete_client_by_id(int target_id) {
	bool deleted = false;

	ifstream in(FILE_CLIENTS);
	ofstream temp(FILE_TEMP);
	if (!in.is_open() || !temp.is_open()) {
		cerr << "Error: cannot open file(s)." << endl;
		return deleted;
	}

	string line;

	while (getline(in, line)) {
		if (line.empty()) continue;

		size_t pos = line.find(',');
		if (pos == string::npos) {
			temp << line << "\n"; // keep malformed line
			continue;
		}

		int id = stoi(line.substr(0, pos));
		if (id != target_id) {
			temp << line << "\n"; // keep everything except target
		}
		else {
			deleted = true;
		}
	}

	in.close();
	temp.close();

	// replace original file
	remove(FILE_CLIENTS);
	rename(FILE_TEMP, FILE_CLIENTS);

	// clear or remove temp file (to ensure no leftovers)
	remove(FILE_TEMP);

	if (deleted)
		cout << "Client with ID " << target_id << " deleted successfully.\n";
	else
		cout << "Client with ID " << target_id << " not found.\n";

	// reload data
	load_clients();

	return deleted;
}


/* SORT UTILS */

void sort_instructors_by_id(bool asc = true) {
	for (int i = 0; i < instructor_count - 1; i++) {
		for (int j = 0; j < instructor_count - i - 1; j++) {
			bool condition = asc
				? (instructors[j].id > instructors[j + 1].id)
				: (instructors[j].id < instructors[j + 1].id);

			if (condition) {
				Instructor temp = instructors[j];
				instructors[j] = instructors[j + 1];
				instructors[j + 1] = temp;
			}
		}
	}
}

void sort_instructors_by_name(bool asc = true) {
	for (int i = 0; i < instructor_count - 1; i++) {
		for (int j = 0; j < instructor_count - i - 1; j++) {
			// Combine name and surname for comparison
			char fullname1[64];
			char fullname2[64];

			strcpy_s(fullname1, instructors[j].name);
			strcat_s(fullname1, " ");
			strcat_s(fullname1, instructors[j].surname);

			strcpy_s(fullname2, instructors[j + 1].name);
			strcat_s(fullname2, " ");
			strcat_s(fullname2, instructors[j + 1].surname);

			bool condition = asc
				? (strcmp(fullname1, fullname2) > 0)
				: (strcmp(fullname1, fullname2) < 0);

			if (condition) {
				Instructor temp = instructors[j];
				instructors[j] = instructors[j + 1];
				instructors[j + 1] = temp;
			}
		}
	}
}

void sort_clients_by_id(bool asc = true) {
	for (int i = 0; i < client_count - 1; i++) {
		for (int j = 0; j < client_count - i - 1; j++) {
			bool condition = asc
				? (clients[j].id > clients[j + 1].id)
				: (clients[j].id < clients[j + 1].id);

			if (condition) {
				Client temp = clients[j];
				clients[j] = clients[j + 1];
				clients[j + 1] = temp;
			}
		}
	}
}

void sort_clients_by_name(bool asc = true) {
	for (int i = 0; i < client_count - 1; i++) {
		for (int j = 0; j < client_count - i - 1; j++) {
			// Combine name and surname for comparison
			char fullname1[64];
			char fullname2[64];

			strcpy_s(fullname1, clients[j].name);
			strcat_s(fullname1, " ");
			strcat_s(fullname1, clients[j].surname);

			strcpy_s(fullname2, clients[j + 1].name);
			strcat_s(fullname2, " ");
			strcat_s(fullname2, clients[j + 1].surname);

			bool condition = asc
				? (strcmp(fullname1, fullname2) > 0)
				: (strcmp(fullname1, fullname2) < 0);

			if (condition) {
				Client temp = clients[j];
				clients[j] = clients[j + 1];
				clients[j + 1] = temp;
			}
		}
	}
}