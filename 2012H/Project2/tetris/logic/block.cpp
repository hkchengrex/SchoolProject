#include "block.h"
#include "game_manager.h"

//This file contains the implementation of the Block Class.

Block::Block(BlockType type, int inX, int inY) : x(inX), y(inY){
	CubeColor thisColor = BLOCK_INFO[type].color;

	//Create the center block
	cubes[0] = new Cube(thisColor, inX, inY);
	for (int i=0; i<CUBES_IN_EACH_BLOCK-1; i++){
		//Create other blocks with position shift
		cubes[i+1] = new Cube(thisColor, inX + BLOCK_INFO[type].cubes[i][0], inY + BLOCK_INFO[type].cubes[i][1]);
	}
}

Block::~Block(){
	//Delete all owned blocks
	for (int i=0; i<CUBES_IN_EACH_BLOCK; i++){
		delete cubes[i];
	}
}

bool Block::isPosValid(int x, int y){
	if (x < 0 || y > 0 || x >= BASE_WIDTH || y <= -BASE_HEIGHT){
		//Check if out of bounds
		return false;
	}else{
		//Check if occupied by the base
		return !GameManager::getManager()->getBase()->isOccupied(x, y);
	}
}

//1 for clockwise, -1 for anticlockwise
bool Block::applyRotation(int dir){
	//Calculate new position
	int oldShift[CUBES_IN_EACH_BLOCK][2]; //Original shift from center
	int newShift[CUBES_IN_EACH_BLOCK][2]; //New shift from the center
	int newPos[CUBES_IN_EACH_BLOCK][2]; //New position

	for (int i=0; i<CUBES_IN_EACH_BLOCK; i++){
		oldShift[i][0] = cubes[i]->getX() - x;
		oldShift[i][1] = cubes[i]->getY() - y;

		//Apply rotational matrix
		newShift[i][0] = oldShift[i][1]*dir;
		newShift[i][1] = -oldShift[i][0]*dir;

		newPos[i][0] = x + newShift[i][0];
		newPos[i][1] = y + newShift[i][1];
	}

	bool isValid = true;
	for (int i=0; i<CUBES_IN_EACH_BLOCK; i++){
		if (!isPosValid(newPos[i][0], newPos[i][1])){
			isValid = false;
		}
	}

	if (isValid){
		for (int i=0; i<CUBES_IN_EACH_BLOCK; i++){
			cubes[i]->setXY(newPos[i][0], newPos[i][1]);
		}
		return true;
	}else{
		return false;
	}
}

bool Block::rotateClockwise(){
	return applyRotation(1);
}

bool Block::rotateAntiClockwise(){
	return applyRotation(-1);
}

bool Block::applyTranslate(int shiftX, int shiftY){
	bool isValid = true;
	for (int i=0; i<CUBES_IN_EACH_BLOCK; i++){
		if (!isPosValid(cubes[i]->getX() + shiftX, cubes[i]->getY() + shiftY)){
			isValid = false;
		}
	}

	if (isValid){
		this->x += shiftX;
		this->y += shiftY;
		for (int i=0; i<CUBES_IN_EACH_BLOCK; i++){
			cubes[i]->setXY(cubes[i]->getX() + shiftX, cubes[i]->getY() + shiftY);
		}
		return true;
	}else{
		return false;
	}
}

bool Block::moveRight(){
	return applyTranslate(1, 0);
}

bool Block::moveLeft(){
	return applyTranslate(-1, 0);
}

bool Block::dropBlock(){
	return applyTranslate(0, -1);
}

//Transfer all the blocks to the base
void Block::mergeAndDelete(){
	Base* base = GameManager::getManager()->getBase();
	for (int i=0; i<CUBES_IN_EACH_BLOCK; i++){
		base->acceptNewCube(cubes[i]);
		cubes[i] = NULL;
	}
	delete this;
}

Cube* Block::getCube(int id) const{
	return cubes[id];
}