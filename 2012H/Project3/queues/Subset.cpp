#include <iostream>
#include <time.h>
#include <string>
#include "randomized_queue.h"

using namespace std;

int main (int argc, char ** argv){

	srand(time(0));
	int subset = atoi(argv[1]);
	RandomizedQueue<string*> rq;

	while ((cin.peek()!='\n')){
		string* s = new string();
		cin >> *s;
		rq.enqueue(s);
	}

	for (int i=0; i<subset; i++){
		string* s = rq.dequeue();
		cout << *s << endl;
	}

	return 0;
}