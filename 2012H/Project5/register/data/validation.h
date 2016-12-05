#ifndef _VALIDATOIN_H
#define _VALIDATOIN_H

#include <string>

using namespace std;

#define STD_ID_LEN 8
#define STD_NAME_MAX_LEN 32
#define MAX_YEAR 3

#define COURSE_CODE_MAXLEN 8
#define COURSE_CODE_MINLEN 7
#define COURSE_FIRST_X_LETTER 4

#define COURSE_NAME_MAX_LEN 50

#define MAX_CREDIT 5
#define MAX_EXAM_MARK 100
#define UNDEF_EXAM_MARK -1

bool isValidStdID(string id);
bool isValidStdName(string name);
bool isValidYear(int year);
bool isValidGender(char gender);

bool isValidCourseCode(string code);
bool isValidCourseName(string name);
bool isValidCredit(int credit);

bool isValidExamMark(int mark);

string getValidStdID();
string getValidStdName();
int getValidYear();
char getValidGender();

string getValidCourseCode();
string getValidCourseName();
int getValidCredit();

#endif