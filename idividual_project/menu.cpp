#include "utils_input.h"

#include "menu.h"
#include "menu_istructors.h"
#include "menu_clients.h"
#include "menu_sessions.h"

const string MENU_ORIGIN = "Main";

const string MENU_OPTIONS[] = {
	"Instructors",
	"Clients",
	"Training Sessions",
	"Exit"
};

void menu() {
	while (true) {
		print_menu_options(MENU_TITLE + MENU_ORIGIN, MENU_OPTIONS);

		int choice = get_input_positive_int(INPUT_PROVIDE_CHOICE);

		switch (choice) {
		case 1: {
			menu_istructors();

			break;
		}
		case 2: {
			menu_clients();

			break;
		}
		case 3: {
			menu_sessions();

			break;
		}
		case 4:
			cout << INPUT_EXIT_MSG << endl;
			return;
		default:
			cout << INPUT_INVALID_CHOICE_MSG << endl;
		}
	}
}
