#include "BoatA.h"

// constructor
BoatA::BoatA() : Boat::Boat() {
	this->status = 0;
}

// constructor with variable
BoatA::BoatA(int a, int b) : Boat::Boat(a, b) {
	this->status = 0;
}

// move function of boatA
void BoatA::move() {
	if (this->status == 0) moveRight();
	else if (this->status == 1) moveLeft();
	else if (this->status == 2) moveLeft();
	else if (this->status == 3) moveRight();
	this->status = (this->status + 1) % 4;
}