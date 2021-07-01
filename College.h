#ifndef __COLLEGE_H
#define __COLLEGE_H

#include <iostream>
#include <string>
#include "Student.h"
#include "Course.h"
#include "Department.h"
using namespace std;

class Department;
class Course;
class Department;

class College
{
	string CollegeName;
	int CollegeID;
	Department** departments;
	int numOfDepartments;
	Student** students;
	int numOfStudents;
	int FailedStudents;

	void addDepartment();
	void addCourseToDepartment();
	void addStudentToDepartment();
	void registerStudentToCourse();
	void gradingStudentsInCourse();
	void printCourseInfo() const;
	void printStudentInfo() const;
	void printDepartmentInfo() const;
	void findStudentsWithBadAcademicStat();
	void removeStudentFromCourse();
	int findDepartment(int code) const;
	void addStudentToCollege(Student& newStud);
	int findCourse(int depCode, int courseCode) const;
	int findStudent(string ID) const;
public:

	College() :CollegeName(string()), CollegeID(0), departments(NULL), numOfDepartments(0), students(NULL), numOfStudents(0), FailedStudents(0){}
	College(const College&);
	~College();
	College& operator=(const College& other);
	void menu();
};

#endif