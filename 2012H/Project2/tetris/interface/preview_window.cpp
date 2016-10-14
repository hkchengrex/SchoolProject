#include "preview_window.h"
#include "game_manager.h"

PreviewWindow::PreviewWindow(QWidget * parent, Qt::WindowFlags f)
 : QLabel(parent, f), pixmap(){

 	QImage image;
 	image.load("res/preview.jpg");

 	pixmap = QPixmap::fromImage(image);
 	this->setPixmap(pixmap);
}

PreviewWindow::~PreviewWindow(){
	
}

void PreviewWindow::updateView(){
	static Block* lastBlock;

	Block* nextBlock = GameManager::getManager()->getNextBlock();
	if (lastBlock == nextBlock){
		//If same block, save some gas
		return;
	}else{
		lastBlock = nextBlock;
	}

	QPixmap newPixmap(pixmap);
	QPainter painter(&newPixmap);
	for (int i=0; i<CUBES_IN_EACH_BLOCK; i++){
		Cube* drawingCube = nextBlock->getCube(i);
		QColor color = resolveColor(drawingCube->getColor());

		painter.fillRect((drawingCube->getX() - nextBlock->getX()+1)*20+1,
						 (nextBlock->getY() - drawingCube->getY()-1)*-20+1,
						  19, 19, color);
	}

	this->setPixmap(newPixmap);
	this->update();
}

