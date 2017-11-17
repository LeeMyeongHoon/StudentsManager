#pragma once
#include <cassert>

inline namespace forAll
{
	const int BEGIN_ID = 1;
	const int END_ID = 1001;
	const int EMPTY_ID = 0;


}

inline namespace forApp
{
	enum MainMenu
	{
		PRINT_ALL, ADD, DELETE, FIND, MODIFY, RESET, EXIT, MAIN_MENU_COUNT
	};
	static char* const MENU_STRINGS[] =
	{
		"Print ALl", "Add", "Delete", "Find", "Modify", "Reset", "Exit"
	};

	static char* const DATA_FILE_NAME = "students.dat";
}

inline namespace forStudent
{
	const int MAX_NAME_LENGTH = 12;
	const int MAX_MAJOR_LENGTH = 15;

	const int ID_PRINT_WIDTH = 5;
	const int MAJOR_PRINT_WIDTH = MAX_MAJOR_LENGTH + 2;
	const int NAME_PRINT_WIDTH = MAX_NAME_LENGTH + 2;
}
