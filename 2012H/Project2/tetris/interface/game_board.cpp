#include "game_board.h"
#include "game_manager.h"
#include "game_controller.h"

GameBoard::GameBoard(QWidget * parent, Qt::WindowFlags f)
 : QLabel(parent, f), pixmap(){

 	//Setup the background image
 	QImage image;
 	image.load("res/background.png");

 	pixmap = QPixmap::fromImage(image);
 	this->setPixmap(pixmap);
}

void GameBoard::updateView(){
	QPixmap newPixmap(pixmap);
	QPainter painter(&newPixmap);

	//Draw the base cubes
	Base* base = GameManager::getManager()->getBase();
	if (base == NULL){
		return;
	}
	for (int i=0; i<BASE_WIDTH; i++){
		for (int k=0; k>-BASE_HEIGHT; k--){
			if (base->isOccupied(i, k)){
				Cube* drawingCube = base->getCube(i, k);
				QColor color = resolveColor(drawingCube->getColor());

				painter.fillRect(drawingCube->getX()*20+1, drawingCube->getY()*-20+1, 19, 19, color);
			}
		}
	}

	//Draw the falling block
	Block* currBlock = GameManager::getManager()->getCurrBlock();
	if (currBlock == NULL){
		return;
	}
	for (int i=0; i<CUBES_IN_EACH_BLOCK; i++){
		Cube* drawingCube = currBlock->getCube(i);
		QColor color = resolveColor(drawingCube->getColor());

		painter.fillRect(drawingCube->getX()*20+1, drawingCube->getY()*-20+1, 19, 19, color);
	}

	//Apply the drawing
	this->setPixmap(newPixmap);
	this->update();
}
