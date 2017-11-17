#pragma once
#include <fstream>

class Student;

class App
{
public:
	App();
	~App();
	void Run();

private:
	std::fstream file;

	void MakeEmptyFile();
	void PrintMenu();
	void PrintFields() const;
	void WriteStudent(const Student& student);
	void DeleteStudent(int id);

	void HandleAdd();
	void HandlePrintAll();
	void HandleDelete();
	void HandleFind();
	void HandleReset();

	int HandleInputId() const;

	bool IsValidId(int id) const;
	bool HaveStudent(int id);

	Student ReadStudent(int id);
};


