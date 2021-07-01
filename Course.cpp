#pragma once
#include "Course.h"
#include "Student.h"
#include "Department.h"
#include <iostream>
#include <string>

Course::Course() : CourseName(string()), CourseNum(0), StudentList(NULL), StudentNum(0), Grade(NULL), Dep(NULL){}

Course::Course(string CourseName, int CourseNum, Student** StudentList, int StudentNum, int* Grade, Department* Dep) {
	this->CourseName = CourseName;
	this->CourseNum = CourseNum;
	this->StudentNum = StudentNum;
	if (this->StudentNum > 0) {
		this->Grade = Grade;
		this->Grade = new int[StudentNum];
		this->StudentList = new Student * [StudentNum];
		for (int i = 0; i < StudentNum; i++) {
			this->StudentList[i] = StudentList[i];
			this->Grade[i] = Grade[i];
		}
	}
	else this->Grade = NULL;
	this->Dep = new Department;
	this->Dep = Dep;
}

Course::Course(const Course& other) {
	*this = other; // Use in operator =
}

Course::~Course() {
	if (StudentList) {
		for (int i = 0; i < StudentNum; i++)
			delete StudentList[i];
		delete[] StudentList;
	}
	if (Grade) 
		delete[] Grade;
	if (Dep)
		delete[] Dep;
}

Course& Course::operator = (const Course & object) {

	if (this != &object) {

		this->CourseName = object.CourseName;
		this->CourseNum = object.CourseNum;
		this->StudentNum = object.StudentNum;
		this->Grade = new int[StudentNum];
		this->StudentList = new Student * [StudentNum];
		for (int i = 0; i < StudentNum; i++) {
			this->Grade[i] = object.Grade[i];
			this->StudentList[i] = object.StudentList[i];
		}
		this->Dep = new Department;
		this->Dep = object.Dep;
	}
	else
		cout << "Self assigment!" << endl;
	return *this;
}

bool Course::operator == (const Course& object)const {
	return this->CourseNum == object.CourseNum;
}

Student& Course::operator [] (int index) {
	if(index>=0 && index < StudentNum)
		return *StudentList[index];
	else {
		cerr << "Out of boundary of the array " << endl;
		exit(1);
	}
}

void Course::printStudentGrades() const
{
	if (StudentNum == 0)
		cout << "No students in this course. " << endl;
	else {
		cout << "-----Student's grade-----" << endl;
		for (int i = 0; i < StudentNum; i++) {
			cout << StudentList[i]->getName() << " : " << Grade[i] << endl;

		}
	}
}

ostream& operator << (ostream& output, const Course& object) {
	cout << endl << "---------Courses info---------" << endl;

	cout << "Course name: ";
	output << object.CourseName << ' ' << endl;

	cout << "Course ID: ";
	output << object.CourseNum << ' ' << endl;

	if (object.Dep) {
		cout << "Course department:" << object.Dep->getDepName() << endl;
		cout << "Number of students in course: ";
		output << object.StudentNum << ' ' << endl;
	}
	else {
		cout << "The course is a general course and not belong to any department yet" << endl;
	}

	if (object.StudentList != nullptr)
	{
		object.printStudentGrades();
	}
	else cout << "There is no student in this course" << endl;
	return output;
}

int Course::getGrade() {
	return Grade[0];
}

istream& operator >> (istream& input, Course& object) {

	input.ignore(INT_MAX, '\n');
	cout << "Enter course's name: " << endl;
	getline(input, object.CourseName);
	cout << endl;

	cout << "Enter course's id: " << endl;
	input >> object.CourseNum;
	return input;
}

int Course::getCourseID() {
	return this->CourseNum;
}

string Course::getCourseName() {
	return this->CourseName;
}

int Course::getStudentGrades(string ID) {
	for (size_t i = 0; i < StudentNum; i++)
	{
		if (ID == StudentList[i]->getStudentID())
			return Grade[i];
	}
}

void Course::removeStudent(Student* student) {

	student->removeCourseFromList(this);
	if (StudentNum > 0) {
		Student** newStudentList = new Student * [--StudentNum];
		int* newGrade = new int[StudentNum];
		for (size_t i = 0; i < StudentNum; i++)
		{
			if(StudentList[i]== student)
			{
				newStudentList[i] = StudentList[i];
				if(Grade!=NULL)
					newGrade[i] = Grade[i];
			}
		}
		delete[] StudentList;
		StudentList = newStudentList;
		delete[] Grade;
		Grade = newGrade;
	}

}

int Course::StudentGrades(const Student& student)const {
	for (size_t i = 0; i < StudentNum; i++)
	{
		if (&student == this->StudentList[i])
			return Grade[i];
	}
}

void Course::setGrade() {
	cout << "Enter Student's ID:" << endl;
	string studentID;
	cin >> studentID;
	if (findStudent(studentID) == -1)
	{
		cout << "A Student with this ID not exists, TRY AGAIN." << endl;
		return;
	}
	cout << "Enter Grade:" << endl;
	int grade;
	cin >> grade;
	while (grade > 100 || grade < 0)
	{
		cout << "out of range, TRY AGAIN" << endl;
		cin >> grade;
	}

	Grade = new int[StudentNum];
	Grade[findStudent(studentID)] = grade;
}

int Course::registerStudent(Student& obj) {
	if (!StudentList) {
		StudentList = new Student * [++StudentNum];
		StudentList[0] = &obj;
		Grade[0] = 0;
		return 0;
	}
	Student** temp = new Student * [++StudentNum];
	for (int i = 0; i < StudentNum - 1; i++) {
		temp[i] = StudentList[i];
	}
	delete[] StudentList;
	StudentList = temp;
	StudentList[StudentNum - 1] = &obj;
}

void Course::registerStudentToCourse(Student* obj) {
	obj->addCourseToList(this);
	if (StudentNum > 0)
	{
		Student** temp = new Student * [++StudentNum];
		for (int i = 0; i < StudentNum - 1; i++)
		{
			temp[i] = StudentList[i];
		}
		delete[] StudentList;
		StudentList = temp;
	}
	else {
		StudentList = new Student * [++StudentNum];
	}
	StudentList[StudentNum - 1] = obj;
}

int Course::findStudent(string ID) const {
	for (int i = 0; i < StudentNum; i++)
	{
		if (StudentList[i]->getStudentID() == ID)
		{
			return i;
		}
	}
	return -1;
}

void Course::printCourse(const Course &obj)const {
	cout << obj;
}

