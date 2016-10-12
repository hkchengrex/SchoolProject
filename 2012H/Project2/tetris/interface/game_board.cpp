#include "game_board.h"
#include "game_manager.h"
#include "game_controller.h"

GameBoard::GameBoard(QWidget * parent, Qt::WindowFlags f)
 : QLabel(parent, f), pixmap(){

 	QImage image;
 	image.load("res/background.png");

 	pixmap = QPixmap::fromImage(image);
 	this->setPixmap(pixmap);
}

GameBoard::~GameBoard(){
	
}

void GameBoard::updateView(){
	QPixmap newPixmap(pixmap);
	QPainter painter(&newPixmap);

	for (int i=0; i<CUBES_IN_EACH_BLOCK; i++){
		Cube* drawingCube = GameManager::getManager()->getCurrBlock()->getCube(i);
		QColor color;

		switch(drawingCube->getColor()){
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

		painter.fillRect(drawingCube->getX()*20-1, drawingCube->getY()*-20+1, 19, 19, color);
	}

	this->setPixmap(newPixmap);
	//this->show();
}
