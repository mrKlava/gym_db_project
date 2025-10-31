#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>

#include "constants.h"
#include "types.h"
#include "data.h"

/* Instructors */
Instructor instructors[MAX_RECORDS];
int instructor_count = 0;
int instructor_last_id = 0;

/* Clients */
// TODO: implement clients data storage

/* Sessions */
// TODO: implement training sessions data storage

using namespace std;

bool load_data() {
	load_ids();
	load_instructors();

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
		if (token == "M") {
			ins.gender = M;
		}
		else if (token == "F") {
			ins.gender = F;
		}

		instructors[instructor_count] = ins;

		instructor_count++;
	}

	cout << "Loaded " << instructor_count << " instructors from " << FILE_INSTRUCTORS << endl;

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
		<< (ins.gender == 1 ? 'M' : 'F') << "\n";

	file.close();

	instructors[instructor_count] = ins;
	instructor_count++;
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

/* DELETE UTILS */

bool delete_instructor_by_id(int target_id) {
	bool deleted = false;

	ifstream in(FILE_INSTRUCTORS);
	ofstream temp("temp.csv");
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
	rename("temp.csv", FILE_INSTRUCTORS);

	// clear or remove temp file (to ensure no leftovers)
	remove("temp.csv");

	if (deleted)
		cout << "Instructor with ID " << target_id << " deleted successfully.\n";
	else
		cout << "Instructor with ID " << target_id << " not found.\n";

	return deleted;
}