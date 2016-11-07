#ifndef _POINT_H
#define _POINT_H

class Point{
private:
	int _x, _y;
public:
	Point(int x, int y) : _x(x), _y(y) {}
	Point (Point p) : _x(p._x), _y(p._y) {}

	int getX() {return _x};
	int getY() {return _y};

	bool isCollinear(Point p1, Point p2, Point p3) = 0;
};

#endif
