#pragma once
#include <iostream>
using namespace std;

class Course;
class Department;
class College;

class Student {
	string StudentName;
	string ID;
	char Gender;
	int age;
	Course** CourseList;
	int CourseNum;
	Department* Dep;

public:
	Student();
	Student(string StudentName, string ID, char Gender, int age, int CourseNum, Course** CourseList, Department* Dep);
	Student(const Student& other);
	~Student();
	Student& operator = (const Student& object);
	bool operator == (const Student& object)const;
	friend ostream& operator << (ostream& output, const Student& object);
	friend istream& operator >> (istream& input, Student& object);
	void setDepartment(Department* department) { Dep = department; }
	float avg();
	void addCourseToList(Course* course);
	string getStudentID() {return this->ID;}
	bool checkName(const string name)const;
	bool checkID(const string ID)const;
	bool checkGender(const char Gender)const;
	bool checkAge(const int age)const;
	void removeCourseFromList(Course* course);
	string getName();
	//
};