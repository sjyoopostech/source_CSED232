#pragma once

#include "Object.h"

// inherited from object
class Boat : public Object {
private :
	bool visibility; // visible or invisible

public :
	// constructors
	Boat();
	Boat(int a, int b);

	// functions for visibility
	void changeVisibility();
	bool getVisibility();
};