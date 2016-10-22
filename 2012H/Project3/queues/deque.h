#ifndef DEQUE_H
#define DEQUE_H

template <class Item>
class Dequq{
private:

public:
	Dequq();
	bool isEmpty();
	int size();
	void addFirst(Item item);
	void addLast(Item item);
	void removeFirst();
	void removeLast();

	class Iterator{
		
	}
	Iterator<Item> iterator();

};

#endif
