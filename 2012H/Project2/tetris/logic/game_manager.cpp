#include "game_manager.h"

GameManager::GameManager() : base(new Base()), score(0), level(1){
	srand (time(NULL));
	genNextBlock();
	genNextBlock();
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

void GameManager::genNextBlock(){
	currBlock = nextBlock;
	nextBlock = new Block(static_cast<BlockType>(rand()%NUMBER_OF_BLOCK_TYPES), BOARD_WIDTH/2, -3);
}

void GameManager::updateGame(){
	//If dropping is not valid -> Ground touched
	if (!dropBlock()){
		currBlock->mergeAndDelete();
		genNextBlock();
	}

	int cleared = base->clearFullLines();
	score += cleared*10;
	level = score/50;
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

Block* GameManager::getCurrBlock(){
	return currBlock;
}

Block* GameManager::getNextBlock(){
	return nextBlock;
}

GameManager* GameManager::getManager(){
	static GameManager gameManager;
	return &gameManager;
}
