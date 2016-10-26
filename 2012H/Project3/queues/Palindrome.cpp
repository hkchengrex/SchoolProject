#include <iostream>
#include <time.h>
#include <string>
#include "deque.h"

using namespace std;

int main (int argc, char ** argv){

	Deque<char> front_q, back_q;
	char in_char;
	while(cin.get(in_char)){
		if (in_char == '\0' || in_char == '\n') break;
		front_q.addFirst(in_char);
		back_q.addLast(in_char);
	}

	int size = front_q.size();
	bool good = true;
	for (int i=0; i<size; i++){
		char a = front_q.removeFirst();
		char b = back_q.removeFirst();

		switch (a){
			case 'A':
				a = 'T';
				break;
			case 'C':
				a = 'G';
				break;
			case 'G':
				a = 'C';
				break;
			case 'T':
				a = 'A';
				break;
			default:
				good = false;
		}

		if (a!=b){
			good = false;
		}
	}

	cout << (good?"true":"false") << endl;

	return 0;
}