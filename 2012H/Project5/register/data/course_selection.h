#ifndef _COURSE_SELECTION_H
#define _COURSE_SELECTION_H

#include <string>
#include "student.h"
#include "course.h"
#include "validation.h"

//This class is for a regrisation record
class CourseSelection{
public:
	string stdID;
	string code;
	int mark;
	
	CourseSelection (const string& _stdID, const string& _code, int _mark = UNDEF_EXAM_MARK) : stdID(_stdID), code(_code), mark(_mark) {}

	CourseSelection (const Student& std, const Course& course, int _mark = UNDEF_EXAM_MARK) : stdID(std.id), code(course.code), mark(_mark) {}

	CourseSelection(int _mark = UNDEF_EXAM_MARK) {}

	//Overloadded operator
	bool operator==(const CourseSelection& selection) const{
		return (code == selection.code) && (stdID == selection.stdID);
	}

	bool operator<(const CourseSelection& selection) const{
		//First by id, then by course code
		if (stdID < selection.stdID){
			return true;
		}else if (stdID > selection.stdID){
			return false;
		}else{
			return code < selection.code;
		}
	}

	bool operator>(const CourseSelection& selection) const{
		//First by id, then by course code
		if (stdID > selection.stdID){
			return true;
		}else if (stdID < selection.stdID){
			return false;
		}else{
			return code > selection.code;
		}
	}

	bool operator<=(const CourseSelection& selection) const{
		return (*this<selection) || (*this==selection);
	}

	bool operator>=(const CourseSelection& selection) const{
		return (*this>selection) || (*this==selection);
	}

	bool operator!=(CourseSelection selection) const{
		return (code != selection.code) && (stdID != selection.code);
	}
};

inline ostream& operator<<(ostream& os, const CourseSelection& selection){
	os << "ID:\t\t" << selection.stdID << endl;
	os << "Code:\t\t" << selection.code << endl;
	if (selection.mark == UNDEF_EXAM_MARK){
		os << "mark:\t\t" << "N/A";
	}else{
		os << "mark:\t\t" << selection.mark;
	}
	return os;
}

typedef SortedList<CourseSelection> SelectionList;

#endif