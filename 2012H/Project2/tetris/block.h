#ifndef _BLOCK_H
#define _BLOCK_H

#include "cube.h"
#include "base.h"
#include "game_manager.h"

//This file contains the definition of the Block Class.

#define NUMBER_OF_BLOCK_TYPES 7
#define CUBES_IN_EACH_BLOCK 4
//This contains the types of block, their names suggested what they look like
//they are also the official names
enum BlockType{
	BLOCK_TYPE_I = 0,
	BLOCK_TYPE_O = 1,
	BLOCK_TYPE_S = 2,
	BLOCK_TYPE_Z = 3,
	BLOCK_TYPE_L = 4,
	BLOCK_TYPE_J = 5,
	BLOCK_TYPE_T = 6
};

struct BlockInfo{
	CubeColor color;
	//Each block contains 3 cube excluding the center.
	//The following array indicate the x/y shift from the center of the 3 blocks.
	int cubes[CUBES_IN_EACH_BLOCK-1][2];
};

const BlockInfo[NUMBER_OF_BLOCK_TYPES] = {
	{COLOR_RED, {{0, 1}, {0, 2}, {0, -1}}}, 		//I type
	{COLOR_GREEN, {{-1, 0}, {0, -1}, {-1, -1}}} 	//O type
	{COLOR_BLUE, {{0, 1}, {-1, 0}, {1, -1}}} 		//S type
	{COLOR_YELLOW, {{0, -1}, {1, 0}, {1, 1}}} 		//Z type
	{COLOR_CYAN, {{0, 1}, {0, -1}, {1, -1}}} 		//L type
	{COLOR_ORANGE, {{0, 1}, {0, -1}, {-1, -1}}} 	//J type
	{COLOR_PURPLE, {{0, 1}, {-1, 0}, {1, 0}}} 		//T type
}

//Block is a class containing some Cube.
//Typically a falling game object, this class handles the rotation and falling.
class Block{
private:
	int x, y; //Position of the center block
	Cube* cubes[CUBES_IN_EACH_BLOCK];

	bool applyRotation(int dir);
public:
	Block(BlockType type, int x, int y);
	~Block();

	bool rotateClockwise();
	bool rotateAntiClockwise();
	bool dropBlock();
	static bool checkValid(int x, int y);
};

#endif
