#include "board.h"
#include <iostream>

void Board::paintEvent(QPaintEvent * e) {
    QPainter p(this);
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(3);

    p.setPen(pen);

    PointPlotter pp(&p);

    for (vector<Point*>::iterator it=pts.begin(); it!=pts.end(); it++){
    	pp.draw(*it);
	}

	if (lines.size() > 0){
		pen.setWidth(2);
		for (vector<Line*>::iterator it=lines.begin(); it!=lines.end(); it++){
			Point* prev = 0;
			for (vector<Point*>::iterator it2=(*it)->getBegin(); it2!=(*it)->getEnd(); it2++){
				if (prev != 0){
					pp.drawTo(prev, *it2);
				}
				prev = *it2;
			}
		}
	}
}

void Board::brute(){
	Brute brute(pts);

	brute.solve(&lines);
	for (vector<Line*>::iterator it=lines.begin(); it!=lines.end(); it++){
		cout << (*it)->toString() << endl;
	}

	this->update();
}

void Board::fast(){
	Fast fast(pts);

	fast.solve(&lines);
	for (vector<Line*>::iterator it=lines.begin(); it!=lines.end(); it++){
		cout << (*it)->toString() << endl;
	}

	this->update();
}

