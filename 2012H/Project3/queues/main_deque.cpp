#include <iostream>
#include "deque.h"

using namespace std;

int main(int argc, char ** argv){
	srand(time(0));

	Deque<char> q;

	cout << "Empty: "<< q.isEmpty() << endl;
	cout << "Size:  " << q.size() << endl;
	q.addFirst('a');
	q.addFirst('b');
	q.addLast('c');
	q.addLast('d');
	q.addFirst('e');
	q.addFirst('f');
	q.addLast('g');
	q.addLast('h');
	cout << "Empty: " << q.isEmpty() << endl;
	cout << "Size:  " << q.size() << endl;

	int i;
	Deque<char>::Iterator itr = q.iterator();
	cout << "Deque content: " ;
	for(i = 0; i < q.size();i++){
		cout << *itr << " ";
		++itr;
	}
	cout << endl;

	cout << "Remove from first: " << q.removeFirst() << endl;
	itr = q.iterator();
	cout << "Deque content: ";
	for(i = 0; i < q.size();i++){
		cout << *itr << " ";
		++itr;
	}

	cout << endl;
	cout << "Remove from end: " << q.removeLast() << endl;
	itr = q.iterator();
	cout << "Deque content: ";
	for(i = 0; i < q.size();i++){
		cout << *itr << " ";
		++itr;
	}
	cout << endl;

	cout << "Remove from first: " << q.removeFirst() << endl;
	cout << "Remove from end: " << q.removeLast() << endl;
	cout << "Remove from first: " << q.removeFirst() << endl;
	cout << "Remove from end: " << q.removeLast() << endl;
	cout << "Remove from first: " << q.removeFirst() << endl;
	cout << "Remove from end: " << q.removeLast() << endl;

	cout << "Empty: " << q.isEmpty() << endl;

	try{
		cout << "Remove from first: " << q.removeFirst() << endl;
	}catch (const runtime_error e){
		cout << "Empty deque error." << endl;
	}

	return 0;
}