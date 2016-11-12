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
	QTime time;
	time.start();

	Brute brute(pts);

	brute.solve(&lines);
	for (vector<Line*>::iterator it=lines.begin(); it!=lines.end(); it++){
		cout << (*it)->toString() << endl;
	}

	cout << time.elapsed() << endl;
	QDialog* dialog = new QDialog();
	dialog->setWindowTitle("Time (ms): " + QString::number(time.elapsed()));
	dialog->setFixedSize(100, 100);
	dialog->show();

	this->repaint();
}

void Board::fast(){
	QTime time;
	time.start();

	Fast fast(pts);

	fast.solve(&lines);
	for (vector<Line*>::iterator it=lines.begin(); it!=lines.end(); it++){
		cout << (*it)->toString() << endl;
	}

	cout << time.elapsed() << endl;
	QDialog* dialog = new QDialog();
	dialog->setWindowTitle("Time (ms): " + QString::number(time.elapsed()));
	dialog->setFixedSize(100, 10);
	dialog->show();

	this->repaint();
}

