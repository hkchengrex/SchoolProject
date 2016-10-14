#include "base.h"

//This file contains the implementation of the Base Class.

Base::Base(){
	for (int i=0; i<BASE_WIDTH; i++){
		for (int k=0; k<BASE_HEIGHT; k++){
			cubes[i][k] = NULL;
		}
	}
}

Base::~Base(){
	for (int i=0; i<BASE_WIDTH; i++){
		for (int k=0; k<BASE_HEIGHT; k++){
			delete cubes[i][k]; //delete NULL pointer is OK
			cubes[i][k] = NULL; //Just in case
		}
	}
}

bool Base::isOccupied(int x, int y) const{
	//If not NULL, then there is something
	return (cubes[x][BASE_HEIGHT+y-1] != NULL);
}

Cube* Base::getCube(int x, int y) const{
	//Return a cube based on index
	return cubes[x][BASE_HEIGHT+y-1];
}

bool Base::checkIsLost() const{
	for (int i=BASE_HEIGHT-1; i>=BASE_HEIGHT-3; i--){
		for (int k=0; k<BASE_WIDTH; k++){
			if (cubes[k][i] != NULL){ //If there is sth
				return true;
			}
		}
	}
	return false;
}

int Base::clearFullLines(){
	int counter = 0;
	for (int i=BASE_HEIGHT-1; i>=0; i--){
		bool isFilled = true;
		//Check if entire column is filled
		for (int k=0; k<BASE_WIDTH; k++){
			if (cubes[k][i] == NULL){
				isFilled = false;
				break;
			}
		}

		//If it is filled, delete the blocks, and drop the rows
		if (isFilled){
			counter++;
			for (int k=0; k<BASE_WIDTH; k++){
				if (cubes[k][i] != NULL){
					delete cubes[k][i];
					cubes[k][i] = NULL;
				}
			}
			//Transfer the blocks to one unit down
			for (int j=i; j<BASE_HEIGHT-1; j++){
				for (int k=0; k<BASE_WIDTH; k++){
					cubes[k][j] = cubes[k][j+1];
					if (cubes[k][j] != NULL){
						cubes[k][j]->setY(cubes[k][j]->getY()-1);
					}
				}
			}
			//Set top row all NULL
			for (int k=0; k<BASE_WIDTH; k++){
				cubes[k][BASE_HEIGHT-1] = NULL;
			}

		}
	}
	return counter;
}

void Base::acceptNewCube(Cube* cube){
	//Accept a new cube from the falling block
	cubes[cube->getX()][BASE_HEIGHT+cube->getY()-1] = cube;
}
