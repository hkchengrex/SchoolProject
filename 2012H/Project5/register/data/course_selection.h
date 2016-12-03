#ifndef _COURSE_SELECTION_H
#define _COURSE_SELECTION_H

#include <string>
#include "student.h"
#include "course.h"

class CourseSelection{
private:
	string stdID;
	string code;
	int mark;

public:
	CourseSelection (string _stdID, string _code, int _mark) : stdID(_stdID), code(_code), mark(_mark) {}

	bool operator==(const CourseSelection& selection){
		return (code == selection.code) && (stdID == selection.code);
	}

	bool operator<(const CourseSelection& selection){
		//First by id, then by course code
		if (stdID < selection.stdID){
			return true;
		}else if (stdID > selection.stdID){
			return false;
		}else{
			return code < selection.code;
		}
	}

	bool operator>(const CourseSelection& selection){
		//First by id, then by course code
		if (stdID > selection.stdID){
			return true;
		}else if (stdID < selection.stdID){
			return false;
		}else{
			return code > selection.code;
		}
	}

	bool operator<=(const CourseSelection& selection){
		return (*this<selection) || (*this==selection);
	}

	bool operator>=(const CourseSelection& selection){
		return (*this>selection) || (*this==selection);
	}

	bool operator!=(CourseSelection selection){
		return (code != selection.code) && (stdID != selection.code);
	}
};

#endif