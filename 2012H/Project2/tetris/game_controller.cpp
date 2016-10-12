#include "game_controller.h"

GameController::GameController(QWidget* parent = 0){
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(ticksEvent()));
	timer->start(DEFALUT_SPEED);
	grabKeyboard();
}

GameController::ticksEvent(){
	GameManager.getManager()->dropBlock();
}

GameController::keyPressEvent(QKeyEvent *event){
	switch(event->key()){
		case Qt::Key_Up:
		break;

		case Qt::Key_Down:
			GameManager.getManager()->dropBlock();
		break;

		case Qt::Key_Left:
			GameManager.getManager()->moveLeft();
		break;

		case Qt::Key_Right:
			GameManager.getManager()->moveRight();
		break;

		case Qt::Key_Z:
			GameManager.getManager()->rotateAntiClockwise();
		break;

		case Qt::Key_X:
			GameManager.getManager()->rotateClockwise();
		break;
	}
}
