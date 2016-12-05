#ifndef _HASH_TABLE
#define _HASH_TABLE

#include <cstdlib>
#include <vector>
#include <exception>
#include "sort_list.h"

using namespace std;

//class T MUST be a Hashable
template <class T, int size>
class HashTable{
private:
	SortedList<T> _vector[size];

public:
	HashTable() {}

	//Find an item within the hashtable
	T* find(const T& item) const{

		SortedList<T> _list = _vector[item.computeHash(size)];

		typename list<T>::iterator iter = _list.begin();

		while (iter != _list.end()){
			if (*iter == item){
				return &(*iter);
			}
			iter++;
		}
		return NULL;
	}

	//Update one record with a new record
	void update(const T& old, const T& newItem){
		SortedList<T> _list = _vector[old.computeHash(size)];
		typename list<T>::iterator iter = _list.begin();

		while (iter != _list.end()){
			if (*iter == old){
				*iter = newItem;
				return;
			}
			iter++;
		}
	}

	//Insert new item into the table
	void insert(const T& item){
		_vector[item.computeHash(size)].insert(item);
	}

	//Remove a item from the table
	void remove(const T& item){
		_vector[item.computeHash(size)].remove(item);
	}

	//An iterator for the hash table
	class Iterator{
	private:
		HashTable& table;
		int currIndex;
		typename list<T>::iterator mIter;

	public:
		Iterator(HashTable& _table, int index = 0) : table(_table), currIndex(index), mIter(table._vector[index].begin())
		{
			while (mIter == table._vector[currIndex].end()){
				currIndex++;
				if (currIndex >= size){
					break;
				}
				mIter = table._vector[currIndex].begin();
			}
		}

		bool notEnd(){
			return currIndex < size;
		}

		T& operator*(){
			return *mIter;
		}

		
		T* operator->(){
			return &(*mIter);
		}

		Iterator& operator++(){ //Pre increment
			if ((++mIter) == table._vector[currIndex].end()){
				currIndex++;
				if (currIndex >= size){
					return *this;
				}
				mIter = table._vector[currIndex].begin();
			}

			while (mIter == table._vector[currIndex].end()){
				currIndex++;
				if (currIndex >= size){
					return *this;
				}
				mIter = table._vector[currIndex].begin();
			}

			return *this;
		}

		Iterator operator++(int){ //Post increment
			Iterator temp(*this);
			operator++();
			return temp;
		}

		bool operator==(const Iterator& iter) const{
			return (currIndex == iter.currIndex) && (mIter == iter.mIter);
		}

		bool operator!=(const Iterator& iter) const{
			return (currIndex != iter.currIndex) || (mIter != iter.mIter);
		}
	};

	Iterator begin(){
		return Iterator(*this);
	}
};

#endif