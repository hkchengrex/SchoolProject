#ifndef _GAME_WINDOW_H
#define _GAME_WINDOW_H

#include <QtGui>
#include <QWidget>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

#include "game_window.h"
#include "game_board.h"
#include "preview_window.h"
#include "game_controller.h"

//This class is the main window for all display items
class GameWindow : public QMainWindow{
	Q_OBJECT

private:
	GameBoard* gameBoard;
	PreviewWindow* previewWindow;
	QLabel* levelLabel, * scoreLabel;
	GameController* gameController;
	
public:
	GameWindow(QWidget * parent = 0, Qt::WindowFlags flags = 0);
	~GameWindow();

	//Update all the display
	void updateView();
	//Return singleton
	static GameWindow* getWindow();
};

#endif
