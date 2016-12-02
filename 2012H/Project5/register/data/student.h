#ifndef _STUDENT_H
#define _STUDENT_H

#include <string>

using namespace std;

class Student : public Hashable{

struct Gender
{
	MALE = 0,
	FEMALE
};

private:
	const int HASH_BASE = 10;

	string id;
	string name;
	int year;
	Gender gender;

public:
	Student(string _id, string _name, int _year, Gender _gender) :
		id(_id), name(_name), year(_year), gender(_gender) {}

	int computeHash(int buckets){
		int sum = 0;
		int power = 1;
		for (int i=0; i<id.size(); i++){
			sum += ((id[i]-48)*power) % buckets;
			power = (power*HASH_BASE) % buckets;
		}
		return sum;
	}

};

#endif