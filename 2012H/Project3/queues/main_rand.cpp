#include <iostream>
#include <time.h>
#include "randomized_queue.h"

using namespace std;

int main(int argc, char ** argv){

	srand(time(0));
	RandomizedQueue<char> rq;

	cout << "Empty: " << rq.isEmpty() << endl;
	cout << "Size:  " << rq.size() << endl;
	rq.enqueue('a');
	rq.enqueue('b');
	rq.enqueue('c');
	rq.enqueue('d');
	rq.enqueue('e');
	rq.enqueue('f');
	rq.enqueue('g');
	rq.enqueue('h');
	cout << "Empty: " << rq.isEmpty() << endl;
	cout << "Size:  " << rq.size() << endl;

	int i;
	RandomizedQueue<char>::Iterator itr = rq.iterator();
	cout << "Queue content: ";
	for(i = 0; i < rq.size();i++){
		cout << *itr << " ";
		++itr;
	}
	cout << endl;

	cout << "Sampling: " ;
	for(i = 0; i < rq.size()*2;i++){
		cout << rq.sample() << " ";
	}
	cout << endl;

	cout << "Dequeue:  " << rq.dequeue() << endl;
	cout << "Dequeue:  " << rq.dequeue() << endl;
	cout << "Dequeue:  " << rq.dequeue() << endl;
	cout << "Dequeue:  " << rq.dequeue() << endl;

	itr = rq.iterator();
	cout << "Queue content: ";
	for(i = 0; i < rq.size();i++){
		cout << *itr << " ";
		++itr;
	}
	cout << endl;

	cout << "Dequeue:  " << rq.dequeue() << endl;
	cout << "Dequeue:  " << rq.dequeue() << endl;
	cout << "Dequeue:  " << rq.dequeue() << endl;
	cout << "Dequeue:  " << rq.dequeue() << endl;

	cout << "Empty:  " << rq.isEmpty() << endl;

	try{
		cout << "Dequeue:  " << rq.dequeue() << endl;
	}catch (const runtime_error e){
		cout << "Empty queue error." << endl;
	}
	cout << endl;

	return 0;
}