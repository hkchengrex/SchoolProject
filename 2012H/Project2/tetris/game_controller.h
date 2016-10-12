#ifndef _GAME_CONTROLLER_H
#define _GAME_CONTROLLER_H

#include "base.h"
#include "block.h"

#include <QTimer>

//This file handle user input and game clock.

class GameController : public QWidget{
	Q_OBJECT

public: 
	GameController(QWidget* parent = 0);
	~GameController();
}

#endif
