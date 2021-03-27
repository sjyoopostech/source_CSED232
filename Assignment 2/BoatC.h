#pragma once

#include "Boat.h"

// inherited from boat, object
class BoatC : public Boat {
private :
	int status; // shows where boat have to go

public :
	// constructors
	BoatC();
	BoatC(int a, int b);

	// move functions
	void move();
};