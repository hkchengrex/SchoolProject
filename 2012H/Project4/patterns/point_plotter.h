#ifndef _POINT_PLOTTER
#define _POINT_PLOTTER

#include <QtGui>
#include <QWidget>
#include "point.h"

#define WIN_WIDTH 500
#define WIN_HEIGHT 500

class PointPlotter{
private:
	QPainter* p;
public:
	PointPlotter(QPainter* painter) : p(painter) {};

	void draw (Point* pt){
		p->drawPoint(pt->getX()*WIN_WIDTH/32768, pt->getY()*WIN_HEIGHT/32768);
	}

	void drawTo (Point* a, Point* b){
		p->drawLine(a->getX()*WIN_WIDTH/32768, a->getY()*WIN_WIDTH/32768, b->getX()*WIN_WIDTH/32768, b->getY()*WIN_WIDTH/32768);
	}
};

#endif