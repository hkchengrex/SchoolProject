#ifndef _SORT_LIST_H
#define _SORT_LIST_H

#include <list>

template <class T>
class SortedList{
private:
	std::list<T> _list;

public:
	SortedList() : _list<T>()
	{

	}

	~SortedList();

	int getSize(){
		return _list.size();
	}

	void insert(T item){
		std::list<T>::iterator iter = _list.begin();
		while ((iter!=_list.end()) && (*iter < item)){
			iter++;
		}
		_list.insert(iter, item);
	}

	std::list<T>::iterator begin(){
		return _list.begin();
	}

	std::list<T>::iterator end(){
		return _list.end();
	}

};

#endif