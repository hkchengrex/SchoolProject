#ifndef RANDOMIZED_QUEUE_H
#define RANDOMIZED_QUEUE_H

#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <time.h>

template <class Item>
class RandomizedQueue{
private:
	int _size; //Size of internal array
	int _ptr; //Current array pointer, aka size of stored items
	Item* _array;

	//Resize the array into a bigger/smaller array
	void resize(int new_size){
		Item* new_array = new Item[new_size];
		int limiting_size = new_size>_size ? _size : new_size;
		memcpy(new_array, _array, sizeof(Item)*limiting_size);
		delete[] _array;
		_array = new_array;
		_size = new_size;
	}

public:
	RandomizedQueue() : _size(1), _ptr(0), _array(new Item[1]){};
	~RandomizedQueue(){
		delete[] _array;
	}
	bool isEmpty() const {return _ptr==0;}
	int size() const {return _ptr;}

	void enqueue(const Item& item){
		if (_ptr >= _size){
			//Double the array size if lack of space
			resize(_size*2);
		}
		_array[_ptr++] = item;
	}

	Item dequeue(){
		if (_ptr <= 0){
			throw std::runtime_error("Underflow");
		}
		int rand_num = rand()%_ptr; //0 ~ _ptr-1
		//Return item from a random slot
		Item selected = _array[rand_num];
		_array[rand_num] = _array[--_ptr]; //Move the last element into the returned slot
		if (_ptr < _size/2){
			//Half the array size if too much space
			resize(_size/2);
		}
		return selected;
	}

	Item sample() const{
		int rand_num = rand()%_ptr; //0 ~ _ptr-1
		return _array[rand_num];
	}


	class Iterator{
	private:
		Item* _array;
		int _size;
		int _ptr;
	public:
		//Copy the entire array but put them in random order.
		Iterator(Item* in_array, int in_size) : _array(new Item[in_size]), _size(in_size), _ptr(0){
			Item temp[in_size];
			memcpy(temp, in_array, sizeof(Item)*in_size);
			int count = in_size;
			while(count > 0){
				int rand_num = rand() % count; //0 ~ count-1
				_array[in_size-count] = temp[rand_num];
				temp[rand_num] = temp[--count];
			}
		}

		~Iterator(){
			delete[] _array;
		}

		Iterator(const Iterator& iter) : _array(new Item[iter._size]), _size(iter._size), _ptr(iter._ptr){
			memcpy(_array, iter._array, sizeof(Item)*iter._size);
		}

		Iterator& operator=(const Iterator& iter){
			memcpy(_array, iter._array, sizeof(Item)*iter._size);
			_size = iter._size;
			_ptr = iter._ptr;
		}

		Item& operator*() const{
			return _array[_ptr];
		}

		Item& operator->() const{
			return _array[_ptr];
		}

		Iterator& operator++(){ //Pre increment
			_ptr++;
			return *this;
		}

		Iterator& operator++(int){ //Post increment
			Iterator temp(*this);
			_ptr++;
			return temp;
		}
	};

	Iterator iterator() const{
		return Iterator(_array, _ptr);
	}
};



#endif
