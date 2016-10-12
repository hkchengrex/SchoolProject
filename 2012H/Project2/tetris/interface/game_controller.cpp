#include "game_controller.h"
#include "game_manager.h"
#include "game_board.h"
#include "game_window.h"
#include <stdio.h>

GameController::GameController(QWidget* parent)
:QWidget(parent), pressKey(0){

	tickTimer = new QTimer(this);
	keyTimer = new QTimer(this);

	connect(tickTimer, SIGNAL(timeout()), this, SLOT(ticksEvent()));
	connect(keyTimer, SIGNAL(timeout()), this, SLOT(keyHandler()));

	tickTimer->start(SPEED_CONSTANT/(6));
	keyTimer->start(KEY_SPEED);

	grabKeyboard();
}

GameController::~GameController(){
	
}

void GameController::ticksEvent(){
	GameManager::getManager()->updateGame();
	GameWindow::getWindow()->updateView();

	tickTimer->setInterval(SPEED_CONSTANT/(GameManager::getManager()->getLevel()+5));
}

void GameController::keyHandler(){
	if (pressKey == 0){
		return;
	}

	switch(pressKey){
		case Qt::Key_Up:
		break;

		case Qt::Key_Down:
			GameManager::getManager()->dropBlock();
		break;

		case Qt::Key_Left:
			GameManager::getManager()->moveLeft();
		break;

		case Qt::Key_Right:
			GameManager::getManager()->moveRight();
		break;

		case Qt::Key_Z:
			GameManager::getManager()->rotateAntiClockwise();
		break;

		case Qt::Key_X:
			GameManager::getManager()->rotateClockwise();
		break;
	}

	GameWindow::getWindow()->updateView();
	pressKey = 0;
}

void GameController::keyPressEvent(QKeyEvent *event){
	switch(event->key()){
		case Qt::Key_Up:
		case Qt::Key_Down:
		case Qt::Key_Left:
		case Qt::Key_Right:
		case Qt::Key_Z:
		case Qt::Key_X:

		pressKey = event->key();
	}
}
