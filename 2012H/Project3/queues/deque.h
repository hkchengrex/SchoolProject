#ifndef DEQUE_H
#define DEQUE_H

#include <cstdlib>
#include <stdexcept>

template <class Item>
class Deque{
private:
	int _size;

	//Double linked node
	class Node{
	public:
		Node() : prev(this), next(this){};
		Node(Item _item, Node* _prev, Node* _next) : item(_item), prev(_prev), next(_next){};
		Item item;
		Node* prev;
		Node* next;
	};

	//The sentinel node's next points to head, prev points to tail
	Node* sentinel; 

public:
	Deque() : _size(0), sentinel(new Node()){};
	~Deque(){
		Node* curr = sentinel;
		do{
			Node* temp = curr->next;
			delete curr;
			curr = temp;
		}while(curr!=sentinel);
	}
	bool isEmpty() const {return _size==0;}
	int size() const {return _size;}

	//Add at the head position
	void addFirst(const Item& item){
		//Sentinel's next always points to head
		Node* node = new Node(item, sentinel, sentinel->next);
		node->prev->next = node;
		node->next->prev = node;
		_size++;
	}

	//Add at the tail position
	void addLast(const Item& item){
		//Sentinel's prev always points to tail
		Node* node = new Node(item, sentinel->prev, sentinel);
		node->prev->next = node;
		node->next->prev = node;
		_size++;
	}

	//Remove at the head position
	Item removeFirst(){
		if (_size <= 0){
			throw std::runtime_error("Underflow");
		}
		_size--;
		//Sentinel's next always points to head
		Node* temp = sentinel->next;
		sentinel->next = sentinel->next->next;
		sentinel->next->prev = sentinel;

		Item item = temp->item;
		delete temp;
		return item;
	}

	//Remove at the tail position
	Item removeLast(){
		if (_size <= 0){
			throw std::runtime_error("Underflow");
		}
		_size--;
		//Sentinel's prev always points to tail
		Node* temp = sentinel->prev;
		sentinel->prev = sentinel->prev->prev;
		sentinel->prev->next = sentinel;

		Item item = temp->item;
		delete temp;
		return item;
	}

	class Iterator{
	private:
		Node* curr;
	public:
		Iterator(Node* start) : curr(start){};
		Iterator(const Iterator& iter) : curr(iter.curr){};

		Iterator& operator=(const Iterator& iter){
			curr = iter.curr;
		}

		Item& operator*() const{
			return curr->item;
		}

		Item& operator->() const{
			return curr->item;
		}

		Iterator& operator++(){ //Pre increment
			curr = curr->next;
			return *this;
		}

		Iterator& operator++(int){ //Post increment
			Iterator temp(*this);
			curr = curr->next;
			return temp;
		}
	};

	//Start from head, not from sentinel
	Iterator iterator() const{
		return Iterator(sentinel->next);
	}
};



#endif
