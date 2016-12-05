#include "actions.h"

#include <iostream>

using namespace std;

void insertStd(){
	StudentTable& table = getStdTable();

	Student student(getValidStdID());

	if (table.find(student)){
		cout << "Student ID already Exist. ";
		hitEnterToContinue();
		return;
	}

	student.name = getValidStdName();
	student.year = getValidYear();
	student.gender = getValidYear();

	table.insert(student);

	cout << "Insertion successful. " << endl;
	hitEnterToContinue();
}

void modifyStd(){
	StudentTable& table = getStdTable();

	Student* student = table.find(getValidStdID());

	if (!student){
		cout << "Student id does not exist.";
		hitEnterToContinue();
		return;
	}

	string input;
	Student newStd = Student(student->id);

	cout << "Enter Student Name[" << student->name << "]: ";
	cin >> input;

	while (!isValidStdName(input)){
		cout << "Invalid. Please input Student name again: ";
		cin >> input;
		cin.ignore();
	}

	newStd.name = input;

	int year;
	cout << "Enter Student Year[" << student->year << "]: ";
	cin >> year;

	while (!isValidYear(year)){
		cout << "Invalid. Please input Student year again: ";
		cin >> year;
		cin.ignore();
	}

	newStd.year = year;

	cout << "Enter Student Gender[" << student->gender << "]: ";
	cin >> input;

	while (input.size()!=1 || !isValidGender(input[0])){
		cout << "Invalid. Please input Student gender again: ";
		cin >> input;
		cin.ignore();
	}

	newStd.gender = input[0];

	table.remove(*student);
	table.insert(newStd);

	cout << "Modification successful. " << endl;
	hitEnterToContinue();
}

void deleteStd(){
	StudentTable& table = getStdTable();

	Student* student = table.find(Student(getValidStdID()));

	if (!student){
		cout << "Student id does not exist.";
		hitEnterToContinue();
		return;
	}

	table.remove(*student);

	cout << "Deletion successful. " << endl;
	hitEnterToContinue();
}

void queryStd(){
	StudentTable& table = getStdTable();

	Student* student = table.find(Student(getValidStdID()));

	if (!student){
		cout << "Student id does not exist.";
		hitEnterToContinue();
	}

	cout << *student << endl;

	hitEnterToContinue();
}

/* ------------------------------- */

void insertCourse(){
	CourseTable& table = getCourseTable();

	Course course(getValidCourseCode());

	if (table.find(course)){
		cout << "Course Code already Exist. ";
		hitEnterToContinue();
		return;
	}

	course.name = getValidCourseName();
	course.credit = getValidCredit();

	table.insert(course);

	cout << "Insertion successful. " << endl;
	hitEnterToContinue();
}

void modifyCourse(){
	CourseTable& table = getCourseTable();

	Course* course = table.find(Course(getValidCourseCode()));

	if (!course){
		cout << "Course code does not exist.";
		hitEnterToContinue();
		return;
	}

	string input;
	Course newCourse = Course(input);

	cout << "Enter Course Name[" << course->name << "]: ";
	cin >> input;

	while (!isValidCourseName(input)){
		cout << "Invalid. Please input Course name again: ";
		cin >> input;
		cin.ignore();
	}

	newCourse.name = input;

	int credit;
	cout << "Enter Course Credit[" << course->credit << "]: ";
	cin >> credit;

	while (!isValidCredit(credit)){
		cout << "Invalid. Please input Course credit again: ";
		cin >> credit;
		cin.ignore();
	}

	newCourse.credit = credit;

	table.remove(*course);
	table.insert(newCourse);

	cout << "Modification successful. " << endl;
	hitEnterToContinue();
}

void deleteCourse(){
	CourseTable& table = getCourseTable();

	Course* course = table.find(Course(getValidCourseCode()));

	if (!course){
		cout << "Course code does not exist.";
		hitEnterToContinue();
		return;
	}

	table.remove(*course);

	cout << "Deletion successful. " << endl;
	hitEnterToContinue();
}

void queryCourse(){
	CourseTable& table = getCourseTable();

	Course* course = table.find(Course(getValidCourseCode()));

	if (!course){
		cout << "Course code does not exist.";
		hitEnterToContinue();
	}

	cout << *course << endl;

	hitEnterToContinue();
}

/* ------------------------------- */

void regCourse(){

}

void dropCourse(){

}

void modifyMark(){

}

void queryRegCourse(){

}

/* ------------------------------- */

void listAllStd(){

}

void listAllCourse(){

}

void listAllCourseOfStd(){

}

void listAllStdOfCourse(){

}

/* ------------------------------- */

void saveToDB(){

}

void loadFromDB(){

}

void hitEnterToContinue(){
	cout << "Hit ENTER to continue. "<< endl;
	cin.ignore();
	cin.get();
}
