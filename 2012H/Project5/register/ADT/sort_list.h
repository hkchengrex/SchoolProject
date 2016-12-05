#ifndef _SORT_LIST_H
#define _SORT_LIST_H

#include <list>

using namespace std;

template <class T>
class SortedList{
private:
	list<T> _list;

public:
	SortedList() : _list()
	{

	}

	int getSize(){
		return _list.size();
	}

	void insert(const T& item){
		typename list<T>::iterator iter = _list.begin();
		while ((iter!=_list.end()) && (*iter < item)){
			iter++;
		}
		_list.insert(iter, item);
	}

	void remove(const T& item){
		_list.remove(item);
	}

	typename list<T>::iterator begin(){
		return _list.begin();
	}

	typename list<T>::iterator end(){
		return _list.end();
	}

};

#endif