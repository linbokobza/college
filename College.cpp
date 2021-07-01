#pragma once

#include "College.h"
#include "Department.h"


College::College(const College& other) : CollegeName(other.CollegeName), CollegeID(other.CollegeID), numOfDepartments(other.numOfDepartments), numOfStudents(other.numOfStudents), FailedStudents(other.FailedStudents){
	this->departments = new Department * [numOfDepartments];
	for (int i = 0; i < numOfDepartments; i++) {
		this->departments[i] = other.departments[i];
	}
	this->students = new Student * [numOfStudents];
	for (int i = 0; i < numOfStudents; i++) {
		this->students[i] = other.students[i];
	}
}

College::~College() {
	if (departments) {
		for (int i = 0; i < numOfDepartments; i++)
			delete departments[i];
		delete[] departments;
	}
	if (students) {
		for (int i = 0; i < numOfStudents; i++)
			delete students[i];
		delete[] students;
	}
}

void College::addDepartment()
{
	cout << "Enter department's name:" << endl;
	string name;
	cin >> name;
	cout << "Enter department's code:" << endl;
	int code;
	cin >> code;
	if (code >= 0) {
		if (findDepartment(code) != -1) {
			cout << "A department with this code already exists." << endl;
			return;
		}
		Department* newDepartment = new Department(name, code);
		if (numOfDepartments > 0) {
			Department** temp = new Department * [++numOfDepartments];
			for (int i = 0; i < numOfDepartments - 1; i++) {
				temp[i] = departments[i];
			}
			delete[] departments;
			departments = temp;
		}
		else {
			departments = new Department * [++numOfDepartments];
		}
		departments[numOfDepartments - 1] = newDepartment;
	}
	else {
		cout << "WRONG CODE TYPE" << endl;
		return;
	}
}

int College::findDepartment(int code) const{
	if (code >= 0) {
		for (size_t i = 0; i < numOfDepartments; i++)
		{
			if (departments[i]->getDepID() == code)
				return i; //exist.
		}
	}
	return -1; //not exist.
}

int College::findStudent(string ID) const {
	for (size_t i = 0; i < numOfStudents; i++)
	{
		if (students[i]->getStudentID() == ID)
			return i; //exist.
	}
	return -1; //not exist.
}

void College::addCourseToDepartment() {

	cout << "Enter department's code:" << endl;
	int code;
	cin >> code;
	if (findDepartment(code) == -1) {
		cout << "A department with this code not exists." << endl;
		return;
	}
	departments[findDepartment(code)]->addCourse();
}

void College::addStudentToDepartment() {
	cout << "Enter department's code:" << endl;
	int code;
	cin >> code;
	if (findDepartment(code) == -1) {
		cout << "A department with this code not exists." << endl;
		return;
	}
	departments[findDepartment(code)]->addStudent();
}

void College::addStudentToCollege(Student& newStud) {
	if (numOfStudents > 0) {
		for (int i = 0; i < numOfStudents; i++) {
			if (newStud == *students[i]) {
				cout << "This student is already signed to this college." << endl;
				return;
			}
		}
		Student** temp = new Student * [++numOfStudents];
		for (int i = 0; i < numOfStudents - 1; i++) {
			temp[i] = students[i];
		}
		delete[] students;
		students = temp;
	}
	else {
		students = new Student * [++numOfStudents];
	}
	students[numOfStudents - 1] = new Student(newStud);
}

void College::registerStudentToCourse() {
	cout << "Enter department's code:" << endl;
	int code;
	cin >> code;
	if (findDepartment(code) == -1) {
		cout << "A department with this code not exists." << endl;
	return;
	}
	this->departments[findDepartment(code)]->registerStudentToCourse();
}

void College::printCourseInfo() const {
	cout << "Enter department's code:" << endl;
	int code;
	cin >> code;
	if (findDepartment(code) == -1) {
		cout << "A department with this code not exists." << endl;
		return;
	}
	cout << "Enter course's code:" << endl;
	int Coursecode;
	cin >> Coursecode;
	if (departments[findDepartment(code)]->findCourse(Coursecode) == -1) {
		cout << "A course with this code not exists." << endl;
		return;
	}
	else cout << *this->departments[findDepartment(code)]->CourseListArray(departments[findDepartment(code)]->findCourse(Coursecode));
}

int College::findCourse(int depCode, int courseCode) const {
	if (departments[depCode]->CourseListArray(courseCode)->getCourseID()!=-1)
		return departments[depCode]->CourseListArray(courseCode)->getCourseID(); //exist
	return -1; //not exist.
}

void College::gradingStudentsInCourse() {
	cout << "Enter department's code:" << endl;
	int code;
	cin >> code;
	if (findDepartment(code) == -1) {
		cout << "A department with this code not exists." << endl;
		return;
	}
	departments[findDepartment(code)]->gradingStudentsInCourse();
	
}

void College::printStudentInfo() const {

	cout << "Enter department's code:" << endl;
	int code;
	cin >> code;
	if (findDepartment(code) == -1) {
		cout << "A department with this code not exists." << endl;
		return;
	}
	departments[findDepartment(code)]->printsStudents();
}

void College::printDepartmentInfo() const {
	cout << "Enter department's code:" << endl;
	int code;
	cin >> code;
	if (findDepartment(code) == -1) {
		cout << "A department with this code not exists." << endl;
		return;
	}
	cout << *(this->departments[findDepartment(code)]);
	
}

void College::findStudentsWithBadAcademicStat() {
	cout << "Enter department's code:" << endl;
	int code;
	cin >> code;
	if (findDepartment(code) == -1) {
		cout << "A department with this code not exists." << endl;
		return;
	}
	Student** failedStudentList = departments[findDepartment(code)]->updatefailedStudens();
	int size = departments[findDepartment(code)]->getFailedNum();

	cout << endl << "---------Failed students info---------" << endl;
	for (size_t i = 0; i < size; i++)
	{
		cout << *failedStudentList[i] << endl;
	}
}

void College::removeStudentFromCourse() {
	cout << "Enter department's code:" << endl;
	int code;
	cin >> code;
	if (findDepartment(code) == -1) {
		cout << "A department with this code not exists." << endl;
		return;
	}
	departments[findDepartment(code)]->removeStudentFromCourse();
}

void College::menu()
{
	while (1)
	{
		fflush(stdin);
		cout << "*************************************************************************" << endl;
		cout << "*************************************************************************" << endl;
		cout << "*************************************************************************" << endl;
		cout << "Welcome to sce. What would you like to do?" << endl;
		cout << "*************************************************************************" << endl;
		cout << "[1] - Add a department to the college." << endl;
		cout << "[2] - Add a course to a department." << endl;
		cout << "[3] - Add a student to a department." << endl;
		cout << "[4] - Register a student to a course." << endl;
		cout << "[5] - Grade a course." << endl;
		cout << "[6] - Print a course's information." << endl;
		cout << "[7] - Print a student's information." << endl;
		cout << "[8] - Print a department's information." << endl;
		cout << "[9] - Calculate the students with bad academic status." << endl;
		cout << "[10]- Remove a student from a course." << endl;
		cout << "[11]- Exit." << endl;
		cout << "*************************************************************************" << endl;

		int choice;
		cin >> choice;
		switch (choice)
		{
		case 1:
			addDepartment();
			break;
		case 2:
			addCourseToDepartment();
			break;
		case 3:
			addStudentToDepartment();
			break;
		case 4:
			registerStudentToCourse();
			break;
		case 5:
			gradingStudentsInCourse();
			break;
		case 6:
			printCourseInfo();
			break;
		case 7:
			printStudentInfo();
			break;
		case 8:
			printDepartmentInfo();
			break;
		case 9:
			findStudentsWithBadAcademicStat();
			break;
		case 10:
			removeStudentFromCourse();
			break;
		case 11:
			cout << "Thank you, goodbye." << endl;
			return;
			break;
		default:
			cout << "No such option , sorry. Choose again please." << endl;
		}
	}
}