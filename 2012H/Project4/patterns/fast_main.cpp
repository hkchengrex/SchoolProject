#include <iostream>
#include <algorithm>
#include <list>

#include "point.h"

using namespace std;

class PointHelper{
public:
	Point* p;
	int index;
	double angle;
	PointHelper(Point* in_p, int i) : p(in_p), index(i), angle(0.0) {};
};

class compareAngle{
private:
	Point* origin;
public:
	compareAngle(Point* p) : origin(p) {};
	bool operator()(PointHelper* p1, PointHelper* p2){
		p1->angle = origin->getAngleTo(p1->p);
		p2->angle = origin->getAngleTo(p2->p);
		return (p1->angle) < (p2->angle);
	}
};

bool compareX(Point* p1, Point* p2){
	return (p1->getX() < p2->getX());
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

	bool* checked = new bool[N*N];
	for (int i=0; i<N*N; i++){
		checked[i] = false;
	}

	PointHelper** temp = new PointHelper*[N];
	for (int i=0; i<N; i++){
		temp[i] = new PointHelper(pts[i], i);
	}

	//i is the origin point
	for (int i=0; i<N; i++){
		//Note that the first item is the origin itself
		sort(temp, temp+N, compareAngle(pts[i]));

		int count = 0;
		list<int> items;
		//Thus skip the first item
		if (!checked[i*N + temp[1]->index]){
			count++;
			items.push_back(temp[1]->index);
		}

		//Use k=N and short-circuit to handle the last-point special case
		for (int k=2; k<=N; k++){
			if (k==N || !checked[i*N + temp[k]->index]){
				if (k!= N && abs(temp[k]->angle - temp[k-1]->angle) < ACCEPTED_ERROR){
					//cout << i << " " << temp[k-1]->index << " " << temp[k]->index << " " << count << endl;
					items.push_back(temp[k]->index);
					count ++;
				}else{
					if (count >= 3){
						cout << count+1 << ": ";
						cout << pts[i]->toString();
						for (list<int>::iterator it=items.begin(); it!=items.end(); it++){
							for (list<int>::iterator it2=items.begin(); it2!=items.end(); it2++){
								checked[(*it)*N + (*it2)] = true;
							}

							cout << " -> " << pts[*it]->toString();

						}
						cout << endl;
					}
					items.clear();
					count = 1;
					if (k != N){
						items.push_back(temp[k]->index);
					}
				}
			}
		}

		for (int k=0; k<N; k++){
			checked[i*N + k] = true;
			checked[k*N + i] = true;
		}
	}

	return 0;
}