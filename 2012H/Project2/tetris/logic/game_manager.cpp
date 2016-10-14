#include "game_manager.h"
#include <stdio.h>

GameManager::GameManager() : base(new Base()), score(0), level(1), gameStarted(false){
	srand (time(NULL));
	//Immediate generate first and next block
	genNextBlock();
	genNextBlock();
}

GameManager::~GameManager(){
	delete currBlock;
	currBlock = NULL;
	delete nextBlock;
	nextBlock = NULL;
	delete base;
	base = NULL;
}

int GameManager::getScore() const{
	return score;
}

int GameManager::getLevel() const{
	return level;
}

Base* GameManager::getBase() const{
	return base;
}

bool GameManager::isStarted() const{
	return gameStarted;
}

void GameManager::genNextBlock(){
	//Generate a new block
	currBlock = nextBlock;
	nextBlock = new Block(static_cast<BlockType>(rand()%NUMBER_OF_BLOCK_TYPES), BOARD_WIDTH/2, -3);
}

void GameManager::updateGame(){
	dropBlock();
}

//Respond to user input
void GameManager::startGame(){
	if (gameStarted){
		return;
	}

	//Get ready for next game
	gameStarted = true;
	currBlock = NULL;
	nextBlock = NULL;
	delete nextBlock;
	delete currBlock;
	delete base;
	base = NULL;
	genNextBlock();
	genNextBlock();
	base = new Base();
	score = 0;
	level = 1;
}

//Transfer all these commands to the currBlock

bool GameManager::moveRight(){
	if (gameStarted && currBlock!=NULL){
		return currBlock->moveRight();
	}else{
		return false;
	}
}

bool GameManager::moveLeft(){
	if (gameStarted && currBlock!=NULL){
		return currBlock->moveLeft();
	}else{
		return false;
	}
}

bool GameManager::rotateClockwise(){
	if (gameStarted && currBlock!=NULL){
		return currBlock->rotateClockwise();
	}else{
		return false;
	}
}

bool GameManager::rotateAntiClockwise(){
	if (gameStarted && currBlock!=NULL){
		return currBlock->rotateAntiClockwise();
	}else{
		return false;
	}
}	

bool GameManager::dropBlock(){
	if (gameStarted && currBlock!=NULL){
		if (!currBlock->dropBlock()){
			//If dropping is not valid -> Ground touched
			currBlock->mergeAndDelete();
			currBlock = NULL;
			int isLost = base->checkIsLost();
			if (isLost){
				//If lost, no longer update game
				gameStarted = false;
			}else{
				//Create next block
				genNextBlock();
				int cleared = base->clearFullLines();
				score += cleared*cleared*10;
				level = score/100 + 1;
				//Cap the max. level
				if (level>=10){
					level = 10;
				}
			}
			return false;
		}else{
			return true;
		}
	}else{
		return false;
	}
}

Block* GameManager::getCurrBlock() const{
	return currBlock;
}

Block* GameManager::getNextBlock() const{
	return nextBlock;
}

//Static method return singleton
GameManager* GameManager::getManager(){
	static GameManager* gameManager = new GameManager;
	return gameManager;
}
