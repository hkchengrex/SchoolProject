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

public:
	GameManager();
	int getScore() const;
	int getLevel() const;
	Base* getBase() const;

	void genNextBlock();
	void updateGame();

	//Respond to user input
	bool moveRight();
	bool moveLeft();
	bool rotateClockwise();
	bool rotateAntiClockwise();
	bool dropBlock();

	Block* getCurrBlock();
	Block* getNextBlock();

	//A unique game manager, can be accessed anywhere
	static GameManager* getManager();
};

#endif
