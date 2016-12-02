#ifndef _HASH_TABLE
#define _HASH_TABLE

#include <vector>
#include "sort_list.h"

//class T MUST be a Hashable
template <class T, int size, int base>
class HashTable{
private:
	class Node{
		T item;
		K key;
	};

	std::vector<T> _vector;

	int computeHash(const K& key){

	}

public:
	HashTable() : _vector(std::vector(size))
	{

	}

	void insert(const T& item){

	}

	void remove(const T& item){

	}
}

#endif