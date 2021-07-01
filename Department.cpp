#pragma once
#include "Department.h"
#include "Course.h"
#include "Student.h"
#include <iostream>
#include <string>


Department::Department() : DepartmentName(string()), DepID(0), StudentAmount(0), FailedStudentAmount(0), CourseAmount(0), CourseList(NULL), StudentList(NULL), FailedStudent(NULL) {}

Department::Department(const Department& other) {
	*this = other; // Use in operator =
}

Department::Department(string DepartmentName, int DepID) : DepartmentName(DepartmentName), DepID(DepID), CourseAmount(0), StudentAmount(0), FailedStudentAmount(0), CourseList(NULL), StudentList(NULL), FailedStudent(NULL) {}

Department& Department::operator = (const Department& object) {
	if (this != &object) {
		this->DepartmentName = object.DepartmentName;
		this->DepID = object.DepID;
		this->StudentAmount = object.StudentAmount;
		this->FailedStudentAmount = object.FailedStudentAmount;
		this->CourseAmount = object.CourseAmount;

		this->CourseList = new Course * [CourseAmount];
		for (int i = 0; i < CourseAmount; i++) {
			this->CourseList[i] = object.CourseList[i];
		}

		this->StudentList = new Student * [StudentAmount];
		for (int i = 0; i < StudentAmount; i++) {
			this->StudentList[i] = object.StudentList[i];
		}

		this->FailedStudent = new Student * [FailedStudentAmount];
		for (int i = 0; i < FailedStudentAmount; i++) {
			this->FailedStudent[i] = object.FailedStudent[i];
		}
	}
	else
		cout << "Self assigment!" << endl;
	return *this;
}

bool Department::operator == (const Department& object)const {
	return this->DepID == object.DepID;
}

Department::~Department() {
	if (CourseList) {
		for (int i = 0; i < CourseAmount; i++)
			delete CourseList[i];
		delete[] CourseList;
	}
	if (StudentList) {
		for (int i = 0; i < StudentAmount; i++)
			delete StudentList[i];
		delete[] StudentList;
	}
	if (FailedStudent) {
		for (int i = 0; i < FailedStudentAmount; i++)
			delete FailedStudent[i];
		delete[] FailedStudent;
	}
}

Course* Department::CourseListArray(int index) {
	if (index >= 0 && index < CourseAmount)
		return CourseList[index];
	else {
		cerr << "Out of boundary of the array" << endl;
		return NULL;
	}
}

Student Department::StudentListArray(int index) {
	if (index >= 0 && index < CourseAmount)
		return *StudentList[index];
	else {
		cerr << "Out of boundary of the array" << endl;
	}
}

string Department::getDepName() {
	return this->DepartmentName;
}

Student** Department::updatefailedStudens() {
	int j = 0;
	if (FailedStudent) {
		delete[] FailedStudent;
		FailedStudentAmount = 0;
	}
	for (size_t i = 0; i < StudentAmount; i++)
	{
		if (StudentList[i]->avg() < 60)
			FailedStudentAmount++;
	}
	FailedStudent = new Student * [FailedStudentAmount];
	for (size_t i = 0; i < StudentAmount; i++)
	{
		if (StudentList[i]->avg() < 60) {
			FailedStudent[j] = StudentList[i];
			j++;
		}
	}
	return FailedStudent;
}

void Department::removeStudentFromCourse() {
	cout << "Enter course's code:" << endl;
	int Coursecode;
	cin >> Coursecode;
	if (findCourse(Coursecode) == -1) {
		cout << "A course with this code not exists." << endl;
		return;
	}
	cout << "Enter student's ID:" << endl;
	string ID;
	cin >> ID;
	if (findStudent(ID) == -1)
	{
		cout << "A Student with this ID not exists." << endl;
		return;
	}
	Student* newStudent = StudentList[findStudent(ID)];
	CourseList[findCourse(Coursecode)]->removeStudent(newStudent);
	cout << "The student was removed successfully" << endl;
}

ostream& operator << (ostream& output, const Department& object) {

	cout << endl << "---------Departments info---------" << endl;
	cout << "Department: ";
	output << object.DepartmentName << ' ' << endl;

	cout << "Department code: ";
	output << object.DepID << ' ' << endl;

	if (object.StudentList) {
		cout << "Students amount: ";
		output << object.StudentAmount << ' ' << endl;
		for (size_t i = 0; i < object.StudentAmount; i++)
		{
			cout << "#" << i + 1 << endl;
			output << *object.StudentList[i] << endl;
		}
	}
	else output << "There are 0 students in the department. " << endl;

	if (object.FailedStudent) {
		cout << "Failed students amount: ";
		output << object.FailedStudentAmount << ' ' << endl;
		for (size_t i = 0; i < object.FailedStudentAmount; i++)
		{
			cout << "#" << i + 1 << endl;
			output << *object.FailedStudent[i] << endl;
		}
	}

	if (object.CourseList) {
		cout << "Courses amount: ";
		output << object.CourseAmount << ' ' << endl;
		for (size_t i = 0; i < object.CourseAmount; i++)
		{
			cout << "#" << i + 1 << endl;
			output << *object.CourseList[i] << endl;
		}
	}
	else output << "There are 0 courses in the department.  " << endl;

	return output;
}

istream& operator >> (istream& input, Department& object) {
	cout << "Enter department's name: " << endl;
	input >> object.DepartmentName;

	cout << "Enter department's id: " << endl;
	input >> object.DepID;

	return input;
}

Student& Department::operator += (Student& object) {
	int count = 0;
	if (object.avg() < 60) {
		FailedStudentAmount++;
		Student** temp = new Student * [FailedStudentAmount];
		for (size_t i = 0; i < FailedStudentAmount - 1; i++)
		{
			*temp[i] = *FailedStudent[i];
			count++;
		}
		*temp[count + 1] = object;

		for (size_t i = 0; i < FailedStudentAmount - 1; i++)
		{
			delete FailedStudent[i];
		}
		delete[] FailedStudent;

		FailedStudent = new Student * [FailedStudentAmount];
		FailedStudent = temp;
	}
	return *FailedStudent[FailedStudentAmount - 1];
}

int Department::getDepID() {
	return this->DepID;
}

void Department::addCourse() {
	Course* newCourse = new Course();
	cin >> *newCourse;
	newCourse->setDepartment(this);
	if (!CourseList) {
		CourseList = new Course * [++CourseAmount];
		CourseList[0] = newCourse;
		return;
	}
	Course** temp = new Course * [++CourseAmount];
	for (size_t i = 0; i < CourseAmount - 1; i++)
	{
		temp[i] = CourseList[i];
	}
	temp[CourseAmount - 1] = newCourse;
	delete[] CourseList;
	CourseList = temp;
}

bool Department::isexist(Course& course) {
	for (size_t i = 0; i < CourseAmount; i++)
	{
		if (CourseList[i] == &course) {
			return true;
		}
	}
	return false;
}

void Department::addStudent() {
	Student* newStudent = new Student();
	cin >> *newStudent;
	newStudent->setDepartment(this);
	if (!StudentList) {
		StudentList = new Student * [++StudentAmount];
		StudentList[0] = newStudent;
		return;
	}

	Student** temp = new Student * [++StudentAmount];
	for (size_t i = 0; i < StudentAmount - 1; i++)
	{
		temp[i] = StudentList[i];
	}
	delete[] StudentList;
	StudentList = temp;
	StudentList[StudentAmount - 1] = newStudent;
}

int Department::findCourse(int index)const {
	for (size_t i = 0; i < CourseAmount; i++)
	{
		if (this->CourseList[i]->getCourseID() == index)
			return i; //exist.
	}
	return -1; //not exist.
}

void Department::registerStudentToCourse() {
	cout << "Enter course's code:" << endl;
	int courseCode;
	cin >> courseCode;
	if (this->findCourse(courseCode) == -1)
	{
		cout << "A Course with this code not exists." << endl;
		return;
	}
	cout << "Student's details:" << endl;
	Student* newStudent = new Student();
	cin >> *newStudent;

	if (this->findStudent(newStudent->getStudentID()) == -1)
	{
		cout << "A Student with this ID not exists." << endl;
		return;
	}
	newStudent = StudentList[findStudent(newStudent->getStudentID())];
	this->CourseList[findCourse(courseCode)]->registerStudentToCourse(newStudent);
}

void Department::gradingStudentsInCourse() {
	cout << "Enter course's code:" << endl;
	int courseCode;
	cin >> courseCode;
	if (this->findCourse(courseCode) == -1)
	{
		cout << "A Course with this code not exists." << endl;
		return;
	}
	CourseList[findCourse(courseCode)]->setGrade();


}

int Department::findStudent(string student_ID) const {
	for (int i = 0; i < StudentAmount; i++)
	{
		if (this->StudentList[i]->getStudentID() == student_ID)
		{
			return i;
		}
	}
	return -1;
}

Course* Department::indexCourse(int index) {
	if (index >= 0 && index < CourseAmount)
		return CourseList[index];
	else {
		cout << "Out of boundary of the array!" << endl;
		return NULL;
	}
}

void  Department::printsStudents() {
	cout << "Please enter student ID:" << endl;

	string studentID;
	cin >> studentID;
	int i = 0;
	if (this->findStudent(studentID) == -1)
	{
		cout << "A student with this ID not exists." << endl;
		return;
	}
	cout << *StudentList[findStudent(studentID)];
}