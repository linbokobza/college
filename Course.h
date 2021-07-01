#pragma once
#include <iostream>
#include "Student.h"

using namespace std;

class Student;
class Department;
class College;

class Course {
	string CourseName;
	int CourseNum;
	Student** StudentList;
	int StudentNum;
	int* Grade;
	Department* Dep;

public:
	Course();
	Course(string CourseName, int CourseNum, Student** StudentList, int StudentNum, int* Grade, Department* Dep);
	Course(const Course& other);
	~Course();
	bool operator == (const Course& object)const;
	Course& operator = (const Course& object);
	Student& operator [] (int index);
	friend istream& operator >> (istream&, Course&);
	friend ostream& operator << (ostream&, const Course&);
	void printStudentGrades() const;
	void registerStudentToCourse(Student* student);
	int StudentGrades(const Student& student)const;
	int getStudentGrades(string ID);
	int getCourseID();
	int registerStudent(Student& obj);
 	void printCourse(const Course& obj)const;
	int findStudent(string ID) const;
	void setGrade();
	string getCourseName();
	void setDepartment(Department* department) { Dep = department; }
	void removeStudent(Student* student);
	int getGrade();

};
