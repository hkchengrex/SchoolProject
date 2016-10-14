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

	Block* currBlock = GameManager::getManager()->getCurrBlock();
	for (int i=0; i<CUBES_IN_EACH_BLOCK; i++){
		Cube* drawingCube = currBlock->getCube(i);
		QColor color = resolveColor(drawingCube->getColor());

		painter.fillRect(drawingCube->getX()*20+1, drawingCube->getY()*-20+1, 19, 19, color);
	}

	Base* base = GameManager::getManager()->getBase();
	for (int i=0; i<BASE_WIDTH; i++){
		for (int k=0; k>-BASE_HEIGHT; k--){
			if (base->isOccupied(i, k)){
				Cube* drawingCube = base->getCube(i, k);
				QColor color = resolveColor(drawingCube->getColor());

				painter.fillRect(drawingCube->getX()*20+1, drawingCube->getY()*-20+1, 19, 19, color);
			}
		}
	}

	this->setPixmap(newPixmap);
	this->update();
}
