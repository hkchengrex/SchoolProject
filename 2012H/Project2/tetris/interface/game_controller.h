#ifndef _GAME_CONTROLLER_H
#define _GAME_CONTROLLER_H

#include "base.h"
#include "block.h"

#include <QWidget>
#include <QTimer>
#include <QKeyEvent>

//This file handle user input and game clock.

#define DEFALUT_SPEED 1000

class GameController : public QWidget{
	Q_OBJECT

private:
	QTimer* timer;

public: 
	GameController(QWidget* parent = 0);
	~GameController();

	void keyPressEvent(QKeyEvent *event);

public slots:
	void ticksEvent();
};

#endif
