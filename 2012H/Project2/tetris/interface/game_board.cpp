#include "game_board.h"
#include "game_manager.h"
#include "game_controller.h"
#include <stdio.h>

GameBoard::GameBoard(QWidget * parent, Qt::WindowFlags f)
 : QLabel(parent, f), pixmap(){

 	QImage image;
 	image.load("res/background.png");

 	pixmap = QPixmap::fromImage(image);
 	this->setPixmap(pixmap);
}

GameBoard::~GameBoard(){
	
}

QColor getColor(CubeColor in_color){
	QColor color;

	switch(in_color){
		case (COLOR_RED):
			color = QColor(255, 0, 0);
		break;
		case (COLOR_GREEN):
			color = QColor(0, 255, 0);
		break;
		case (COLOR_BLUE):
			color = QColor(0, 0, 255);
		break;
		case (COLOR_YELLOW):
			color = QColor(255, 255, 0);
		break;
		case (COLOR_CYAN):
			color = QColor(0, 255, 255);
		break;
		case (COLOR_ORANGE):
			color = QColor(255, 128, 0);
		break;
		case (COLOR_PURPLE):
			color = QColor(128, 0, 255);
		break;
		default:
			color = QColor(255, 255, 255);
		break;
	}
	return color;
}

void GameBoard::updateView(){
	QPixmap newPixmap(pixmap);
	QPainter painter(&newPixmap);

	Block* currBlock = GameManager::getManager()->getCurrBlock();
	for (int i=0; i<CUBES_IN_EACH_BLOCK; i++){
		Cube* drawingCube = currBlock->getCube(i);
		QColor color = getColor(drawingCube->getColor());

		painter.fillRect(drawingCube->getX()*20+1, drawingCube->getY()*-20+1, 19, 19, color);
	}

	Base* base = GameManager::getManager()->getBase();
	for (int i=0; i<BASE_WIDTH; i++){
		for (int k=0; k>-BASE_HEIGHT; k--){
			//printf("%d %d\n", i, k);
			if (base->isOccupied(i, k)){
				Cube* drawingCube = base->getCube(i, k);
				QColor color = getColor(drawingCube->getColor());

				painter.fillRect(drawingCube->getX()*20+1, drawingCube->getY()*-20+1, 19, 19, color);
			}
		}
	}

	this->setPixmap(newPixmap);
	//this->show();
}
