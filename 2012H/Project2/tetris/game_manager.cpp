#include "game_manager.h"

GameManager::GameManager() : base(), score(0), level(0){
	srand (time(NULL));
}

int GameManager::getScore() const{
	return score;
}

int GameManager::getLevel() const{
	return level;
}

Base* GameManager::getBase() const{
	return &base;
}

void GameManager::genNextBlock(){
	currBlock = nextBlock;
	nextBlock = new Block((BlockType)rand()%NUMBER_OF_BLOCK_TYPES, BOARD_WIDTH/2, 3);
}

void GameManager::updateGame(){
	int cleared = base->clearFullLines();
}

//Respond to user input
bool GameManager::moveRight(){
	return currBlock->moveRight();
}

bool GameManager::moveLeft(){
	return currBlock->moveLeft();
}

bool GameManager::rotateClockwise(){
	return currBlock->rotateClockwise();
}

bool GameManager::rotateAntiClockwise(){
	return currBlock->rotateAntiClockwise();
}	

bool GameManager::dropBlock(){
	return currBlock->dropBlock();
}


GameManager* GameManager::getManager() const{
	static GameManager gameManager;
	return &gameManager;
}
