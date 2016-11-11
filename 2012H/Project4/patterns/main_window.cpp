#include "main_window.h"
#include <QAction>

MainWindow::MainWindow(vector<Point*> v, QWidget * parent, Qt::WindowFlags flags):
QMainWindow(parent, flags),
menubar(new QMenuBar(this)),
menu(new QMenu("&Method")),
board(new Board(v))
{
	bruteAction = new QAction("&Brute", this);
	fastAction = new QAction("&Fast", this);

	connect(bruteAction, SIGNAL(triggered()), board, SLOT(brute()));
	connect(fastAction, SIGNAL(triggered()), board, SLOT(fast()));

	menu->addAction(bruteAction);
	menu->addAction(fastAction);
	menubar->addAction(menu->menuAction());

	this->setFixedSize(WIN_WIDTH, WIN_HEIGHT);
	this->setCentralWidget(board);
	this->setMenuBar(menubar);
}

