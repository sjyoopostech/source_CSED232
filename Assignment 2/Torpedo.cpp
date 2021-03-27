#include "Torpedo.h"

// constructor
Torpedo::Torpedo() : Object::Object() {
	this->status = 0;
}

// constructor with variable
Torpedo::Torpedo(int a, int b) : Object::Object(a, b) {
	this->status = 0;
}

// move function of torpedo
void Torpedo::move() {
	moveUp();
	if (this->status == 1) moveLeft();
	if (this->status == 2) moveRight();
}

// change direction of torpedo
void Torpedo::changestatus(int type) {
	this->status = type;
}