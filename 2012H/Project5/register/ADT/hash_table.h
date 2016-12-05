#ifndef _HASH_TABLE
#define _HASH_TABLE

#include <cstdlib>
#include <vector>
#include "sort_list.h"

using namespace std;

//class T MUST be a Hashable
template <class T, int size>
class HashTable{
private:
	vector<SortedList<T> > _vector;

public:
	HashTable() : _vector(std::vector<SortedList<T> >(size)) {}

	T* find(const T& item) const{

		SortedList<T> list = _vector[item.computeHash(size)];
		typename list<T>::iterator iter = list.begin();

		while (iter != list.end()){
			if (*iter == item){
				return &(*iter);
			}
			iter++;
		}

		return NULL;
	}

	void update(const T& old, const T& newItem) const{
		SortedList<T> list = _vector[old.computeHash(size)];
		typename list<T>::iterator iter = list.begin();

		while (iter != list.end()){
			if (*iter == old){
				*iter = newItem;
				return;
			}
			iter++;
		}

	}

	void insert(const T& item){
		_vector[item.computeHash(size)].insert(item);
	}

	void remove(const T& item){
		_vector[item.computeHash(size)].remove(item);
	}

	class Iterator{
	private:
		const HashTable& table;
		int currIndex;
		typename list<T>::iterator mIter;

	public:
		Iterator(const HashTable& _table, int index = 0) : table(_table), currIndex(index), mIter(table._vector[index].begin()) {}

		Iterator& goToEnd(){
			currIndex = table._vector.size() - 1;
			mIter = table._vector[currIndex].end();
		}

		T& operator*() const{
			return *mIter;
		}

		
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
};

#endif