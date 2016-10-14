#include "game_manager.h"

GameManager::GameManager() : base(new Base()), score(0), level(1), gameStarted(false){
	srand (time(NULL));
	genNextBlock();
	genNextBlock();
}

GameManager::~GameManager(){
	delete currBlock;
	delete nextBlock;
	delete base;
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
	currBlock = nextBlock;
	nextBlock = new Block(static_cast<BlockType>(rand()%NUMBER_OF_BLOCK_TYPES), BOARD_WIDTH/2, -3);
}

void GameManager::updateGame(){
	if (gameStarted){
		//If dropping is not valid -> Ground touched
		if (!dropBlock()){
			currBlock->mergeAndDelete();
			genNextBlock();
		}

		int cleared = base->clearFullLines();
		score += cleared*cleared*10;
		level = score/100 + 1;
		//Cap the max. level
		if (level>=10){
			level = 10;
		}
	}

	int isLost = base->checkIsLost();
	if (isLost){
		gameStarted = false;
	}
}

//Respond to user input
void GameManager::startGame(){
	if (gameStarted){
		return;
	}

	gameStarted = true;
	delete currBlock;
	delete nextBlock;
	delete base;
	genNextBlock();
	genNextBlock();
	base = new Base();
	score = 0;
	level = 1;
}

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

Block* GameManager::getCurrBlock() const{
	return currBlock;
}

Block* GameManager::getNextBlock() const{
	return nextBlock;
}

GameManager* GameManager::getManager(){
	static GameManager gameManager;
	return &gameManager;
}
