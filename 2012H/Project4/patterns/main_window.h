#ifndef _MAIN_WINDOW_H
#define _MAIN_WINDOW_H

#include <QtGui>
#include <QWidget>
#include <QMainWindow>
#include <QVBoxLayout>

//This class is the main window for all display items
class MainWindow : public QMainWindow{
	Q_OBJECT

private:
	QMenuBar* menubar;
	QMenu* menu;
public:
	MainWindow(QWidget * parent = 0, Qt::WindowFlags flags = 0);

	//Update all the display
	void updateView();
};

#endif
