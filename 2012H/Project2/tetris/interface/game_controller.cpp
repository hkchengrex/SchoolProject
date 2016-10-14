#include "game_controller.h"
#include "game_manager.h"
#include "game_board.h"
#include "game_window.h"
#include <stdio.h>

GameController::GameController(QWidget* parent)
:QWidget(parent), tickTimer(new QTimer(this)){

	connect(tickTimer, SIGNAL(timeout()), this, SLOT(ticksEvent()));
	tickTimer->start(SPEED_CONSTANT);

	//Grab the keyboard attention
	grabKeyboard();
}

GameController::~GameController(){
	//delete tickTimer; //Handled by QT
	//tickTimer = NULL;
}

void GameController::ticksEvent(){
	//The main heartbeat of the game
	if (GameManager::getManager()->isStarted()){
		GameManager::getManager()->updateGame();
		GameWindow::getWindow()->updateView();
	}
	tickTimer->setInterval(SPEED_CONSTANT-(GameManager::getManager()->getLevel()-1)*100);
}

void GameController::keyPressEvent(QKeyEvent *event){
	//Read the keys and act
	switch(event->key()){
		case Qt::Key_Up:
			GameManager::getManager()->startGame();
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
	if (GameManager::getManager()->isStarted()){
		GameWindow::getWindow()->updateView();
	}
}
