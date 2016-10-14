#include "game_window.h"
#include "game_manager.h"

GameWindow::GameWindow(QWidget * parent, Qt::WindowFlags flags)
: 	QMainWindow(parent, flags),
	gameBoard(new GameBoard()),
	previewWindow(new PreviewWindow()),
	levelLabel(new QLabel()),
	scoreLabel(new QLabel()),
	gameController(new GameController()){

	QWidget *dummy = new QWidget();
	QHBoxLayout *hBoxLayout = new QHBoxLayout();
	QVBoxLayout *leftVLayout = new QVBoxLayout();
	QVBoxLayout *rightVLayout = new QVBoxLayout();

	leftVLayout->addWidget(gameBoard);
	leftVLayout->addWidget(gameController);

	rightVLayout->addWidget(previewWindow);
	rightVLayout->addWidget(levelLabel);
	rightVLayout->addWidget(scoreLabel);

	hBoxLayout->addLayout(leftVLayout);
	hBoxLayout->addLayout(rightVLayout);

	dummy->setLayout(hBoxLayout);

	setCentralWidget(dummy);
}

GameWindow::~GameWindow(){
	delete gameBoard;
	delete previewWindow;
	delete scoreLabel;
	delete levelLabel;
	delete gameController;
}

void GameWindow::updateView(){
	gameBoard->updateView();
	previewWindow->updateView();

	GameManager* manager = GameManager::getManager();
	int level = manager->getLevel();
	int score = manager->getScore();
	QString levelString = QString("Level: %1").arg(level, 3);
	QString scoreString = QString("Score: %1").arg(score, 3);

	levelLabel->setText(levelString);
	scoreLabel->setText(scoreString);
}

GameWindow* GameWindow::getWindow(){
	static GameWindow gameWindow;
	return &gameWindow;
}
