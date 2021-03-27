#pragma once

class Object {
private :
	int axisX; // x axis
	int axisY; // y axis

protected :
	// move functions
	void moveUp();
	void moveDown();

public :
	// constructors
	Object();
	Object(int a, int b);

	// move functions
	void moveLeft();
	void moveRight();

	// get functions
	int getX();
	int getY();
};