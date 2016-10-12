#include "game_controller.h"
#include "game_manager.h"
#include "game_board.h"
#include "game_window.h"

GameController::GameController(QWidget* parent):QWidget(parent){
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(ticksEvent()));
	timer->start(DEFALUT_SPEED);
	grabKeyboard();
}

GameController::~GameController(){
	
}

void GameController::ticksEvent(){
	GameManager::getManager()->updateGame();
	GameWindow::getWindow()->updateView();

	timer->setInterval(5000/(GameManager::getManager()->getLevel()+5));
}

void GameController::keyPressEvent(QKeyEvent *event){
	switch(event->key()){
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
}
