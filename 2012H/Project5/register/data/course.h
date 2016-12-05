#ifndef _COURSE_H
#define _COURSE_H

#include <string>
#include <vector>
#include <iostream>
#include "../ADT/hashable.h"
#include "../ADT/hash_table.h"

using namespace std;

#define COURSE_HASH_BASE 36
#define COURSE_HASH_BUCKETS 17

class Course : public Hashable{
	
public:
	string code;
	string name;
	int credit;

	Course(string _code, string _name, int _credit) : code(_code), name(_name), credit(_credit) {}

	//Conversion constructor for key only
	Course(string _code) : code(_code) {}

	int computeHash(int buckets) const{
		int sum = 0;
		int power = 1;
		for (int i=0; i<code.size(); i++){

			int mapped;
			if (code[i]<58){
				mapped = code[i]-48;
			}else{
				mapped = code[i]-55;
			}

			sum = (sum + mapped*power) % buckets;
			power = (power*COURSE_HASH_BASE) % buckets;
		}
		return sum;
	}

	bool operator==(const Course& course){
		return code == course.code;
	}

	bool operator<=(const Course& course){
		return code <= course.code;
	}

	bool operator>=(const Course& course){
		return code >= course.code;
	}

	bool operator<(const Course& course){
		return code < course.code;
	}

	bool operator>(const Course& course){
		return code > course.code;
	}

	bool operator!=(const Course& course){
		return code != course.code;
	}

};

inline ostream& operator<<(ostream& os, const Course& course){
	os << "Code:\t\t" << course.code << endl;
	os << "Name:\t\t" << course.name << endl;
	os << "Credit:\t\t" << course.credit;

	return os;
}

typedef HashTable<Course, COURSE_HASH_BUCKETS> CourseTable;

#endif