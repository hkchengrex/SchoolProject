#ifndef _STUDENT_H
#define _STUDENT_H

#include <string>
#include "../ADT/hashable.h"
#include "../ADT/hash_table.h"

using namespace std;

#define STD_HASH_BASE 10
#define STD_HASH_BUCKETS 29

typedef HashTable<Student, STD_HASH_BUCKETS> StudentTable;

class Student : public Hashable{

struct Gender
{
	MALE = 0,
	FEMALE
};

private:
	string id;
	string name;
	int year;
	Gender gender;

public:
	Student(string _id, string _name, int _year, Gender _gender) : id(_id), name(_name), year(_year), gender(_gender) {}

	//Conversion constructor for key only
	Student(string _id) : id(_id) {}

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