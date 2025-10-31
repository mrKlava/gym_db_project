#ifndef UI_H
#define UI_H

#include "types.h"

void menu();
void menu_istructors();
void menu_clients();
void menu_trainig_sessions();

void print_table_instructors();

Instructor& get_instructor();
void delete_instructor();

void get_input_string(const char* prompt, char* destination, int length);
Gender get_input_gender();

int get_input_positive_int(const char* prompt);

#endif