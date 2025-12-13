#ifndef MENU_H
#define MENU_H

#pragma once
#include <iostream>
#include <string>

#include "types.h"

using namespace std;

// MENU UTILS

void menu();

// INPUT UTILS

void get_input_string(const char* prompt, char* destination, int length);
int get_input_positive_int(const char* prompt);
double get_input_positive_double(const char* prompt);

Gender get_input_gender();

Date get_input_date(const char* prompt);
Time get_input_time(const char* prompt);
DateTime get_input_datetime(const char* prompt);

int get_input_existing_client_id(const char* prompt);
int get_input_existing_instructor_id(const char* prompt);

// PRINTING UTILS
template <size_t N>
void print_menu_options(string title, const string(&options)[N]) {
	cout << endl;
	cout << "=============================" << endl;
	cout << title << endl;
	cout << "-----------------------------" << endl;
	for (size_t i = 0; i < N; i++) {
		cout << (i + 1) << ". " << options[i] << endl;
	}
	cout << "=============================" << endl;
}

#endif