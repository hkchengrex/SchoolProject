#ifndef _HASH_TABLE
#define _HASH_TABLE

#include <vector>
#include "sort_list.h"

using namespace std;

//class T MUST be a Hashable
template <class T, int size>
class HashTable{
private:
	std::vector<SortedList<T>> _vector;

public:
	HashTable() : _vector(std::vector(size)) {}

	T* find(const T& item){
		SortedList<T>* list = &(_vector[item.computeHash(size)]);
		list<T>::iterator iter = list->begin();

		while (iter != list->end()){
			if (*iter == item){
				return &(*iter);
			}
		}

		return NULL;
	}

	void insert(const T& item){
		_vector[item.computeHash(size)].insert(T);
	}

	void remove(const T& item){
		_vector[item.computeHash(size)].remove(T);
	}

	class Iterator{
	private:
		const HashTable& table;
		int currIndex;
		list<T>::iterator mIter;

	public:
		Iterator(const HashTable& _table, int index = 0) : _table(table), currIndex(index), mIter(table._vector[index].begin()) {}

		Iterator& goToEnd(){
			currIndex = table._vector.size() - 1;
			mIter = table._vector[currIndex].end();
		}

		T& operator*() const{
			return *mIter;
		}

		T
		T* operator->() const{
			return &(*mIter);
		}

		Iterator& operator++(){ //Pre increment
			if ((++mIter) == table._vector[currIndex].end()){
				currIndex++;
				mIter = table._vector[currIndex].being();
			}
			return *this;
		}

		Iterator& operator++(int){ //Post increment
			Iterator temp(*this);
			if ((++mIter) == table._vector[currIndex].end()){
				currIndex++;
				mIter = table._vector[currIndex].being();
			}
			return temp;
		}

		bool operator==(const Iterator& iter){
			return (currIndex == iter.currIndex) && (mIter == iter.mIter);
		}
	};
}

#endif