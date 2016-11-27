#ifndef _HASH_TABLE
#define _HASH_TABLE

#include <vector>
#include "sort_list.h"

template <class T, int size, int base>
class HashTable{
private:
	std::vector<T> _vector;
public:
	HashTable() : _vector(std::vector(size))
	{

	}
}

#endif