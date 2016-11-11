#include <iostream>
#include <algorithm>

#include "brute.h"

int main(){

	int N;
	cin >> N;

	vector<Point*> pts(N);
	for (int i=0; i<N; i++){
		int x, y;
		cin >> x >> y;
		pts[i] = new Point(x, y);
	}

	Brute brute(pts);

	vector<Line*> lines;
	brute.solve(&lines);

	for (vector<Line*>::iterator it=lines.begin(); it!=lines.end(); it++){
		cout << (*it)->toString() << endl;
	}

	return 0;
}