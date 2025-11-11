#ifndef MENU_INSTRUCTORS_H
#define MENU_INSTRUCTORS_H

#include "types.h"

void menu_istructors();

void menu_view_instructors();

void menu_sort_id_instructors();
void menu_sort_name_instructors();

void menu_filter_gender_instructors();
void menu_search_instructors();

void menu_add_insrtuctors();
void menu_delete_istructors();

void print_table_instructors();
void print_table_instructors_by_gender(Gender gender_filter);
void print_search_instructors_by_id(int id);
void print_search_instructors_by_name();

Instructor get_instructor();

#endif