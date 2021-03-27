#include "Object.h"

// constructor
Object::Object() {
	this->axisX = 0;
	this->axisY = 0;
}

// constructor with variable
Object::Object(int a, int b) {
	this->axisX = a;
	this->axisY = b;
}

// move up function
void Object::moveUp() {
	this->axisY++;
}

// move down function
void Object::moveDown() {
	this->axisY--;
}

// move left function
void Object::moveLeft() {
	this->axisX--;
}

// move right function
void Object::moveRight() {
	this->axisX++;
}

// get x axis
int Object::getX() {
	return this->axisX;
}

// get y axis
int Object::getY() {
	return this->axisY;
}