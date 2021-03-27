#include "Boat.h"

// constructor
Boat::Boat() : Object::Object() {
	this->visibility = true;
}

// consturctor with variable
Boat::Boat(int a, int b) : Object::Object(a, b) {
	this->visibility = true;
}

// change visible and invisible
void Boat::changeVisibility() {
	if (this->visibility == true) this->visibility = false;
	else this->visibility = true;
}

// get visibility
bool Boat::getVisibility() {
	return this->visibility;
}