#include "main_window.h"

MainWindow::MainWindow(QWidget * parent, Qt::WindowFlags flags):
QMainWindow(parent, flags),
menubar(new QMenuBar(this)),
menu(new QMenu("&Method"))
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

	menu->addAction("&Brute");
	menu->addAction("&Fast");
	menubar->addAction(menu->menuAction());

	mainLayout->setMenuBar(menubar);
    setLayout(mainLayout);
}

