#ifndef _GAME_BOARD_H
#define _GAME_BOARD_H

#include <QtGui>
#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QPainter>
#include <QPaintEvent>

#include "base.h"
#include "block.h"
#include "util.h"

#define BOARD_WIDTH BASE_WIDTH
#define BOARD_HEIGHT BASE_HEIGHT

//This class is for the UI of the game board
class GameBoard : public QLabel{
	Q_OBJECT

private:
	QPixmap pixmap;

public:
	GameBoard(QWidget * parent = 0, Qt::WindowFlags f = 0);

	//Update its UI
	void updateView();
};

#endif
