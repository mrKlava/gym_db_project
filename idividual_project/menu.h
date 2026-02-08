#ifndef MENU_H
#define MENU_H

#pragma once
#include <iostream>
#include <string>

#include "types.h"

using namespace std;

/* CONSTANTS - Messages */
const char INPUT_PROVIDE_CHOICE[] = "Please enter your choice: ";
const char INPUT_PROVIDE_ID[] = "Please enter ID: ";

const char INPUT_INVALID_CHOICE_MSG[] = "Invalid choice. Please try again.";

const char INPUT_NOT_FOUND[] = "Not Found.";
const char INPUT_EXIT_MSG[] = "Exiting the program.";

const char TEXT_CLIENT[] = "Client";
const char TEXT_CLIENT_ID[] = "Client ID";
const char TEXT_CLIENT_NAME[] = "Client Name";
const char TEXT_CLIENT_GENDER[] = "Client Gender";

const char TEXT_INSTRUCTOR[] = "Instructor";
const char TEXT_INSTRUCTOR_ID[] = "Instructor ID";
const char TEXT_INSTRUCTOR_NAME[] = "Instructor Name";
const char TEXT_INSTUCTOR_GENDER[] = "Instructor Gender";

const char TEXT_SESSION[] = "Training Session";
const char TEXT_SESSION_ID[] = "Training Session ID";
const char TEXT_SESSION_PRICE[] = "Training Session Price";
const char TEXT_SESSION_DATE[] = "Date";

const string MENU_SORT_BY_TITLE = "Sort By:";

const string MENU_TITLE = "Menu:";
const string MENU_VIEW_TITLE = "View Menu:";
const string MENU_SORT_TITLE = "Sort Menu:";
const string MENU_FILTER_TITLE = "Filter Menu:";
const string MENU_SEARCH_TITLE = "Search Menu:";


/* MAIN MENU */
void menu();

/* PRINTING UTILS */
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