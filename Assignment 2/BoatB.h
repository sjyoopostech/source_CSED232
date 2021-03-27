#pragma once

#include "Boat.h"

// inherited from boat, object
class BoatB : public Boat {
private :
	int status; // shows where boat have to go

public :
	// constructors
	BoatB();
	BoatB(int a, int b);

	// move functions
	void move();
};