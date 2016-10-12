#include "game_window.h"

GameWindow::GameWindow(QWidget * parent, Qt::WindowFlags flags)
: 	QMainWindow(parent, flags),
	gameBoard(new GameBoard()),
	gameController(new GameController()){

	QWidget *dummy = new QWidget();
	QHBoxLayout *hBoxLayout = new QHBoxLayout();
	QVBoxLayout *leftVLayout = new QVBoxLayout();
	QVBoxLayout *rightVLayout = new QVBoxLayout();

	leftVLayout->addWidget(gameBoard);
	leftVLayout->addWidget(gameController);

	hBoxLayout->addLayout(leftVLayout);
	hBoxLayout->addLayout(rightVLayout);

	dummy->setLayout(hBoxLayout);

	setCentralWidget(dummy);
}

GameWindow::~GameWindow(){

}

void GameWindow::updateView(){
	gameBoard->updateView();
}

GameWindow* GameWindow::getWindow(){
	static GameWindow gameWindow;
	return &gameWindow;
}
