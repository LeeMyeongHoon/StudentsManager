#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

#include "App.h"
#include "Common.h"
#include "Student.h"

App::App()
{
}


App::~App()
{
	if (file.is_open())
	{
		file.close();
	}

}

void App::Run()
{
	file.open(DATA_FILE_NAME, std::ios::binary | std::ios::out | std::ios::in);
	if (!file)
	{
		MakeEmptyFile();
		file.open(DATA_FILE_NAME, std::ios::binary | std::ios::out | std::ios::in);
	}

	bool exit = false;
	while (!exit)
	{
		PrintMenu();
		std::cout << "your input : ";

		MainMenu mainMenu;
		std::cin >> (int&)mainMenu;
		switch (mainMenu)
		{
		case PRINT_ALL:
			HandlePrintAll();
			break;
		case ADD:
			HandleAdd();
			break;
		case DELETE:
			HandleDelete();
			break;
		case FIND:
			HandleFind();
			break;
		case MODIFY:
			break;
		case RESET:
			HandleReset();
			break;
		case EXIT:
			exit = true;
			break;
		default:
			break;
		}
	}
}

void App::MakeEmptyFile()
{
	file.open(DATA_FILE_NAME, std::ios::out);
	HandleReset();
	file.close();
}

void App::PrintMenu()
{
	system("cls");
	for (int i = 0; i < MAIN_MENU_COUNT; i++)
	{
		std::cout << '[' << i << "] " << MENU_STRINGS[i] << '\n';
	}
	std::cout << '\n';
}

void App::PrintFields() const
{
	std::cout << std::left
		<< std::setw(ID_PRINT_WIDTH) << "ID"
		<< std::setw(NAME_PRINT_WIDTH) << "Name"
		<< "Major" << '\n';
}

void App::HandleAdd()
{
	std::cout << "id : (" << BEGIN_ID << " ~ " << END_ID - 1 << "), name, major :\n";

	int id = HandleInputId();
	if (id == -1)
	{
		return;
	}
	if (HaveStudent(id))
	{
		std::cout << "Error : there is already a student with the id.\n";
		system("PAUSE");
		return;
	}

	std::string name, major;

	std::cin >> name >> major;
	if (name.size() > MAX_NAME_LENGTH || major.size() > MAX_MAJOR_LENGTH)
	{
		std::cout << "Error : too long name or major\n";
		system("PAUSE");
		return;
	}

	WriteStudent(Student(id, name, major));
	std::cout << "Success\n";
	system("PAUSE");

}

void App::HandlePrintAll()
{
	std::cout << '\n';
	PrintFields();
	for (int id = BEGIN_ID; id < END_ID; id++)
	{
		Student student = ReadStudent(id);
		if (!student.IsEmpty())
		{
			student.Print();
		}
	}
	std::cout << '\n';
	system("PAUSE");
}

void App::HandleDelete()
{
	std::cout << "id : (" << BEGIN_ID << " ~ " << END_ID - 1 << "), name, major :\n";
	int id = HandleInputId();

	if (id == -1)
	{
		return;
	}

	if (HaveStudent(id) == false)
	{
		std::cout << "Error : there isn't a student with the id.\n";
		system("PAUSE");
		return;
	}

	DeleteStudent(id);
	std::cout << "Success" << '\n';
	system("PAUSE");
}

void App::HandleFind()
{
	std::cout << "id : ";
	int id = HandleInputId();
	if (id == -1)
	{
		return;
	}

	Student student = ReadStudent(id);
	if (student.IsEmpty())
	{
		std::cout << "Error : there isn't a student with the id.\n";
		system("PAUSE");
		return;
	}
	student.Print();
	system("PAUSE");
}

void App::HandleReset()
{
	file.seekp(0);
	for (size_t i = EMPTY_ID; i < END_ID; i++)
	{
		Student emptyStudent;
		file.write((char*)&emptyStudent, sizeof(Student));
	}
	std::cout << "Success\n";
	system("PAUSE");
}

int App::HandleInputId() const
{
	int id;
	std::cin >> id;
	if (std::cin.fail())
	{
		std::cout << "Error : you should input a integer for id.\n";
		std::cin.clear();
		std::cin.ignore(INT64_MAX, '\n');
		system("PAUSE");
		return -1;
	}
	if (!IsValidId(id))
	{
		std::cout << "Error : invalid range\n";
		system("PAUSE");
		return -1;
	}
	return id;
}

Student App::ReadStudent(int id)
{
	Student student;
	file.seekg(sizeof(Student) * id);
	file.read((char*)&student, sizeof(Student));

	return student;
}

void App::WriteStudent(const Student& student)
{
	file.seekp(sizeof(Student) * student.GetId());
	file.write((char*)&student, sizeof(Student));
}

void App::DeleteStudent(int id)
{
	file.seekp(sizeof(Student)*id);
	Student emptyStudent;
	file.write((char*)&emptyStudent, sizeof(Student));
}

bool App::IsValidId(int id) const
{
	return id >= BEGIN_ID && id < END_ID;
}

bool App::HaveStudent(int id)
{
	return !ReadStudent(id).IsEmpty();
}
