#include <iostream>
#include <iomanip>
#include "Student.h"



Student::Student()
	:id(EMPTY_ID)
{
}

Student::Student(int id, std::string& name, std::string& major)
	: id(id)
{
	auto nameLength = name.copy(this->name, MAX_NAME_LENGTH);
	this->name[nameLength] = '\0';

	auto majorLength = major.copy(this->major, MAX_MAJOR_LENGTH);
	this->major[majorLength] = '\0';
}


Student::~Student()
{
}

void Student::Print() const
{
	std::cout << std::left
		<< std::setw(ID_PRINT_WIDTH) << id
		<< std::setw(NAME_PRINT_WIDTH) << name
		<< major << '\n';
}

bool Student::IsEmpty() const
{
	return id == EMPTY_ID;
}

int Student::GetId() const
{
	return id;
}
