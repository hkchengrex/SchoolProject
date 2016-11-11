#ifndef _BOARD_H
#define _BOARD_H

#include <QtGui>
#include <QWidget>
#include <QMainWindow>
#include <QVBoxLayout>
#include <vector>
#include "point.h"
#include "point_plotter.h"
#include "brute.h"
#include "fast.h"

//This class is the main window for all display items
class Board : public QLabel{
	Q_OBJECT

private:
	vector<Point*> pts;
	vector<Line*> lines;

public:
	Board(vector<Point*> points, QWidget * parent = 0, Qt::WindowFlags f = 0) : QLabel(parent, f), pts(points){}
	void paintEvent(QPaintEvent * e);

protected slots:
	void brute();
	void fast();
};


#endif
