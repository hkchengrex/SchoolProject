#ifndef _INDEXES_H
#define _INDEXES_H

#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>
#include "../ADT/hashable.h"
#include "course.h"
#include "student.h"
#include "course_selection.h"

using namespace std;

class CourseKey : public Hashable{

private:
	const string code;
	list<CourseSelection*> _list;

public:
	CourseKey(const string& _code) : code(_code) {}
	CourseKey(const Course& course) : code(course.code) {}

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

	bool contains(const Student& std) const{
		typename list<CourseSelection*>::const_iterator iter = _list.begin();
		while (iter != _list.end()){
			if ((*iter)->stdID == std.id){
				return true;
			}
			iter++;
		}
		return false;
	}

	CourseSelection* find(const Student& std) const{
		typename list<CourseSelection*>::const_iterator iter = _list.begin();
		while (iter != _list.end()){
			if ((*iter)->stdID == std.id){
				return *iter;
			}
			iter++;
		}
		return NULL;
	}

	void insert(CourseSelection* selection){
		_list.push_back(selection);
	}

	void remove(CourseSelection* selection){
		_list.remove(selection);
	}

	CourseKey& operator=(const CourseKey& std){
		_list = std._list;
		return *this;
	}

	bool operator==(const CourseKey& course) const{
		return code == course.code;
	}

	bool operator<=(const CourseKey& course) const{
		return code <= course.code;
	}

	bool operator>=(const CourseKey& course) const{
		return code >= course.code;
	}

	bool operator<(const CourseKey& course) const{
		return code < course.code;
	}

	bool operator>(const CourseKey& course) const{
		return code > course.code;
	}

	bool operator!=(const CourseKey& course) const{
		return code != course.code;
	}
};

class StudentKey : public Hashable{

private:
	const string id;
	list<CourseSelection*> _list;

public:
	StudentKey(const string& _id) : id(_id) {}
	StudentKey(const Student& std) : id(std.id) {}
	StudentKey(const StudentKey& key) : id(key.id), _list(key._list) {}

	int computeHash(int buckets) const{
		int sum = 0;
		int power = 1;
		for (int i=0; i<id.size(); i++){
			sum = (sum + (id[i]-48)*power) % buckets;
			power = (power*STD_HASH_BASE) % buckets;
		}
		return sum;
	}

	int size() const{
		return _list.size();
	}

	bool contains(const Course& course) const{
		typename list<CourseSelection*>::const_iterator iter = _list.begin();
		while (iter != _list.end()){
			if ((*iter)->code == course.code){
				return true;
			}
			iter++;
		}
		return false;
	}

	CourseSelection* find(const Course& course) const{
		typename list<CourseSelection*>::const_iterator iter = _list.begin();
		while (iter != _list.end()){
			if ((*iter)->code == course.code){
				return *iter;
			}
			iter++;
		}
		return NULL;
	}

	void insert(CourseSelection* selection){
		_list.push_back(selection);
	}

	void remove(CourseSelection* selection){
		_list.remove(selection);
	}

	StudentKey& operator=(const StudentKey& std){
		_list = std._list;
		return *this;
	}

	bool operator==(const StudentKey& std) const{
		return id == std.id;
	}

	bool operator<=(const StudentKey& std) const{
		return id <= std.id;
	}

	bool operator>=(const StudentKey& std) const{
		return id >= std.id;
	}

	bool operator<(const StudentKey& std) const{
		return id < std.id;
	}

	bool operator>(const StudentKey& std) const{
		return id > std.id;
	}

	bool operator!=(const StudentKey& std) const{
		return id != std.id;
	}

};

typedef HashTable<CourseKey, COURSE_HASH_BUCKETS> CourseKeyTable;
typedef HashTable<StudentKey, STD_HASH_BUCKETS> StudentKeyTable;

#endif