#include <iostream>
#include <algorithm>

#include "fast.h"

int main(){

	int N;
	cin >> N;

	vector<Point*> pts(N);
	for (int i=0; i<N; i++){
		int x, y;
		cin >> x >> y;
		pts[i] = new Point(x, y);
	}

	Fast fast(pts);

	vector<Line*> lines;
	fast.solve(&lines);

	for (vector<Line*>::iterator it=lines.begin(); it!=lines.end(); it++){
		cout << (*it)->toString() << endl;
	}

	return 0;
}