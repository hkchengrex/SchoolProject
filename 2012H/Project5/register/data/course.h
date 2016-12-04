#ifndef _COURSE_H
#define _COURSE_H

#include <string>
#include <vector>
#include "../ADT/hashable.h"
#include "../ADT/hash_table.h"

using namespace std;

#define COURSE_HASH_BASE 36
#define COURSE_HASH_BUCKETS 17

typedef HashTable<Course, COURSE_HASH_BUCKETS> CourseTable;

class Course : public Hashable{

private:
	string code;
	string name;
	int credit;

public:
	Course(string _code, string _name, int _credit) : code(_code), name(_name), credit(_credit) {}

	//Conversion constructor for key only
	Course(string _code) : code(_code) {}

	int computeHash(int buckets){
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


#endif