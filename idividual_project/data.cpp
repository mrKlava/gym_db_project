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
int instructor_count = 0;
int instructor_last_id = 0;
Instructor instructors[MAX_RECORDS];

/* Clients */
int client_count = 0;
int client_last_id = 0;
Client clients[MAX_RECORDS];

/* Sessions */
int session_count = 0;
int session_last_id = 0;
TrainingSession sessions[MAX_RECORDS];


bool load_data() {
	load_ids();
	load_instructors();
	load_clients();
	load_sessions();

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
		if (key == "session_id") {
			session_last_id = atoi(value.c_str());
		}
	}
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

bool load_sessions() {
	ifstream f(FILE_SESSIONS);

	if (!f.is_open()) {
		cerr << "Error: Could not open file " << FILE_SESSIONS << endl;
		return false;
	}

	string line;

	session_count = 0;

	while (getline(f, line)) {
		if (line.empty()) continue;

		stringstream ss(line);
		string token;

		TrainingSession session{};

		// 1) ID
		if (!getline(ss, token, ',')) continue;
		session.id = atoi(token.c_str());

		// 2) instructor_id
		if (!getline(ss, token, ',')) continue;
		session.instructor_id = atoi(token.c_str());

		// 3) client_id
		if (!getline(ss, token, ',')) continue;
		session.client_id = atoi(token.c_str());

		// 4) start datetime "YYYY-MM-DD HH:MM:SS"
		if (!getline(ss, token, ',')) continue;
		{
			int y, m, d, hh, mm, ss_;
			if (sscanf_s(token.c_str(), "%d-%d-%d %d:%d:%d",
				&y, &m, &d, &hh, &mm, &ss_) != 6)
			{
				cerr << "Warning: Invalid start datetime for session ID "
					<< session.id << endl;
				continue;
			}
			session.start.date.year = y;
			session.start.date.month = (Month)m;
			session.start.date.day = d;
			session.start.time.hour = hh;
			session.start.time.minute = mm;
		}

		// 5) end datetime
		if (!getline(ss, token, ',')) continue;
		{
			int y, m, d, hh, mm, ss_;
			if (sscanf_s(token.c_str(), "%d-%d-%d %d:%d:%d",
				&y, &m, &d, &hh, &mm, &ss_) != 6)
			{
				cerr << "Warning: Invalid end datetime for session ID "
					<< session.id << endl;
				continue;
			}
			session.end.date.year = y;
			session.end.date.month = (Month)m;
			session.end.date.day = d;
			session.end.time.hour = hh;
			session.end.time.minute = mm;
		}

		// 6) price
		if (!getline(ss, token, ',')) continue;
		session.price = atof(token.c_str());

		// Store in array
		sessions[session_count] = session;
		session_count++;
	}

	cout << "Loaded " << session_count << " Training Sessions from " << FILE_SESSIONS << endl;

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

bool add_session(const TrainingSession& session) {
	if (session_count >= MAX_RECORDS) {
		cerr << "Error: Maximum number of sessions reached." << endl;
		return false;
	}
	// Append to file
	ofstream file(FILE_SESSIONS, ios::app); // append mode
	if (!file.is_open()) {
		cerr << "Error: Could not open file " << FILE_SESSIONS << " for writing." << endl;
		return false;
	}
	// Write record in CSV format
	file << session.id << ","
		<< session.instructor_id << ","
		<< session.client_id << ","
		<< session.start.date.year << "-" << session.start.date.month << "-" << session.start.date.day << " "
		<< session.start.time.hour << ":" << session.start.time.minute << ":00" << ","
		<< session.end.date.year << "-" << session.end.date.month << "-" << session.end.date.day << " "
		<< session.end.time.hour << ":" << session.end.time.minute << ":00" << ","
		<< session.price << "\n";
	file.close();

	sessions[session_count] = session;
	session_count++;

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

int next_session_id() {
	int new_id = ++session_last_id;

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
			if (key == "session_id") {
				new_content += "session_id=" + to_string(new_id) + "\n";

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

bool delete_session_by_id(int target_id) {
	bool deleted = false;

	ifstream in(FILE_SESSIONS);
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
	remove(FILE_SESSIONS);
	rename(FILE_TEMP, FILE_SESSIONS);

	// clear or remove temp file (to ensure no leftovers)
	remove(FILE_TEMP);

	if (deleted)
		cout << "Session with ID " << target_id << " deleted successfully.\n";
	else
		cout << "Session with ID " << target_id << " not found.\n";

	// reload data
	load_sessions();

	return deleted;
}

/* SORT UTILS */

// clients

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

// instructors

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

// sessions

void sort_sessions_by_id(bool asc = true) {
	for (int i = 0; i < session_count - 1; i++) {
		for (int j = 0; j < session_count - i - 1; j++) {
			bool condition = asc
				? (sessions[j].id > sessions[j + 1].id)
				: (sessions[j].id < sessions[j + 1].id);
			if (condition) {
				TrainingSession temp = sessions[j];
				sessions[j] = sessions[j + 1];
				sessions[j + 1] = temp;
			}
		}
	}
}

void sort_sessions_by_client_id(bool asc = true) {
	for (int i = 0; i < session_count - 1; i++) {
		for (int j = 0; j < session_count - i - 1; j++) {
			bool condition = asc
				? (sessions[j].client_id > sessions[j + 1].client_id)
				: (sessions[j].client_id < sessions[j + 1].client_id);
			if (condition) {
				TrainingSession temp = sessions[j];
				sessions[j] = sessions[j + 1];
				sessions[j + 1] = temp;
			}
		}
	}
}

void sort_sessions_by_instructor_id(bool asc = true) {
	for (int i = 0; i < session_count - 1; i++) {
		for (int j = 0; j < session_count - i - 1; j++) {
			bool condition = asc
				? (sessions[j].instructor_id > sessions[j + 1].instructor_id)
				: (sessions[j].instructor_id < sessions[j + 1].instructor_id);
			if (condition) {
				TrainingSession temp = sessions[j];
				sessions[j] = sessions[j + 1];
				sessions[j + 1] = temp;
			}
		}
	}
}

void sort_sessions_by_price(bool asc = true) {
	for (int i = 0; i < session_count - 1; i++) {
		for (int j = 0; j < session_count - i - 1; j++) {
			bool condition = asc
				? (sessions[j].price > sessions[j + 1].price)
				: (sessions[j].price < sessions[j + 1].price);
			if (condition) {
				TrainingSession temp = sessions[j];
				sessions[j] = sessions[j + 1];
				sessions[j + 1] = temp;
			}
		}
	}
}

void sort_sessions_by_start_datetime(bool asc = true) {
	for (int i = 0; i < session_count - 1; i++) {
		for (int j = 0; j < session_count - i - 1; j++) {
			bool condition = asc
				? (compare_datetimes(sessions[j].start, sessions[j + 1].start) > 0)
				: (compare_datetimes(sessions[j].start, sessions[j + 1].start) < 0);
			if (condition) {
				TrainingSession temp = sessions[j];
				sessions[j] = sessions[j + 1];
				sessions[j + 1] = temp;
			}
		}
	}
}

/* UTILS */

int compare_datetimes(const DateTime& a, const DateTime& b) {
	// Compare year
	if (a.date.year != b.date.year)
		return a.date.year - b.date.year;

	// Compare month
	if (a.date.month != b.date.month)
		return (int)a.date.month - (int)b.date.month;

	// Compare day
	if (a.date.day != b.date.day)
		return a.date.day - b.date.day;

	// Compare hour
	if (a.time.hour != b.time.hour)
		return a.time.hour - b.time.hour;

	// Compare minute
	if (a.time.minute != b.time.minute)
		return a.time.minute - b.time.minute;

	// Equal
	return 0;
}

bool is_end_after_start(const DateTime& start, const DateTime& end) {
	return compare_datetimes(end, start) > 0;
}

bool is_client_exists(int client_id) {
	for (int i = 0; i < client_count; i++) {
		if (clients[i].id == client_id) {
			return true;
		}
	}
	return false;
}


bool is_instructor_exists(int instructor_id) {
	for (int i = 0; i < instructor_count; i++) {
		if (instructors[i].id == instructor_id) {
			return true;
		}
	}
	return false;
}
