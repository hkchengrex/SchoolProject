#ifndef _BRUTE_H
#define _BRUTE_H

#include <iostream>
#include <algorithm>
#include <vector>

#include "point.h"

class Brute{
private:
	vector<Point*> pts;
public:
	Brute(vector<Point*> v) : pts(v) {}
	~Brute() {}

	void solve(vector<Line*>* lines){
		sort(&(pts.front()), &(pts.back())+1, Point::compareX);

		for (int i=0; i<pts.size(); i++){
			for (int j=i+1; j<pts.size(); j++){
				for (int k=j+1; k<pts.size(); k++){
					for (int l=k+1 ;l<pts.size(); l++){
						if (pts[i]->isCollinear(pts[j], pts[k], pts[l])){
							Line* line = new Line();
							line->addPoint(pts[i]);
							line->addPoint(pts[j]);
							line->addPoint(pts[k]);
							line->addPoint(pts[l]);
							line->order();

							lines->push_back(line);
						}
					}
				}
			}
		}
	}
};

#endif