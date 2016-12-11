#ifndef _SORT_LIST_H
#define _SORT_LIST_H

#include <list>
#include <cstdlib>

using namespace std;

template <class T>
class SortedList{
private:
	list<T> _list;

public:

	SortedList() : _list()
	{

	}

	int getSize() const{
		return _list.size();
	}

	//Check whether the list contain such item
	bool contains(const T& item) const{
		typename list<T>::const_iterator iter = _list.begin();
		while ((iter!=_list.end())){
			if (*iter == item){
				return true;
			}
			iter++;
		}
		return false;
	}

	//Get a contained item, null if not exist
	T* get(const T& item){
		typename list<T>::iterator iter = _list.begin();
		while ((iter!=_list.end())){
			if (*iter == item){
				return &(*iter);
			}
			iter++;
		}
		return NULL;
	}

	//Insert a new item, make sure it is sorted
	void insert(const T& item){
		typename list<T>::iterator iter = _list.begin();
		while ((iter!=_list.end()) && (*iter < item)){
			iter++;
		}
		_list.insert(iter, item);
	}

	//Remove an item
	void remove(const T& item){
		_list.remove(item);
	}

	//Clear all items
	void clear(){
		_list.clear();
	}

	typename list<T>::iterator begin(){
		return _list.begin();
	}

	typename list<T>::iterator end(){
		return _list.end();
	}

};

#endif