#ifndef _BASE_H
#define _BASE_H

#include <stdbool.h>
#include <stddef.h>
#include "cube.h"

//This file contains the definition of the Base Class.

#define BASE_WIDTH 10
#define BASE_HEIGHT 20

//Base is a class containing all the Cubes that are landed on it.
class Base{
private:
	Cube* cubes[BASE_WIDTH][BASE_HEIGHT];
public:
	Base();
	~Base();

	bool isOccupied(int x, int y) const;
	Cube* getCube(int x, int y) const;
	int clearFullLines();
	//Accept a new cube from a dropped block
	void acceptNewCube(Cube* cube);
};

#endif
