#ifndef _COURSE_H
#define _COURSE_H

class Course : public Hashable{

private:
	const int HASH_BASE = 29;

	string code;
	string name;
	int credit;

public:
	Course(string _code, string _name, int _credit) : code(_code), name(_name), credit(_credit)
	{

	}

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

			sum += (mapped*power) % buckets;
			power = (power*HASH_BASE) % buckets;
		}
		return sum;
	}
};

#endif