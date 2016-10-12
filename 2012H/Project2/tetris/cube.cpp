#include "cube.h"

//This file contains the implementation of the Cube Class.

Cube::Cube(CubeColor inColor, int inX, int inY) : mColor(inColor), x(inX), y(inY){

}

int Cube::getX() const{
	return x;
}

int Cube::getY() const{
	return y;
}

CubeColor Cube::getColor() const{
	return mColor;
}

void Cube::setX(int newX){
	x = newX;
}

void Cube::setY(int newY){
	y = newY;
}

void Cube::setXY(int newX, int newY){
	setX(newX);
	setY(newY);
}

void Cube::dropY(){
	setY(getY()-1);
}
