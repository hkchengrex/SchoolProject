#ifndef _INDEXES_H
#define _INDEXES_H

#include <string>
#include <vector>
#include "../ADT/hashable.h"
#include "course.h"
#include "stduent.h"
#include "course_selection.h"

using namespace std;

typedef HashTable<CourseKey, COURSE_HASH_BUCKETS> CourseIndexTable;
typedef HashTable<StudentKey, STD_HASH_BUCKETS> StudentIndexTable;

class CourseKey : public Hashable{

private:
	string code;
	vector<CourseSelection*> pointer;

public:
	CourseKey(string _code) : code(_code) {}

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

class StudentKey : public Hashable{

struct Gender
{
	MALE = 0,
	FEMALE
};

private:
	string id;
	vector<CourseSelection*> pointer;

public:
	StudentKey(string _id) : id(_id) {}

	int computeHash(int buckets){
		int sum = 0;
		int power = 1;
		for (int i=0; i<id.size(); i++){
			sum = (sum + (id[i]-48)*power) % buckets;
			power = (power*STD_HASH_BASE) % buckets;
		}
		return sum;
	}

	bool operator==(const Student& std){
		return id == std.id;
	}

	bool operator<=(const Student& std){
		return id <= std.id;
	}

	bool operator>=(const Student& std){
		return id >= std.id;
	}

	bool operator<(const Student& std){
		return id < std.id;
	}

	bool operator>(const Student& std){
		return id > std.id;
	}

	bool operator!=(const Student& std){
		return id != std.id;
	}

};

#endif