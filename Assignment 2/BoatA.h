#pragma once

#include "Boat.h"

// inherited from boat, object
class BoatA : public Boat {
private :
	int status; // shows where boat have to go

public :
	// constructors
	BoatA();
	BoatA(int a, int b);

	// move functions
	void move();
};