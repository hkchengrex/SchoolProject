#ifndef _GAME_MANAGER_H
#define _GAME_MANAGER_H

#include <stdlib.h>
#include <stddef.h>
#include <time.h>

#include "base.h"
#include "block.h"
#include "game_board.h"

//This is a class containing game-related information
class GameManager{
private:
	Base* base;
	
	int score, level;
	Block* currBlock, *nextBlock;
	bool gameStarted;
	void endGame();

public:
	GameManager();
	~GameManager();
	int getScore() const;
	int getLevel() const;
	Base* getBase() const;
	bool isStarted() const;

	void genNextBlock();
	void updateGame();

	//Respond to user input
	void startGame();
	bool moveRight();
	bool moveLeft();
	bool rotateClockwise();
	bool rotateAntiClockwise();
	bool dropBlock();

	Block* getCurrBlock() const;
	Block* getNextBlock() const;

	//A unique game manager, can be accessed anywhere
	static GameManager* getManager();
};

#endif
