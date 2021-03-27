#include "BoatC.h"

// constructor
BoatC::BoatC() : Boat::Boat() {
	this->status = 0;
}

// constructor with variable
BoatC::BoatC(int a, int b) : Boat::Boat(a, b) {
	this->status = 0;
}

// move function of boatC
void BoatC::move() {
	if (this->status == 0) changeVisibility();
	else if (this->status == 1) changeVisibility();
	this->status = (this->status + 1) % 3;
}