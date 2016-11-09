#ifndef _POINT_H
#define _POINT_H

#include <math.h>
#include <cmath>
#include <string>
#include <cstdio>
#include <iostream>

using namespace std;

#define PI 3.14159265
#define ACCEPTED_ERROR 0.0001

class Point{
private:
	int _x, _y;
public:
	Point(int x, int y) : _x(x), _y(y) {}
	Point (const Point& p) : _x(p._x), _y(p._y) {}
	~Point() {}

	int getX() {return _x;}
	int getY() {return _y;}

	bool operator<(const Point& p) const{
		return (_x == p._x) ? (_y < p._y) : (_x < p._x);
	}

	bool operator==(const Point& p) const{
		return (_x == p._x) && (_y == p._y);
	}

	bool operator>(const Point& p) const{
		return (!(*this>p)) && (!(*this<p));
	}

	double getAngleTo(const Point* p) const{
		//Handle itself special case
		if (p->_y == _y && p->_x == _x){
			return -361.0;
		}
		return atan2(p->_y - _y, p->_x - _x) * 180.0 /PI;
	}

	double getAngleFrom(const Point* p) const{
		return p->getAngleTo(this);
	}

	bool isCollinear(const Point* p1, const Point* p2, const Point* p3) const{
		return ((abs(getAngleTo(p1) - getAngleTo(p2)) < ACCEPTED_ERROR) && (abs(getAngleTo(p2) - getAngleTo(p3)) < ACCEPTED_ERROR));
	}

	string toString(){
		char buf[100];
		sprintf(buf, "(%d, %d)", _x, _y);
		string str = buf;
		return str;
	}
};

#endif
