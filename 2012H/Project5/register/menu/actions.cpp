#include "actions.h"

#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std;

/*********************/
//The followings are for student menu

//Insert a student action
void insertStd(){
	StudentTable& table = getStdTable();

	Student student(getValidStdID());

	//Studnet id must be unique
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

//Modify current studnet
void modifyStd(){
	StudentTable& table = getStdTable();

	Student* student = table.find(getValidStdID());

	//Give error if student does not exist
	if (!student){
		cout << "Student id does not exist.";
		hitEnterToContinue();
		return;
	}

	string input;
	Student newStd = Student(student->id);

	//Change name
	cout << "Enter Student Name[" << student->name << "]: ";
	cin.ignore();
	getline(cin, input);

	while (!isValidStdName(input)){
		cout << "Invalid. Please input Student name again: ";
		cin.ignore();
		getline(cin, input);
	}

	newStd.name = input;

	//Change year
	int year;
	cout << "Enter Student Year[" << student->year << "]: ";
	cin >> year;

	while (!isValidYear(year)){
		cout << "Invalid. Please input Student year again: ";
		cin >> year;
		cin.ignore();
	}

	newStd.year = year;

	//change gender ???
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

//Delete a student record
void deleteStd(){
	StudentTable& table = getStdTable();

	Student* student = table.find(Student(getValidStdID()));

	//Cannot delet if student not exist
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

//Search and print a student record
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
//The following are for course menu

void insertCourse(){
	CourseTable& table = getCourseTable();

	Course course(getValidCourseCode());

	//Course code must be unique
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

	//Change course name
	cout << "Enter Course Name[" << course->name << "]: ";
	cin.ignore();
	getline(cin, input);

	while (!isValidCourseName(input)){
		cout << "Invalid. Please input Course name again: ";
		cin.ignore();
		getline(cin, input);
	}

	newCourse.name = input;

	//Change course credit
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
//The followings actions are for add/drop course

void regCourse(){
	SelectionList& mList = getCourseSelectionList();
	StudentTable& stdTable = getStdTable();
	CourseTable& courseTable = getCourseTable();

	Student* student = stdTable.find(getValidStdID());

	//Must have this student
	if (!student){
		cout << "Student id does not exist.";
		hitEnterToContinue();
		return;
	}

	Student copyOfStd(*student);
	student = &copyOfStd;

	Course* course = courseTable.find(getValidCourseCode());

	//And must have this course
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

	//This student must not have added this course already
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

//Query for a course reg and print it out
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
//The following are for generating HTML reports


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

				//Print all records in table
				myfile << "<TR>\n"
						"<TD>" << iter->id << "</TD>\n"
						"<TD>" << iter->name << "</TD>\n"
						"<TD>" << iter->year << "</TD>\n"
						"<TD>" << gender << "</TD>\n"
						"</TR>\n\n";
			}

			myfile << "</TABLE>\n"
					<< "</P>\n";
		}else{
			//If no student
			myfile << "<P>\n"
						"No student found\n"
						"</P>\n";
		}

		myfile << "</BODY>\n"
					"</HTML>\n";
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

			//Write table for records
			for (CourseTable::Iterator iter = getCourseTable().begin(); iter.notEnd(); iter++){
				myfile << "<TR>\n"
						"<TD>" << iter->code << "</TD>\n"
						"<TD>" << iter->name << "</TD>\n"
						"<TD>" << iter->credit << "</TD>\n"
						"</TR>\n\n";
			}

			myfile << "</TABLE>\n"
					<< "</P>\n";
		}else{
			//If no course
			myfile << "<P>\n"
						"No course found\n"
						"</P>\n";
		}

		myfile << "</BODY>\n"
					"</HTML>\n";
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
					"<TITLE>Course Records for Student " << stdID << "</TITLE>\n"
					"</HEAD>\n"
					"<BODY bgColor=#ffffcc>\n"
					"<H1><FONT color=#6600ff>HKUST Course Registration System</FONT></H1>\n"
					"<H2>Course Records for Student: " << stdName << " (" << stdID << ")" << "</H2>\n";

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

					//Print all records in table
					if (mark == UNDEF_EXAM_MARK){
						myfile << "<TR>\n"
								"<TD>" << iter->code << "</TD>\n"
								"<TD>" << course.name << "</TD>\n"
								"<TD>" << course.credit << "</TD>\n"
								"<TD>" << "N/A" << "</TD>\n"
								"</TR>\n\n";
					}else{
						myfile << "<TR>\n"
								"<TD>" << iter->code << "</TD>\n"
								"<TD>" << course.name << "</TD>\n"
								"<TD>" << course.credit << "</TD>\n"
								"<TD>" << mark << "</TD>\n"
								"</TR>\n\n";
					}
				}
			}

			myfile << "</TABLE>\n"
					<< "</P>\n";
		}else{
			//if no course
			myfile << "<P>\n"
						"No course taken\n"
						"</P>\n";
		}

		myfile << "</BODY>\n"
					"</HTML>\n";
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
					"<H2>Student Records for Course: " << courseName << " (" << code << ")" << "</H2>\n";

		SelectionList& mList = getCourseSelectionList();
		//If the list is not empty
		if (mList.begin () != mList.end()){
			//Print header
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

					//Print all records in table
					if (mark == UNDEF_EXAM_MARK){
						myfile << "<TR>\n"
								"<TD>" << stdID << "</TD>\n"
								"<TD>" << student.name << "</TD>\n"
								"<TD>" << student.year << "</TD>\n"
								"<TD>" << gender << "</TD>\n"
								"<TD>" << "N/A" << "</TD>\n"
								"</TR>\n\n";
					}else{
						myfile << "<TR>\n"
								"<TD>" << stdID << "</TD>\n"
								"<TD>" << student.name << "</TD>\n"
								"<TD>" << student.year << "</TD>\n"
								"<TD>" << gender << "</TD>\n"
								"<TD>" << mark << "</TD>\n"
								"</TR>\n\n";
					}
				}
			}

			myfile << "</TABLE>\n"
					<< "</P>\n";
		}else{
			//If no student
			myfile << "<P>\n"
						"No student takes this course\n"
						"</P>\n";
		}

		myfile << "</BODY>\n"
					"</HTML>\n";
	}
	myfile.close();

	cout << "Generation successful!" << endl;
	hitEnterToContinue();
}

/* ------------------------------- */
//The following are for saving and loading database operation

void saveToDB(){
	fstream file;

	//Open file for storing the database
	string fileName;
	cin.ignore();
	cout << "Please input file name: " << endl;
	cin >> fileName;

	try{
		file.open(fileName.c_str(), fstream::out);

		//Save all student records
		for (StudentTable::Iterator iter = getStdTable().begin(); iter.notEnd(); iter++){
			file << iter->id << "\n"
					<< iter->name << "\n"
					<< iter->year << "\n"
					<< iter->gender << "\n";
		}

		file << "\n";

		//Save all course records
		for (CourseTable::Iterator iter = getCourseTable().begin(); iter.notEnd(); iter++){
			file << iter->code << "\n"
					<< iter->name << "\n"
					<< iter->credit << "\n";
		}

		file << "\n";

		//Save all reg record
		SelectionList& mList = getCourseSelectionList();

		for (list<CourseSelection>::iterator iter = mList.begin(); iter != mList.end(); ++iter){
			file << iter->stdID << "\n"
					<< iter->code << "\n"
					<< iter->mark << "\n";
		}

		file << "\n";

		file.close();

		cout << "Generation successful!" << endl;
	}catch (...){
		cout << "Generation failed!" << endl;
	}
	hitEnterToContinue();
}

void loadFromDB(){
	//Temp data for not to affect current database
	StudentTable stdTable;
	CourseTable courseTable;
	SelectionList selectionList;

	fstream file;

	//Ask for file name
	string fileName;
	cin.ignore();
	cout << "Please input file name: " << endl;
	cin >> fileName;

	try{
		ifstream file(fileName.c_str());

		//Load all student record
		while(file.peek() != '\n'){
			char buf[100];
			Student std;

			file.getline(buf, 100);
			std.id = buf;
			if (!isValidStdID(std.id)){
				throw "id error";
			}

			file.getline(buf, 100);
			std.name = buf;
			if (!isValidStdName(std.name)){
				throw "name error";
			}

			file.getline(buf, 100);
			std.year = atoi(buf);
			if (!isValidYear(std.year)){
				throw "year error";
			}

			file.getline(buf, 100);
			std.gender = buf[0];
			if (!isValidGender(std.gender)){
				throw "gender error";
			}

			stdTable.insert(std);
		}

		//Remove the new line
		file.get();

		//Get all course data
		while(file.peek() != '\n'){
			char buf[100];
			Course course;

			file.getline(buf, 100);
			course.code = buf;
			if (!isValidCourseCode(course.code)){
				throw "code error";
			}

			file.getline(buf, 100);
			course.name = buf;
			if (!isValidCourseName(course.name)){
				throw "name error";
			}

			file.getline(buf, 100);
			course.credit = atoi(buf);
			if (!isValidCredit(course.credit)){
				throw "credit error";
			}

			courseTable.insert(course);
		}

		//Remove the new line
		file.get();

		//Get all reg course data
		while(file.peek() != '\n'){
			char buf[100];
			CourseSelection selection;

			file.getline(buf, 100);
			selection.stdID = buf;
			if (!isValidStdID(selection.stdID)){
				throw "stdID error";
			}

			file.getline(buf, 100);
			selection.code = buf;
			if (!isValidCourseCode(selection.code)){
				throw "code error";
			}

			file.getline(buf, 100);
			selection.mark = atoi(buf);
			if (!isValidExamMark(selection.mark)){
				throw "mark error";
			}

			selectionList.insert(selection);
		}

		//Remove all old data
		getStdTable().clear();
		getCourseTable().clear();
		getCourseSelectionList().clear();

		//Insert new data into the singleton
		for (StudentTable::Iterator iter = stdTable.begin(); iter.notEnd(); iter++){
			getStdTable().insert(*iter);
		}

		for (CourseTable::Iterator iter = courseTable.begin(); iter.notEnd(); iter++){
			getCourseTable().insert(*iter);
		}

		for (list<CourseSelection>::iterator iter = selectionList.begin(); iter != selectionList.end(); ++iter){
			getCourseSelectionList().insert(*iter);
		}

		cout << "Load successful!" << endl;

	}catch(...){
		cout << "Load failed!" << endl;
	}

	hitEnterToContinue();
}

//A helper function to stop the program and wait for user to hit enter
void hitEnterToContinue(){
	cout << "Hit ENTER to continue. "<< endl;
	cin.ignore();
	cin.get();
}

