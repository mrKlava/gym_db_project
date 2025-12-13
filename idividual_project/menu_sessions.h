#ifndef MENU_SESSIONS_H
#define MENU_SESSIONS_H

#include "types.h"

void menu_sessions();

void menu_view_sessions();

void menu_sort_id_sessions();
void menu_sort_client_sessions();
void menu_sort_instructor_sessions();
void menu_sort_price_sessions();
void menu_sort_date_sessions();

void menu_filter_sessions();
void menu_search_sessions();

void menu_add_session();
void menu_delete_sessions();

void print_table_sessions();
void print_table_sessions_by_client(int client_filter);
void print_table_sessions_by_instructor(int instructor_filter);
void print_search_session_by_id(int id);

TrainingSession get_session();

#endif