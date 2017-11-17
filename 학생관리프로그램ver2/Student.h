#pragma once
#include "Common.h"

class Student
{
public:
	Student();
	Student(int id, std::string& name, std::string& major);
	~Student();

	void Print() const;

	bool IsEmpty() const;

	int GetId() const;

private:
	int id;
	char name[MAX_NAME_LENGTH + 1];
	char major[MAX_MAJOR_LENGTH + 1];
};

