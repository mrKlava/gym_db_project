#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>

#include "constants.h"
#include "types.h"
#include "data.h"

Instructor instructors[MAX_RECORDS];
int instructor_count = 0;

using namespace std;

bool load_data() {
	return load_instructors();
}

bool load_instructors () {
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

