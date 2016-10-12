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
	nextBlock = new Block(rand()%NUMBER_OF_BLOCK_TYPES, BOARD_WIDTH/2, 3);
}

GameManager* GameManager::getManager() const{
	static GameManager gameManager;
	return &gameManager;
}
