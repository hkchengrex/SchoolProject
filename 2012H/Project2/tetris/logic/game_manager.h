#ifndef _GAME_MANAGER_H
#define _GAME_MANAGER_H

#include <stdlib.h>
#include <time.h>
#include "base.h"
#include "block.h"

//This is a class containing game-related information
class GameManager{
private:
	int score, level;
	Block* currBlock, nextBlock;
	const Base base;
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

	//A unique game manager, can be accessed anywhere
	static GameManager* getManager() const;
}

#endif
