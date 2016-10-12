#ifndef _GAME_WINDOW_H
#define _GAME_WINDOW_H

#include <QtGui>
#include <QWidget>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "game_window.h"
#include "game_board.h"
#include "game_controller.h"

class GameWindow : public QMainWindow{
	Q_OBJECT

private:
	GameBoard* gameBoard;
	GameController* gameController;
	
public:
	GameWindow(QWidget * parent = 0, Qt::WindowFlags flags = 0);
	~GameWindow();

	void updateView();
	static GameWindow* getWindow();
};

#endif
