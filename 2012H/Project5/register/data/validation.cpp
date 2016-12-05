#include "validation.h"
#include <iostream>

bool isValidStdID(string id){
	//If length mismatch
	if (id.size() != STD_ID_LEN){
		return false;
	}

	//If any is not number
	for (int i=0; i<STD_ID_LEN; i++){
		if (id[i]<48 || id[i]>57){
			return false;
		}
	}

	return true;
}

bool isValidStdName(string name){
	//Check length only
	return (name.size() >= 1 && name.size() <= STD_NAME_MAX_LEN);
}

bool isValidYear(int year){
	return (year>=1 && year<=MAX_YEAR);
}

bool isValidGender(char gender){
	return (gender=='M' || gender=='F');
}

bool isValidCourseCode(string code){
	//Check length
	if (code.size()>COURSE_CODE_MAXLEN || code.size()<COURSE_CODE_MINLEN){
		return false;
	}

	//Check first X all are upper case letter
	for (int i=0; i<COURSE_FIRST_X_LETTER; i++){
		if (code[i]<65 || code[i]>90){
			return false;
		}
	}

	//Check the remaining are upper letters/numbers
	for (int i=COURSE_FIRST_X_LETTER; i<code.size(); i++){
		if (!((code[i]>=65 && code[i]<=90) || (code[i]>=48 && code[i]<=57))){
			return false;
		}
	}

	return true;
}

bool isValidCourseName(string name){
	//Check length only
	return (name.size() >= 1 && name.size() <= COURSE_NAME_MAX_LEN);
}

bool isValidCredit(int credit){
	return (credit>=0 && credit<=MAX_CREDIT);
}

bool isValidExamMark(int mark){
	return ((mark==UNDEF_EXAM_MARK) || (mark>=0 && mark<= MAX_EXAM_MARK));
}

string getValidStdID(){
	string input;

	cout << "Enter Student id: ";
	cin >> input;

	while (!isValidStdID(input)){
		cout << "Invalid. Please input Student id again: ";
		cin.ignore();
		cin >> input;
	}

	return input;
}

string getValidStdName(){
	string input;

	cout << "Enter Student Name: ";
	cin >> input;

	while (!isValidStdName(input)){
		cout << "Invalid. Please input Student name again: ";
		cin.ignore();
		cin >> input;
	}

	return input;
}

int getValidYear(){
	int year;
	cout << "Enter Student Year[1-" << MAX_YEAR << "]: ";
	cin >> year;

	while (!isValidYear(year)){
		cout << "Invalid. Please input Student year again: ";
		cin.ignore();
		cin >> year;
	}

	return year;
}

char getValidGender(){
	string input;
	cout << "Enter Student Gender[M/F]: ";
	cin >> input;

	while (input.size()!=1 || !isValidGender(input[0])){
		cout << "Invalid. Please input Student gender again: ";
		cin.ignore();
		cin >> input;
	}

	return input[0];
}

string getValidCourseCode(){
	string input;

	cout << "Enter Course Code: ";
	cin >> input;

	while (!isValidCourseCode(input)){
		cout << "Invalid. Please input Course Code again: ";
		cin.ignore();
		cin >> input;
	}

	return input;
}

string getValidCourseName(){
	string input;

	cout << "Enter Course Name: ";
	cin >> input;

	while (!isValidCourseName(input)){
		cout << "Invalid. Please input Course Name again: ";
		cin.ignore();
		cin >> input;
	}

	return input;
}

int getValidCredit(){
	int credit;
	cout << "Enter Credit[1-" << MAX_CREDIT << "]: ";
	cin >> credit;

	while (!isValidCredit(credit)){
		cout << "Invalid. Please input Credit again: ";
		cin.ignore();
		cin >> credit;
	}

	return credit;
}