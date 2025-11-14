#ifndef MENU_CLIENTS_H
#define MENU_CLIENTS_H

#include "types.h"

void menu_clients();

void menu_view_clients();

void menu_sort_id_clients();
void menu_sort_name_clients();

void menu_filter_gender_clients();
void menu_search_clients();

void menu_add_clients();
void menu_delete_clients();

void print_table_clients();
void print_table_clients_by_gender(Gender gender_filter);
void print_search_clients_by_id(int id);
void print_search_clients_by_name();

Client get_client();

#endif