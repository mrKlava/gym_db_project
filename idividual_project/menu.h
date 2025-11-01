#ifndef MENU_H
#define MENU_H

#pragma once
#include <iostream>
#include <string>

#include "types.h"

using namespace std;

void menu();
void menu_clients();
void menu_trainig_sessions();

void get_input_string(const char* prompt, char* destination, int length);
Gender get_input_gender();

int get_input_positive_int(const char* prompt);

template <size_t N>
void print_menu_options(const string(&options)[N]) {
	cout << endl;
	cout << "=============================" << endl;
	cout << options[0] << endl;
	cout << "-----------------------------" << endl;
	for (size_t i = 1; i < N; i++) {
		cout << (i) << ". " << options[i] << endl;
	}
	cout << "=============================" << endl;
}

#endif