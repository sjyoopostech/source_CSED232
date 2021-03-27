#pragma once

#include "Object.h"

// inherited from object
class Torpedo : public Object {
private :
	int status; // determines direction of torpedo
public :
	// constructors
	Torpedo();
	Torpedo(int a, int b);

	// move functions
	void move();

	// change status
	void changestatus(int type);
};