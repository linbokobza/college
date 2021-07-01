#pragma once
#include "Student.h"
#include "Course.h"
#include "Department.h"
#include <iostream>
#include <string>

Student::Student() : StudentName(string()), ID("0"), Gender('M'), age(0), CourseNum(0), CourseList(NULL), Dep(NULL) {}

Student::Student(string StudentName, string ID, char Gender, int age, int CourseNum, Course** CourseList, Department* Dep) {
	this->CourseNum = CourseNum;
	this->CourseList = new Course * [CourseNum];
	for (size_t i = 0; i < CourseNum; i++)
	{
		this->CourseList[i] = CourseList[i];
	}
	this->Dep = new Department;
	this->Dep = Dep;

	for (int i = 0; i < this->ID.length(); i++)
	{
		if (this->ID[i] >= 0 && this->ID[i] < 10)
			this->ID = ID;
		else {
			cout << "Please try again!" << endl;
			exit(1);
		}
	}
	for (int i = 0; i < this->StudentName.length(); i++)
	{
		if ((this->StudentName[i] >= 'A' && this->ID[i] <= 'Z') || (this->StudentName[i] >= 'a' && this->ID[i] <= 'z'))
			this->StudentName = StudentName;
		else {
			cout << "Please try again!" << endl;
			exit(1);
		}
	}
	if (this->Gender == 'F' || this->Gender == 'M')
		this->Gender = Gender;
	else {
		cout << "Please try again!" << endl;
		exit(1);
	}
	if (this->age > 0)
		this->age = age;
	else {
		cout << "Please try again!" << endl;
		exit(1);
	}
}

Student::Student(const Student& other) : StudentName(other.StudentName), ID(other.ID), Gender(other.Gender), age(other.age), CourseNum(other.CourseNum) {
	this->Dep = other.Dep;
	if (CourseNum > 0) {
		this->CourseList = new Course * [CourseNum];
		for (int i = 0; i < CourseNum; i++) {
			this->CourseList[i] = new Course[CourseNum];
			CourseList[i] = other.CourseList[i];
		}
	}
	else
		CourseList = NULL;
}

Student::~Student() {
	if (CourseList) {
		for (int i = 0; i < CourseNum; i++)
			delete CourseList[i];
		delete[] CourseList;
	}
	if (Dep)
		delete[] Dep;
}

Student& Student::operator = (const Student& object) {
	if (this != &object) {
		this->StudentName = object.StudentName;
		this->ID = object.ID;
		this->Gender = object.Gender;
		this->age = object.age;
		this->CourseNum = object.CourseNum;
		this->Dep = object.Dep;
		if (CourseNum > 0) {
			this->CourseList = new Course * [CourseNum];
			for (int i = 0; i < CourseNum; i++) {
				this->CourseList[i] = new Course[CourseNum];
				CourseList[i] = object.CourseList[i];
			}
		}
		else
			CourseList = NULL;
	}
	return *this;
}

bool Student::operator == (const Student& object)const {
	return this->ID == object.ID;
}

ostream& operator << (ostream& output, const Student& object) {
	cout << endl << "--------Students info--------" << endl;

	cout << "Name: ";
	output << object.StudentName << ' ' << endl;

	cout << "ID: ";
	output << object.ID << ' ' << endl;

	cout << "Gender: ";
	output << object.Gender << ' ' << endl;

	cout << "Age: ";
	output << object.age << ' ' << endl;

	if (object.Dep)
		output << "Department: " << object.Dep->getDepName() << endl;
	else if (object.Dep == NULL)
		output << "The student is not registered to any department." << endl;

	if (object.CourseList)
	{
		for (int i = 0; i < object.CourseNum; i++) {
			output << "Course name: " << object.CourseList[i]->getCourseName() << ' ' << endl;
			output << "Course number: " << object.CourseList[i]->getCourseID() << ' ' << endl;
		}
	}
	else cout << "The student is not registered to any courses." << endl;
	return output;
}

string Student::getName() {
	return StudentName;
}

void Student::removeCourseFromList(Course* course) {
	if (CourseNum > 0) {
		Course** temp = new Course * [--CourseNum];
		for (size_t i = 0; i < CourseNum; i++)
		{
			if (CourseList[i] == course)
				temp[i] = CourseList[i];
		}
		delete[] CourseList;
		CourseList = temp;
	}
}

bool Student::checkName(const string name)const {
	int count = 0;
	for (int i = 0; i < this->StudentName.length(); i++)
		if (isalpha(name[i]))
			count++;

	if (count == name.length())
		return true;

	cout << "Please try again!" << endl;
	return false;
}

bool Student::checkID(const string ID)const {
	int count = 0;
	for (int i = 0; i < ID.length(); i++)
		if (!(isalpha(ID[i])))
			count++;

	if (count == ID.length())
		return true;

	cout << "Please try again!" << endl;
	return false;
}

bool Student::checkGender(const char Gender)const {

	if (!((Gender == 'F' || Gender == 'M') || (Gender == 'f' || Gender == 'm'))) {
		cout << "Please try again!" << endl;
		return false;
	}
	return true;
}

bool Student::checkAge(const int age)const {

	if (age < 0) {
		cout << "Please try again!" << endl;
		return false;
	}
	return true;
}

istream& operator >> (istream& input, Student& object) {
	input.ignore(INT_MAX, '\n');

	//student name
	do {
		cout << "Enter student's name: " << endl;
		getline(input, object.StudentName);

	} while (object.checkName(object.StudentName) == false);

	//student ID
	do {
		cout << "Enter student's id: " << endl;
		input >> object.ID;
	} while (object.checkID(object.ID) == false);

	//gender
	do {
		cout << "Enter student's gender <F-female/M-male>: " << endl;
		input >> object.Gender;
	} while (object.checkGender(object.Gender) == false);

	//age
	do {
		cout << "Enter student's age: " << endl;
		input >> object.age;
	} while (object.checkGender(object.Gender) == false);

	return input;
}

float Student::avg() {
	int sum = 0;
	if (CourseNum == 0)
		return 0;
	else {
		for (int i = 0; i < this->CourseNum; i++)
			sum += this->CourseList[i]->StudentGrades(*this);
		return (float)(sum / CourseNum);
	}
}

void Student::addCourseToList(Course* course) {
	if (CourseNum > 0)
	{
		Course** temp = new Course * [++CourseNum];
		for (int i = 0; i < this->CourseNum - 1; i++)
		{
			temp[i] = CourseList[i];
		}
		delete[] CourseList;
		CourseList = temp;
	}
	else {
		CourseList = new Course * [++CourseNum];
	}
	CourseList[CourseNum - 1] = course;
}
