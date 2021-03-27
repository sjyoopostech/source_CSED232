#include "BoatB.h"

// constructor
BoatB::BoatB() : Boat::Boat() {
	this->status = 0;
}

// constructor with variable
BoatB::BoatB(int a, int b) : Boat::Boat(a, b) {
	this->status = 0;
}

// move function of boatB
void BoatB::move() {
	if (this->status == 0) moveRight();
	else if (this->status == 1) moveDown();
	else if (this->status == 2) moveLeft();
	else if (this->status == 3) moveUp();
	this->status = (this->status + 1) % 4;
}