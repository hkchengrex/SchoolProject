#include <iostream>
#include <algorithm>

#include "point.h"

bool compareX(Point* p1, Point* p2){
	return (*p1 < *p2);
}

class Brute(){
private:
	Point** pts;
public:
	Brute(Point** p) : pts(p) {}
	~Brute() {}
}

int main(){

	int N;
	cin >> N;

	Point** pts = new Point*[N];
	for (int i=0; i<N; i++){
		int x, y;
		cin >> x >> y;
		pts[i] = new Point(x, y);
	}

	sort(pts, pts+N, compareX);

	for (int i=0; i<N; i++){
		for (int j=i+1; j<N; j++){
			for (int k=j+1; k<N; k++){
				for (int l=k+1 ;l<N; l++){
					if (pts[i]->isCollinear(pts[j], pts[k], pts[l])){
						cout << "4: " << 
							pts[i]->toString() << " -> " << 
							pts[j]->toString() << " -> " << 
							pts[k]->toString() << " -> " << 
							pts[l]->toString() << endl;
					}
				}
			}
		}
	}

	return 0;
}