#ifndef _STUDENT_H
#define _STUDENT_H

#include <string>
#include <iostream>
#include "../ADT/hashable.h"
#include "../ADT/hash_table.h"

using namespace std;

#define STD_HASH_BASE 10
#define STD_HASH_BUCKETS 29

class Student : public Hashable{

public:
	string id;
	string name;
	int year;
	char gender;

	Student(string _id, string _name, int _year, char _gender) : id(_id), name(_name), year(_year), gender(_gender) {}

	//Conversion constructor for key only
	Student(string _id) : id(_id) {}

	int computeHash(int buckets) const{
		int sum = 0;
		int power = 1;
		for (int i=0; i<id.size(); i++){
			sum = (sum + (id[i]-48)*power) % buckets;
			power = (power*STD_HASH_BASE) % buckets;
		}
		return sum;
	}

	bool operator==(const Student& std) const{
		return id == std.id;
	}

	bool operator<=(const Student& std) const{
		return id <= std.id;
	}

	bool operator>=(const Student& std) const{
		return id >= std.id;
	}

	bool operator<(const Student& std) const{
		return id < std.id;
	}

	bool operator>(const Student& std) const{
		return id > std.id;
	}

	bool operator!=(const Student& std) const{
		return id != std.id;
	}

};

inline ostream& operator<<(ostream& os, const Student& std){
	os << "ID:\t\t" << std.id << endl;
	os << "Name:\t\t" << std.name << endl;
	os << "Year:\t\t" << std.year << endl;
	os << "Gender:\t\t" << std.gender;

	return os;
}

typedef HashTable<Student, STD_HASH_BUCKETS> StudentTable;

#endif