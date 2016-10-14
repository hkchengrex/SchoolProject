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
	Cube* cubes[BASE_WIDTH][BASE_HEIGHT]; //Bottom-left as origin
public:
	Base();
	~Base();

	//Return true if there is sth in that grid, top-left as origin
	bool isOccupied(int x, int y) const;

	//Return A cube, top-left as origin
	Cube* getCube(int x, int y) const;

	//Return true if there is sth. on the top 2 rows
	bool checkIsLost() const;

	//Clear all the filled lines and drop the rows
	//Return: No. of rows cleared
	int clearFullLines();
	
	//Accept a new cube from a dropped block
	void acceptNewCube(Cube* cube);
};

#endif
