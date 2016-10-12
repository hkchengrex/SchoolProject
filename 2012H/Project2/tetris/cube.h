#ifndef _CUBE_H
#define _CUBE_H

//This file contains the definition of the Cube Class.

enum CubeColor{
	COLOR_RED,
	COLOR_GREEN,
	COLOR_BLUE,
	COLOR_YELLOW,
	COLOR_CYAN,
	COLOR_ORANGE,
	COLOR_PURPLE
};

//Cube represent one square unit in the game.
class Cube{
private:
	int x, y;
	const CubeColor mColor;
public:
	Cube(CubeColor inColor, int inX, int inY);

	int getX() const;
	int getY() const;
	CubeColor getColor() const;
	void setX(int newX);
	void setY(int newY);
	void setXY(int newX, int newY);
	void dropY();
};

#endif
