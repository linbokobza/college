#pragma once
#include <iostream>
using namespace std;

class Course;
class Student; 
class College;

class Department {
	string DepartmentName;
	int DepID;
	int CourseAmount;
	Course** CourseList;
	Student** StudentList;
	int StudentAmount;
	Student** FailedStudent;
	int FailedStudentAmount;

public:
	Department();
	Department(string DepartmentName, int DepID);
	Department(const Department& other);
	~Department();
	Department& operator = (const Department& object);
	bool operator == (const Department& object)const;
	Course* CourseListArray(int index); 
	Student StudentListArray(int index);
	friend ostream& operator << (ostream& output, const Department& object);
	friend istream& operator >> (istream& input, Department& object);
	Student& operator += (Student& object);
	int getDepID();
	void addCourse();
	void addStudent();
	bool isexist(Course& course);
	int getCourseAmount() { return CourseAmount; }
	int getStudentAmount() { return StudentAmount; }
	void printsStudents();
	void registerStudentToCourse();
	int findCourse(int index)const ;
	int findStudent(string student_ID) const;
	void gradingStudentsInCourse();
	string getDepName();
	Course* indexCourse(int index);
	Student** updatefailedStudens();
	int getFailedNum() { return FailedStudentAmount; }
	void removeStudentFromCourse();
};