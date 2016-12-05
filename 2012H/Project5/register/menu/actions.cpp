#include "actions.h"

#include <iostream>
#include <fstream>
#include <stdio.h>

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
	student.gender = getValidGender();

	table.insert(student);
	StudentKeyTable& keyTable = getStdKeyTable();
	keyTable.insert(StudentKey(student));

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
	StudentKeyTable& keyTable = getStdKeyTable();
	keyTable.remove(StudentKey(*student));

	cout << "Deletion successful. " << endl;
	hitEnterToContinue();
}

void queryStd(){
	StudentTable& table = getStdTable();

	Student* student = table.find(Student(getValidStdID()));

	if (!student){
		cout << "Student id does not exist.";
		hitEnterToContinue();
		return;
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
	CourseKeyTable& keyTable = getCourseKeyTable();
	keyTable.insert(CourseKey(course));

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
	CourseKeyTable& keyTable = getCourseKeyTable();
	keyTable.remove(CourseKey(*course));

	cout << "Deletion successful. " << endl;
	hitEnterToContinue();
}

void queryCourse(){
	CourseTable& table = getCourseTable();

	Course* course = table.find(Course(getValidCourseCode()));

	if (!course){
		cout << "Course code does not exist.";
		hitEnterToContinue();
		return;
	}

	cout << *course << endl;

	hitEnterToContinue();
}

/* ------------------------------- */

void regCourse(){
	SelectionList& mList = getCourseSelectionList();
	StudentTable& stdTable = getStdTable();
	CourseTable& courseTable = getCourseTable();

	Student* student = stdTable.find(getValidStdID());

	if (!student){
		cout << "Student id does not exist.";
		hitEnterToContinue();
		return;
	}

	Student copyOfStd(*student);
	student = &copyOfStd;

	Course* course = courseTable.find(getValidCourseCode());

	if (!course){
		cout << "Course code does not exist.";
		hitEnterToContinue();
		return;
	}

	Course copyOfCourse(*course);
	course = &copyOfCourse;

	StudentKeyTable& stdKeyTable = getStdKeyTable();
	CourseKeyTable& courseKeyTable = getCourseKeyTable();

	StudentKey* stdKey = stdKeyTable.find(StudentKey(*student));

	CourseSelection selection(*student, *course);

	if (mList.contains(selection)){
		cout << "Student already registered this course." << endl;
		hitEnterToContinue();
		return;
	}

	mList.insert(selection);

	stdKey->insert(&selection);

	CourseKey* courseKey = courseKeyTable.find(CourseKey(*course));
	
	courseKey->insert(&selection);

	cout << "Add course successful." << endl; 
	hitEnterToContinue();
}

void dropCourse(){
	SelectionList& mList = getCourseSelectionList();
	StudentTable& stdTable = getStdTable();
	CourseTable& courseTable = getCourseTable();

	Student* student = stdTable.find(getValidStdID());

	if (!student){
		cout << "Student id does not exist.";
		hitEnterToContinue();
		return;
	}

	Student copyOfStd(*student);
	student = &copyOfStd;

	Course* course = courseTable.find(getValidCourseCode());

	if (!course){
		cout << "Course code does not exist.";
		hitEnterToContinue();
		return;
	}

	Course copyOfCourse(*course);
	course = &copyOfCourse;

	StudentKeyTable& stdKeyTable = getStdKeyTable();
	CourseKeyTable& courseKeyTable = getCourseKeyTable();
	StudentKey* stdKey = stdKeyTable.find(StudentKey(*student));

	CourseSelection selection(*student, *course);

	if (!mList.contains(selection)){
		cout << "Student did not register this course." << endl;
		hitEnterToContinue();
		return;
	}

	CourseKey* courseKey = courseKeyTable.find(CourseKey(*course));
	stdKey->remove(&selection);
	courseKey->remove(&selection);
	mList.remove(selection);

	cout << "Drop course successful." << endl; 
	hitEnterToContinue();
}

void modifyMark(){
	SelectionList& mList = getCourseSelectionList();
	StudentTable& stdTable = getStdTable();
	CourseTable& courseTable = getCourseTable();

	Student* student = stdTable.find(getValidStdID());

	if (!student){
		cout << "Student id does not exist.";
		hitEnterToContinue();
		return;
	}

	Student copyOfStd(*student);
	student = &copyOfStd;

	Course* course = courseTable.find(getValidCourseCode());

	if (!course){
		cout << "Course code does not exist.";
		hitEnterToContinue();
		return;
	}

	Course copyOfCourse(*course);
	course = &copyOfCourse;

	StudentKeyTable& stdKeyTable = getStdKeyTable();
	StudentKey* stdKey = stdKeyTable.find(StudentKey(*student));

	CourseSelection selection(*student, *course);

	CourseSelection* found = mList.get(selection);
	if (!found){
		cout << "Student did not register this course." << endl;
		hitEnterToContinue();
		return;
	}

	found->mark = getValidExamMark();

	cout << "Change mark successful." << endl; 
	hitEnterToContinue();
}

void queryRegCourse(){
	SelectionList& mList = getCourseSelectionList();
	StudentTable& stdTable = getStdTable();
	CourseTable& courseTable = getCourseTable();

	Student* student = stdTable.find(getValidStdID());

	if (!student){
		cout << "Student id does not exist.";
		hitEnterToContinue();
		return;
	}

	Student copyOfStd(*student);
	student = &copyOfStd;

	Course* course = courseTable.find(getValidCourseCode());

	if (!course){
		cout << "Course code does not exist.";
		hitEnterToContinue();
		return;
	}

	Course copyOfCourse(*course);
	course = &copyOfCourse;

	StudentKeyTable& stdKeyTable = getStdKeyTable();
	StudentKey* stdKey = stdKeyTable.find(StudentKey(*student));

	CourseSelection selection(*student, *course);

	CourseSelection* found = mList.get(selection);
	if (!found){
		cout << "Student did not register this course." << endl;
		hitEnterToContinue();
		return;
	}

	cout << *found << endl;
	hitEnterToContinue();
}

/* ------------------------------- */


void listAllStd(){
	ofstream myfile ("Students.html");
	if (myfile.is_open()){
		myfile << "<HTML>\n"
					"<HEAD>\n"
					"<HEAD>\n"
					"<TITLE>All Students List</TITLE>\n"
					"</HEAD>\n"
					"<BODY bgColor=#ffffcc>\n"
					"<H1><FONT color=#6600ff>HKUST Course Registration System</FONT></H1>\n"
					"<H2>All Students List</H2>\n";

		//If the table is not empty
		if (getStdTable().begin().notEnd()){
			myfile << "<P>\n"
						"<TABLE cellSpacing=1 cellPadding=1 border=1>\n"
						"\n"
						"<TR>\n"
						"<TD>Student ID</TD>\n"
						"<TD>Student Name</TD>\n"
						"<TD>Year</TD>\n"
						"<TD>Gender</TD>\n"
						"</TR>\n"
						"\n";

			for (StudentTable::Iterator iter = getStdTable().begin(); iter.notEnd(); iter++){
				string gender;
				if (iter->gender == 'M'){
					gender = "Male";
				}else{
					gender = "Female";
				}

				myfile << "<TR>\n"
						"<TD>" << iter->id << "</TD>\n"
						"<TD>" << iter->name << "</TD>\n"
						"<TD>" << iter->year << "</TD>\n"
						"<TD>" << gender << "</TD>\n"
						"</TR>\n";
			}
		}else{
			myfile << "<P>\n"
						"No student found\n"
						"</P>\n";
		}

		myfile << "</TABLE>\n"
					"</P>\n"
					"</BODY>\n"
					"</HTML>\n"
					"\n";
	}
	myfile.close();

	cout << "Generation successful!" << endl;
	hitEnterToContinue();
}

void listAllCourse(){
	ofstream myfile ("Courses.html");
	if (myfile.is_open()){

		//Write HTML headers
		myfile << "<HTML>\n"
					"<HEAD>\n"
					"<HEAD>\n"
					"<TITLE>All Course List</TITLE>\n"
					"</HEAD>\n"
					"<BODY bgColor=#ffffcc>\n"
					"<H1><FONT color=#6600ff>HKUST Course Registration System</FONT></H1>\n"
					"<H2>All Course List</H2>\n";

		//If the table is not empty
		if (getCourseTable().begin().notEnd()){
			myfile << "<P>\n"
						"<TABLE cellSpacing=1 cellPadding=1 border=1>\n"
						"\n"
						"<TR>\n"
						"<TD>Course Code</TD>\n"
						"<TD>Course Name</TD>\n"
						"<TD>Credit</TD>\n"
						"</TR>\n"
						"\n";

			for (CourseTable::Iterator iter = getCourseTable().begin(); iter.notEnd(); iter++){
				myfile << "<TR>\n"
						"<TD>" << iter->code << "</TD>\n"
						"<TD>" << iter->name << "</TD>\n"
						"<TD>" << iter->credit << "</TD>\n"
						"</TR>\n";
			}
		}else{
			myfile << "<P>\n"
						"No course found\n"
						"</P>\n";
		}

		myfile << "</TABLE>\n"
					"</P>\n"
					"</BODY>\n"
					"</HTML>\n"
					"\n";
	}
	myfile.close();

	cout << "Generation successful!" << endl;
	hitEnterToContinue();
}

void listAllCourseOfStd(){
	string stdID = getValidStdID();

	StudentTable& table = getStdTable();
	Student* student = table.find(Student(stdID));

	if (!student){
		cout << "Student id does not exist.";
		hitEnterToContinue();
		return;
	}

	string stdName = student->name;

	ofstream myfile ((stdID + ".html").c_str());

	if (myfile.is_open()){

		//Write HTML headers
		myfile << "<HTML>\n"
					"<HEAD>\n"
					"<HEAD>\n"
					"<TITLE>Course Records for Student" << stdID << "</TITLE>\n"
					"</HEAD>\n"
					"<BODY bgColor=#ffffcc>\n"
					"<H1><FONT color=#6600ff>HKUST Course Registration System</FONT></H1>\n"
					"<H2>Course Records for Student: " << stdName << "(" << stdID << ")" << "</H2>\n";

		SelectionList& mList = getCourseSelectionList();
		//If the list is not empty
		if (mList.begin () != mList.end()){
			myfile << "<P>\n"
						"<TABLE cellSpacing=1 cellPadding=1 border=1>\n"
						"\n"
						"<TR>\n"
						"<TD>Course Code</TD>\n"
						"<TD>Course Name</TD>\n"
						"<TD>Credit</TD>\n"
						"<TD>Exam Mark</TD>\n"
						"</TR>\n"
						"\n";

			for (list<CourseSelection>::iterator iter = mList.begin(); iter != mList.end(); ++iter){
				if (iter->stdID == stdID){
					string code = iter->code;
					Course course = *(getCourseTable().find(Course(code)));
					int mark = iter->mark;

					if (mark == UNDEF_EXAM_MARK){
						myfile << "<TR>\n"
								"<TD>" << iter->code << "</TD>\n"
								"<TD>" << course.name << "</TD>\n"
								"<TD>" << course.credit << "</TD>\n"
								"<TD>" << "N/A" << "</TD>\n"
								"</TR>\n";
					}else{
						myfile << "<TR>\n"
								"<TD>" << iter->code << "</TD>\n"
								"<TD>" << course.name << "</TD>\n"
								"<TD>" << course.credit << "</TD>\n"
								"<TD>" << mark << "</TD>\n"
								"</TR>\n";
					}
				}
			}
		}else{
			myfile << "<P>\n"
						"No course found\n"
						"</P>\n";
		}

		myfile << "</TABLE>\n"
					"</P>\n"
					"</BODY>\n"
					"</HTML>\n"
					"\n";
	}
	myfile.close();

	cout << "Generation successful!" << endl;
	hitEnterToContinue();
}

void listAllStdOfCourse(){
	string code = getValidCourseCode();

	CourseTable& table = getCourseTable();
	Course* course = table.find(Course(code));

	if (!course){
		cout << "Course code does not exist.";
		hitEnterToContinue();
		return;
	}

	string courseName = course->name;

	ofstream myfile ((code + ".html").c_str());

	if (myfile.is_open()){

		//Write HTML headers
		myfile << "<HTML>\n"
					"<HEAD>\n"
					"<HEAD>\n"
					"<TITLE>Student Records for Course " << code << "</TITLE>\n"
					"</HEAD>\n"
					"<BODY bgColor=#ffffcc>\n"
					"<H1><FONT color=#6600ff>HKUST Course Registration System</FONT></H1>\n"
					"<H2>Student Records for Course: " << courseName << "(" << code << ")" << "</H2>\n";

		SelectionList& mList = getCourseSelectionList();
		//If the list is not empty
		if (mList.begin () != mList.end()){
			myfile << "<P>\n"
						"<TABLE cellSpacing=1 cellPadding=1 border=1>\n"
						"\n"
						"<TR>\n"
						"<TD>Student ID</TD>\n"
						"<TD>Student Name</TD>\n"
						"<TD>Year</TD>\n"
						"<TD>Gender</TD>\n"
						"<TD>Exam Mark</TD>\n"
						"</TR>\n"
						"\n";

			for (list<CourseSelection>::iterator iter = mList.begin(); iter != mList.end(); ++iter){
				if (iter->code == code){
					string stdID = iter->stdID;
					Student student = *(getStdTable().find(Student(stdID)));
					int mark = iter->mark;
					string gender;

					if (student.gender == 'M'){
						gender = "Male";
					}else{
						gender = "Female";
					}

					if (mark == UNDEF_EXAM_MARK){
						myfile << "<TR>\n"
								"<TD>" << stdID << "</TD>\n"
								"<TD>" << student.name << "</TD>\n"
								"<TD>" << student.year << "</TD>\n"
								"<TD>" << gender << "</TD>\n"
								"<TD>" << "N/A" << "</TD>\n"
								"</TR>\n";
					}else{
						myfile << "<TR>\n"
								"<TD>" << stdID << "</TD>\n"
								"<TD>" << student.name << "</TD>\n"
								"<TD>" << student.year << "</TD>\n"
								"<TD>" << gender << "</TD>\n"
								"<TD>" << mark << "</TD>\n"
								"</TR>\n";
					}
				}
			}
		}else{
			myfile << "<P>\n"
						"No student found\n"
						"</P>\n";
		}

		myfile << "</TABLE>\n"
					"</P>\n"
					"</BODY>\n"
					"</HTML>\n"
					"\n";
	}
	myfile.close();

	cout << "Generation successful!" << endl;
	hitEnterToContinue();
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
